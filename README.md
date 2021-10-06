# Triple Controller to USB

Based on [DaemonBite Retro Controllers](https://github.com/MickGyver/DaemonBite-Retro-Controllers-USB) by combining the NES/SNES and Genesis projects together for a specific wiring layout to support 3 different controllers with a single Arduino Pro Micro.

* PCB - **Done**
* Software - **Done**
* 3D Case - _**In Work**_

## Wiring Diagram

![Triple Controller Wiring](https://user-images.githubusercontent.com/31223405/129961434-cc9ba3af-9f03-45be-8147-0c608614a966.png)

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

## Connectors
* **SNES:** [AliExpress](https://www.aliexpress.com/item/32838396935.html) *(Min 1)*
* **NES:** [AliExpress](https://www.aliexpress.com/item/4000396420735.html) *(Min 30)*
* **GENESIS:** [AliExpress](https://www.aliexpress.com/item/4000406448270.html) *(Min 100)*

## PCB + Assembled Examples
![unassembled](https://user-images.githubusercontent.com/31223405/134262489-26a5180b-2c78-4ba8-993b-f7132f75200f.jpg)
![built](https://user-images.githubusercontent.com/31223405/134262494-764370c2-681a-4ca3-b86f-3c8e0dfe66e6.jpg)



