# Emulating generic RISC-V 32bit machine on QEMU

## Requirements

1. GNU RISC-V toolchains Tested on:
  * Self built from https://github.com/riscv-collab/riscv-gnu-toolchain/tree/357800bf2c5115ade5bc33f69af79c641db63cc8

1. qemu-riscv32-system. Tested on:
  * QEMU emulator version 8.2.2 (Debian 1:8.2.2+ds-0ubuntu1.10)

1. Linux OS. Tested on:
  * Ubuntu 24.04 LTS

## How to build

Add path of toolchain that is described above section, such as:

```
$ export PATH="/YOUR_PATH/riscv64-unknown-elf/bin:${PATH}"
```

For release build:

```
$ make
```

For debug build:

```
$ make DEBUG=1
```

To clean build artifacts:

```
$ make clean
```

If the build was successful, the RTOSDemo.elf executable will be located in the output directory.

## How to run

For the RV32 build:

```
$ qemu-system-riscv32 -nographic -machine virt -net none -chardev stdio,id=con,mux=on \
    -serial chardev:con -mon chardev=con,mode=readline -bios none -smp 4 \
    -s --kernel output/RTOSDemo.elf
```

## How to debug with gdb

Append -s and -S options to the previous qemu command.

- -s: enable to attach gdb to QEMU at port 1234
- -S: start and halted CPU (wait for attach from gdb)

It is recommended to use the 'debug build' so that gdb can automatically map symbols.
Run these commands after starting the QEMU with above options:

```
$ riscv64-unknown-elf-gdb output/RTOSDemo.elf
```

## Description

This demo supports `configNUMBER_OF_CORES` set to 1 for single-core or N for SMP.
- For single-core:
    - Tested with "test demo" and "blinky demo"
    - `configUSE_CORE_AFFINITY` should be set to 0
- For SMP:
    - Test with "blinky demo" with 2, 4 cores

This port is a practice project, so the code might not be perfectly structured.
Feedback and help are very welcome!

TODOs:
- More tests on SMP
- PICOLIBS support
- Reuse main stacks as ISR stacks for each core
- Cleanup & Refactoring
