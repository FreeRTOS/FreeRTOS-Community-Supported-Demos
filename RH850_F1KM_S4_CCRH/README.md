# RH850 F1KM-S4 FreeRTOS Community Supported Demo

## Introduction
This directory contains demo project for Renesas RH850 F1KM-S4 R7F701649

This example implements the standard test demos detailed in following link: [RTOS Third Party Demo](https://github.com/FreeRTOS/FreeRTOS/blob/main/FreeRTOS/Demo/ThirdParty/Template/README.md)

## IDE
- [E2Studio suport RH850 family](https://www.renesas.com/us/en/software-tool/e2studio-information-rh850-family)

## How to use
Open e2studio and import this project File->Open Projects from File System

In order to see log you can add your thread safe transmit function in here or use Dynamic printf feature supported by E2Studio.

```c
int printf (const char * format, ...)
{
    char    tx_buff[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(tx_buff, format, arg);
    va_end(arg);

    /* Put your transmit function here */

    return 0;
}

```

Select test case you want to run by changing definition `configSTART_<Test_Name>_TESTS` in `freertos\FreeRTOSConfig.h` macros to `0` or ` 1` as needed

