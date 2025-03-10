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
* File Name        : Config_UART0.c
* Component Version: 1.0.0
* Device(s)        : R9A02G0214CNE
* Description      : This file implements device driver for Config_UART0.
* Creation Date    : 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_UART0.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_uart0_tx_address;    /* uart0 transmit buffer address */
volatile uint16_t g_uart0_tx_count;        /* uart0 transmit data number */
volatile uint8_t * gp_uart0_rx_address;    /* uart0 receive buffer address */
volatile uint16_t g_uart0_rx_count;        /* uart0 receive data number */
uint16_t g_uart0_rx_length;                /* uart0 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Create
* Description  : This function initializes the UART0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Create(void)
{
    R_SAU0->SPS0 &= _00F0_SAU_CKM0_CLEAR;
    R_SAU0->SPS0 |= _0000_SAU_CKM0_PCLKB_0;
    R_SAU0->ST0 |= (_0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON);
    /* Mask SAU0_ENDI0 interrupt */
    R_CLIC->clicintie27_b.IE = 0U;    /* disable SAU0_ENDI0 interrupt */
    R_ICU->IELSR8 &= 0xFFFEFFFFU;    /* clear SAU0_ENDI0 interrupt flag */
    /* Set SAU0_ENDI0 interrupt */
    R_CLIC->clicintctl27 = _FF_INT_PRIORITY_0;    /* set SAU0_ENDI0 interrupt priority */
    R_CLIC->clicintattr27 = _C3_INT_VECTOR_MODE;    /* set SAU0_ENDI0 interrupt to vector mode */
    R_ICU->IELSR8 &= 0xFFFFFFE0U;
    R_ICU->IELSR8 |= 0x12U;    /* set SAU0_ENDI0 interrupt event selection */
    /* Mask SAU0_ENDI1 interrupt */
    R_CLIC->clicintie28_b.IE = 0U;    /* disable SAU0_ENDI1 interrupt */
    R_ICU->IELSR9 &= 0xFFFEFFFFU;    /* clear SAU0_ENDI1 interrupt flag */
    /* Mask SAU0_INTSRE0 interrupt */
    R_CLIC->clicintie36_b.IE = 0U;    /* disable SAU0_INTSRE0 interrupt */
    R_ICU->IELSR17 &= 0xFFFEFFFFU;    /* clear SAU0_INTSRE0 interrupt flag */
    /* Set SAU0_ENDI1 interrupt */
    R_CLIC->clicintctl28 = _EF_INT_PRIORITY_1;    /* set SAU0_ENDI1 interrupt priority */
    R_CLIC->clicintattr28 = _C3_INT_VECTOR_MODE;    /* set SAU0_ENDI1 interrupt to vector mode */
    R_ICU->IELSR9 &= 0xFFFFFFE0U;
    R_ICU->IELSR9 |= 0x12U;    /* set SAU0_ENDI1 interrupt event selection */
    /* Set SAU0_INTSRE0 interrupt */
    R_CLIC->clicintctl36 = _EF_INT_PRIORITY_1;    /* set SAU0_INTSRE0 interrupt priority */
    R_CLIC->clicintattr36 = _C3_INT_VECTOR_MODE;    /* set SAU0_INTSRE0 interrupt to vector mode */
    R_ICU->IELSR17 &= 0xFFFFFFE0U;
    R_ICU->IELSR17 |= 0x14U;    /* set SAU0_INTSRE0 interrupt event selection */
    /* Set for transmit mode*/
    R_SAU0->SMR00 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CKM0 | _0000_SAU_TRIGGER_SOFTWARE | 
                    _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    R_SAU0->SCR00 = _0004_SAU_SCRMN_INITIALVALUE | _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | 
                    _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0003_SAU_LENGTH_8;
    R_SAU0->SDR00 = _2800_SAU0_CH0_TRANSMIT_DIVISOR;
    R_PORGA->SNFEN |= _01_SAU_RXD0_FILTER_ON;
    /* Set for receive mode*/
    R_SAU0->SIR01 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    R_SAU0->SMR01 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CKM0 | _0100_SAU_TRIGGER_RXD | 
                    _0000_SAU_EDGE_FALL | _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    R_SAU0->SCR01 = _0004_SAU_SCRMN_INITIALVALUE | _4000_SAU_RECEPTION | _0400_SAU_INTSRE_ENABLE | 
                    _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0003_SAU_LENGTH_8;
    R_SAU0->SDR01 = _9800_SAU0_CH1_RECEIVE_DIVISOR;
    R_SAU0->SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;
    R_SAU0->SOL0 |= _0000_SAU_CHANNEL0_NORMAL;    /* output level normal */
    R_SAU0->SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable UART0 output */
    /* Set TxD0 pin */
    R_PFS->P302PFS_b.NCODR = 0U;
    R_PFS->P302PFS_b.PMR = 0U;
    R_PFS->P302PFS_b.PSEL = 0x11U;
    R_PFS->P302PFS_b.PMR = 1U;
    R_PFS->P302PFS_b.PDR = 1U;
    /* Set RxD0 pin */
    R_PFS->P303PFS_b.NCODR = 1U;
    R_PFS->P303PFS_b.PMR = 0U;
    R_PFS->P303PFS_b.PSEL = 0x11U;
    R_PFS->P303PFS_b.PMR = 1U;
    R_PFS->P303PFS_b.PDR = 0U;

    R_Config_UART0_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Start
* Description  : This function starts UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Start(void)
{
    R_SAU0->SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;    /* output level normal */
    R_SAU0->SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable UART0 output */
    R_SAU0->SS0 |= (_0002_SAU_CH1_START_TRG_ON | _0001_SAU_CH0_START_TRG_ON);    /* enable UART0 receive and transmit */
    R_ICU->IELSR8 &= 0xFFFEFFFFU;    /* clear SAU0_ENDI0 interrupt flag */
    R_CLIC->clicintie27_b.IE = 1U;    /* enable SAU0_ENDI0 interrupt */
    R_ICU->IELSR9 &= 0xFFFEFFFFU;    /* clear SAU0_ENDI1 interrupt flag */
    R_ICU->IELSR17 &= 0xFFFEFFFFU;    /* clear SAU0_INTSRE0 interrupt flag */
    R_CLIC->clicintie28_b.IE = 1U;    /* enable SAU0_ENDI1 interrupt */
    R_CLIC->clicintie36_b.IE = 1U;    /* enable SAU0_INTSRE0 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Stop
* Description  : This function stops UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Stop(void)
{
    R_CLIC->clicintie27_b.IE = 0U;    /* disable SAU0_ENDI0 interrupt */
    R_CLIC->clicintie28_b.IE = 0U;    /* disable SAU0_ENDI1 interrupt */
    R_CLIC->clicintie36_b.IE = 0U;    /* disable SAU0_INTSRE0 interrupt */
    R_SAU0->ST0 |= (_0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON);
    R_SAU0->SOE0 &= (uint16_t)~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable UART0 output */
    R_ICU->IELSR8 &= 0xFFFEFFFFU;    /* clear SAU0_ENDI0 interrupt flag */
    R_ICU->IELSR9 &= 0xFFFEFFFFU;    /* clear SAU0_ENDI1 interrupt flag */
    R_ICU->IELSR17 &= 0xFFFEFFFFU;    /* clear SAU0_INTSRE0 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Send
* Description  : This function sends UART0 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_UART0_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart0_tx_address = tx_buf;
        g_uart0_tx_count = tx_num;
        R_CLIC->clicintie27_b.IE = 0U;    /* disable SAU0_ENDI0 interrupt */
        R_SAU0->SDR00_b.DAT = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
        R_CLIC->clicintie27_b.IE = 1U;    /* enable SAU0_ENDI0 interrupt */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Receive
* Description  : This function receives UART0 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_UART0_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart0_rx_count = 0U;
        g_uart0_rx_length = rx_num;
        gp_uart0_rx_address = rx_buf;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Loopback_Enable
* Description  : This function enables the UART0 loopback function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Loopback_Enable(void)
{
    R_PORGA->ULBS_b.ULBS0 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Loopback_Disable
* Description  : This function disables the UART0 loopback function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Loopback_Disable(void)
{
    R_PORGA->ULBS_b.ULBS0 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

