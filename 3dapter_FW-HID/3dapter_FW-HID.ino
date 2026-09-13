
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
#include "NesSnesShiftReader.h"
#include "Gamepad.h"

// ATT: 20 chars max (including NULL at the end) according to Arduino source code.
// Additionally serial number is used to differentiate arduino projects to have different button maps!
const char *gp_serial = "3DAPTER";

#define NES       0
#define SNES      1
#define GENESIS   2

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

// Manage EEPROM by making sure everything has
// its own index.
enum EEPROMIndices { GENESIS_EEPROM };

// Set up USB HID gamepads
Gamepad_ Gamepad[3];
SegaController32U4 controller(GENESIS_EEPROM);
NesSnesShiftReader nesSnesReader;

uint16_t currentState = 0;

void setup()
{
  nesSnesReader.init();

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

    uint32_t nesButtons, nesAxes, snesButtons, snesAxes;
    nesSnesReader.read(nesButtons, nesAxes, snesButtons, snesAxes);

    Gamepad[NES]._GamepadReport.buttons = nesButtons;
    Gamepad[NES]._GamepadReport.Y = ((nesAxes & DPAD_DOWN) >> 1) - (nesAxes & DPAD_UP);
    Gamepad[NES]._GamepadReport.X = ((nesAxes & DPAD_RIGHT) >> 3) - ((nesAxes & DPAD_LEFT) >> 2);

    Gamepad[SNES]._GamepadReport.buttons = snesButtons;
    Gamepad[SNES]._GamepadReport.Y = ((snesAxes & DPAD_DOWN) >> 1) - (snesAxes & DPAD_UP);
    Gamepad[SNES]._GamepadReport.X = ((snesAxes & DPAD_RIGHT) >> 3) - ((snesAxes & DPAD_LEFT) >> 2);

    sendState();
  }
}

void sendState()
{
  Gamepad[0].send();
  Gamepad[1].send();
  Gamepad[2].send();
  __builtin_avr_delay_cycles(16000);
}
