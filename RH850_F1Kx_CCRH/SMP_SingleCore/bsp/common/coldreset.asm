;-------------------------------------------------------------------------------
;-- Module      = coldreset.asm
;-- Version     = 1.0.0
;--               manually created
;--
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
;--              Device:         U2Ax
;--              IDE:            CCRH V2.04.00 or later
;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
;-- Revision Control History:
;-- 1.0.0 :   20th-Feb-2023    : Initial Version
;-------------------------------------------------------------------------------

;-----------------------------------------------------------------------------
; Macro
;-----------------------------------------------------------------------------
  RESET_ENABLE .set 1
  PE1_USED     .set 1

  DEVICE_F1KH  .set 1
  ;DEVICE_F1KM  .set 1

$ifdef DEVICE_F1KH
  ;PE2_USED     .set 1

  ; local ram address
  LOCAL_RAM_CPU1_ADDR         .set 0xFEBD0000     ; LOCAL RAM(CPU1) start address
  LOCAL_RAM_CPU1_END          .set 0xFEBFFFFF     ; LOCAL RAM(CPU1) end address

  $ifdef PE2_USED
  LOCAL_RAM_CPU2_ADDR         .set 0xFE9D0000     ; LOCAL RAM(CPU2) start address
  LOCAL_RAM_CPU2_END          .set 0xFE9FFFFF     ; LOCAL RAM(CPU2) end address
  $endif

  GLOBAL_RAM_ADDR             .set 0xFEFB8000     ; GLOBAL RAM start address
  GLOBAL_RAM_END              .set 0xFEFFFFFF     ; GLOBAL RAM end address

  MEV_ADDR                    .set 0xFFFEEC04  ; G0MEV0

$endif

$ifdef DEVICE_F1KM
  ; local ram address
  LOCAL_RAM_CPU1_ADDR         .set 0xFEBC0000     ; LOCAL RAM(CPU1) start address
  LOCAL_RAM_CPU1_END          .set 0xFEBFFFFF     ; LOCAL RAM(CPU1) end address
$endif

  EIPC  .set 0
  EIPSW .set 1
  EIIC  .set 13

  USE_TABLE_REFERENCE_METHOD .set 1
;-------------------------------------------------------------------------------
;-------------  Public functions
;-------------------------------------------------------------------------------
  .extern _RESET_PE1
  .extern _RESET_PEn
  .extern Irq_Handler
;-------------------------------------------------------------------------------
;-------------  Common Startup Routine
;-------------------------------------------------------------------------------
  .section "STARTUP_CODE", text
  .public    _RESET
  .align 4

_RESET:
  ; PE0 set Boot Control Register for all PE
  stsr  0,    r10, 2
  shr   16, r10
  cmp   1,  r10 ; PE1
  bne   aa
  synci
  bb: jr   _BOOTCTRL_SETTING
  aa: jr   _PE_RESET

;-----------------------------------------------------------------------------
;   PEn activation
;-----------------------------------------------------------------------------
_BOOTCTRL_SETTING:
;$if 0
    ; FFC58000
     ld.w   0xFFC58000[r0], r10     ; get BOOTCTR
     mov    1, r3                   ; enabled PE0 by default, disable all other PEn
     st.w   r11, 0xFFC58000[r0]     ; set BOOTCTRL

    stsr    0, r10, 2               ; get HTCFG0.PEID
    shr    16, r10
    cmp     1, r10
    bz      _BOOTCTRL_SETTING_PE1   ; if HTCFG0.PEID is 1

_BOOTCTRL_SETTING_PE1:
$ifdef PE2_USED
    ld.w    0xFFC58000[r0], r10     ; get BOOTCTRL
    ori     2, r10, r11             ; set 1 in BOOTCTRL.BC1 for enabled PE1
    st.w    r11, 0xFFC58000[r0]     ; set BOOTCTRL
    mov     0x0, r2                 ; wait for 100us(0x9c40(40,000)count)
    br     .L.start_PE2.1
.L.start_PE2.0:
    add     0x1, r2
.L.start_PE2.1:
    andi    0xffff, r2, tp
    ori     0x9c40, r0, r6
    cmp     r6, tp
    blt    .L.start_PE2.0
$endif
;$endif
    nop

_PE_RESET:
    ;--------------------------------
    ; Register Initialization
    ;--------------------------------

    ;- General purpose register
    $nowarning
    mov     r0, r1          ; r1  Assembler reserved register
    $warning
    mov     r0, r2          ; r2  Register for address and data variables
    mov     r0, r3          ; r3  Stack pointer(SP)
    mov     r0, r4          ; r4  Global pointer(GP)
    mov     r0, r5          ; r5  Text pointer(TP)
    mov     r0, r6          ; r6  Register for addresses and data variables
    mov     r0, r7          ; r7  Register for addresses and data variables
    mov     r0, r8          ; r8  Register for addresses and data variables
    mov     r0, r9          ; r9  Register for addresses and data variables
    mov     r0, r10         ; r10 Register for addresses and data variables
    mov     r0, r11         ; r11 Register for addresses and data variables
    mov     r0, r12         ; r12 Register for addresses and data variables
    mov     r0, r13         ; r13 Register for addresses and data variables
    mov     r0, r14         ; r14 Register for addresses and data variables
    mov     r0, r15         ; r15 Register for addresses and data variables
    mov     r0, r16         ; r16 Register for addresses and data variables
    mov     r0, r17         ; r17 Register for addresses and data variables
    mov     r0, r18         ; r18 Register for addresses and data variables
    mov     r0, r19         ; r19 Register for addresses and data variables
    mov     r0, r20         ; r20 Register for addresses and data variables
    mov     r0, r21         ; r21 Register for addresses and data variables
    mov     r0, r22         ; r22 Register for addresses and data variables
    mov     r0, r23         ; r23 Register for addresses and data variables
    mov     r0, r24         ; r24 Register for addresses and data variables
    mov     r0, r25         ; r25 Register for addresses and data variables
    mov     r0, r26         ; r26 Register for addresses and data variables
    mov     r0, r27         ; r27 Register for addresses and data variables
    mov     r0, r28         ; r28 Register for addresses and data variables
    mov     r0, r29         ; r29 Register for addresses and data variables
    mov     r0, r30         ; r30 Element pointer(EP)
    mov     r0, r31         ; r31 Link pointer(LP)

    ;- Basic system register
    ldsr    r0,  0, 0       ; SR0,0  EIPC
    ldsr    r0,  2, 0       ; SR2,0  FEPC
    ldsr    r0, 16, 0       ; SR16,0 CTPC
    ldsr    r0, 28, 0       ; SR28,0 EIWR
    ldsr    r0, 29, 0       ; SR29,0 FEWR
    ldsr    r0,  3, 1       ; SR3,1  EBASE
    ldsr    r0,  4, 1       ; SR4,1  INTBP
    ldsr    r0,  6, 2       ; SR6,2  MEA
    ldsr    r0,  8, 2       ; SR8,2  MEI

    ;- FPU system register
    mov     0x00010020, r10 ; set 1 in PSW.CU0 for writing FPU Function Register
                            ; set 1 in PSW.ID for prohibiting EI-level interrupt
    ldsr    r10, 5, 0       ; SR5,0  PSW

    mov     0x00220000, r10 ; set 1 in FPSR.FS
    ldsr    r10, 6, 0       ; SR6,0  FPSR
    ldsr    r0,  7, 0       ; SR7,0  FPEPC
    ldsr    r0,  8, 0       ; SR8,0  FPST
    ldsr    r0,  9, 0       ; SR9,0  FPCC

    ;--------------------------------
    ; jump to entry point of each PE
    ;--------------------------------

    stsr    0, r10, 2               ; get HTCFG0.PEID
    shr     16, r10
    cmp     1, r10
    bz      __start_PE1             ; if HTCFG0.PEID is 1
$ifdef PE2_USED
    cmp     2, r10
    bz      __start_PE2             ; if HTCFG0.PEID is 2
$endif  ; PE2_USED
;-----------------------------------------------------------------------------
;   __start_PE1
;-----------------------------------------------------------------------------
__start_PE1:
$ifdef PE2_USED
    st.w    r0, MEV_ADDR
$endif
    jarl    _hdwinit_PE1, lp        ; initialize hardware
    jr32    _RESET_PE1              ; jump to RESET PE1 to start PE1 app

$ifdef PE2_USED
  ; Jump to PEn Startup Routine
    cmp     2, r10
    bz      __start_PE2             ; if HTCFG0.PEID is 2
$endif
;-----------------------------------------------------------------------------
;   __start_PE1
;-----------------------------------------------------------------------------
$ifdef PE2_USED
__start_PE2:
    jarl    _hdwinit_PE2, lp        ; initialize hardware
    jr32    _RESET_PEn              ; jump to RESET PE1
$endif  ; PE2_USED

;-----------------------------------------------------------------------------
;   _hdwinit_PE1
;-----------------------------------------------------------------------------
  .section "STARTUP_CODE", text
  .align 4

_hdwinit_PE1:
    mov     lp, r14                 ; save return address

    ; clear Local RAM(CPU1)
    mov     LOCAL_RAM_CPU1_ADDR, r6
    mov     LOCAL_RAM_CPU1_END, r7
    jarl    _zeroclr4, lp

$ifdef PE2_USED
    ; finish the clock gearup seaquence
    mov     MEV_ADDR, r10
    set1    4, [r10]

.L.hdwinit_PE1.0:

    mov     MEV_ADDR, r10
    set1    0, [r10]                ; Bit0 indicate PE1 wait for PEx
$endif
; TODO: Check multicores sync up
;$ifdef PE2_USED
    ; wait for PE2
;.L.hdwinit_PE1.1:
;    tst1    1, [r10]                ; Bit1 indicate PE2 wait for PE1
;    bnz    .L.hdwinit_PE1.2
;    snooze
;    br     .L.hdwinit_PE1.1
;$endif  ; PE2_USED

;.L.hdwinit_PE1.2:
    mov     r14, lp
    jmp     [lp]

;-----------------------------------------------------------------------------
;   _hdwinit_PE1
;-----------------------------------------------------------------------------
$ifdef PE2_USED
  .section "STARTUP_CODE", text
  .align 4

_hdwinit_PE2:
    mov     lp, r14                 ; save return address
    ; clear Local RAM(CPU2)
    mov     LOCAL_RAM_CPU2_ADDR, r6
    mov     LOCAL_RAM_CPU2_END, r7
    jarl    _zeroclr4, lp

    ; wait for PE0
    ; mov     MEV_ADDR, r10

;.L.hdwinit_PE2.0:
;    tst1    4, [r10]                ; Check the value of bit 4 of MEV_ADDR
;    bnz    .L.hdwinit_PE2.1
;    snooze
;    br     .L.hdwinit_PE2.0

;.L.hdwinit_PE2.1:
;    mov     MEV_ADDR, r10
;    set1    1, [r10]                ; Bit1 indicate PE2 wait for PEx

    ; wait for PE1
;.L.hdwinit_PE2.2:
;    tst1    0, [r10]                ; Bit0 indicate PE1 wait for PE2
;    bnz    .L.hdwinit_PE2.3
;    snooze
;    br     .L.hdwinit_PE2.2

;.L.hdwinit_PE2.3:
    mov     r14, lp
    jmp     [lp]
$endif
;-----------------------------------------------------------------------------
;   zeroclr4
;-----------------------------------------------------------------------------
    .section "STARTUP_CODE", text
    .align 4
_zeroclr4:
    br      .L.zeroclr4.2
.L.zeroclr4.1:
    st.w    r0, [r6]
    add     4, r6
.L.zeroclr4.2:
    cmp     r6, r7
    bh      .L.zeroclr4.1
    jmp	[lp]

;-------------------------------------------------------------------------------
;-------------  Add section ".RESET_PE0" to your linker command file
;-------------  at address 0x0000
;-------------------------------------------------------------------------------
  .section "RESET", text
  .align 4
;-------------------------------------------------------------------------------
;-------------  Initializing of interrupt vector table
;-------------  Please don't modify this section
;-------------------------------------------------------------------------------
  .public _RESET_VECTOR
  .offset 0x0000
_RESET_VECTOR:
$ifdef RESET_ENABLE
  .extern _RESET
   jr _RESET
$else
  jr __unused_isr
$endif

$ifdef PE2_USED
  .section "RESET_PE2", text
  .align 4
;-------------------------------------------------------------------------------
;-------------  Initializing of interrupt vector table
;-------------  Please don't modify this section
;-------------------------------------------------------------------------------
  .public _RESET_VECTOR_PE2
  .offset 0x0000
_RESET_VECTOR_PE2:
$ifdef RESET_ENABLE
  .extern _RESET
  jr32 _RESET
$else
  jr __unused_isr
$endif

$endif
