/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_bsp_config_reference.h
* H/W Platform : GENERIC_R9A02G021
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
*         : 29.03.2024 1.10     Update the description of BSP_CFG_CONFIGURATOR_VERSION
*         : 10.06.2024 1.20     Change the macro name endwith "DISABLE" to "FUNCTIONS"
*         :                     Add new macro BSP_CFG_PFB_ENABLE
*         : 26.07.2024 1.21		Remove BSP_CFG_MTIME_COUNTER_HIGHERBITS, BSP_CFG_MTIME_COUNTER_LOWERBITS
*         :                     Remove BSP_CFG_MTIME_COMPARE_HIGHERBITS, BSP_CFG_MTIME_COMPARE_LOWERBITS
*         :                     Add BSP_CFG_MACHINE_TIMER_MODE, BSP_CFG_MTIME_INTERVAL_VALUE, BSP_CFG_MTIME_INTERVAL_UNIT

***********************************************************************************************************************/

#ifndef R_BSP_CONFIG_REF_HEADER_FILE
#define R_BSP_CONFIG_REF_HEADER_FILE
/*************************************************
 * MCU information
 *************************************************/

/* Enter the product part number for your MCU. This information will be used to obtain information about your MCU such 
   as package and memory size.
   To help parse this information, the part number will be defined using multiple macros.
   R 9 A 02 G021 4 C  NK
   | | | |    |  | |  |  Macro Name                             Description
   | | | |    |  | |  |__BSP_CFG_MCU_PART_PACKAGE             = Package type, number of pins, and pin pitch
   | | | |    |  | | 
   | | | |    |  | |_____not used                             = Quality ID (Industrial and Consumer application)
   | | | |    |  |                                              
   | | | |    |  |_______not used                             = Operating Temperature
   | | | |    |__________not used                             = Product No.
   | | | |_______________not used                             = Process Generation No.
   | | |_________________BSP_CFG_MCU_PART_ROM_TYPE            = Device Type
   | |___________________not used                             = Renesas MCU
   |_____________________not used                             = Renesas semiconductor product.
*/

/* Package type. Set the macro definition based on values below:
   Character(s) = Value for macro = Package Type/Number of Pins/Pin Pitch
   BY           = 0x0             = WLCSP /16/0.40
   NK           = 0x1             = HWQFN/24/0.50
   NH           = 0x2             = HWQFN/32/0.50
   NE           = 0x3             = QFN/48/0.50
*/
#define BSP_CFG_MCU_PART_PACKAGE        (0x0)

/* Device type
 A = Single Chip : 0
*/
#define BSP_CFG_MCU_PART_ROM_TYPE (0)

/*************************************************
 * ROM register setting
 *************************************************/
/* Set your desired ID code. NOTE, leave at the default (all 0xFF's) if you do not wish to use an ID code. If you set 
   this value and program it into the MCU then you will need to remember the ID code because the debugger will ask for 
   it when trying to connect. Note that the E1/E20 will ignore the ID code when programming the MCU during debugging.
   If you set this value and then forget it then you can clear the ID code by connecting up in serial boot mode using 
   FDT. The ID Code is 16 bytes long. The macro below define the ID Code in 4-byte sections.
   NOTE: do not set OSIS bit 127 to zero, otherwise the device will be bricked.
*/
#define BSP_CFG_OCD_SERIAL_ID_VALUE_0 (0xFFFFFFFF)
#define BSP_CFG_OCD_SERIAL_ID_VALUE_1 (0xFFFFFFFF)
#define BSP_CFG_OCD_SERIAL_ID_VALUE_2 (0xFFFFFFFF)
#define BSP_CFG_OCD_SERIAL_ID_VALUE_3 (0xFFFFFFFF)

/* A user ID can be set through serial programming by using a flash memory programmer. */
#define BSP_CFG_USER_ID_SETTING_0 (0xFFFFFFFF)
#define BSP_CFG_USER_ID_SETTING_1 (0xFFFFFFFF)
#define BSP_CFG_USER_ID_SETTING_2 (0xFFFFFFFF)
#define BSP_CFG_USER_ID_SETTING_3 (0xFFFFFFFF)

#define BSP_CFG_OFS0_REG_VALUE  (0xFFFFFFFF)
#define BSP_CFG_OFS1_REG_VALUE  (0xFFFFFFFF)

/***********************************************************
 * Invalid memory access detection control register ()
 ***********************************************************/
/* Access Window Start Block Address - AWS register
These bits specify the start block address for the access window. They do not represent the block number of the access
window. The access window is only valid in the program flash area. The block address specifies the first address of
the block and consists of the address bits [21:11]
*/
#define BSP_CFG_ACCESS_WINDOW_START_BLOCK_ADDRESS (0x7FF)

/* Access Window End Block Address - AWS register
These bits specify the end block address for the access window.
They do not represent the block number of the access window.
The access window is only valid in the program flash area. The end block address for the access window is the next block
to the acceptable programming and erasure region defined by the access window. The block address specifies the first
address of the block and consists of the address bits [21:11].
*/
#define BSP_CFG_ACCESS_WINDOW_END_BLOCK_ADDRESS (0x7FF)

/* Protection of On-chip Debugger Connection - SECS register
This bit controls the connection to on-chip debugger.
NOTE: When this bit is set to 0, it cannot be changed to 1 except for ALeRASE sequence
 0 = On-chip debugger is not connectable.
 1 = On-chip debugger is connectable.
*/
#define BSP_CFG_OCD_PROTECTION (1)

/* Protection of Access Window Function- SECS register
This bit controls the command for setting the access window.
NOTE: When this bit is set to 0, it cannot be changed to 1.
 0: Executing the configuration setting command for programming Access Window
(FAWE[10:0], FAWS[10:0]) is invalid. ALeRASE sequence is invalid.
 1: Executing the configuration setting command for programming Access Window
(FAWE[10:0], FAWS[10:0]) is valid. ALeRASE sequence is valid.
*/
#define BSP_CFG_AWF_PROTECTION (1)

/*************************************************
 * Data flash
 *************************************************/
/* Data flash memory area access control
  Data flash control register(DFLCTL)
  DFLEN
0 : Access to the data flash memory area is disabled.
1 : Access to the data flash memory area is enabled.
*/
#define BSP_CFG_DATA_FLASH_ACCESS_ENABLE (0)

/* Flash Read Protection Access Control Register (FLRPROTAC)
 0 : Enable flash read protection.
 1 : Disable flash read protection.
*/
#define BSP_CFG_FLRPROTAC_REG_FUNCTIONS (1)
 
/* Flash Read Protection Start Address Register (FLRPROTS)
 Address where the region starts, for use in region determination. The value range is from 0x0000_0000 to 0x000F_FFFC,
 excluding reserved areas. The lower 2 bits are read as 0. When programming to the code flash, the lower 2 bits write
 value should be 0.
*/
#define BSP_CFG_FLRPROTS_REG_VALUE (0x000FFFFC)

/* Flash Read Protection End Address Register (FLRPROTE)
 Address where the region ends, for use in region determination. The value range is from 0x0000_0003 to 0x000F_FFFF,
 excluding reserved areas. The lower 2 bits are read as 1. When programming to the code flash, the lower 2 bits write
 value should be 1.
*/
#define BSP_CFG_FLRPROTE_REG_VALUE (0x000FFFFF)

/*************************************************
 * Definition for switching functions
 *************************************************/
/* Start up select
 0 : Enable BSP startup program.
 1 : Disable BSP startup program.(e.g. Using user startup program.)
*/
#define BSP_CFG_STARTUP_FUNCTIONS (0)

/* Initialization of peripheral functions by Code Generator/Smart Configurator
 0 : Disable initialization of peripheral functions by Code Generator/Smart Configurator.
 1 : Enable initialization of peripheral functions by Code Generator/Smart Configurator.
*/
#define BSP_CFG_CONFIGURATOR_SELECT (0)

/* Version number of Smart Configurator.
   This macro definitions is updated by Smart Configurator.
   If you are using e2studio, set the following values.
   2023-07 : 1000
   2024-04 : 1010
   If you are using the standalone version of Smart Configurator,
   set the following values.
   v1.0.0  : 1000
   v1.1.0  : 1010
*/
#define BSP_CFG_CONFIGURATOR_VERSION (1000)

/* API function disable(R_BSP_StartClock, R_BSP_StopClock)
 0 : Enable API functions
 1 : Disable API functions
*/
#define BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS (0)

/* API function disable(R_BSP_ChangeICLKClockSetting)
 0 : Enable API functions
 1 : Disable API functions
*/
#define BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS (0)

/* Interrupt API functions setting(bsp_mapped_interrupt_open)
 0 : Enable interrupt-related API functions
 1 : Disable interrupt-related API functions
*/
#define BSP_CFG_INTERRUPT_SETTING_API_FUNCTIONS (0)

/* Parameter check enable
 0 : Disable parameter check.
 1 : Enable parameter check.
*/
#define BSP_CFG_PARAM_CHECKING_ENABLE (1)

/* If the user would like to determine if a warm start reset has occurred, then they may enable one or more of the
   following callback definitions AND provide a call back function name for the respective callback
   function (to be defined by the user). Setting BSP_CFG_USER_WARM_START_CALLBACK_PRE_INITC_ENABLED = 1 will result
   in a callback to the user defined my_sw_warmstart_prec_function just prior to the initialization of the C
   runtime environment by bsp_init_system.
   Setting BSP_CFG_USER_WARM_START_CALLBACK_POST_INITC_ENABLED = 1 will result in a callback to the user defined
   my_sw_warmstart_postc_function just after the initialization of the C runtime environment by bsp_init_hardware.
*/
#define BSP_CFG_USER_WARM_START_CALLBACK_PRE_INITC_ENABLED  (0)
#define BSP_CFG_USER_WARM_START_PRE_C_FUNCTION              my_sw_warmstart_prec_function

#define BSP_CFG_USER_WARM_START_CALLBACK_POST_INITC_ENABLED (0)
#define BSP_CFG_USER_WARM_START_POST_C_FUNCTION             my_sw_warmstart_postc_function

/*************************************************
 * Clock settings
 *************************************************/
/* System Clock Division Control Register (SCKDIVCR)
   System Clock (ICLK) Select (ICK[2:0])
 0 : x 1/1
 1 : x 1/2
 2 : x 1/4
 3 : x 1/8
 4 : x 1/16
 5 : x 1/32
 6 : x 1/64
*/
#define BSP_CFG_ICLK_DIV (4)

/* System Clock Division Control Register (SCKDIVCR)
   Peripheral Module Clock B (PCLKB) Select (PCKB[2:0])
 0 : x 1/1
 1 : x 1/2
 2 : x 1/4
 3 : x 1/8
 4 : x 1/16
 5 : x 1/32
 6 : x 1/64
*/
#define BSP_CFG_PCLKB_DIV (4)

/* System Clock Source Control Register (SCKSCR)
   Clock Source Select (CKSEL[2:0])
 0 : HOCO
 1 : MOCO
 2 : LOCO
 3 : External clock input (EXTAL)
 4 : Sub-clock oscillator (SOSC)
*/
#define BSP_CFG_CLOCK_SOURCE_SEL (1)

/* External Clock Input Control Register (MOSCCR)
 0 : Stop
 1 : Operate
*/
#define BSP_CFG_EXTCLK_OPERATION (0)

/* Sub-Clock Oscillator Control Register (SOSCCR)
 0 : Stop
 1 : Operate
*/
#define BSP_CFG_SUBCLK_OPERATION (0)

/* Sub-Clock Oscillator Mode Control Register (SOMCR)
 0 : Normal Mode
 1 : Low Power Mode 1
 2 : Low Power Mode 2
 3 : Low Power Mode 3
*/
#define BSP_CFG_SUBCLK_MODE (0)

/* Sub-Clock Oscillator Margin Check Register (SOMRG)
 0 : Normal Current
 1 : Lower Margin check
 2 : Upper Margin check
*/
#define BSP_CFG_SUBCLK_MARGIN (0)

/* Low-Speed On-Chip Oscillator Control Register (LOCOCR)
 0 : Stop
 1 : Operate
*/
#define BSP_CFG_LOCO_OPERATION (0)

/* High-Speed On-Chip Oscillator Control Register (HOCOCR)
 0 : Stop
 1 : Operate
*/
#define BSP_CFG_HOCO_OPERATION (1)

/* Middle-Speed On-Chip Oscillator Control Register (MOCOCR)
 0 : Stop
 1 : Operate
*/
#define BSP_CFG_MOCO_OPERATION (1)

/* Clock Out Control Register (CKOCR)
   Clock Out Source Select (CKOSEL[2:0])
 0 : HOCO
 1 : MOCO
 2 : LOCO
 3 : External clock input (EXTAL)
 4 : Sub-clock oscillator (SOSC)
*/
#define BSP_CFG_CLKOUT_SEL (0)

/* Clock Out Control Register (CKOCR)
   Clock Output Frequency Division Ratio (CKODIV[2:0])
 0 : x 1/1
 1 : x 1/2
 2 : x 1/4
 3 : x 1/8
 4 : x 1/16
 5 : x 1/32
 6 : x 1/64
 7 : x 1/128
*/
#define BSP_CFG_CLKOUT_DIV (0)

/* Clock Out Control Register (CKOCR)
   Clock Out Enable (CKOEN)
 0 : Disable
 1 : Enable
*/
#define BSP_CFG_CLKOUT_ENABLE (0)

/* Subsystem Clock Supply Mode Control Register (OSMCR)
   Selection of the operating clock for the realtime clock, 32-bit interval timer,
   serial interfaces UARTA0 and UARTA1, remote control signal receiver (WUTMMCK0)
 0 : Subsystem clock (SOSC)
 1 : Low-speed on-chip oscillator clock (LOCO)
*/
#define BSP_CFG_SUBCLK_SEL (0)

/* Input clock frequency in Hz (EXTAL). */
#define BSP_CFG_EXTAL_HZ (20000000)

/* Input clock frequency in Hz (JTAG). */
#define BSP_CFG_EXTCLK_INPUT_JTAG_HZ (6250000)

/* Operation Power Mode Select (OPCCR register and SOPCCR register)
 0: High-speed mode
 1: Middle-speed mode
 2: Subosc-speed mode
 3: Low-speed mode 
 */
#define BSP_CFG_OPERATION_MODE (1)

/* Clock source select
 0 : Machine timer clock
 1 : CPU clock
*/
#define BSP_CFG_MTIME_CLOCK_SOURCE (0)

/* Machine timer
 0 : Disable
 1 : Enable
*/
#define BSP_CFG_MACHINE_TIMER (0)

/* Machine timer mode
 0 : One-shot
 1 : Periodic
*/
#define BSP_CFG_MACHINE_TIMER_MODE (1)

/* Machine timer interval value */
#define BSP_CFG_MTIME_INTERVAL_VALUE (100)

/* Interval value unit
 1          : count
 1000       : ms
 1000000    : us
 1000000000 : ns
*/
#define BSP_CFG_MTIME_INTERVAL_UNIT (1000)

/* Machine timer interrupt priority
 0xFF: Level 0 (high)
 0xEF: Level 1
 0xDF: Level 2
 0xCF: Level 3
 0xBF: Level 4
 0xAF: Level 5
 0x9F: Level 6
 0x8F: Level 7
 0x7F: Level 8
 0x6F: Level 9
 0x5F: Level 10
 0x4F: Level 11
 0x3F: Level 12
 0x2F: Level 13
 0x1F: Level 14
 0x0F: Level 15 (low)
 */
 #define BSP_CFG_MTIP_PRIORITY (0x0F)

/* Machine software interrupt
 0 : Disable
 1 : Enable
*/
#define BSP_CFG_SOFTWARE_INTERRUPT (0)

/* Machine timer interrupt priority
 0xFF: Level 0 (high)
 0xEF: Level 1
 0xDF: Level 2
 0xCF: Level 3
 0xBF: Level 4
 0xAF: Level 5
 0x9F: Level 6
 0x8F: Level 7
 0x7F: Level 8
 0x6F: Level 9
 0x5F: Level 10
 0x4F: Level 11
 0x3F: Level 12
 0x2F: Level 13
 0x1F: Level 14
 0x0F: Level 15 (low)
 */
 #define BSP_CFG_MSIP_PRIORITY (0x0F)

/* Prefetch Buffer Enable Register (PFBER)
 0: Prefetch buffer is disabled
 1: Prefetch buffer is enabled
*/
#define BSP_CFG_PFB_ENABLE (1)

#endif /* R_BSP_CONFIG_REF_HEADER_FILE */
