;-------------------------------------------------------------------------------
;-- Module      = startup_PE1.asm
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

;-----------------------------------------------------------------------------
;  asm macros
;-----------------------------------------------------------------------------
  PE1_USED     .set 1
  ;PE2_USED     .set 1
  CUx_EBV      .set 0x00018000
  ; if using eiint as table reference method,
  ; enable next line's macro.
  ; USE_TABLE_REFERENCE_METHOD .set 0
;-------------------------------------------------------------------------------
;-------------  Public functions
;-------------------------------------------------------------------------------

;-----------------------------------------------------------------------------
;  system stack
;-----------------------------------------------------------------------------
$ifdef PE2_USED
MEVSIZE  .set  0x4
  .section ".mev_address.bss", bss
  .align 4
  .ds  (MEVSIZE)
  .align 4
_mevtop:
$endif

STACKSIZE  .set  0x1000
  .section ".stack.bss", bss
  .align 4
  .ds  (STACKSIZE)
  .align 4
_stacktop:

;-----------------------------------------------------------------------------
;  section initialize table
;-----------------------------------------------------------------------------
  .section ".INIT_DSEC.const", const
  .align 4
  .dw      #__s.data,  #__e.data,  #__s.data.R

  .section ".INIT_BSEC.const", const
  .align 4
  .dw  #__s.bss,  #__e.bss

;-------------------------------------------------------------------------------
;-------------- Sync PE0 Routine
;-------------------------------------------------------------------------------
;  .extern _SYNC_PE0
;_SYNC_PE0:
;      mov     __s.mev_address.bss, r20
;      set1    1, 0x0[r20]
;Lock: ldl.w   [r20], r21
;      cmp     r0, r21
;      bnz     Lock_wait
;      mov     1, r21
;      stc.w   r21, [r20]
;      cmp     r0, r21
;      bnz     Lock_success
;Lock_wait:
;      snooze
;      br      Lock
;Lock_success:
;      jmp     [lp]

;-----------------------------------------------------------------------------
;  startup
;-----------------------------------------------------------------------------
  .section "RESET_PE1", text
  .public  _RESET_PE1
  .align 4
_RESET_PE1:
  ;-- Initialization of the stack pointer
  mov  #_stacktop, sp    ;  set sp register

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
$if 1                     ; disable this block when not using FPU
  stsr  5, r10, 0         ; r10 <- PSW
  movhi  0x0001, r0, r11
  or  r11, r10
  ldsr  r10, 5, 0         ; enable FPU

  movhi  0x0002, r0, r11
  ldsr  r11, 6, 0         ; initialize FPSR
  ldsr  r0, 7, 0          ; initialize FPEPC
$endif

;-------------  PE1 Initialization
  ;-- Initialization of the interrupt base pointer
;$ifdef USE_TABLE_REFERENCE_METHOD
  .extern _g_vector_table_PE1
  mov   #_g_vector_table_PE1, r10
  ldsr  r10, 4, 1 ; INTBP
;$endif

  ;-- First set EBASE register address
  mov   #__sex_entry_PE1, r10
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
  mov  #_main, r10
  ldsr  r10, 2, 0             ; FEPC <- #_main
  ; apply PSW and PC to start user mode
  feret

_exit:
  br  _exit      ;  end of program

;-------------------------------------------------------------------------------
;-------------  Interrupt service routine of unused interrupts
;-------------------------------------------------------------------------------

  .extern  __unused_isr
__unused_isr:
  br    __unused_isr

;-------------------------------------------------------------------------------
;-------------  Start Section for exception table
;-------------------------------------------------------------------------------
  .section "ex_entry_PE1", const
  .public _ex_entry_PE1
  .align 512
_ex_entry_PE1:
$ifdef PE1_USED
;----RESET
    .offset 0x0000
    jr _RESET

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
    .extern _vIrq_Handler
    jr _vIrq_Handler

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
