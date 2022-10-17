/*
 *  GNU GENERAL PUBLIC LICENSE
 *  Version 3, 29 June 2007
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *  
 */

#include "SegaController32U4.h"
#include "Gamepad.h"

// ATT: 20 chars max (including NULL at the end) according to Arduino source code.
// Additionally serial number is used to differentiate arduino projects to have different button maps!
const char *gp_serial = "S-NES-GEN-V2";

#define NES       0
#define SNES      1
#define GENESIS   2

#define BUTTONS   0
#define AXES      1

#define UP        0x01
#define DOWN      0x02
#define LEFT      0x04
#define RIGHT     0x08

#define NTT_BIT   0x00
#define NODATA    0x00

void sendLatch();
void sendClock();
void sendState();

// Controller DB9 pins (looking face-on to the end of the plug):
// 5 4 3 2 1
//  9 8 7 6
//
// Wire it all up according to the following table:
//
// Triple Controller    V1            V2        *** = V1 to V2 Change
// ------------------------------------------------------------------
// VCC                  VCC ()        VCC ()
// GND                  GND ()        GND ()
// Shared-LATCH         2   (PD1)     2   (PD1)
// Shared-CLOCK         3   (PD0)     3   (PD0)
// NES-Data1 (4)        A0  (PF7)     A0  (PF7)
// NES-DataD4 (5)       N/C           9   (PB5) ***
// NES-DataD3 (6)       N/C           8   (PB4) ***
// SNES-Data1 (4)       A1  (PF6)     A1  (PF6)
// SNES-DataD2 (5)      N/C           RX  (PD2) ***
// SNES-DataD3 (6)      N/C           TX  (PD3) ***
// DB9-1                5   (PC6)     5   (PC6)
// DB9-2                6   (PD7)     6   (PB2)
// DB9-3                A2  (PF5)     A2  (PF5)
// DB9-4                A3  (PF4)     A3  (PF4)
// DB9-5                VCC ()        16  (PB2) ***
// DB9-6                14  (PB3)     14  (PB3)
// DB9-7                7   (PE6)     7   (PE6)
// DB9-8                GND ()        GND ()
// DB9-9                15  (PB1)     15  (PB1)

/* Power Pad Number Guide
 * C/O: http://www.neshq.com/hardgen/powerpad.txt

+---------/          \-----------+
|                       SIDE B   |
|   __      __       __     __   |
|  /  \    /  \     /  \   /  \  |
| | 1  |  | 2  |   | 3  | | 4  | |
|  \__/    \__/     \__/   \__/  |
|   __      __       __     __   |
|  /  \    /  \     /  \   /  \  |
| | 5  |  | 6  |   | 7  | | 8  | |
|  \__/    \__/     \__/   \__/  |
|   __      __       __     __   |
|  /  \    /  \     /  \   /  \  |
| | 9  |  | 10 |   | 11 | | 12 | |
|  \__/    \__/     \__/   \__/  |
|                                |
+--------------------------------+

           __________
+---------/          \-----------+
|                       SIDE A   |
|           __       __          |
|          /  \     /  \         |
|         |B 3 |   |B 2 |        |
|          \__/     \__/         |
|   __      __       __     __   |
|  /  \    /  \     /  \   /  \  |
| |B 8 |  |R 7 |   |R 6 | |B 5 | |
|  \__/    \__/     \__/   \__/  |
|           __       __          |
|          /  \     /  \         |
|         |B 11|   |B 10|        |
|          \__/     \__/         |
|                                |
+--------------------------------+
*/

// Manage EEPROM by making sure everything has
// its own index.
enum EEPROMIndices { GENESIS_EEPROM };

// Set up USB HID gamepads
Gamepad_ Gamepad[3];
SegaController32U4 controller(GENESIS_EEPROM);

// Controllers
uint32_t  controllerData[2][2] = {{0,0},{0,0}};
uint32_t  axisIndicator[32] = {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t  currentState = 0;
bool      nttActive = false;

uint32_t  dataMaskNES[8] =        {0x02,   // A
                                   0x01,   // B
                                   0x40,   // Start 
                                   0x80,   // Select
                                   UP,     // D-Up
                                   DOWN,   // D-Down
                                   LEFT,   // D-Left
                                   RIGHT   // D-Right
                                   }; 

// Power Pad D4
uint32_t  dataMaskPowerPadD4[8] = {0x08,    // PowerPad #4
                                   0x04,    // PowerPad #3
                                   0x800,   // PowerPad #12
                                   0x80,    // PowerPad #8
                                   NODATA,  // No Data
                                   NODATA,  // No Data
                                   NODATA,  // No Data
                                   NODATA   // No Data
                                   }; 

// Power Pad D3
uint32_t  dataMaskPowerPadD3[8] = {0x02,   // PowerPad #2
                                   0x01,   // PowerPad #1
                                   0x10,   // PowerPad #5
                                   0x100,  // PowerPad #9
                                   0x20,   // PowerPad #6
                                   0x200,  // PowerPad #10
                                   0x400,  // PowerPad #11
                                   0x40    // PowerPad #7
                                   }; 

uint32_t  dataMaskSNES[32] =      {0x01,    // B
                                   0x04,    // Y
                                   0x40,    // Start   
                                   0x80,    // Select
                                   UP,      // D-Up
                                   DOWN,    // D-Down
                                   LEFT,    // D-Left
                                   RIGHT,   // D-Right
                                   0x02,    // A
                                   0x08,    // X
                                   0x10,    // L
                                   0x20,    // R
                                   NODATA,  // SNES Control Bit
                                   NTT_BIT, // NTT Indicator Bit
                                   NODATA,  // SNES Control Bit
                                   NODATA,  // SNES Control Bit
                                   0x100,   // NTT 0
                                   0x200,   // NTT 1
                                   0x400,   // NTT 2
                                   0x800,   // NTT 3
                                   0x1000,  // NTT 4
                                   0x2000,  // NTT 5
                                   0x4000,  // NTT 6
                                   0x8000,  // NTT 7
                                   0x10000, // NTT 8
                                   0x20000, // NTT 9
                                   0x40000, // NTT *
                                   0x80000, // NTT #
                                   0x100000,// NTT .
                                   0x200000,// NTT C
                                   NODATA,  // NTT No Data
                                   0x800000,// NTT End Comms
                                   };

void setup()
{
  // Setup NES / SNES latch and clock pins (2/3 or PD1/PD0)
  DDRD  |=  B00000011; // output
  PORTD &= ~B00000011; // low

  // Setup NES / SNES data pins (A0/A1 or PF6/PF7)
  DDRF  &= ~B11000000; // inputs
  PORTF |=  B11000000; // enable internal pull-ups

  // Setup NES PowerPad data pins (8/9 or PB4/PB5)
  DDRB  &= ~B00110000; // inputs
  PORTB |=  B00110000; // enable internal pull-ups

  // Setup power pin (DB9 Pin 5) as output high (PB2)
  DDRB  |= B00000100; // output
  PORTB |= B00000100; // high

  delay(250);
}

void loop() 
{ 
  while(true)
  {
    //8 cycles needed to capture 6-button controllers
    for(uint8_t i = 0; i < 8; i++)
    {
      currentState = controller.updateState();
    }

    currentState = controller.getFinalState();
    Gamepad[GENESIS]._GamepadReport.buttons = currentState >> 4;
    Gamepad[GENESIS]._GamepadReport.Y = ((currentState & SC_BTN_DOWN) >> SC_BIT_SH_DOWN) - ((currentState & SC_BTN_UP) >> SC_BIT_SH_UP);
    Gamepad[GENESIS]._GamepadReport.X = ((currentState & SC_BTN_RIGHT) >> SC_BIT_SH_RIGHT) - ((currentState & SC_BTN_LEFT) >> SC_BIT_SH_LEFT);

    for(uint8_t j = 0; j < 1; j++)
    {
      sendLatch();

      controllerData[NES][BUTTONS] = 0;
      controllerData[NES][AXES] = 0;
      
      controllerData[SNES][BUTTONS] = 0;
      controllerData[SNES][AXES] = 0;

      nttActive = false;
  
      for(uint8_t dataBitCounter = 0; dataBitCounter < 32; dataBitCounter++)
      {
        // If no NTT controller, end the loop early
        if(!nttActive && dataBitCounter > 13)
        {
          break;
        }

        //NES Power Pad Controller
        if((dataBitCounter < 8) && ((PINB & B00100000) == 0)) //Power Pad Pin D4 (bottom)
        { 
          controllerData[NES][BUTTONS] |= dataMaskPowerPadD4[dataBitCounter];
        }

        if((dataBitCounter < 8) && ((PINB & B00010000) == 0)) //Power Pad Pin D3 (middle)
        { 
          controllerData[NES][BUTTONS] |= dataMaskPowerPadD3[dataBitCounter];
        }

        // NES Controller
        if((dataBitCounter < 8) && ((PINF & B10000000) == 0)) //If NES data line is low (indicating a press)
        { 
          if(axisIndicator[dataBitCounter])
          {
            controllerData[NES][AXES] |= dataMaskNES[dataBitCounter];
          }
          else
          {
            controllerData[NES][BUTTONS] |= dataMaskNES[dataBitCounter];
          }
        }

        // SNES / NTT Controller 
        if((PINF & B01000000) == 0) //If SNES data line is low (indicating a press)
        {
          if(dataBitCounter == 13)
          {
            nttActive = true;
          }
          
          if(axisIndicator[dataBitCounter])
          {
            controllerData[SNES][AXES] |= dataMaskSNES[dataBitCounter];
          }
          else
          {
            controllerData[SNES][BUTTONS] |= dataMaskSNES[dataBitCounter];
          }
        }
        
        sendClock();
      }
  
      Gamepad[NES]._GamepadReport.buttons = controllerData[NES][BUTTONS];
      Gamepad[NES]._GamepadReport.Y = ((controllerData[NES][AXES] & DOWN) >> 1) - (controllerData[NES][AXES] & UP);
      Gamepad[NES]._GamepadReport.X = ((controllerData[NES][AXES] & RIGHT) >> 3) - ((controllerData[NES][AXES] & LEFT) >> 2);

      Gamepad[SNES]._GamepadReport.buttons = controllerData[SNES][BUTTONS];
      Gamepad[SNES]._GamepadReport.Y = ((controllerData[SNES][AXES] & DOWN) >> 1) - (controllerData[SNES][AXES] & UP);
      Gamepad[SNES]._GamepadReport.X = ((controllerData[SNES][AXES] & RIGHT) >> 3) - ((controllerData[SNES][AXES] & LEFT) >> 2);
    }    

  sendState();
 }
}

void sendLatch()
{
  // Send a latch pulse to NES/SNES
  PORTD |=  B00000010; // Set HIGH
  __builtin_avr_delay_cycles(192);
  PORTD &= ~B00000010; // Set LOW
  __builtin_avr_delay_cycles(72);
}

void sendClock()
{
  // Send a clock pulse to NES/SNES
  PORTD |=  B00000001; // Set HIGH
  __builtin_avr_delay_cycles(96);
  PORTD &= ~B00000001; // Set LOW
  __builtin_avr_delay_cycles(72);
}

void sendState()
{
  Gamepad[0].send();
  Gamepad[1].send();
  Gamepad[2].send();
  __builtin_avr_delay_cycles(16000);
}
