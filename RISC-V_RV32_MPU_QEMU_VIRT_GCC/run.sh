#! /bin/bash
qemu-system-riscv32 \
    -smp 1 \
    -machine virt \
    -bios none \
    --kernel build/gcc/output/RTOSDemo.elf \
    -chardev stdio,id=con,mux=on \
    -serial chardev:con -mon chardev=con,mode=readline \
    -net none \
    -nographic \
    $@
