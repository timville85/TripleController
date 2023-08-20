# 3dapter (formerly Triple Controller to USB)

This project combines the NES, SNES and Genesis DaemonBite Retro Controllers projects together with a custom PCB to support 3 different controllers with a single socketed Arduino Pro Micro. PCB (KiCad + Gerbers), 3D Cases, and muliple firmware versions (Arduino code) all available in this repository.

PCB Kits + Fully Assembled units (with firmware of your choice) available on [Tindie](https://www.tindie.com/products/timville/triple-controller-classic-gaming-usb-adapter/)

3 different firmware versions are available in this repo:
* Default: Optimized for MiSTer, PC, Raspberry Pi, etc. - reports as 3 separate controllers, supports multiplayer from a single unit.
* Analogue Pocket: Optimized for Pocket Dock - reports as a single wired XInput device.
* Nintendo Switch: Optimized for Nintendo Switch Online NES, SNES, and Genesis collections - reports as a single wired switch controller.

## Resources Used

* [DaemonBite Retro Controllers](https://github.com/MickGyver/DaemonBite-Retro-Controllers-USB)
* https://github.com/esden/pretty-kicad-libs
* https://github.com/ddribin/nes-port-breadboard
* https://github.com/Biacco42/ProMicroKiCad
* http://www.neshq.com/hardgen/powerpad.txt

## 3D Case Files

3D Case files were designed by [Dinierto Designs](https://www.etsy.com/shop/DiniertoDesigns) and are available on [Thingiverse](https://www.thingiverse.com/thing:5011783)

3D Case Size Reference:
* 33mm - Most Micro USB Pro Micro / Sparkfun USB-C Pro Micro boards
* 35-36mm - Most AliExpress USB-C Pro Micro boards
* 36-37mm - Some AliExpress USB-C Pro Micro boards (typically with empty hole next to USB-C port)

## Wiring Diagram

![TripleController-V2 1-Layout](https://user-images.githubusercontent.com/31223405/163745351-3b86d7f5-2a6d-496b-9ffa-7e4f6356e45c.PNG)

Current Draw Readings from DIO Pin 16 (used for 5v supply for DB9 port):
* Krikzz Joyzz:	38mA
* 8BitDo M30 2.4G: 29mA
* OEM SEGA 3-Button Wired: 3mA
* OEM SEGA 6-Button Wired: 3mA
* Retrobit 6-Button Wired: 2mA
(Arduino DIO Max Rated Current: 40mA)

## Tested Controllers

The following controllers have been personally tested and are supported with the Triple Controller. All listed devices also fit when using the 3D Case as well.

NES:
* OEM NES Controller
* OEM NES PowerPad (Default FW Only)
* 8BitDo N30 2.4G Receiver
* 8BitDo NES Retro Receiver

SEGA / Genesis:
* OEM SEGA Master System 2-Button Controller
* OEM Genesis 3-Button Controller
* OEM Genesis 6-Button Controller
* 8BitDo M30 2.4G Receiver
* 8BitDo Genesis Retro Receiver
* Krikzz Joyzz

SNES:
* OEM SNES Controller
* OEM SFC Controller
* OEM SNES NTT Controller (Default FW Only)
* 8BitDo SN30 2.4G Receiver
* 8BitDo SNES Retro Receiver

## Bill of Materials
* **3dapter / Triple Controller PCB**

* **1x SNES Socket (90 deg):** [AliExpress - Gamers Zone Store](https://www.aliexpress.com/item/32838396935.html) 

* **1x NES Socket:** [AliExpress - Gamers Zone Store](https://www.aliexpress.com/item/1005003699734963.html)

* **1x Genesis Socket:** [AliExpress - Gamers Zone Store](https://www.aliexpress.com/item/1005003699497865.html)

* **Micro USB Arduino Pro Micro (reinforced USB port):** [Amazon](https://www.amazon.com/gp/product/B01HCXMBOU/) *(Pack of 3)*

* **1x Arduino Pro Micro (USB-C):** [AliExpress](https://www.aliexpress.com/item/32888212119.html)

* **2x 1x12 Female Header:** [Digi-Key](https://www.digikey.com/en/products/detail/sullins-connector-solutions/PPTC121LFBN-RC/807231)

## PCB + Assembled Examples

![unassembled](https://user-images.githubusercontent.com/31223405/134262489-26a5180b-2c78-4ba8-993b-f7132f75200f.jpg)

![built](https://user-images.githubusercontent.com/31223405/134262494-764370c2-681a-4ca3-b86f-3c8e0dfe66e6.jpg)
