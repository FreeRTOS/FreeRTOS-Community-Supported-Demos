;;/***********************************************************************************************************************
;;* DISCLAIMER
;;* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
;;* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
;;* applicable laws, including copyright laws. 
;;* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
;;* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
;;* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
;;* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
;;* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
;;* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
;;* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
;;* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
;;* following link:
;;* http://www.renesas.com/disclaimer
;;*
;;* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
;;***********************************************************************************************************************/
;;/***********************************************************************************************************************
;;* File Name    : machine_timer_aux.s
;;* Description  : 
;;***********************************************************************************************************************/
;;/***********************************************************************************************************************
;;* History : DD.MM.YYYY Version  Description
;;*         : 26.07.2024 1.21     First Release
;;*         : 18.09.2024 1.22     Updated header comment
;;***********************************************************************************************************************/

	.text
 	.global set_mtimer_cmp  /*! global timerroutine */
	.type set_mtimer_cmp, @function

 	.global reset_mtimer  /*! global timerroutine */
	.type reset_mtimer, @function

 	.global get_mtimer  /*! global timerroutine */
	.type get_mtimer, @function

	.equ MTIME_CMPLOW_ADD, 0xE6000008
	.equ MTIME_LOW_ADD, 0xE6000000

reset_mtimer:
	li t0, -1
	la t1, MTIME_LOW_ADD
	sw t0, 0xC(t1)     # all 1 in high cmp
	sw a0, 4(t1)     # set ctr value high to 0
	sw t0, 8(t1)     # all 1 in low cmp
	sw a0, 0(t1)     # set ctr value low to 0

	ret

set_mtimer_cmp:
# New comparand is in a1:a0.
	li t0, -1
	la t1, MTIME_CMPLOW_ADD
	sw t0, 0(t1)     # No smaller than old value.
	sw a1, 4(t1)     # No smaller than new value.
	sw a0, 0(t1)     # New value.

	ret

get_mtimer:
# Value is in a1:a0.
	la t1, MTIME_LOW_ADD
	lw a1, 4(t1)     # read timer.
	lw a0, 0(t1)     #

	ret


