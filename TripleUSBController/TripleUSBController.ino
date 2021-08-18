/*  DaemonBite (S)NES Controllers to USB Adapter
 *  Author: Mikael Norrgård <mick@daemonbite.com>
 *
 *  Copyright (c) 2020 Mikael Norrgård <http://daemonbite.com>
 *  
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
const char *gp_serial = "NES-SNES-GENESIS";

#define GAMEPAD_COUNT      2
#define GAMEPAD_COUNT_MAX  2  
#define BUTTON_READ_DELAY 20 // Delay between button reads in µs
#define CYCLES_LATCH     128 // 128 12µs according to specs (8 seems to work fine) (1 cycle @ 16MHz takes 62.5ns so 62.5ns * 128 = 8000ns = 8µs)
#define CYCLES_CLOCK      64 // 6µs according to specs (4 seems to work fine)
#define CYCLES_PAUSE1     64 // 6µs according to specs (4 seems to work fine)
#define CYCLES_PAUSE2     58 // 6µs according to specs (4 seems to work fine)

#define BUTTONS  0
#define AXES     1
#define UP    0x01
#define DOWN  0x02
#define LEFT  0x04
#define RIGHT 0x08

#define DELAY_CYCLES(n) __builtin_avr_delay_cycles(n)

inline void sendLatch() __attribute__((always_inline));
inline void sendClock() __attribute__((always_inline));

// Controller DB9 pins (looking face-on to the end of the plug):
// 5 4 3 2 1
//  9 8 7 6
//
// Wire it all up according to the following table:
//
// NES           SNES        Arduino Pro Micro
// --------------------------------------
// VCC                        VCC (NES & SNES)
// GND                        GND (NES & SNES)
// OUT0 (LATCH)               2   (PD1, NES & SNES)
// CUP  (CLOCK)               3   (PD0, NES & SNES)
// D1   (GP1: DATA)           A0  (PF7, NES) 
// D1   (GP2: DATA)           A1  (PF6, SNES)
// DB9-1                      5   (PC6, GENESIS)
// DB9-2                      6   (PD7, GENESIS)
// DB9-3                      A2  (PF5, GENESIS)
// DB9-4                      A3  (PF4, GENESIS)
// DB9-5                      VCC (GENESIS)
// DB9-6                      14  (PB3, GENESIS)
// DB9-7                      7   (PE6, GENESIS)
// DB9-8                      GND (GENESIS)
// DB9-9                      15  (PB1, GENESIS)

enum ControllerType {
  NONE,
  NES,
  SNES
};

// Set up USB HID gamepads
Gamepad_ Gamepad[3];
SegaController32U4 controller;

// Controllers
uint8_t buttons[GAMEPAD_COUNT_MAX][2] = {{0,0},{0,0}};
uint8_t buttonsPrev[GAMEPAD_COUNT_MAX][2] = {{0,0},{0,0}};
uint8_t gpBit[GAMEPAD_COUNT_MAX] = {B10000000,B01000000};
ControllerType controllerType[GAMEPAD_COUNT_MAX] = {NES,SNES};
uint8_t btnByte[12] = {0,0,0,0,1,1,1,1,0,0,0,0};
uint8_t btnBits[12] = {0x01,0x04,0x40,0x80,UP,DOWN,LEFT,RIGHT,0x02,0x08,0x10,0x20};
uint8_t gp = 0;
uint8_t buttonCount = 12;

// Controller states
word currentState = 0;
word lastState = 1;

// Timing
uint32_t microsButtons = 0;

void setup()
{
  // Setup latch and clock pins (2,3 or PD1, PD0)
  DDRD  |=  B00000011; // output
  PORTD &= ~B00000011; // low

  // Setup data pins A0-A3 (PF7-PF4)
  DDRF  &= ~B11000000; // inputs
  PORTF |=  B11000000; // enable internal pull-ups
  
  delay(300);
}

void loop() { while(1)
{
  //8 cycles needed to capture 6-button controllers
  for(int i = 0; i < 8; i++)
  {
    currentState = controller.getStateMD();
    sendState();
  }
  
  if((micros() - microsButtons) > BUTTON_READ_DELAY)
  {    
    // Pulse latch
    sendLatch();

    buttons[0][BUTTONS] = 0;
    buttons[0][AXES] = 0;
    buttons[1][BUTTONS] = 0;
    buttons[1][AXES] = 0;

    for(uint8_t btn=0; btn<buttonCount; btn++)
    {
      for(gp=0; gp<GAMEPAD_COUNT; gp++) 
      {
        if((PINF & gpBit[gp])==0) buttons[gp][btnByte[btn]] |= btnBits[btn];
      }
      sendClock();
    }

    bitWrite(buttons[0][BUTTONS], 1, bitRead(buttons[0][BUTTONS], 0));
    bitWrite(buttons[0][BUTTONS], 0, bitRead(buttons[0][BUTTONS], 2));
    buttons[0][BUTTONS] &= 0xC3;

    // Has any buttons changed state?
    if (buttons[0][BUTTONS] != buttonsPrev[0][BUTTONS] || buttons[0][AXES] != buttonsPrev[0][AXES])
    {
      Gamepad[0]._GamepadReport.buttons = buttons[0][BUTTONS];
      Gamepad[0]._GamepadReport.Y = ((buttons[0][AXES] & DOWN) >> 1) - (buttons[0][AXES] & UP);
      Gamepad[0]._GamepadReport.X = ((buttons[0][AXES] & RIGHT) >> 3) - ((buttons[0][AXES] & LEFT) >> 2);
      buttonsPrev[0][BUTTONS] = buttons[0][BUTTONS];
      buttonsPrev[0][AXES] = buttons[0][AXES];
      Gamepad[0].send();
    }

    if (buttons[1][BUTTONS] != buttonsPrev[1][BUTTONS] || buttons[1][AXES] != buttonsPrev[1][AXES])
    {
      Gamepad[1]._GamepadReport.buttons = buttons[1][BUTTONS];
      Gamepad[1]._GamepadReport.Y = ((buttons[1][AXES] & DOWN) >> 1) - (buttons[1][AXES] & UP);
      Gamepad[1]._GamepadReport.X = ((buttons[1][AXES] & RIGHT) >> 3) - ((buttons[1][AXES] & LEFT) >> 2);
      buttonsPrev[1][BUTTONS] = buttons[1][BUTTONS];
      buttonsPrev[1][AXES] = buttons[1][AXES];
      Gamepad[1].send();
    }
    
    microsButtons = micros();
  }

}}

void sendLatch()
{
  // Send a latch pulse to (S)NES controller(s)
  PORTD |=  B00000010; // Set HIGH
  DELAY_CYCLES(CYCLES_LATCH); 
  PORTD &= ~B00000010; // Set LOW
  DELAY_CYCLES(CYCLES_PAUSE2);
}

void sendClock()
{
  // Send a clock pulse to (S)NES controller(s)
  PORTD |=  B00000001; // Set HIGH
  DELAY_CYCLES(CYCLES_CLOCK); 
  PORTD &= ~B00000001; // Set LOW
  DELAY_CYCLES(CYCLES_PAUSE1); 
}

void sendState()
{
  // Only report controller state if it has changed
  if (currentState != lastState)
  {
    Gamepad[2]._GamepadReport.buttons = currentState >> 4;
    Gamepad[2]._GamepadReport.Y = ((currentState & SC_BTN_DOWN) >> SC_BIT_SH_DOWN) - ((currentState & SC_BTN_UP) >> SC_BIT_SH_UP);
    Gamepad[2]._GamepadReport.X = ((currentState & SC_BTN_RIGHT) >> SC_BIT_SH_RIGHT) - ((currentState & SC_BTN_LEFT) >> SC_BIT_SH_LEFT);
    Gamepad[2].send();
    lastState = currentState;
  }
}
