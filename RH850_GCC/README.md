# RH850/U2C demo on QEMU, GCC

Demo for the community supported RH850 GCC port
(`FreeRTOS/Source/portable/ThirdParty/Community-Supported-Ports/GCC/RH850`)
on the `rh850-u2c` machine of qemu-system-rh850 (RH850/U2C, G4KH core).

- `qemu_rh850_u2c/blinky`: two tasks and a software timer send to a queue;
  the receiver prints each message.
- `qemu_rh850_u2c/full`: the Template TestRunner with every test it lists.
  It runs 30 s of virtual time and prints the check task status every 5 s.
- `bsp/`: reset code, vectors, faults, linker script, the U2C SoC
  definitions, the INTC, OSTM, RLIN3 and test-exit drivers and the board
  glue for the port.

## Tools

- GCC v850-elf 14.3:
  https://github.com/linumiz/rh850-gcc-toolchain/releases/tag/v1.0.0
- qemu-system-rh850 11.1.1:
  https://github.com/linumiz/qemu-rh850/releases/tag/v1.0.0
- picolibc with the v850 machine: https://github.com/linumiz/picolibc
  (tag rh850-freertos-v1, commit 1bd8ab39bac9606f2c3d540c2b0f4dd7c4ca1864),
  built by the Makefile with meson and ninja.
- GNU make.

## Build

    cd FreeRTOS/Demo/ThirdParty/Community-Supported-Demos/RH850_GCC/qemu_rh850_u2c
    make PICOLIBC_SRC=<picolibc checkout>

This builds `build/hard/blinky.elf` and `build/hard/full.elf`. Options:
- `FLOAT=soft`: `-msoft-float`, no FPU use by tasks (`build/soft`);
- `OPT=-O0`;
- `PICOLIBC_PREFIX=<dir>`: use an installed picolibc built for the same
  flags instead of building it.

## Run

    make run-blinky
    make run-full

The QEMU command line is:

    qemu-system-rh850 -M rh850-u2c,test-exit=on -icount shift=4,sleep=on -nographic -kernel build/hard/full.elf

The test-exit device ends QEMU with the program's exit code: 0 for pass.

## Expected output

blinky:

    Message received from software timer
    Message received from task
    ...
    blinky pass

full (hard float):

    full demo start (FPU on)
    No errors
    No errors
    No errors
    No errors
    No errors
    No errors
    full: 85 tasks, stack free/size (words) at the end:
    ...
    full pass

A failing test prints `full FAIL: <reason>` and QEMU exits with a
non-zero code.
