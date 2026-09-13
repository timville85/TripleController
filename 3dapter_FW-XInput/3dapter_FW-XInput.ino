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

#include <XInput.h>
#include "SegaController32U4.h"
#include "NesSnesShiftReader.h"

#define NES       0
#define SNES      1
#define GENESIS   2

#define BUTTONS   0
#define AXES      1

// Bit values match the shared NesSnesShiftReader's DPAD_* constants.
#define UP        0x01
#define DOWN      0x02
#define LEFT      0x04
#define RIGHT     0x08

void sendState();

// Manage EEPROM by making sure everything has
// its own index.
enum EEPROMIndices { GENESIS_EEPROM };

// Set up USB HID gamepads
SegaController32U4 controller(GENESIS_EEPROM);
NesSnesShiftReader nesSnesReader;

// Controllers
uint32_t  controllerData[2][2] = {{0,0},{0,0}};
uint16_t  currentGenesisState = 0;

void setup()
{
  XInput.setAutoSend(false);

  nesSnesReader.init();

  // Setup power pin (DB9 Pin 5) as output high (PB2)
  DDRB  |= B00000100; // output
  PORTB |= B00000100; // high

  delay(250);
}

void loop()
{
    digitalWrite(10, HIGH);

    currentGenesisState = 0;

    //8 cycles needed to capture 6-button controllers
    for(uint8_t i = 0; i < 8; i++)
    {
      currentGenesisState = controller.updateState();
    }

    currentGenesisState = controller.getFinalState();

    nesSnesReader.read(controllerData[NES][BUTTONS], controllerData[NES][AXES],
                        controllerData[SNES][BUTTONS], controllerData[SNES][AXES]);

  sendState();
}

void sendState()
{
  // Reset all cached button presses to force a full update every cycle.
  XInput.releaseAll();

  // Use controller data from all 3 inputs to map to single XInput Controller (takes about 350us per controller cycle)
  XInput.setButton(BUTTON_A,      (controllerData[NES][BUTTONS] & 0x01) | (controllerData[SNES][BUTTONS] & 0x01) | (currentGenesisState & SC_BTN_B)     );
  XInput.setButton(BUTTON_B,      (controllerData[NES][BUTTONS] & 0x02) | (controllerData[SNES][BUTTONS] & 0x02) | (currentGenesisState & SC_BTN_C)     );
  XInput.setButton(BUTTON_BACK,   (controllerData[NES][BUTTONS] & 0x40) | (controllerData[SNES][BUTTONS] & 0x40) | (currentGenesisState & SC_BTN_MODE)  );
  XInput.setButton(BUTTON_START,  (controllerData[NES][BUTTONS] & 0x80) | (controllerData[SNES][BUTTONS] & 0x80) | (currentGenesisState & SC_BTN_START) );

  XInput.setDpad( (controllerData[NES][AXES] & UP)          |  (controllerData[SNES][AXES] & UP)          | ((currentGenesisState & SC_BTN_UP) >> SC_BIT_SH_UP),
                 ((controllerData[NES][AXES] & DOWN) >> 1)  | ((controllerData[SNES][AXES] & DOWN) >> 1)  | ((currentGenesisState & SC_BTN_DOWN) >> SC_BIT_SH_DOWN),
                 ((controllerData[NES][AXES] & LEFT) >> 2)  | ((controllerData[SNES][AXES] & LEFT) >> 2)  | ((currentGenesisState & SC_BTN_LEFT) >> SC_BIT_SH_LEFT),
                 ((controllerData[NES][AXES] & RIGHT) >> 3) | ((controllerData[SNES][AXES] & RIGHT) >> 3) | ((currentGenesisState & SC_BTN_RIGHT) >> SC_BIT_SH_RIGHT),
                true);

  XInput.setButton(BUTTON_X,   (controllerData[SNES][BUTTONS] & 0x04) | (currentGenesisState & SC_BTN_A) );
  XInput.setButton(BUTTON_Y,   (controllerData[SNES][BUTTONS] & 0x08) | (currentGenesisState & SC_BTN_Y) );
  XInput.setButton(BUTTON_LB,  (controllerData[SNES][BUTTONS] & 0x10) | (currentGenesisState & SC_BTN_X) );
  XInput.setButton(BUTTON_RB,  (controllerData[SNES][BUTTONS] & 0x20) | (currentGenesisState & SC_BTN_Z) );

  XInput.setButton(BUTTON_LOGO, (currentGenesisState & SC_BTN_HOME));

  // Takes about 1.4-1.5ms to send USB Packet on MiSTer (at 1000hz polling rate)
  // Takes about 3-4ms to send USB Packet on Analogue Pocket Dock (likely 250hz polling rate)
  XInput.send();
}
