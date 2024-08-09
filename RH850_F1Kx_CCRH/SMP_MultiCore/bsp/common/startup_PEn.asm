;-------------------------------------------------------------------------------
;-- Module      = startup_PEn.asm
;-- Version     = 1.0.0
;-------------------------------------------------------------------------------
;--                                  COPYRIGHT
;-------------------------------------------------------------------------------
;-- Copyright (c) 2023 by Renesas Electronics Europe GmbH,
;--               a company of the Renesas Electronics Corporation
;-------------------------------------------------------------------------------
;-- Purpose:      Startup Code
;--
;-------------------------------------------------------------------------------
;--
;-- Warranty Disclaimer
;--
;-- Because the Product(s) is licensed free of charge, there is no warranty
;-- of any kind whatsoever and expressly disclaimed and excluded by Renesas,
;-- either expressed or implied, including but not limited to those for
;-- non-infringement of intellectual property, merchantability and/or
;-- fitness for the particular purpose.
;-- Renesas shall not have any obligation to maintain, service or provide bug
;-- fixes for the supplied Product(s) and/or the Application.
;--
;-- Each User is solely responsible for determining the appropriateness of
;-- using the Product(s) and assumes all risks associated with its exercise
;-- of rights under this Agreement, including, but not limited to the risks
;-- and costs of program errors, compliance with applicable laws, damage to
;-- or loss of data, programs or equipment, and unavailability or
;-- interruption of operations.
;--
;-- Limitation of Liability
;--
;-- In no event shall Renesas be liable to the User for any incidental,
;-- consequential, indirect, or punitive damage (including but not limited
;-- to lost profits) regardless of whether such liability is based on breach
;-- of contract, tort, strict liability, breach of warranties, failure of
;-- essential purpose or otherwise and even if advised of the possibility of
;-- such damages. Renesas shall not be liable for any services or products
;-- provided by third party vendors, developers or consultants identified or
;-- referred to the User by Renesas in connection with the Product(s) and/or
;-- the Application.
;--
;-------------------------------------------------------------------------------
;-- Environment:
;--              Device:         F1KH
;--              IDE:            CCRH V2.04.00 or later
;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
;-- Revision Control History:
;-- 1.0.0 :   20th-Feb-2023    : Initial Version
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
;-------------  Selection of external interrupt service handler
;-------------  User modifiable section
;-------------  Please uncomment the required interrupt service handler
;-------------------------------------------------------------------------------


;-------------------------------------------------------------------------------
;-------------  ASM macros
;-------------------------------------------------------------------------------
  CUx_EBV .set 0x00018000
  ;USE_TABLE_REFERENCE_METHOD .set 0
  PE2_USED     .set 1

;-------------------------------------------------------------------------------
;------------- Public function delaration
;-------------------------------------------------------------------------------
  .extern __unused_isr
  .extern _SYNC_PE1
  .extern _exit

  .section "RESET_PEn", text
  .align 4
;-----------------------------------------------------------------------------
;  system stack
;-----------------------------------------------------------------------------
$ifdef PE2_USED
STACKSIZE  .set  0x1000
  .section ".stack_pe2.bss", bss
  .align 4
  .ds  (STACKSIZE)
  .align 4
_PE2_stacktop:
$endif
;-----------------------------------------------------------------------------
;  section initialize table
;-----------------------------------------------------------------------------
  .section ".INIT_DSEC.const", const
  .align 4
  .dw  #__s.data,  #__e.data,  #__s.data.R

  .section ".INIT_BSEC.const", const
  .align 4
  .dw  #__s.bss,  #__e.bss

;-----------------------------------------------------------------------------
;  startup
;-----------------------------------------------------------------------------
  .section "RESET_PEn", text
  .align 4
  .public  _RESET_PEn

_RESET_PEn:
  ;-- Waiting CPU1 startup
  ;jarl  _SYNC_PE1, lp

  ;-- Initialization of the global pointer
  mov  #__gp_data, gp    ;  set gp register

  ;-- Initialization of the ep register
  mov  #__ep_data, ep    ;  set ep register

  ;-- Initialization of the RAM areas
  mov  #__s.INIT_DSEC.const, r6
  mov  #__e.INIT_DSEC.const, r7
  mov  #__s.INIT_BSEC.const, r8
  mov  #__e.INIT_BSEC.const, r9
  jarl32  __INITSCT_RH, lp  ;  call in library function

  ; enable FPU
$if 1                       ; disable this block when not using FPU
  stsr  5, r10, 0           ; r10 <- PSW
  movhi  0x0001, r0, r11
  or  r11, r10
  ldsr  r10, 5, 0           ; enable FPU

  movhi  0x0002, r0, r11
  ldsr  r11, 6, 0           ; initialize FPSR
  ldsr  r0, 7, 0            ; initialize FPEPC
$endif

stsr    0, r10, 2           ; get HTCFG0.PEID
$ifdef PE2_USED
    shr   16, r10
    cmp   2, r10
    bz      _PE2_Initialization             ; if HTCFG0.PEID is 2
$endif

;-------------  PEn Initialization
$ifdef PE2_USED
_PE2_Initialization:

  ;-- Initialization of the stack pointer
  mov  #_PE2_stacktop, sp    ;  set sp register

  ;-- Initialization of the interrupt base pointer
;$ifdef USE_TABLE_REFERENCE_METHOD
  .extern _g_vector_table_PE2
  mov    #_g_vector_table_PE2, r10
  ldsr  r10, 4, 1 ; INTBP
;$endif

  ;-- First set EBASE register address
  mov   #__sex_entry_PE2, r10
$endif

$ifndef USE_TABLE_REFERENCE_METHOD
  ;-- Set RINT bit for direct vector interupt and
  ;-- And Set RINT bit for reducing interrupt processing
  mov   0x0000001, r11        ; DV bit
  or    r11, r10
$endif
  ldsr  r10, 3, 1             ; EBASE
  ;-- then set 1 to PSW.EBV -> RBASE!=EBASE
  stsr  5, r10, 0             ; PSW
  ;-- then set 1 to PSW.CU0 and CU1
  mov   CUx_EBV, r11          ; CUx_EBV
  or    r11, r10
  ldsr  r10, 5, 0             ; PSW
  ; set various flags to PSW via FEPSW
  stsr  5, r10, 0             ; r10 <- PSW
  ldsr  r10, 3, 0             ; FEPSW <- r10
  mov  #_exit, lp             ; lp <- #_exit
  ; Jump to main()

;-----------------------------------------------
; jump to entry point of each PE main function
;-----------------------------------------------

stsr    0, r10, 2               ; get HTCFG0.PEID
$ifdef PE2_USED
    shr     16, r10
    cmp     2, r10
    bz      _INIT_PE2           ; if HTCFG0.PEID is 1
$endif

_exit:
  br  _exit      ;  end of program

_loop:
  br    _loop

$ifdef PE2_USED
_INIT_PE2:
  mov  #_main_PE2, r10
  ldsr  r10, 2, 0    ; FEPC <- #_main
  ; apply PSW and PC to start user mode
  feret
  br  _exit
$endif

;-------------------------------------------------------------------------------
;-------------  Start Section for exception table
$ifdef PE2_USED
.section "ex_entry_PE2", text
.public _ex_entry_PE2
.align 4
;-------------------------------------------------------------------------------
_ex_entry_PE2:
;----RESET
    .offset 0x0000
    jr __unused_isr

;----SYSERR
    .offset 0x0010
    jr __unused_isr

;----FETRAP
    .offset 0x0030
    jr __unused_isr

;----TRAP0
    .offset 0x0040
    .extern _vTRAP0_Handler
    jr _vTRAP0_Handler

;----TRAP1
    .offset 0x0050
    jr __unused_isr

;----RIEX
    .offset 0x0060
    jr __unused_isr

;----UCPOP
    .offset 0x0080
    jr __unused_isr

;----MIP_MDP
    .offset 0x0090
    jr __unused_isr

;----PIE
    .offset 0x00a0
    jr __unused_isr

;----MAE_MAEX
    .offset 0x00c0
    jr __unused_isr

;----FENMI
    .offset 0x00e0
    jr __unused_isr

;----FEINT
    .offset 0x00f0
    jr __unused_isr

;----EIINTn priority_0
    .offset 0x0100
$ifdef USE_TABLE_REFERENCE_METHOD
    jr __unused_isr
$else
    .extern _vIrq_Handler
    jr _vIrq_Handler
$endif

$endif
;-------------  End of exception table
;-------------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;    dummy section
;-----------------------------------------------------------------------------
    .section ".data", data
.L.dummy.data:
    .section ".bss", bss
.L.dummy.bss:
    .section ".const", const
.L.dummy.const:
    .section ".text", text
.L.dummy.text:
