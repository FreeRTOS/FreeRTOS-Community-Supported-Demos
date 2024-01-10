OVERVIEW

This project containes demo app for TM4C123GH6PM board by TI.

Demo :
1. blinky
2. Full

First, you should get the `arm-none-eabi-gcc` tool-chain. You may  have the `lm4flash` tool to flash kernel for TM4C123G on Linux/Unix OS.

Second, you should put this project at `FreeRTOS/FreeRTOS/Demo/ThirdPart/Community-Supported-Demos/` directory.

1. blinky Demo

Then, build and flash:

```
$ cd Blinky_Demo
$ make
$ lm4flash gcc/blinky.bin
```

2. Full Demo
```
$ cd Full_Demo
$ make
$ lm4flash gcc/full.bin
```

To see the console output for the test results, serial port should be configured as:
- baud rate : 115200
- data : 8-bits 
- parity : N 
- stopo bit: 1-bits
- flow control none

NOTE:
a. To avoid memory issues, the tests are grouped into 2 sections. Update TESTGROUP to select the desired group or alternatively run tests one by one by defining configSTART_<Test_Name>_TESTS macros to 0 or 1 as needed.

REFERENCES:
https://www.ti.com/product/TM4C123GH6PM
