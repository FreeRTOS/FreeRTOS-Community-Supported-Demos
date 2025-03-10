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
* File Name        : r_cg_icu.h
* Version          : 1.0.30
* Device(s)        : R9A02G0214CNE
* Description      : General header file for ICU peripheral.
* Creation Date    : 
***********************************************************************************************************************/


#ifndef ICU_H
#define ICU_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    IRQ Control Register i (IRQCRi)
*/
/* IRQi digital filter enable (FLTEN) */
#define _00_ICU_IRQ_FILTER_DISABLE              (0x00U)    /* IRQi digital filter is disabled */
#define _80_ICU_IRQ_FILTER_ENABLE               (0x80U)    /* IRQi digital filter is enabled */
/* IRQi digital filter sampling clock select (FCLKSEL[1:0]) */
#define _00_ICU_IRQ_FILTER_PCLKB                (0x00U)    /* PCLKB */
#define _10_ICU_IRQ_FILTER_PCLKB_8              (0x10U)    /* PCLKB/8 */
#define _20_ICU_IRQ_FILTER_PCLKB_32             (0x20U)    /* PCLKB/32 */
#define _30_ICU_IRQ_FILTER_PCLKB_64             (0x30U)    /* PCLKB/64 */
/* IRQi detection sense select (IRQMD[1:0]) */
#define _00_ICU_IRQ_EDGE_FALLING                (0x00U)    /* falling edge */
#define _01_ICU_IRQ_EDGE_RISING                 (0x01U)    /* rising edge */
#define _02_ICU_IRQ_EDGE_BOTH                   (0x02U)    /* rising and falling edges */
#define _03_ICU_IRQ_EDGE_LOW_LEVEL              (0x03U)    /* low level */

/*
    Non-Maskable Interrupt Enable Register (NMIER)
*/
/* NMI pin interrupt enable (NMIEN) */
#define _0000_ICU_MNI_INTERRRUPT_DISABLE        (0x0000U)    /* disables NMI pin interrupt */
#define _0080_ICU_MNI_INTERRRUPT_ENABLE         (0x0080U)    /* enables NMI pin interrupt */

/*
    Non-Maskable Interrupt Status Clear Register (NMICLR)
*/
/* NMI pin interrupt status flag clear (NMICLR) */
#define _0000_ICU_NMI_FLAG_NOT_CLEAR            (0x0000U)    /* no effect */
#define _0080_ICU_NMI_FLAG_CLEAR                (0x0080U)    /* clear the NMISR.NMIST flag */

/*
    NMI Pin Interrupt Control Register (NMICR)
*/
/* NMI digital filter enable (NFLTEN) */
#define _00_ICU_NMI_FILTER_DISABLE              (0x00U)    /* NMI digital filter is disabled */
#define _80_ICU_NMI_FILTER_ENABLE               (0x80U)    /* NMI digital filter is enabled */
/* NMI digital filter sampling clock select (NFCLKSEL[1:0]) */
#define _00_ICU_NMI_FILTER_PCLKB                (0x00U)    /* PCLKB */
#define _10_ICU_NMI_FILTER_PCLKB_8              (0x10U)    /* PCLKB/8 */
#define _20_ICU_NMI_FILTER_PCLKB_32             (0x20U)    /* PCLKB/32 */
#define _30_ICU_NMI_FILTER_PCLKB_64             (0x30U)    /* PCLKB/64 */
/* NMI detection set (NMIMD) */
#define _00_ICU_NMI_EDGE_FALLING                (0x00U)    /* falling edge */
#define _01_ICU_NMI_EDGE_RISING                 (0x01U)    /* rising edge */

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

