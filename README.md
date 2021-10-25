# Triple Controller to USB

Based on [DaemonBite Retro Controllers](https://github.com/MickGyver/DaemonBite-Retro-Controllers-USB) by combining the NES/SNES and Genesis projects together for a specific wiring layout to support 3 different controllers with a single Arduino Pro Micro.

PCB Kits + Assembled units available on [Tindie](https://www.tindie.com/products/timville/triple-controller-classic-gaming-usb-adapter/)

3D Case files were designed by [Dinierto Designs](https://www.etsy.com/shop/DiniertoDesigns) and are available on [Thingiverse](https://www.thingiverse.com/thing:5011783)

## Wiring Diagram

![Triple Controller Wiring](https://user-images.githubusercontent.com/31223405/129961434-cc9ba3af-9f03-45be-8147-0c608614a966.png)

## Tested Controllers

The following controllers have been personally tested and are supported with the Triple Controller. All listed devices also fit when using the 3D Case as well.

NES:
* OEM NES Controller
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
* 8BitDo SN30 2.4G Receiver
* 8BitDo SNES Retro Receiver

## Controller Button Mapping
```
HID      NES        SNES       GENESIS
---------------------------------------------
00       B          B          B
01       A          A          C
02       N/A        Y          A
03       N/A        X          Y
04       N/A        L          X
05       N/A        R          Z
06       SELECT     SELECT     MODE
07       START      START      START
08       N/A        N/A        HOME (8BitDo)
```

## MiSTer Home Menu Suggestion
* **NES:** SELECT + DOWN
* **SNES:** SELECT + DOWN
* **GENESIS:** MODE + DOWN

*Note: SELECT + DOWN = HOME on 8BitDo N30*

## Tested Parts
* **SNES:** [AliExpress](https://www.aliexpress.com/item/32838396935.html) *(Min 1)*
* **NES:** [AliExpress](https://www.aliexpress.com/item/4000396420735.html) *(Min 30)*
* **SEGA / GENESIS:** [AliExpress](https://www.aliexpress.com/item/4000406448270.html) *(Min 100)*
* **Micro USB Arduino (3-18v model):** [AliExpress](https://www.aliexpress.com/item/32888212119.html)
* **USB C Arduino (Type C model):** [AliExpress](https://www.aliexpress.com/item/32888212119.html)

## PCB + Assembled Examples
![unassembled](https://user-images.githubusercontent.com/31223405/134262489-26a5180b-2c78-4ba8-993b-f7132f75200f.jpg)
![built](https://user-images.githubusercontent.com/31223405/134262494-764370c2-681a-4ca3-b86f-3c8e0dfe66e6.jpg)
