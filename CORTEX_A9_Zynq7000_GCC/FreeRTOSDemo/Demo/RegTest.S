    .text
    .arm

    /* Values to fill the registers. */
    /* Test 1 */
    .set REG0T1,  0xFF
    .set REG1T1,  0x11
    .set REG2T1,  0x22
    .set REG3T1,  0x33
    .set REG4T1,  0x44
    .set REG5T1,  0x55
    .set REG6T1,  0x66
    .set REG7T1,  0x77
    .set REG8T1,  0x88
    .set REG9T1,  0x99
    .set REG10T1, 0xAA
    .set REG11T1, 0xBB
    .set REG12T1, 0xCC
    .set REG14T1, 0xEE
    /* Test 2 */
    .set REG0T2,  0xFF00
    .set REG1T2,  0x1100
    .set REG2T2,  0x2200
    .set REG3T2,  0x3300
    .set REG4T2,  0x4400
    .set REG5T2,  0x5500
    .set REG6T2,  0x6600
    .set REG7T2,  0x7700
    .set REG8T2,  0x8800
    .set REG9T2,  0x9900
    .set REG10T2, 0xAA00
    .set REG11T2, 0xBB00
    .set REG12T2, 0xCC00
    .set REG14T2, 0xEE00
    /* Test 3 */
    .set REG0T3,  0xFF0000
    .set REG1T3,  0x110000
    .set REG2T3,  0x220000
    .set REG3T3,  0x330000
    .set REG4T3,  0x440000
    .set REG5T3,  0x550000
    .set REG6T3,  0x660000
    .set REG7T3,  0x770000
    .set REG8T3,  0x880000
    .set REG9T3,  0x990000
    .set REG10T3, 0xAA0000
    .set REG11T3, 0xBB0000
    .set REG12T3, 0xCC0000
    .set REG14T3, 0xEE0000
    /* Test 4 */
    .set REG0T4,  0xFF000000
    .set REG1T4,  0x11000000
    .set REG2T4,  0x22000000
    .set REG3T4,  0x33000000
    .set REG4T4,  0x44000000
    .set REG5T4,  0x55000000
    .set REG6T4,  0x66000000
    .set REG7T4,  0x77000000
    .set REG8T4,  0x88000000
    .set REG9T4,  0x99000000
    .set REG10T4, 0xAA000000
    .set REG11T4, 0xBB000000
    .set REG12T4, 0xCC000000
    .set REG14T4, 0xEE000000

    /* Task functions. */
    .global vRegisterTest1Task
    .global vRegisterTest2Task
    .global vRegisterTest3Task
    .global vRegisterTest4Task

    /* Loop counters. */
    .extern ulRegisterTest1Counter
    .extern ulRegisterTest2Counter
    .extern ulRegisterTest3Counter
    .extern ulRegisterTest4Counter

.macro testFILL_VFP_REGISTERS     

    /* Fill VFP registers with known values. */
    vmov d0, r0, r1
	vmov d1, r2, r3
	vmov d2, r4, r5
	vmov d3, r6, r7
	vmov d4, r8, r9
	vmov d5, r10, r11
	vmov d6, r12, r14
	vmov d7, r0, r1
	vmov d8, r2, r3
	vmov d9, r4, r5
	vmov d10, r6, r7
	vmov d11, r8, r9
	vmov d12, r10, r11
	vmov d13, r12, r14
	vmov d14, r0, r1
	vmov d15, r2, r3

    vmov d16, r0, r1
	vmov d17, r2, r3
	vmov d18, r4, r5
	vmov d19, r6, r7
	vmov d20, r8, r9
	vmov d21, r10, r11
	vmov d22, r12, r14
	vmov d23, r0, r1
	vmov d24, r2, r3
	vmov d25, r4, r5
	vmov d26, r6, r7
	vmov d27, r8, r9
	vmov d28, r10, r11
	vmov d29, r12, r14
	vmov d30, r0, r1
	vmov d31, r2, r3

.endm

.type vRegisterTest1Task, %function
vRegisterTest1Task:

    /* 1. Fill the registers stored as part of task context with known values. 
	 * 2. Force a context switch.
	 * 3. Verify that all the registers contain expected values.
	 * 4. If all the register contain expected values, increment ulRegisterTest1Counter.
	 */

    /* Fill the general purpose registers with known values. */
    mov r0,  #REG0T1
    mov r1,  #REG1T1
    mov r2,  #REG2T1
    mov r3,  #REG3T1
    mov r4,  #REG4T1
    mov r5,  #REG5T1
    mov r6,  #REG6T1
    mov r7,  #REG7T1
    mov r8,  #REG8T1
    mov r9,  #REG9T1
    mov r10, #REG10T1
    mov r11, #REG11T1
    mov r12, #REG12T1
    mov r14, #REG14T1

    testFILL_VFP_REGISTERS

    /* Test1 loop. */
1:
    /* Force a context-switch. */
    svc 0

    /* Check the general purpose registers. */
    cmp r0,  #REG0T1
    bne test1Error
    cmp r1,  #REG1T1
    bne test1Error
    cmp r2,  #REG2T1
    bne test1Error
    cmp r3,  #REG3T1
    bne test1Error
    cmp r4,  #REG4T1
    bne test1Error
    cmp r5,  #REG5T1
    bne test1Error
    cmp r6,  #REG6T1
    bne test1Error
    cmp r7,  #REG7T1
    bne test1Error
    cmp r8,  #REG8T1
    bne test1Error
    cmp r9,  #REG9T1
    bne test1Error
    cmp r10, #REG10T1
    bne test1Error
    cmp r11, #REG11T1
    bne test1Error
    cmp r12, #REG12T1
    bne test1Error
    cmp r14, #REG14T1
    bne test1Error

    /* Check FPU registers. */

    vmov r0, r1, d0
    cmp r0, #REG0T1
    bne test1Error
    cmp r1, #REG1T1
    bne test1Error

    vmov r2, r3, d1
    cmp r2, #REG2T1
    bne test1Error
    cmp r3, #REG3T1
    bne test1Error

    vmov r4, r5, d2
    cmp r4, #REG4T1
    bne test1Error
    cmp r5, #REG5T1
    bne test1Error

    vmov r6, r7, d3
    cmp r6, #REG6T1
    bne test1Error
    cmp r7, #REG7T1
    bne test1Error

    vmov r8, r9, d4
    cmp r8, #REG8T1
    bne test1Error
    cmp r9, #REG9T1
    bne test1Error

    vmov r10, r11, d5
    cmp r10, #REG10T1
    bne test1Error
    cmp r11, #REG11T1
    bne test1Error

    vmov r12, r14, d6
    cmp r12, #REG12T1
    bne test1Error
    cmp r14, #REG14T1
    bne test1Error

    vmov r0, r1, d7
    cmp r0, #REG0T1
    bne test1Error
    cmp r1, #REG1T1
    bne test1Error

    vmov r2, r3, d8
    cmp r2, #REG2T1
    bne test1Error
    cmp r3, #REG3T1
    bne test1Error

    vmov r4, r5, d9
    cmp r4, #REG4T1
    bne test1Error
    cmp r5, #REG5T1
    bne test1Error

    vmov r6, r7, d10
    cmp r6, #REG6T1
    bne test1Error
    cmp r7, #REG7T1
    bne test1Error

    vmov r8, r9, d11
    cmp r8, #REG8T1
    bne test1Error
    cmp r9, #REG9T1
    bne test1Error

    vmov r10, r11, d12
    cmp r10, #REG10T1
    bne test1Error
    cmp r11, #REG11T1
    bne test1Error

    vmov r12, r14, d13
    cmp r12, #REG12T1
    bne test1Error
    cmp r14, #REG14T1
    bne test1Error

    vmov r0, r1, d14
    cmp r0, #REG0T1
    bne test1Error
    cmp r1, #REG1T1
    bne test1Error

    vmov r2, r3, d15
    cmp r2, #REG2T1
    bne test1Error
    cmp r3, #REG3T1
    bne test1Error

    vmov r0, r1, d16
    cmp r0, #REG0T1
    bne test1Error
    cmp r1, #REG1T1
    bne test1Error

    vmov r2, r3, d17
    cmp r2, #REG2T1
    bne test1Error
    cmp r3, #REG3T1
    bne test1Error

    vmov r4, r5, d18
    cmp r4, #REG4T1
    bne test1Error
    cmp r5, #REG5T1
    bne test1Error

    vmov r6, r7, d19
    cmp r6, #REG6T1
    bne test1Error
    cmp r7, #REG7T1
    bne test1Error

    vmov r8, r9, d20
    cmp r8, #REG8T1
    bne test1Error
    cmp r9, #REG9T1
    bne test1Error

    vmov r10, r11, d21
    cmp r10, #REG10T1
    bne test1Error
    cmp r11, #REG11T1
    bne test1Error

    vmov r12, r14, d22
    cmp r12, #REG12T1
    bne test1Error
    cmp r14, #REG14T1
    bne test1Error

    vmov r0, r1, d23
    cmp r0, #REG0T1
    bne test1Error
    cmp r1, #REG1T1
    bne test1Error

    vmov r2, r3, d24
    cmp r2, #REG2T1
    bne test1Error
    cmp r3, #REG3T1
    bne test1Error

    vmov r4, r5, d25
    cmp r4, #REG4T1
    bne test1Error
    cmp r5, #REG5T1
    bne test1Error

    vmov r6, r7, d26
    cmp r6, #REG6T1
    bne test1Error
    cmp r7, #REG7T1
    bne test1Error

    vmov r8, r9, d27
    cmp r8, #REG8T1
    bne test1Error
    cmp r9, #REG9T1
    bne test1Error

    vmov r10, r11, d28
    cmp r10, #REG10T1
    bne test1Error
    cmp r11, #REG11T1
    bne test1Error

    vmov r12, r14, d29
    cmp r12, #REG12T1
    bne test1Error
    cmp r14, #REG14T1
    bne test1Error

    vmov r0, r1, d30
    cmp r0, #REG0T1
    bne test1Error
    cmp r1, #REG1T1
    bne test1Error

    vmov r2, r3, d31
    cmp r2, #REG2T1
    bne test1Error
    cmp r3, #REG3T1
    bne test1Error
    
    /* Increment the loop counter. */
    push {r0, r1}
    ldr r0, =ulRegisterTest1Counter
    ldr r1, [r0]
    add r1, r1 ,#1
    str r1, [r0]
    pop {r0, r1}

    b 1b

/* A register with a wrong value has been found. */
test1Error: b .
    
.type vRegisterTest2Task, %function
vRegisterTest2Task:

    /* Fill the general purpose registers with known values. */
    mov r0,  #REG0T2
    mov r1,  #REG1T2
    mov r2,  #REG2T2
    mov r3,  #REG3T2
    mov r4,  #REG4T2
    mov r5,  #REG5T2
    mov r6,  #REG6T2
    mov r7,  #REG7T2
    mov r8,  #REG8T2
    mov r9,  #REG9T2
    mov r10, #REG10T2
    mov r11, #REG11T2
    mov r12, #REG12T2
    mov r14, #REG14T2

    testFILL_VFP_REGISTERS

    /* Test2 loop. */
2:
    /* Force a context-switch. */
    svc 0
    
    /* Check the general purpose registers. */
    cmp r0,  #REG0T2
    bne test2Error
    cmp r1,  #REG1T2
    bne test2Error
    cmp r2,  #REG2T2
    bne test2Error
    cmp r3,  #REG3T2
    bne test2Error
    cmp r4,  #REG4T2
    bne test2Error
    cmp r5,  #REG5T2
    bne test2Error
    cmp r6,  #REG6T2
    bne test2Error
    cmp r7,  #REG7T2
    bne test2Error
    cmp r8,  #REG8T2
    bne test2Error
    cmp r9,  #REG9T2
    bne test2Error
    cmp r10, #REG10T2
    bne test2Error
    cmp r11, #REG11T2
    bne test2Error
    cmp r12, #REG12T2
    bne test2Error
    cmp r14, #REG14T2
    bne test2Error

    /* Check FPU registers. */

    vmov r0, r1, d0
    cmp r0, #REG0T2
    bne test2Error
    cmp r1, #REG1T2
    bne test2Error

    vmov r2, r3, d1
    cmp r2, #REG2T2
    bne test2Error
    cmp r3, #REG3T2
    bne test2Error

    vmov r4, r5, d2
    cmp r4, #REG4T2
    bne test2Error
    cmp r5, #REG5T2
    bne test2Error

    vmov r6, r7, d3
    cmp r6, #REG6T2
    bne test2Error
    cmp r7, #REG7T2
    bne test2Error

    vmov r8, r9, d4
    cmp r8, #REG8T2
    bne test2Error
    cmp r9, #REG9T2
    bne test2Error

    vmov r10, r11, d5
    cmp r10, #REG10T2
    bne test2Error
    cmp r11, #REG11T2
    bne test2Error

    vmov r12, r14, d6
    cmp r12, #REG12T2
    bne test2Error
    cmp r14, #REG14T2
    bne test2Error

    vmov r0, r1, d7
    cmp r0, #REG0T2
    bne test2Error
    cmp r1, #REG1T2
    bne test2Error

    vmov r2, r3, d8
    cmp r2, #REG2T2
    bne test2Error
    cmp r3, #REG3T2
    bne test2Error

    vmov r4, r5, d9
    cmp r4, #REG4T2
    bne test2Error
    cmp r5, #REG5T2
    bne test2Error

    vmov r6, r7, d10
    cmp r6, #REG6T2
    bne test2Error
    cmp r7, #REG7T2
    bne test2Error

    vmov r8, r9, d11
    cmp r8, #REG8T2
    bne test2Error
    cmp r9, #REG9T2
    bne test2Error

    vmov r10, r11, d12
    cmp r10, #REG10T2
    bne test2Error
    cmp r11, #REG11T2
    bne test2Error

    vmov r12, r14, d13
    cmp r12, #REG12T2
    bne test2Error
    cmp r14, #REG14T2
    bne test2Error

    vmov r0, r1, d14
    cmp r0, #REG0T2
    bne test2Error
    cmp r1, #REG1T2
    bne test2Error

    vmov r2, r3, d15
    cmp r2, #REG2T2
    bne test2Error
    cmp r3, #REG3T2
    bne test2Error

    vmov r0, r1, d16
    cmp r0, #REG0T2
    bne test2Error
    cmp r1, #REG1T2
    bne test2Error

    vmov r2, r3, d17
    cmp r2, #REG2T2
    bne test2Error
    cmp r3, #REG3T2
    bne test2Error

    vmov r4, r5, d18
    cmp r4, #REG4T2
    bne test2Error
    cmp r5, #REG5T2
    bne test2Error

    vmov r6, r7, d19
    cmp r6, #REG6T2
    bne test2Error
    cmp r7, #REG7T2
    bne test2Error

    vmov r8, r9, d20
    cmp r8, #REG8T2
    bne test2Error
    cmp r9, #REG9T2
    bne test2Error

    vmov r10, r11, d21
    cmp r10, #REG10T2
    bne test2Error
    cmp r11, #REG11T2
    bne test2Error

    vmov r12, r14, d22
    cmp r12, #REG12T2
    bne test2Error
    cmp r14, #REG14T2
    bne test2Error

    vmov r0, r1, d23
    cmp r0, #REG0T2
    bne test2Error
    cmp r1, #REG1T2
    bne test2Error

    vmov r2, r3, d24
    cmp r2, #REG2T2
    bne test2Error
    cmp r3, #REG3T2
    bne test2Error

    vmov r4, r5, d25
    cmp r4, #REG4T2
    bne test2Error
    cmp r5, #REG5T2
    bne test2Error

    vmov r6, r7, d26
    cmp r6, #REG6T2
    bne test2Error
    cmp r7, #REG7T2
    bne test2Error

    vmov r8, r9, d27
    cmp r8, #REG8T2
    bne test2Error
    cmp r9, #REG9T2
    bne test2Error

    vmov r10, r11, d28
    cmp r10, #REG10T2
    bne test2Error
    cmp r11, #REG11T2
    bne test2Error

    vmov r12, r14, d29
    cmp r12, #REG12T2
    bne test2Error
    cmp r14, #REG14T2
    bne test2Error

    vmov r0, r1, d30
    cmp r0, #REG0T2
    bne test2Error
    cmp r1, #REG1T2
    bne test2Error

    vmov r2, r3, d31
    cmp r2, #REG2T2
    bne test2Error
    cmp r3, #REG3T2
    bne test2Error

    /* Increment the loop counter. */
    push {r0, r1}
    ldr r0, =ulRegisterTest2Counter
    ldr r1, [r0]
    add r1, r1 ,#1
    str r1, [r0]
    pop {r0, r1}
    
    b 2b

test2Error: b .

.type vRegisterTest3Task, %function
vRegisterTest3Task:

    /* Fill the general purpose registers with known values. */
    mov r0,  #REG0T3
    mov r1,  #REG1T3
    mov r2,  #REG2T3
    mov r3,  #REG3T3
    mov r4,  #REG4T3
    mov r5,  #REG5T3
    mov r6,  #REG6T3
    mov r7,  #REG7T3
    mov r8,  #REG8T3
    mov r9,  #REG9T3
    mov r10, #REG10T3
    mov r11, #REG11T3
    mov r12, #REG12T3
    mov r14, #REG14T3

    testFILL_VFP_REGISTERS
    
    /* Test3 loop. */
3:
    /* Force a context-switch. */
    svc 0
    
    /* Check the general purpose registers. */
    cmp r0,  #REG0T3
    bne test3Error
    cmp r1,  #REG1T3
    bne test3Error
    cmp r2,  #REG2T3
    bne test3Error
    cmp r3,  #REG3T3
    bne test3Error
    cmp r4,  #REG4T3
    bne test3Error
    cmp r5,  #REG5T3
    bne test3Error
    cmp r6,  #REG6T3
    bne test3Error
    cmp r7,  #REG7T3
    bne test3Error
    cmp r8,  #REG8T3
    bne test3Error
    cmp r9,  #REG9T3
    bne test3Error
    cmp r10, #REG10T3
    bne test3Error
    cmp r11, #REG11T3
    bne test3Error
    cmp r12, #REG12T3
    bne test3Error
    cmp r14, #REG14T3
    bne test3Error

    /* Check FPU registers. */

    vmov r0, r1, d0
    cmp r0, #REG0T3
    bne test3Error
    cmp r1, #REG1T3
    bne test3Error

    vmov r2, r3, d1
    cmp r2, #REG2T3
    bne test3Error
    cmp r3, #REG3T3
    bne test3Error

    vmov r4, r5, d2
    cmp r4, #REG4T3
    bne test3Error
    cmp r5, #REG5T3
    bne test3Error

    vmov r6, r7, d3
    cmp r6, #REG6T3
    bne test3Error
    cmp r7, #REG7T3
    bne test3Error

    vmov r8, r9, d4
    cmp r8, #REG8T3
    bne test3Error
    cmp r9, #REG9T3
    bne test3Error

    vmov r10, r11, d5
    cmp r10, #REG10T3
    bne test3Error
    cmp r11, #REG11T3
    bne test3Error

    vmov r12, r14, d6
    cmp r12, #REG12T3
    bne test3Error
    cmp r14, #REG14T3
    bne test3Error

    vmov r0, r1, d7
    cmp r0, #REG0T3
    bne test3Error
    cmp r1, #REG1T3
    bne test3Error

    vmov r2, r3, d8
    cmp r2, #REG2T3
    bne test3Error
    cmp r3, #REG3T3
    bne test3Error

    vmov r4, r5, d9
    cmp r4, #REG4T3
    bne test3Error
    cmp r5, #REG5T3
    bne test3Error

    vmov r6, r7, d10
    cmp r6, #REG6T3
    bne test3Error
    cmp r7, #REG7T3
    bne test3Error

    vmov r8, r9, d11
    cmp r8, #REG8T3
    bne test3Error
    cmp r9, #REG9T3
    bne test3Error

    vmov r10, r11, d12
    cmp r10, #REG10T3
    bne test3Error
    cmp r11, #REG11T3
    bne test3Error

    vmov r12, r14, d13
    cmp r12, #REG12T3
    bne test3Error
    cmp r14, #REG14T3
    bne test3Error

    vmov r0, r1, d14
    cmp r0, #REG0T3
    bne test3Error
    cmp r1, #REG1T3
    bne test3Error

    vmov r2, r3, d15
    cmp r2, #REG2T3
    bne test3Error
    cmp r3, #REG3T3
    bne test3Error

    vmov r0, r1, d16
    cmp r0, #REG0T3
    bne test3Error
    cmp r1, #REG1T3
    bne test3Error

    vmov r2, r3, d17
    cmp r2, #REG2T3
    bne test3Error
    cmp r3, #REG3T3
    bne test3Error

    vmov r4, r5, d18
    cmp r4, #REG4T3
    bne test3Error
    cmp r5, #REG5T3
    bne test3Error

    vmov r6, r7, d19
    cmp r6, #REG6T3
    bne test3Error
    cmp r7, #REG7T3
    bne test3Error

    vmov r8, r9, d20
    cmp r8, #REG8T3
    bne test3Error
    cmp r9, #REG9T3
    bne test3Error

    vmov r10, r11, d21
    cmp r10, #REG10T3
    bne test3Error
    cmp r11, #REG11T3
    bne test3Error

    vmov r12, r14, d22
    cmp r12, #REG12T3
    bne test3Error
    cmp r14, #REG14T3
    bne test3Error

    vmov r0, r1, d23
    cmp r0, #REG0T3
    bne test3Error
    cmp r1, #REG1T3
    bne test3Error

    vmov r2, r3, d24
    cmp r2, #REG2T3
    bne test3Error
    cmp r3, #REG3T3
    bne test3Error

    vmov r4, r5, d25
    cmp r4, #REG4T3
    bne test3Error
    cmp r5, #REG5T3
    bne test3Error

    vmov r6, r7, d26
    cmp r6, #REG6T3
    bne test3Error
    cmp r7, #REG7T3
    bne test3Error

    vmov r8, r9, d27
    cmp r8, #REG8T3
    bne test3Error
    cmp r9, #REG9T3
    bne test3Error

    vmov r10, r11, d28
    cmp r10, #REG10T3
    bne test3Error
    cmp r11, #REG11T3
    bne test3Error

    vmov r12, r14, d29
    cmp r12, #REG12T3
    bne test3Error
    cmp r14, #REG14T3
    bne test3Error

    vmov r0, r1, d30
    cmp r0, #REG0T3
    bne test3Error
    cmp r1, #REG1T3
    bne test3Error

    vmov r2, r3, d31
    cmp r2, #REG2T3
    bne test3Error
    cmp r3, #REG3T3
    bne test3Error

    /* Increment the loop counter. */
    push {r0, r1}
    ldr r0, =ulRegisterTest3Counter
    ldr r1, [r0]
    add r1, r1 ,#1
    str r1, [r0]
    pop {r0, r1}
    
    b 3b

test3Error: b .

.type vRegisterTest4Task, %function
vRegisterTest4Task:

    /* Fill the general purpose registers with known values. */
    mov r0,  #REG0T4
    mov r1,  #REG1T4
    mov r2,  #REG2T4
    mov r3,  #REG3T4
    mov r4,  #REG4T4
    mov r5,  #REG5T4
    mov r6,  #REG6T4
    mov r7,  #REG7T4
    mov r8,  #REG8T4
    mov r9,  #REG9T4
    mov r10, #REG10T4
    mov r11, #REG11T4
    mov r12, #REG12T4
    mov r14, #REG14T4

    testFILL_VFP_REGISTERS

    /* Test4 loop. */
4:
    /* Force a context-switch. */
    svc 0
    
    /* Check the general purpose registers. */
    cmp r0,  #REG0T4
    bne test4Error
    cmp r1,  #REG1T4
    bne test4Error
    cmp r2,  #REG2T4
    bne test4Error
    cmp r3,  #REG3T4
    bne test4Error
    cmp r4,  #REG4T4
    bne test4Error
    cmp r5,  #REG5T4
    bne test4Error
    cmp r6,  #REG6T4
    bne test4Error
    cmp r7,  #REG7T4
    bne test4Error
    cmp r8,  #REG8T4
    bne test4Error
    cmp r9,  #REG9T4
    bne test4Error
    cmp r10, #REG10T4
    bne test4Error
    cmp r11, #REG11T4
    bne test4Error
    cmp r12, #REG12T4
    bne test4Error
    cmp r14, #REG14T4
    bne test4Error

    /* Check FPU registers. */

    vmov r0, r1, d0
    cmp r0, #REG0T4
    bne test4Error
    cmp r1, #REG1T4
    bne test4Error

    vmov r2, r3, d1
    cmp r2, #REG2T4
    bne test4Error
    cmp r3, #REG3T4
    bne test4Error

    vmov r4, r5, d2
    cmp r4, #REG4T4
    bne test4Error
    cmp r5, #REG5T4
    bne test4Error

    vmov r6, r7, d3
    cmp r6, #REG6T4
    bne test4Error
    cmp r7, #REG7T4
    bne test4Error

    vmov r8, r9, d4
    cmp r8, #REG8T4
    bne test4Error
    cmp r9, #REG9T4
    bne test4Error

    vmov r10, r11, d5
    cmp r10, #REG10T4
    bne test4Error
    cmp r11, #REG11T4
    bne test4Error

    vmov r12, r14, d6
    cmp r12, #REG12T4
    bne test4Error
    cmp r14, #REG14T4
    bne test4Error

    vmov r0, r1, d7
    cmp r0, #REG0T4
    bne test4Error
    cmp r1, #REG1T4
    bne test4Error

    vmov r2, r3, d8
    cmp r2, #REG2T4
    bne test4Error
    cmp r3, #REG3T4
    bne test4Error

    vmov r4, r5, d9
    cmp r4, #REG4T4
    bne test4Error
    cmp r5, #REG5T4
    bne test4Error

    vmov r6, r7, d10
    cmp r6, #REG6T4
    bne test4Error
    cmp r7, #REG7T4
    bne test4Error

    vmov r8, r9, d11
    cmp r8, #REG8T4
    bne test4Error
    cmp r9, #REG9T4
    bne test4Error

    vmov r10, r11, d12
    cmp r10, #REG10T4
    bne test4Error
    cmp r11, #REG11T4
    bne test4Error

    vmov r12, r14, d13
    cmp r12, #REG12T4
    bne test4Error
    cmp r14, #REG14T4
    bne test4Error

    vmov r0, r1, d14
    cmp r0, #REG0T4
    bne test4Error
    cmp r1, #REG1T4
    bne test4Error

    vmov r2, r3, d15
    cmp r2, #REG2T4
    bne test4Error
    cmp r3, #REG3T4
    bne test4Error

    vmov r0, r1, d16
    cmp r0, #REG0T4
    bne test4Error
    cmp r1, #REG1T4
    bne test4Error

    vmov r2, r3, d17
    cmp r2, #REG2T4
    bne test4Error
    cmp r3, #REG3T4
    bne test4Error

    vmov r4, r5, d18
    cmp r4, #REG4T4
    bne test4Error
    cmp r5, #REG5T4
    bne test4Error

    vmov r6, r7, d19
    cmp r6, #REG6T4
    bne test4Error
    cmp r7, #REG7T4
    bne test4Error

    vmov r8, r9, d20
    cmp r8, #REG8T4
    bne test4Error
    cmp r9, #REG9T4
    bne test4Error

    vmov r10, r11, d21
    cmp r10, #REG10T4
    bne test4Error
    cmp r11, #REG11T4
    bne test4Error

    vmov r12, r14, d22
    cmp r12, #REG12T4
    bne test4Error
    cmp r14, #REG14T4
    bne test4Error

    vmov r0, r1, d23
    cmp r0, #REG0T4
    bne test4Error
    cmp r1, #REG1T4
    bne test4Error

    vmov r2, r3, d24
    cmp r2, #REG2T4
    bne test4Error
    cmp r3, #REG3T4
    bne test4Error

    vmov r4, r5, d25
    cmp r4, #REG4T4
    bne test4Error
    cmp r5, #REG5T4
    bne test4Error

    vmov r6, r7, d26
    cmp r6, #REG6T4
    bne test4Error
    cmp r7, #REG7T4
    bne test4Error

    vmov r8, r9, d27
    cmp r8, #REG8T4
    bne test4Error
    cmp r9, #REG9T4
    bne test4Error

    vmov r10, r11, d28
    cmp r10, #REG10T4
    bne test4Error
    cmp r11, #REG11T4
    bne test4Error

    vmov r12, r14, d29
    cmp r12, #REG12T4
    bne test4Error
    cmp r14, #REG14T4
    bne test4Error

    vmov r0, r1, d30
    cmp r0, #REG0T4
    bne test4Error
    cmp r1, #REG1T4
    bne test4Error

    vmov r2, r3, d31
    cmp r2, #REG2T4
    bne test4Error
    cmp r3, #REG3T4
    bne test4Error

    /* Increment the loop counter. */
    push {r0, r1}
    ldr r0, =ulRegisterTest4Counter
    ldr r1, [r0]
    add r1, r1 ,#1
    str r1, [r0]
    pop {r0, r1}
    
    b 4b

test4Error: b .

.end