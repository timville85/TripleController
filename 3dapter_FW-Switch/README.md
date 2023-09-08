# 3dapter - Nintendo Switch Firmware

This alternative firmware will allow the 3dapter (Triple Controller) to appear a single Switch-compatible controller. All 3 controller inputs will share the same singular player input (i.e. use only one controller at time). 

The controller inputs have been mapped to align to map to the Nintendo Switch Virtual NES, SNES, and Genesis apps. Switch-specific button combos have been added to support in-game menus, home buttons, and screenshot capabities.

## IMPORTANT NOTE
**Installing the XInput Library will remove the self-reset listener from the Arduino board. This means you will need to manually reset the Arduino when updating the code on the board or switching to a different firmware.**

**You can accomplish this by connecting the RST and GND pins together - a tip of a screwdriver works well since the pins are next to each other.**

<img src="https://github.com/timville85/TripleController/assets/31223405/b407d6e9-23bf-4204-840a-c814300fc317" width=30% height=30%>

## Switch Special Button Combos

NES:
* In-Game Menu ("-" Button): Select + D-Pad Down
* Home Button: Select + Start
* Screenshot: Select + Up

SNES:
* In-Game Menu ("-" Button): Select + D-Pad Down
* Home Button: Select + Start
* Screenshot: Select + Up

Genesis (6-Button):
* In-Game Menu ("-" Button): Mode + Down
* Home Button: Mode + Start (or 8BitDo M30 Heart Button)
* Screenshot: Mode + D-Pad Up

Genesis (3-Button):
* In-Game Menu ("-" Button): Start + A + B + C
* Home Button: Start + A + Down
* Screenshot: Start + A + Up

Input Toggle to swap D-Pad Input / Left Analog Joystick
* Hold Select/Mode + Down for 1.5 seconds
* Reports 8-Way Input (Cardinal + Diagonal)

Input Toggle to swap X / RB buttons
* Hold Mode + B for 1.5 Seconds
* Useful for games within the "Sega Genesis Classics" collection

## Resources Used

* [LUFA Arduino Board & Library](https://github.com/CrazyRedMachine/Arduino-Lufa)
* [Switch-Fightstick](https://github.com/progmem/Switch-Fightstick).

## Install Instructions

### 1. Add the following URL as an Additional Board Manager URL (in File -> Preferences menu)
`https://github.com/CrazyRedMachine/Arduino-Lufa/raw/master/package_arduino-lufa_index.json`

### 2. Select and Install **`LUFA AVR Boards`** from the Arduino Board Manager

### 3. Select **`Arduino LUFA AVR Boards -> Arduino Leonardo (LUFA)`** from Boards list

### 4. Download project to Arduino Pro Micro board

Remember after download your Arduino Pro Micro will no longer report as a Serial device and will not appear in the "Port" list in the Arduino software.

Note: If you are replacing existing code on the 3dapter, trigger the download from the Arduino software and then trigger a reset on the Arduino Pro Micro within a few seconds of starting the download. If the download fails initially due to not finding the COM port, repeat the download/reset process and it should work the second time.
