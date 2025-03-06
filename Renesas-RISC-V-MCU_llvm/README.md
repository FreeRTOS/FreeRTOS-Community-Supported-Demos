# Renesas RISC-V MCU FreeRTOS port

## Hardware Page

https://www.renesas.com/en/products/microcontrollers-microprocessors/risc-v/r9a02g021-ultra-low-power-48mhz-mcu-renesas-risc-v-cpu-core

## How to setup the tool-chain

- Download Renesas E2 Studio IDE
- Import the files contained in the `src` folder of this repo
- Exclude from the build:
	- `src/smc_gen/general/r_cg_vect_table.c`
	- all except one of the files in `FreeRTOS/Source/Portable/MemMang`
		- `heap2.c` is suggested
- Add to the default includes of the compiler:
	- `src/Demo/Common`
	- `src/Demo`
	- `FreeRTOS/FreeRTOS/Source/Portable/GCC/RISC-V` 
	- `FreeRTOS/FreeRTOS/Source/Portable/GCC/RISC-V/chip_specific_extensions/RISCV_MTIME_CLINT_no_extensions` 
	- `FreeRTOS/FreeRTOS/Source/include` 
	- **NOTE**: The actual compiler from the Renesas toolchain is LLVM, but since the GCC port files work perfectly they are used here
- Add to the default includes of the assembler:
	- `FreeRTOS/FreeRTOS/Source/Portable/GCC/RISC-V`
- (Enable the machine timer from the Smart Configurator)

## How to build and run the project

- Inside `src/Demo/FreeRTOSConfig.h` you can find some `#define configSTART_*_TESTS 0`
	- Choose the test you would like to run and change from 0 to 1 the number of the related defines
- Press the Run button

## Print might not print full words

Print on UART has been implemented just for testing purposes. It is not perfect: sometimes it misses the print of some characters. For testing purposes it is more than enough.

## Memory size related problems

> The size of the memory in this MCU is limited. You cannot run multiple tests at once or single tests might not fit in the memory. Here are presented various errors you might encounter and their resultion, if any.

### Error while linking

If the linker cannot fit the program in the memory then you might want to change stack and heap sizes, remove functions, ... flipping bits of the defines the config file of FreeRTOS.

### Malloc error while executing

You need to expand the size of the heap, if possible.

### Stack too small while executing

You need to expand the size of the heap, if possible. 

In the case of the interrupt stack, remember that there is a specific configuration entry called `configISR_STACK_SIZE_WORDS` in the config file of FreeRTOS.

