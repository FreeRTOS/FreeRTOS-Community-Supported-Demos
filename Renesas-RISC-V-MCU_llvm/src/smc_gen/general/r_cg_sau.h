/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021, 2023 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_cg_sau.h
* Version          : 1.0.30
* Device(s)        : R9A02G0214CNE
* Description      : General header file for SAU peripheral.
* Creation Date    : 
***********************************************************************************************************************/


#ifndef SAU_H
#define SAU_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/*
    Serial Clock Select Register m (SPSm)
*/
/* Section of operation clock (CKm1) (PRS1[3:0]) */
#define _0000_SAU_CKM1_PCLKB_0            (0x0000U)    /* ckm1 - PCLKB */
#define _0010_SAU_CKM1_PCLKB_1            (0x0010U)    /* ckm1 - PCLKB/2^1 */
#define _0020_SAU_CKM1_PCLKB_2            (0x0020U)    /* ckm1 - PCLKB/2^2 */
#define _0030_SAU_CKM1_PCLKB_3            (0x0030U)    /* ckm1 - PCLKB/2^3 */
#define _0040_SAU_CKM1_PCLKB_4            (0x0040U)    /* ckm1 - PCLKB/2^4 */
#define _0050_SAU_CKM1_PCLKB_5            (0x0050U)    /* ckm1 - PCLKB/2^5 */
#define _0060_SAU_CKM1_PCLKB_6            (0x0060U)    /* ckm1 - PCLKB/2^6 */
#define _0070_SAU_CKM1_PCLKB_7            (0x0070U)    /* ckm1 - PCLKB/2^7 */
#define _0080_SAU_CKM1_PCLKB_8            (0x0080U)    /* ckm1 - PCLKB/2^8 */
#define _0090_SAU_CKM1_PCLKB_9            (0x0090U)    /* ckm1 - PCLKB/2^9 */
#define _00A0_SAU_CKM1_PCLKB_10           (0x00A0U)    /* ckm1 - PCLKB/2^10 */
#define _00B0_SAU_CKM1_PCLKB_11           (0x00B0U)    /* ckm1 - PCLKB/2^11 */
#define _00C0_SAU_CKM1_PCLKB_12           (0x00C0U)    /* ckm1 - PCLKB/2^12 */
#define _00D0_SAU_CKM1_PCLKB_13           (0x00D0U)    /* ckm1 - PCLKB/2^13 */
#define _00E0_SAU_CKM1_PCLKB_14           (0x00E0U)    /* ckm1 - PCLKB/2^14 */
#define _00F0_SAU_CKM1_PCLKB_15           (0x00F0U)    /* ckm1 - PCLKB/2^15 */
#define _000F_SAU_CKM1_CLEAR              (0x000FU)    /* clear bit4 - bit7 */
/* Section of operation clock (CKm0) (PRS0[3:0]) */
#define _0000_SAU_CKM0_PCLKB_0            (0x0000U)    /* ckm0 - PCLKB */
#define _0001_SAU_CKM0_PCLKB_1            (0x0001U)    /* ckm0 - PCLKB/2^1 */
#define _0002_SAU_CKM0_PCLKB_2            (0x0002U)    /* ckm0 - PCLKB/2^2 */
#define _0003_SAU_CKM0_PCLKB_3            (0x0003U)    /* ckm0 - PCLKB/2^3 */
#define _0004_SAU_CKM0_PCLKB_4            (0x0004U)    /* ckm0 - PCLKB/2^4 */
#define _0005_SAU_CKM0_PCLKB_5            (0x0005U)    /* ckm0 - PCLKB/2^5 */
#define _0006_SAU_CKM0_PCLKB_6            (0x0006U)    /* ckm0 - PCLKB/2^6 */
#define _0007_SAU_CKM0_PCLKB_7            (0x0007U)    /* ckm0 - PCLKB/2^7 */
#define _0008_SAU_CKM0_PCLKB_8            (0x0008U)    /* ckm0 - PCLKB/2^8 */
#define _0009_SAU_CKM0_PCLKB_9            (0x0009U)    /* ckm0 - PCLKB/2^9 */
#define _000A_SAU_CKM0_PCLKB_10           (0x000AU)    /* ckm0 - PCLKB/2^10 */
#define _000B_SAU_CKM0_PCLKB_11           (0x000BU)    /* ckm0 - PCLKB/2^11 */
#define _000C_SAU_CKM0_PCLKB_12           (0x000CU)    /* ckm0 - PCLKB/2^12 */
#define _000D_SAU_CKM0_PCLKB_13           (0x000DU)    /* ckm0 - PCLKB/2^13 */
#define _000E_SAU_CKM0_PCLKB_14           (0x000EU)    /* ckm0 - PCLKB/2^14 */
#define _000F_SAU_CKM0_PCLKB_15           (0x000FU)    /* ckm0 - PCLKB/2^15 */
#define _00F0_SAU_CKM0_CLEAR              (0x00F0U)    /* clear bit0 - bit3 */

/*
    Serial Mode Register mn (SMRmn)
*/
#define _0020_SAU_SMRMN_INITIALVALUE     (0x0020U)    /* SMRmn initial value */
/* Selection of operation clock (MCK) of channel n (CKS) */
#define _0000_SAU_CLOCK_SELECT_CKM0      (0x0000U)    /* operation clock CKm0 set by SPSm register */
#define _8000_SAU_CLOCK_SELECT_CKM1      (0x8000U)    /* operation clock CKm1 set by SPSm register */
/* Selection of transfer clock (TCLK) of channel n (CCS) */
#define _0000_SAU_CLOCK_MODE_CKS         (0x0000U)    /* divided operation clock MCK specified by CKS bit */
#define _4000_SAU_CLOCK_MODE_TI0N        (0x4000U)    /* clock input from SCKp pin (slave transfer in CSI mode) */
/* Selection of start trigger source (STS) */
#define _0000_SAU_TRIGGER_SOFTWARE       (0x0000U)    /* only software trigger is valid */
#define _0100_SAU_TRIGGER_RXD            (0x0100U)    /* valid edge of RXD pin */
/* Controls inversion of level of receive data of channel n in UART mode (SIS0) */
#define _0000_SAU_EDGE_FALL              (0x0000U)    /* falling edge is detected as the start bit */
#define _0040_SAU_EDGE_RISING            (0x0040U)    /* rising edge is detected as the start bit */
/* Setting of operation mode of channel n (MD1[1:0]) */
#define _0000_SAU_MODE_CSI               (0x0000U)    /* CSI mode */
#define _0002_SAU_MODE_UART              (0x0002U)    /* UART mode */
#define _0004_SAU_MODE_IIC               (0x0004U)    /* simplified IIC mode */
/* Selection of interrupt source of channel n (MD0) */
#define _0000_SAU_TRANSFER_END           (0x0000U)    /* transfer end interrupt */
#define _0001_SAU_BUFFER_EMPTY           (0x0001U)    /* buffer empty interrupt */

/*
    Serial Communication Operation Setting Register mn (SCRmn)
*/
#define _0004_SAU_SCRMN_INITIALVALUE     (0x0004U)    /* SCRmn initial value */
/* Setting of operation mode of channel n (TRXE[1:0]) */
#define _0000_SAU_NOT_COMMUNICATION      (0x0000U)    /* does not start communication */
#define _4000_SAU_RECEPTION              (0x4000U)    /* reception only */
#define _8000_SAU_TRANSMISSION           (0x8000U)    /* transmission only */
#define _C000_SAU_RECEPTION_TRANSMISSION (0xC000U)    /* reception and transmission */
/* Selection of data and clock phase in CSI mode (DCP[1:0]) */
#define _0000_SAU_TIMING_1               (0x0000U)    /* type 1 */
#define _1000_SAU_TIMING_2               (0x1000U)    /* type 2 */
#define _2000_SAU_TIMING_3               (0x2000U)    /* type 3 */
#define _3000_SAU_TIMING_4               (0x3000U)    /* type 4 */
/* Selection of masking of error interrupt signal (EOC) */
#define _0000_SAU_INTSRE_MASK            (0x0000U)    /* masks error interrupt SAUm_INTSREn */
#define _0400_SAU_INTSRE_ENABLE          (0x0400U)    /* enables generation of error interrupt SAUm_INTSREn */
/* Setting of parity bit in UART mode (PTC[1:0]) */
#define _0000_SAU_PARITY_NONE            (0x0000U)    /* none parity */
#define _0100_SAU_PARITY_ZERO            (0x0100U)    /* zero parity */
#define _0200_SAU_PARITY_EVEN            (0x0200U)    /* even parity */
#define _0300_SAU_PARITY_ODD             (0x0300U)    /* odd parity */
/* Selection of data transfer sequence in CSI and UART modes (DIR) */
#define _0000_SAU_MSB                    (0x0000U)    /* msb */
#define _0080_SAU_LSB                    (0x0080U)    /* lsb */
/* Setting of stop bit in UART mode (SLC[1:0]) */
#define _0000_SAU_STOP_NONE              (0x0000U)    /* none stop bit */
#define _0010_SAU_STOP_1                 (0x0010U)    /* 1 stop bit */
#define _0020_SAU_STOP_2                 (0x0020U)    /* 2 stop bits */
/* Setting of data length in CSI and UART modes (DLS[1:0]) */
#define _0001_SAU_LENGTH_9               (0x0001U)    /* 9-bit data length */
#define _0002_SAU_LENGTH_7               (0x0002U)    /* 7-bit data length */
#define _0003_SAU_LENGTH_8               (0x0003U)    /* 8-bit data length */

/*
    Serial Flag Clear Trigger Register mn (SIRmn)
*/
/* Clear trigger of framing error of channel n (FECT) */
#define _0004_SAU_SIRMN_FECTMN           (0x0004U)    /* clears the FEF bit of the SSRmn register to 0 */
/* Clear trigger of parity error flag of channel n (PECT) */
#define _0002_SAU_SIRMN_PECTMN           (0x0002U)    /* clears the PEF bit of the SSRmn register to 0 */
/* Clear trigger of overrun error flag of channel n (OVCT) */
#define _0001_SAU_SIRMN_OVCTMN           (0x0001U)    /* clears the OVF bit of the SSRmn register to 0 */

/*
    Serial Status Register mn (SSRmn)
*/
/* Communication status indication flag of channel n (TSF) */
#define _0040_SAU_UNDER_EXECUTE          (0x0040U)    /* communication is under execution */
/* Buffer register status indication flag of channel n (BFF) */
#define _0020_SAU_VALID_STORED           (0x0020U)    /* valid data is stored in the SDRmn register */
/* Framing error detection flag of channel n (FEF) */
#define _0004_SAU_FRAM_ERROR             (0x0004U)    /* a framing error occurs during UART reception */
/* Parity error detection flag of channel n (PEF) */
#define _0002_SAU_PARITY_ERROR           (0x0002U)    /* a parity error occurs or ACK is not detected */
/* Overrun error detection flag of channel n (OVF) */
#define _0001_SAU_OVERRUN_ERROR          (0x0001U)    /* an overrun error occurs */

/*
    Serial Channel Start Register m (SSm)
*/
/* Operation start trigger of channel 3 (SS3) */
#define _0000_SAU_CH3_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0008_SAU_CH3_START_TRG_ON       (0x0008U)    /* sets SE0.SE[3] to 1 and enters the communication wait status */
/* Operation start trigger of channel 2 (SS2) */
#define _0000_SAU_CH2_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0004_SAU_CH2_START_TRG_ON       (0x0004U)    /* sets SE0.SE[2] to 1 and enters the communication wait status */
/* Operation start trigger of channel 1 (SS1) */
#define _0000_SAU_CH1_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0002_SAU_CH1_START_TRG_ON       (0x0002U)    /* sets SE0.SE[1] to 1 and enters the communication wait status */
/* Operation start trigger of channel 0 (SS0) */
#define _0000_SAU_CH0_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0001_SAU_CH0_START_TRG_ON       (0x0001U)    /* sets SE0.SE[0] to 1 and enters the communication wait status */

/*
    Serial Channel Stop Register m (STm)
*/
/* Operation stop trigger of channel 3 (ST3) */
#define _0000_SAU_CH3_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0008_SAU_CH3_STOP_TRG_ON        (0x0008U)    /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 2 (ST2) */
#define _0000_SAU_CH2_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0004_SAU_CH2_STOP_TRG_ON        (0x0004U)    /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 (ST1) */
#define _0000_SAU_CH1_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0002_SAU_CH1_STOP_TRG_ON        (0x0002U)    /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 0 (ST0) */
#define _0000_SAU_CH0_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0001_SAU_CH0_STOP_TRG_ON        (0x0001U)    /* operation is stopped (stop trigger is generated) */

/*
    Serial Output Enable Register m (SOEm)
*/
/* Serial output enable/disable of channel 3 (SOE3) */
#define _0000_SAU_CH3_OUTPUT_DISABLE     (0x0000U)    /* stops output by serial communication operation */
#define _0008_SAU_CH3_OUTPUT_ENABLE      (0x0008U)    /* enables output by serial communication operation */
/* Serial output enable/disable of channel 2 (SOE2) */
#define _0000_SAU_CH2_OUTPUT_DISABLE     (0x0000U)    /* stops output by serial communication operation */
#define _0004_SAU_CH2_OUTPUT_ENABLE      (0x0004U)    /* enables output by serial communication operation */
/* Serial output enable/disable of channel 1 (SOE1) */
#define _0000_SAU_CH1_OUTPUT_DISABLE     (0x0000U)    /* stops output by serial communication operation */
#define _0002_SAU_CH1_OUTPUT_ENABLE      (0x0002U)    /* enables output by serial communication operation */
/* Serial output enable/disable of channel 0 (SOE0) */
#define _0000_SAU_CH0_OUTPUT_DISABLE     (0x0000U)    /* stops output by serial communication operation */
#define _0001_SAU_CH0_OUTPUT_ENABLE      (0x0001U)    /* enables output by serial communication operation */

/*
    Serial Output Register m (SOm)
*/
/* Serial clock output of channel 3 (CKO3) */
#define _0000_SAU_CH3_CLOCK_OUTPUT_0     (0x0000U)    /* serial clock output value is "0" */
#define _0800_SAU_CH3_CLOCK_OUTPUT_1     (0x0800U)    /* serial clock output value is "1" */
/* Serial clock output of channel 2 (CKO2) */
#define _0000_SAU_CH2_CLOCK_OUTPUT_0     (0x0000U)    /* serial clock output value is "0" */
#define _0400_SAU_CH2_CLOCK_OUTPUT_1     (0x0400U)    /* serial clock output value is "1" */
/* Serial clock output of channel 1 (CKO1) */
#define _0000_SAU_CH1_CLOCK_OUTPUT_0     (0x0000U)    /* serial clock output value is "0" */
#define _0200_SAU_CH1_CLOCK_OUTPUT_1     (0x0200U)    /* serial clock output value is "1" */
/* Serial clock output of channel 0 (CKO0) */
#define _0000_SAU_CH0_CLOCK_OUTPUT_0     (0x0000U)    /* serial clock output value is "0" */
#define _0100_SAU_CH0_CLOCK_OUTPUT_1     (0x0100U)    /* serial clock output value is "1" */
/* Serial data output of channel 3 (SO3) */
#define _0000_SAU_CH3_DATA_OUTPUT_0      (0x0000U)    /* serial data output value is "0" */
#define _0008_SAU_CH3_DATA_OUTPUT_1      (0x0008U)    /* serial data output value is "1" */
/* Serial data output of channel 2 (SO2) */
#define _0000_SAU_CH2_DATA_OUTPUT_0      (0x0000U)    /* serial data output value is "0" */
#define _0004_SAU_CH2_DATA_OUTPUT_1      (0x0004U)    /* serial data output value is "1" */
/* Serial data output of channel 1 (SO1) */
#define _0000_SAU_CH1_DATA_OUTPUT_0      (0x0000U)    /* serial data output value is "0" */
#define _0002_SAU_CH1_DATA_OUTPUT_1      (0x0002U)    /* serial data output value is "1" */
/* Serial data output of channel 0 (SO0) */
#define _0000_SAU_CH0_DATA_OUTPUT_0      (0x0000U)    /* serial data output value is "0" */
#define _0001_SAU_CH0_DATA_OUTPUT_1      (0x0001U)    /* serial data output value is "1" */

/*
    Serial Output Level Register m (SOLm)
*/
/* Selects inversion of the level of the transmit data of channel 2 in UART mode (SOL2) */
#define _0000_SAU_CHANNEL2_NORMAL        (0x0000U)    /* normal bit level */
#define _0004_SAU_CHANNEL2_INVERTED      (0x0004U)    /* inverted bit level */
/* Selects inversion of the level of the transmit data of channel 0 in UART mode (SOL0) */
#define _0000_SAU_CHANNEL0_NORMAL        (0x0000U)    /* normal bit level */
#define _0001_SAU_CHANNEL0_INVERTED      (0x0001U)    /* inverted bit level */

/*
    Serial Standby Control Register m (SSCm)
*/
/* Setting of the Snooze mode (SWC) */
#define _0000_SAU_SNOOZE_OFF             (0x0000U)    /* do not use the Snooze mode function */
#define _0001_SAU_SNOOZE_ON              (0x0001U)    /* use the Snooze mode function */

/*
    Input Switch Control Register (ISC)
*/
/* Switch of the serial clock input source of SPI01 (ISC76[1:0]) */
#define _00_SPI01_INPUT_SCK01_PIN        (0x00U)    /* input signal of the SCK01 pin (normal operation) */
#define _80_SPI01_INPUT_TO01_SIGNAL      (0x80U)    /* TO01 output signal */
#define _3F_SPI01_INPUT_CLEAR            (0x3FU)    /* clear ISC76[1:0] bits */
/* Switch of the serial clock input source of SPI00 (ISC43[1:0]) */
#define _00_SPI00_INPUT_SCK00_PIN        (0x00U)    /* input signal of the SCK00 pin (normal operation) */
#define _10_SPI00_INPUT_TO01_SIGNAL      (0x10U)    /* TO01 output signal */
#define _E7_SPI00_INPUT_CLEAR            (0xE7U)    /* clear ISC43[1:0] bits */

/*
    SAU Noise Filter Enable Register (SNFEN)
*/
/* Use of noise filter of RxD2 (SNFEN20) */
#define _00_SAU_RXD2_FILTER_OFF          (0x00U)    /* noise filter off */
#define _10_SAU_RXD2_FILTER_ON           (0x10U)    /* noise filter on */
/* Use of noise filter of RxD1 (SNFEN10) */
#define _00_SAU_RXD1_FILTER_OFF          (0x00U)    /* noise filter off */
#define _04_SAU_RXD1_FILTER_ON           (0x04U)    /* noise filter on */
/* Use of noise filter of RxD0 (SNFEN00) */
#define _00_SAU_RXD0_FILTER_OFF          (0x00U)    /* noise filter off */
#define _01_SAU_RXD0_FILTER_ON           (0x01U)    /* noise filter on */

/*
    UART Loopback Selection Register (ULBS)
*/
/* UART2 loopback function setting (ULBS2) */
#define _00_UART2_LOOPBACK_DISABLE       (0x00U)    /* disable UART2 loopback function */
#define _04_UART2_LOOPBACK_ENABLE        (0x04U)    /* enable UART2 loopback function */
/* UART1 loopback function setting (ULBS1) */
#define _00_UART1_LOOPBACK_DISABLE       (0x00U)    /* disable UART1 loopback function */
#define _02_UART1_LOOPBACK_ENABLE        (0x02U)    /* enable UART1 loopback function */
/* UART0 loopback function setting (ULBS0) */
#define _00_UART0_LOOPBACK_DISABLE       (0x00U)    /* disable UART0 loopback function */
#define _01_UART0_LOOPBACK_ENABLE        (0x01U)    /* enable UART0 loopback function */

/* SAU Used Flag */
#define _00_SAU_IIC_MASTER_FLAG_CLEAR    (0x00U)
#define _01_SAU_IIC_SEND_FLAG            (0x01U)
#define _02_SAU_IIC_RECEIVE_FLAG         (0x02U)
#define _04_SAU_IIC_SENDED_ADDRESS_FLAG  (0x04U)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

