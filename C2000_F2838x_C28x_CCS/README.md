
OVERVIEW

This directory contains demo projects for TMS320F2838xD (C2000 compiler 20.2.1.LTS) for the TMDSCNCD28388D controlcard board.

LIST OF EXAMPLES:
1. freertos_ex1_c28x_port_val
2. freertos_ex2_c28x_led_blinky
3. freertos_ex3_c28x_dual_blinky
4. freertos_ex4_c28x_interrupt_latency

EXAMPLE DESCRIPTION:
1. freertos_ex1_c28x_port_val Demo

This example implements the standard test demos detailed in following link:https://github.com/FreeRTOS/FreeRTOS/blob/main/FreeRTOS/Demo/ThirdParty/Template/README.md

The whole functionality is included in the freertos_ex1_c28x_port_val.c file by calling the void vStartTests( void ) function which contains the tests available in the [FreeRTOS/Demo/Common/Minimal](https://github.com/FreeRTOS/FreeRTOS/tree/main/FreeRTOS/Demo/Common/Minimal).  

This example uses the "check" task to periodically inspect the standard demo tasks in order to ensure all the tasks are functioning as expected. The "check" task blinks LED2 post inspecting all the standard demos tasks.

To see the console output for the test results, serial port(SCIA) sould be configured as: 
 - baud rate 9600
 - data 8-bit
 - parity none
 - stop bits 1-bit
 - flow control none
 
NOTE:
a. To avoid memory issues, the tests are grouped into 2 sections. Update TESTGROUP to select the desired group or alternatively run tests one by one by defining configSTART_<Test_Name>_TESTS macros to 0 or 1 as needed.
b. configSTART_INTERRUPT_QUEUE_TESTS are not added in this demo.


2. freertos_ex2_led_blinky Demo

This example demonstrates a simple blinky demo which uses various RTOS features to blink the two onboard LEDs.

3. freertos_ex3_c28x_dual_blinky Demo

This example demonstrates the usage of FreeRTOS kernel on both CPU1 and CPU2 cores.

4. freertos_ex4_c28x_interrupt_latency
This example demonstrates usage of interrupts along with RTOS functionality. CPU Timer1 is configured with 1 sec period and the interrupt latency is measured through ERAD IP.

QUICK START:
To run the demos on TMDSCNCD28388D controlcard, the following steps are required:
 - Install Code Compser Studio(CCS): https://www.ti.com/tool/CCSTUDIO
 - Install latest C2000Ware package: https://www.ti.com/tool/C2000WARE
 - Update the C2000WARE_ROOT and FreeRTOS_ROOT path variable in the example projectspec files available at following location in the repo: FreeRTOS-Community-Supported-Demos\C2000_F2838x_C28x_CCS\CCS
 - Import the example project file in CCS
 - Build and debug the project

TOOL CHAIN SUPPORT:
Code Composer Studio™ IDE (CCS) v11.1.0 or newer
C2000 Compiler v20.2.1.LTS or newer
C2000Ware_3_01_00_00 or newer
FreeRTOSv202112.00

KNOWN ISSUES:
Support for "fpu64" is not added yet to the port. The examples should specify "fpu32" as option for floating point.

REFERENCES:
https://www.ti.com/tool/TMDSCNCD28388D
https://www.ti.com/tool/C2000WARE
https://www.ti.com/tool/CCSTUDIO
