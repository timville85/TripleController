EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "NES Port Breadboard Adapter"
Date "2021-07-07"
Rev "1.0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 "MIT License"
Comment4 "Author: Dave Dribin"
$EndDescr
$Comp
L Mechanical:MountingHole H1
U 1 1 60E147EE
P 5300 4050
F 0 "H1" H 5400 4096 50  0000 L CNN
F 1 "MountingHole" H 5400 4005 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 5300 4050 50  0001 C CNN
F 3 "~" H 5300 4050 50  0001 C CNN
	1    5300 4050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 60E14FCE
P 5300 4300
F 0 "H2" H 5400 4346 50  0000 L CNN
F 1 "MountingHole" H 5400 4255 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 5300 4300 50  0001 C CNN
F 3 "~" H 5300 4300 50  0001 C CNN
	1    5300 4300
	1    0    0    -1  
$EndComp
Text Label 4800 3100 0    50   ~ 0
GND
Wire Wire Line
	5100 3600 5100 3500
Wire Wire Line
	5100 3500 4750 3500
Wire Wire Line
	5000 3700 5000 3600
Wire Wire Line
	4900 3800 4900 3700
Wire Wire Line
	4900 3700 4750 3700
Text Label 4800 3400 0    50   ~ 0
DATA
Text Label 4800 3300 0    50   ~ 0
LATCH
Text Label 4800 3200 0    50   ~ 0
CLK
Text Label 6050 3400 0    50   ~ 0
D4
Text Label 6050 3300 0    50   ~ 0
D3
Wire Wire Line
	6300 3300 6300 3700
Wire Wire Line
	6200 3400 6200 3600
Wire Wire Line
	5100 3400 4750 3400
Wire Wire Line
	5100 3300 4750 3300
Wire Wire Line
	5100 3200 4750 3200
Wire Wire Line
	5100 3100 4750 3100
Wire Wire Line
	6400 3200 6400 3800
Text Label 6050 3200 0    50   ~ 0
VDD
$Comp
L nes-port-breadboard:NES_Port_Male J1
U 1 1 60C605E6
P 5550 3250
F 0 "J1" H 5550 3700 50  0000 C CNN
F 1 "NES_Port_Male" H 5550 3600 50  0000 C CNN
F 2 "nes-port-breadboard:NES_Port_Male_Horizontal" H 5550 3250 50  0001 C CNN
F 3 "" H 5550 3250 50  0001 C CNN
	1    5550 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 3400 6200 3400
Wire Wire Line
	6000 3200 6400 3200
Wire Wire Line
	6300 3300 6000 3300
Wire Wire Line
	5100 3600 6200 3600
Wire Wire Line
	5000 3700 6300 3700
Wire Wire Line
	4900 3800 6400 3800
Wire Wire Line
	5000 3600 4750 3600
$Comp
L Connector_Generic:Conn_01x07 J2
U 1 1 60C61DBB
P 4550 3400
F 0 "J2" H 4468 3917 50  0000 C CNN
F 1 "Conn_01x07" H 4468 3826 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 4550 3400 50  0001 C CNN
F 3 "~" H 4550 3400 50  0001 C CNN
	1    4550 3400
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
