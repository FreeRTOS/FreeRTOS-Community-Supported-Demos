# RH850 F1KH-D8 FreeRTOS Partner Supported Demo

## Introduction
This directory contains demo project for Renesas RH850 F1KH-D8 R7F701715

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

## Linker Script
Add below linker script to your linker section
```c
RESET,RESET_PE1,RESET_PEn,STARTUP_CODE/0,ex_entry_PE1/800,ex_entry_PE2,.const,.INIT_BSEC.const,.INIT_DSEC.const,.data,.text/00002000,.stack_pe2.bss/FE9D0000,.stack.bss,.data.R,.bss/FEFB8000,.mev_address.bss/FFFEEC04,RESET_PE2/0800000
```
![Linker section](../Image//Linker.png)

## Note
1. The configuration `configRUN_MULTIPLE_PRIORITIES` must be set to `0` to PASS the following test cases:
- `vStartGenericQueueTasks`
- `vStartQueuePeekTasks`
- `vStartEventGroupTasks`
- `vInterruptSemaphorePeriodicTest`
- `vTimerPeriodicISRTests`
2. The test cases `vPeriodicStreamBufferProcessing` and `portYIELD_FROM_ISR` are out of scope.
