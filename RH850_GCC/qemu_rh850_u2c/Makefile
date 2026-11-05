# Builds blinky and the full Template test suite for qemu_rh850_u2c.
# make [FLOAT=hard|soft] [OPT=-O2] [PICOLIBC_SRC=dir | PICOLIBC_PREFIX=dir]

FREERTOS_DIR ?= ../../../../..
KERNEL_DIR := $(FREERTOS_DIR)/Source
PORT_DIR := $(KERNEL_DIR)/portable/ThirdParty/Community-Supported-Ports/GCC/RH850
DEMO_DIR := $(FREERTOS_DIR)/Demo
BSP := ../bsp
CORE ?= G4KH

CROSS ?= v850-elf-
CC := $(CROSS)gcc
FLOAT ?= hard
OPT ?= -O2
BUILD ?= build/$(FLOAT)
QEMU ?= qemu-system-rh850
QEMU_ARGS ?= -M rh850-u2c,test-exit=on -icount shift=4,sleep=on

CPU_FLAGS := -mv850e3v5 -mrh850-abi
ifeq ($(FLOAT),soft)
CPU_FLAGS += -msoft-float
FPU := 0
else ifeq ($(FLOAT),hard)
FPU := 1
else
$(error FLOAT must be hard or soft)
endif

# picolibc: an install dir, or built here from a source checkout
ifdef PICOLIBC_PREFIX
LIBC := $(PICOLIBC_PREFIX)
LIBC_DEP :=
else
LIBC := $(abspath $(BUILD))/picolibc/install
LIBC_DEP := $(LIBC)/lib/libc.a
endif

CFLAGS := $(CPU_FLAGS) $(OPT) -g -Wall -Wextra -Werror -fno-common \
	-ffunction-sections -fdata-sections -MMD -MP \
	-DconfigENABLE_FPU=$(FPU) -DRH850_INTC_HANDLERS=8
INC := -I$(KERNEL_DIR)/include -I$(PORT_DIR) -I$(PORT_DIR)/core_specific/$(CORE) \
	-I$(BSP)/soc/common/include -I$(BSP)/soc/u2c \
	-I$(BSP)/drivers/intc -I$(BSP)/drivers/ostm -I$(BSP)/drivers/rlin3 -I$(BSP)/drivers/test_exit \
	-I$(BSP)/boards/qemu_rh850_u2c -isystem $(LIBC)/include
blinky_INC := -Iblinky -Iconfig $(INC)
full_INC := -Ifull -Iconfig -I$(DEMO_DIR)/Common/include $(INC)
LDFLAGS := $(CPU_FLAGS) -nostartfiles -T $(BSP)/soc/common/rh850.ld \
	-L$(BSP)/soc/u2c -L$(LIBC)/lib -Wl,--gc-sections
LIBS := $(LIBC)/lib/libc.a -lgcc $(LIBC)/lib/libc.a

.PHONY: all clean run-blinky run-full
all: $(BUILD)/blinky.elf $(BUILD)/full.elf

blinky_OBJS := \
	$(BUILD)/blinky/kernel/croutine.o \
	$(BUILD)/blinky/kernel/event_groups.o \
	$(BUILD)/blinky/kernel/list.o \
	$(BUILD)/blinky/kernel/queue.o \
	$(BUILD)/blinky/kernel/stream_buffer.o \
	$(BUILD)/blinky/kernel/tasks.o \
	$(BUILD)/blinky/kernel/timers.o \
	$(BUILD)/blinky/kernel/heap_4.o \
	$(BUILD)/blinky/port/port.o \
	$(BUILD)/blinky/port/portasm.o \
	$(BUILD)/blinky/config/freertos_hooks.o \
	$(BUILD)/blinky/config/libc_locks.o \
	$(BUILD)/blinky/bsp/crt0.o \
	$(BUILD)/blinky/bsp/vectors.o \
	$(BUILD)/blinky/bsp/fault_entry.o \
	$(BUILD)/blinky/bsp/irq_entry.o \
	$(BUILD)/blinky/bsp/fault.o \
	$(BUILD)/blinky/bsp/libc_glue.o \
	$(BUILD)/blinky/bsp/soc.o \
	$(BUILD)/blinky/bsp/rh850_intc.o \
	$(BUILD)/blinky/bsp/rh850_ostm.o \
	$(BUILD)/blinky/bsp/rh850_rlin3.o \
	$(BUILD)/blinky/bsp/test_exit.o \
	$(BUILD)/blinky/bsp/board.o \
	$(BUILD)/blinky/bsp/board_freertos.o \
	$(BUILD)/blinky/app/main.o \

$(BUILD)/blinky.elf: $(blinky_OBJS) $(LIBC_DEP)
	$(CC) $(LDFLAGS) -Wl,-Map=$(BUILD)/blinky.map -o $@ $(blinky_OBJS) $(LIBS)

$(BUILD)/blinky/kernel/croutine.o: $(KERNEL_DIR)/croutine.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/kernel/event_groups.o: $(KERNEL_DIR)/event_groups.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/kernel/list.o: $(KERNEL_DIR)/list.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/kernel/queue.o: $(KERNEL_DIR)/queue.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/kernel/stream_buffer.o: $(KERNEL_DIR)/stream_buffer.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/kernel/tasks.o: $(KERNEL_DIR)/tasks.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/kernel/timers.o: $(KERNEL_DIR)/timers.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/kernel/heap_4.o: $(KERNEL_DIR)/portable/MemMang/heap_4.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/port/port.o: $(PORT_DIR)/port.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/port/portasm.o: $(PORT_DIR)/portasm.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/config/freertos_hooks.o: config/freertos_hooks.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/config/libc_locks.o: config/libc_locks.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/crt0.o: $(BSP)/soc/common/crt0.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/vectors.o: $(BSP)/soc/common/vectors.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/fault_entry.o: $(BSP)/soc/common/fault_entry.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/irq_entry.o: $(BSP)/soc/common/irq_entry.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/fault.o: $(BSP)/soc/common/fault.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/libc_glue.o: $(BSP)/soc/common/libc_glue.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/soc.o: $(BSP)/soc/u2c/soc.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/rh850_intc.o: $(BSP)/drivers/intc/rh850_intc.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/rh850_ostm.o: $(BSP)/drivers/ostm/rh850_ostm.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/rh850_rlin3.o: $(BSP)/drivers/rlin3/rh850_rlin3.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/test_exit.o: $(BSP)/drivers/test_exit/test_exit.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/board.o: $(BSP)/boards/qemu_rh850_u2c/board.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/bsp/board_freertos.o: $(BSP)/boards/qemu_rh850_u2c/board_freertos.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@
$(BUILD)/blinky/app/main.o: blinky/main.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(blinky_INC) -c $< -o $@

-include $(blinky_OBJS:.o=.d)

full_OBJS := \
	$(BUILD)/full/kernel/croutine.o \
	$(BUILD)/full/kernel/event_groups.o \
	$(BUILD)/full/kernel/list.o \
	$(BUILD)/full/kernel/queue.o \
	$(BUILD)/full/kernel/stream_buffer.o \
	$(BUILD)/full/kernel/tasks.o \
	$(BUILD)/full/kernel/timers.o \
	$(BUILD)/full/kernel/heap_4.o \
	$(BUILD)/full/port/port.o \
	$(BUILD)/full/port/portasm.o \
	$(BUILD)/full/config/freertos_hooks.o \
	$(BUILD)/full/config/libc_locks.o \
	$(BUILD)/full/bsp/crt0.o \
	$(BUILD)/full/bsp/vectors.o \
	$(BUILD)/full/bsp/fault_entry.o \
	$(BUILD)/full/bsp/irq_entry.o \
	$(BUILD)/full/bsp/fault.o \
	$(BUILD)/full/bsp/libc_glue.o \
	$(BUILD)/full/bsp/soc.o \
	$(BUILD)/full/bsp/rh850_intc.o \
	$(BUILD)/full/bsp/rh850_ostm.o \
	$(BUILD)/full/bsp/rh850_rlin3.o \
	$(BUILD)/full/bsp/test_exit.o \
	$(BUILD)/full/bsp/board.o \
	$(BUILD)/full/bsp/board_freertos.o \
	$(BUILD)/full/app/main.o \
	$(BUILD)/full/app/RegTests.o \
	$(BUILD)/full/app/regtest_gcc.o \
	$(BUILD)/full/app/IntQueueTimer.o \
	$(BUILD)/full/app/TestRunner.o \
	$(BUILD)/full/minimal/AbortDelay.o \
	$(BUILD)/full/minimal/BlockQ.o \
	$(BUILD)/full/minimal/blocktim.o \
	$(BUILD)/full/minimal/countsem.o \
	$(BUILD)/full/minimal/death.o \
	$(BUILD)/full/minimal/dynamic.o \
	$(BUILD)/full/minimal/EventGroupsDemo.o \
	$(BUILD)/full/minimal/flop.o \
	$(BUILD)/full/minimal/GenQTest.o \
	$(BUILD)/full/minimal/integer.o \
	$(BUILD)/full/minimal/IntQueue.o \
	$(BUILD)/full/minimal/IntSemTest.o \
	$(BUILD)/full/minimal/MessageBufferAMP.o \
	$(BUILD)/full/minimal/MessageBufferDemo.o \
	$(BUILD)/full/minimal/PollQ.o \
	$(BUILD)/full/minimal/QPeek.o \
	$(BUILD)/full/minimal/QueueOverwrite.o \
	$(BUILD)/full/minimal/QueueSet.o \
	$(BUILD)/full/minimal/QueueSetPolling.o \
	$(BUILD)/full/minimal/recmutex.o \
	$(BUILD)/full/minimal/semtest.o \
	$(BUILD)/full/minimal/StaticAllocation.o \
	$(BUILD)/full/minimal/StreamBufferDemo.o \
	$(BUILD)/full/minimal/StreamBufferInterrupt.o \
	$(BUILD)/full/minimal/TaskNotify.o \
	$(BUILD)/full/minimal/TaskNotifyArray.o \
	$(BUILD)/full/minimal/TimerDemo.o \

$(BUILD)/full.elf: $(full_OBJS) $(LIBC_DEP)
	$(CC) $(LDFLAGS) -Wl,-Map=$(BUILD)/full.map -o $@ $(full_OBJS) $(LIBS)

$(BUILD)/full/kernel/croutine.o: $(KERNEL_DIR)/croutine.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/kernel/event_groups.o: $(KERNEL_DIR)/event_groups.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/kernel/list.o: $(KERNEL_DIR)/list.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/kernel/queue.o: $(KERNEL_DIR)/queue.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/kernel/stream_buffer.o: $(KERNEL_DIR)/stream_buffer.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/kernel/tasks.o: $(KERNEL_DIR)/tasks.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/kernel/timers.o: $(KERNEL_DIR)/timers.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/kernel/heap_4.o: $(KERNEL_DIR)/portable/MemMang/heap_4.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/port/port.o: $(PORT_DIR)/port.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/port/portasm.o: $(PORT_DIR)/portasm.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/config/freertos_hooks.o: config/freertos_hooks.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/config/libc_locks.o: config/libc_locks.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/crt0.o: $(BSP)/soc/common/crt0.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/vectors.o: $(BSP)/soc/common/vectors.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/fault_entry.o: $(BSP)/soc/common/fault_entry.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/irq_entry.o: $(BSP)/soc/common/irq_entry.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/fault.o: $(BSP)/soc/common/fault.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/libc_glue.o: $(BSP)/soc/common/libc_glue.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/soc.o: $(BSP)/soc/u2c/soc.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/rh850_intc.o: $(BSP)/drivers/intc/rh850_intc.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/rh850_ostm.o: $(BSP)/drivers/ostm/rh850_ostm.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/rh850_rlin3.o: $(BSP)/drivers/rlin3/rh850_rlin3.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/test_exit.o: $(BSP)/drivers/test_exit/test_exit.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/board.o: $(BSP)/boards/qemu_rh850_u2c/board.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/bsp/board_freertos.o: $(BSP)/boards/qemu_rh850_u2c/board_freertos.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/app/main.o: full/main.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/app/RegTests.o: full/RegTests.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/app/regtest_gcc.o: full/regtest_gcc.S | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/app/IntQueueTimer.o: full/IntQueueTimer.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/app/TestRunner.o: full/TestRunner.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/AbortDelay.o: $(DEMO_DIR)/Common/Minimal/AbortDelay.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/BlockQ.o: $(DEMO_DIR)/Common/Minimal/BlockQ.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/blocktim.o: $(DEMO_DIR)/Common/Minimal/blocktim.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/countsem.o: $(DEMO_DIR)/Common/Minimal/countsem.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/death.o: $(DEMO_DIR)/Common/Minimal/death.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/dynamic.o: $(DEMO_DIR)/Common/Minimal/dynamic.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/EventGroupsDemo.o: $(DEMO_DIR)/Common/Minimal/EventGroupsDemo.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/flop.o: $(DEMO_DIR)/Common/Minimal/flop.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/GenQTest.o: $(DEMO_DIR)/Common/Minimal/GenQTest.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/integer.o: $(DEMO_DIR)/Common/Minimal/integer.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/IntQueue.o: $(DEMO_DIR)/Common/Minimal/IntQueue.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/IntSemTest.o: $(DEMO_DIR)/Common/Minimal/IntSemTest.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/MessageBufferAMP.o: $(DEMO_DIR)/Common/Minimal/MessageBufferAMP.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/MessageBufferDemo.o: $(DEMO_DIR)/Common/Minimal/MessageBufferDemo.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/PollQ.o: $(DEMO_DIR)/Common/Minimal/PollQ.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/QPeek.o: $(DEMO_DIR)/Common/Minimal/QPeek.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/QueueOverwrite.o: $(DEMO_DIR)/Common/Minimal/QueueOverwrite.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/QueueSet.o: $(DEMO_DIR)/Common/Minimal/QueueSet.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/QueueSetPolling.o: $(DEMO_DIR)/Common/Minimal/QueueSetPolling.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/recmutex.o: $(DEMO_DIR)/Common/Minimal/recmutex.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/semtest.o: $(DEMO_DIR)/Common/Minimal/semtest.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/StaticAllocation.o: $(DEMO_DIR)/Common/Minimal/StaticAllocation.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/StreamBufferDemo.o: $(DEMO_DIR)/Common/Minimal/StreamBufferDemo.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/StreamBufferInterrupt.o: $(DEMO_DIR)/Common/Minimal/StreamBufferInterrupt.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/TaskNotify.o: $(DEMO_DIR)/Common/Minimal/TaskNotify.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/TaskNotifyArray.o: $(DEMO_DIR)/Common/Minimal/TaskNotifyArray.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@
$(BUILD)/full/minimal/TimerDemo.o: $(DEMO_DIR)/Common/Minimal/TimerDemo.c | $(LIBC_DEP)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(full_INC) -c $< -o $@

-include $(full_OBJS:.o=.d)

# picolibc for the same CPU flags; our crt0 is used, so no picocrt
comma := ,
empty :=
space := $(empty) $(empty)
LIBC_ARGS = $(subst $(space),$(comma)$(space),$(patsubst %,'%',$(CPU_FLAGS) $(1)))
LIBC_BUILD := $(abspath $(BUILD))/picolibc/build

ifndef PICOLIBC_PREFIX
$(LIBC_DEP):
	@test -n "$(PICOLIBC_SRC)" || { echo "Set PICOLIBC_SRC or PICOLIBC_PREFIX"; exit 1; }
	@mkdir -p $(BUILD)/picolibc
	@{ echo "[binaries]"; echo "c = '$(CC)'"; echo "ar = '$(CROSS)ar'"; \
	  echo "nm = '$(CROSS)nm'"; echo "strip = '$(CROSS)strip'"; \
	  echo "[host_machine]"; echo "system = 'none'"; echo "cpu_family = 'v850'"; \
	  echo "cpu = 'v850'"; echo "endian = 'little'"; \
	  echo "[properties]"; echo "skip_sanity_check = true"; \
	  echo "[built-in options]"; \
	  echo "c_args = [$(call LIBC_ARGS,-ffunction-sections -fdata-sections -fno-common)]"; \
	  echo "c_link_args = [$(call LIBC_ARGS,-nostdlib)]"; } > $(BUILD)/picolibc/cross.txt
	meson setup --cross-file $(BUILD)/picolibc/cross.txt --prefix $(LIBC) \
		--libdir lib --includedir include --buildtype=minsize -Dmultilib=false -Dpicocrt=false -Dsemihost=false -Dtests=false -Dspecsdir=none -Dthread-local-storage=false -Dsingle-thread=false -Dstdio-locking=true -Dformat-default=long-long \
		$(LIBC_BUILD) $(PICOLIBC_SRC)
	ninja -C $(LIBC_BUILD) -j 32
	meson install -C $(LIBC_BUILD) --quiet
endif

run-blinky: $(BUILD)/blinky.elf
	$(QEMU) $(QEMU_ARGS) -nographic -kernel $<

run-full: $(BUILD)/full.elf
	$(QEMU) $(QEMU_ARGS) -nographic -kernel $<

clean:
	rm -rf build
