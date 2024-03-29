# 3dapter - HID Firmware for MiSTer / PC

The default HID firmware will allow the 3dapter (Triple Controller) to appear a multiplayer input controller with each controller input acting as it's own separate player/input.

## Controller Button Mapping

To maintain proper button mapping on MiSTer, it's recommended to map the SNES controller on the MiSTer Main menu and the NES / Genesis controllers will align to their core defaults properly.

```
Button   NES        SNES       GENESIS (normal)    GENESIS (MiSTer)
-------------------------------------------------------------------
01       B          B          B                   A 
02       A          A          A                   B
03       N/A        Y          Y                   X
04       N/A        X          X                   Y
05       N/A        L          Z                   Z
06       N/A        R          C                   C
07       SELECT     SELECT     MODE                MODE
08       START      START      START               START
09       N/A        N/A        HOME (8BitDo)       (N/A but HOME will send MODE + DOWN)
```

## MiSTer Home Menu Suggestion
* **NES:** SELECT + DOWN
* **SNES:** SELECT + DOWN
* **GENESIS:** MODE + DOWN

*Note: SELECT + DOWN = HOME on 8BitDo N30*

## MiSTer mode on 8bitdo M30 controller

The 3dapter exposes three "players" on one USB device.  Unfortunately MiSTer does not support setting keymaps per "player", MiSTer mode works around this by making sure the positional mapping is the same between all controllers.

MiSTer mode can be toggled on and off with "HOME + Z" (you have to press HOME first, Z second). This setting is saved to EEPROM and preserved across power cycles. The default is "normal mode".

When the Genesis controller is in MiSTer mode:

- The HOME button sends "DOWN + MODE" (This is because no equivalent of the HOME button exists on the other controller ports)

- Buttons are swapped: A with B and X with Y. This is such that the position of the buttons is consistent between SNES and Genesis.

## Retroarch Port Binding

Some Retroarch users have reported issues regarding setting the correct “Device Index” setting, since the 3dapter reports a single “device” to RetroArch with 3 different controllers, each as their own “index”.

In Retroarch, go to Settings → Input → Port 1 Binds → Device Index and then choose #3 for DB9 and presumably #1 or #2 for NES and SNES. Save and it sticks for that game, core or content directory.

https://retropie.org.uk/forum/topic/26681/port-binds/
https://retropie.org.uk/docs/RetroArch-Configuration/#core-input-remapping

## Install Instructions

### 1. Select "Arduino AVR Boards - Arduino Leonardo" from Boards List

### 2. Download project to Arduino Pro Micro board

## Restoring Firmware After Alternative Firmware Downloads

If you previously used the Analogue Pocket or Nintendo Switch firmware versions, your Arduino Pro Micro will no longer report as a Serial device and will not appear in the "Port" list in the Arduino software. Using the default 3dapter firmware does not suffer from this issue.

To restore the default firmware for your Arduino Pro Micro, you will need to manually reset the Arduino Pro Micro by shorting the Reset + Ground pins together to trigger a reset. 

1. Open the default firmware project in the Arduino software.
2. Connect your Arduino Pro Micro to your computer.
3. Trigger the download from the Arduino software. The Arduino software will first compile the project before beginning the download.
4. Once the "compiling" step has finished, trigger a reset on the Arduino Pro Micro by briefly touching the Reset (RST) and Ground (GND) pins together. This should make the Arduino forcefully switch into bootloader mode and allow the download to complete. If the download fails initially due to not finding the COM port, repeat the download/reset process and it should work the second time.