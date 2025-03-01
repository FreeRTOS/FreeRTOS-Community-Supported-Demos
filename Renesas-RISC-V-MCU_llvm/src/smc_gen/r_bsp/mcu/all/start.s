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
;;* File Name    : start.S
;;* Description  : 
;;***********************************************************************************************************************/
;;/***********************************************************************************************************************
;;* History : DD.MM.YYYY Version  Description
;;*         : 20.01.2024 1.00     First Release
;;          : 29.03.2024 1.10     Add code to init the data segment for ECC
;;***********************************************************************************************************************/

    /*reset_program.asm*/
    .extern initialize_vect
    .text
    .global _PowerON_Reset  /*! global Start routine */
    .type _PowerON_Reset, @function

/* call to _PowerON_Reset */
_PowerON_Reset:
# Initialize global pointer
    .option push
    .option norelax
1:
    auipc gp, %pcrel_hi(__global_pointer$)
    addi  gp, gp, %pcrel_lo(1b)
    .option pop

# initialize the stack and frame pointers
    la      sp, __stack
    add s0, sp, zero

# Initialize vect
    call    initialize_vect

# Call bsp_init_system() function - clock setup
    call    bsp_init_system

 # Clear the bss segment
    la      a0, __bss
    la      a2, __ebss
    sub     a2, a2, a0
    li      a1, 0
    call    memset

# Init the data segment
    la      a0, __datastart
    la      a1, __romdatastart
    la      a2, __romdatacopysize
    call    memcpy

# Init the data segment for ECC
    la      a0, __dataeccramstart
    la      a1, __romdataeccramstart
    la      a2, __romdataeccramcopysize
    call    memcpy

# Call bsp_init_hardware() function - hardware setup
    call    bsp_init_hardware

# Make reference to atexit weak to avoid unconditionally pulling in
# support code.  Refer to comments in __atexit.c for more details.
    .weak   atexit
    la      a0, atexit
    beqz    a0, .Lweak_atexit
    .weak   __libc_fini_array


    la      a0, __libc_fini_array   # Register global termination functions
    call    atexit                  #  to be called upon exit

.Lweak_atexit:

    call    __libc_init_array       # Run global initialization functions

    li      a0, 0                  # a0 = argc
    li      a1, 0                  # a1 = argv
    li      a2, 0                  # a2 = envp = NULL
    call    main
    tail    exit

    .size  _PowerON_Reset, .-_PowerON_Reset

