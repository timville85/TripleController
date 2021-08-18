# Triple USB Controller

Based on [DaemonBite Retro Controllers](https://github.com/MickGyver/DaemonBite-Retro-Controllers-USB) by combining the NES/SNES and Genesis projects together for a specific wiring layout to support 3 different controllers with a single Arduino Pro Micro.

## Wiring Diagram

![Triple Controller Wiring](https://user-images.githubusercontent.com/31223405/129961434-cc9ba3af-9f03-45be-8147-0c608614a966.png)

## Controller Button Mapping
```
HID      NES        SNES       GENESIS
---------------------------------------------
00       B          B          A
01       A          A          B
02       N/A        Y          C
03       N/A        X          X
04       N/A        L          Y
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

## Board Example

![IMG_2943_JP](https://user-images.githubusercontent.com/31223405/129971271-703a2122-ab8e-4b4b-badb-ec7858de713b.jpg)
![IMG_2944_JP](https://user-images.githubusercontent.com/31223405/129971276-0a78e276-c9bc-4463-b730-26e553dfd439.jpg)


