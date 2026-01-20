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
$ make -C build/gcc
```

For debug build:

```
$ make -C build/gcc DEBUG=1
```

To clean build artifacts:

```
$ make -C build/gcc clean
```

If the build was successful, the RTOSDemo.elf executable will be located in the build/gcc/output directory.

## How to run

For the RV32 build:

```
$ ./run.sh
```

## How to debug with gdb

Append -s and -S options to the previous qemu command.

- -s: enable to attach gdb to QEMU at port 1234
- -S: start and halted CPU (wait for attach from gdb)

It is recommended to use the 'debug build' so that gdb can automatically map symbols.
Run these commands after starting the QEMU with above options:

```
$ riscv64-unknown-elf-gdb build/gcc/output/RTOSDemo.elf
```

## Description

This demo supports `configENABLE_MPU=1` and `configUSE_MPU_WRAPPERS_V1=0` (mpu_wrapper_v2).
- Unprivileged Task protection is tested with "mpu_blinky.c"

This port is a practice project, so the code might not be perfectly structured.
Feedback and help are very welcome!

TODOs:
- More tests on MPU & FreeRTOS APIs
