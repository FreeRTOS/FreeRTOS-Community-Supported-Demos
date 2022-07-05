#/*
# * FreeRTOS V202112.00
# * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
# *
# * Permission is hereby granted, free of charge, to any person obtaining a copy of
# * this software and associated documentation files (the "Software"), to deal in
# * the Software without restriction, including without limitation the rights to
# * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# * the Software, and to permit persons to whom the Software is furnished to do so,
# * subject to the following conditions:
# *
# * The above copyright notice and this permission notice shall be included in all
# * copies or substantial portions of the Software.
# *
# * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# *
# * https://www.FreeRTOS.org
# * https://aws.amazon.com/freertos
# *
# * 1 tab == 4 spaces!
# */

PART=TM4C123GH6PM
ROOT = ../

include  ${ROOT}/makedefs 

#VERBOSE = 1

KERNEL_PATH := ../../../../../Source
PORT_PATH := $(KERNEL_PATH)/portable/GCC/ARM_CM4F
HEAP_MEM_PATH := ${KERNEL_PATH}/portable/MemMang
DEMO_COMMON_PATH := ../../../../Common
DRIVER_LIB_PATH := ../driverlib


WARNINGS = -Wall -Wunused -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wbad-function-cast -Wcast-align -Wsign-compare -Wshadow -Wpointer-arith
INCLUDE = -I . -I $(KERNEL_PATH)/include -I $(PORT_PATH) -I ${ROOT} -I ${DRIVER_LIB_PATH}

CFLAGS += ${WARNINGS} ${INCLUDE} 

VPATH=${ROOT}:${PORT_PATH}:${HEAP_MEM_PATH}:${KERNEL_PATH}:${DRIVER_LIB_PATH}:./

OBJS = \
${COMPILER}/main.o \
${COMPILER}/startup_gcc.o \
${COMPILER}/sysctl.o \
${COMPILER}/gpio.o \
${COMPILER}/uart.o \
${COMPILER}/interrupt.o \
${COMPILER}/tasks.o \
${COMPILER}/queue.o \
${COMPILER}/list.o \
${COMPILER}/heap_1.o \
${COMPILER}/port.o

all: ${COMPILER}
all: ${COMPILER}/blinky.axf 

clean:
	@rm -rf ${COMPILER}

${COMPILER}:
	@echo ${CFLAGS}
	@mkdir -p ${COMPILER}

${COMPILER}/blinky.axf: ${OBJS}
SCATTERgcc_blinky = TM4C123GH6PM.ld
ENTRY_blinky = ResetISR

-include ${wildcard ${COMPILER}/*.d} __dummy__
