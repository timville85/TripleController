# Triple Controller to USB - XInput Edition

This alternative firmware will allow the Triple Controller to appear a single XInput controller that all 3 controller inputs share. The controller inputs have been mapped to align with the default mapping on the Analogue Pocket Dock (as of firmware 1.1 Beta 6)

Uses the XInput Arduino Library & Boards:
* https://github.com/dmadison/ArduinoXInput
* https://github.com/dmadison/ArduinoXInput_AVR

**PLEASE NOTE: Installing the XInput Library will remove the self-reset listener from the Arduino board. This means you will need to manually reset the Arduino when updating the code on the board. You can accomplish this by connecting the RST and GND pins together - a tip of a screwdriver works well since the pins are next to each other.**

## Install Instructions

### 1. Install XInput Library from Arduino Library Manager:

![Library Installer](https://user-images.githubusercontent.com/31223405/210913898-79e7c503-dfee-435b-9685-0df4602176fe.png)

### 2. Add the following line to the "Additional Boards Manager URLs" list:

`https://raw.githubusercontent.com/dmadison/ArduinoXInput_Boards/master/package_dmadison_xinput_index.json`

### 3. Install XInput Boards from Arduino Boards Manager:

![Board Installer](https://user-images.githubusercontent.com/31223405/210913897-90a02f39-623b-473a-b531-b47f3c0cb15b.png)

### 4. Select Arduino Leonardo w/ XInput from Boards List:

![Board Selection](https://user-images.githubusercontent.com/31223405/210913895-d7c319d9-86e8-4e33-947e-3fe8e6cf977c.png)

### 5. Download project to Arduino board!
