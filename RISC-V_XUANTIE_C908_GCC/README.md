## Introduction
this is the demo project for the Alibaba Xuantie C908/C908V cpu to verify the backport.

For more advanced features of this CPU,
please refer to [this page](https://www.xrvm.com/soft-tools/os/RTOS?spm=xrvm.27140568.0.0.78f19b29Tt40XI)
and get the latest RTOS-SDK.

## Directory Structure

- Demo directory structure

```
RISC-V_XUANTIE_C908_GCC/
├── main.c                  # Main entry point
├── startup.S               # Startup assembly code
├── vectors.S               # Interrupt vector table
├── heap_4.c                # FreeRTOS heap implementation
├── FreeRTOSConfig.h        # FreeRTOS configuration
├── linker/                 # Linker scripts
├── app/                    # Kernel Unit Tests
└── bsp/
    ├── libc_freertos/      # Minimal C library (printf, sleep, etc.)
    ├── chip_riscv_dummy/   # Chip-level support
    │   ├── include/        #   - CSR definitions, SoC headers
    │   └── src/
    │       ├── drivers/    #   - Peripheral drivers (UART, GPIO, SPI, etc.)
    │       └── sys/        #   - System init, IRQ handling, clock
    ├── board_riscv_dummy/  # Board-level support (board init, UART config)
    └── csi/csi2/           # CSI2 driver interface and common utilities

```

- Port directory structure
```
GCC/RISC-V_XUANTIE_C908/
├── port.c              # FreeRTOS port implementation
├── cpu_task_sw.S       # Context switch assembly code
└── portmacro.h         # Port-specific macros and definitions
```

## Building

### Requirements
- GCC: [this page](https://www.xrvm.cn/community/download?versionId=4460156621967921152)

- QEMU at [this page](https://www.xrvm.cn/community/download?versionId=4468398114511851520)

### Files to Compile
To build a FreeRTOS application for XuanTie C908, you need to compile:

**FreeRTOS Kernel** - Core source files of the kernel
**Port** - Select this port, GCC/RISC-V_XUANTIE_C908/. This provides the C908-specific context switching and hardware abstraction.
**Demo** (optional) - Build RISC-V_XUANTIE_C908_GCC/ to run basic unit tests and verify your setup.

### Compiler Options

| Option | Description |
|--------|-------------|
| `-mcpu=c908v` | Target XuanTie C908 with float and vector extensions |
| `-mcpu=c908` | Target XuanTie C908 without float or vector extensions |
| `-mcmodel=medany` | Medium-any code model (required) |
| `-Os` | Optimize for size (recommended) |


**Note:** Choose either `-mcpu=c908v` or `-mcpu=c908` based on your hardware configuration.

### Global Macros
| Macro | Value | Description |
|-------|-------|-------------|
| `CONFIG_PLIC_BASE` | `0x08000000` | PLIC base address (required) |
| `CONFIG_CLINT_BASE` | `0x0c000000` | CLINT base address (required) |
| `CONFIG_BOARD_XIAOHUI_EVB` | `1` | Board selection (required) |
| `CONFIG_ARCH_INTERRUPTSTACK` | `8192` | Interrupt stack size in bytes (recommended) |
| `CONFIG_INIT_TASK_STACK_SIZE` | `4096` | Initial task stack size in bytes (recommended) |
| `configPrimaryCoreID` | `0` | Primary core ID (recommended) |
| `configNUMBER_OF_CORES` | `1` | Number of cores (1 ~ 4) |

For assembly files (.S), you must also define macro **\_\_ASSEMBLY\_\_**,  indicating assembly compilation

## Example Setup with CMAKE

### STEP-1: Setup the Environment
- Create an additional `Project` directory, with some symbolic links:
- then create a `CMakeLists.txt`
```
poon@DESKTOP-Q815LOG:~/opensource/freertos-git/Project$ ls -al
total 1992
drwxr-xr-x 4 poon poon    4096 Feb 11 15:36 .
drwxr-xr-x 8 poon poon    4096 Jan  8 13:10 ..
-rw-r--r-- 1 poon poon    7387 Feb 11 13:32 CMakeLists.txt
lrwxrwxrwx 1 poon poon      50 Jan  8 12:38 FreeRTOS-Kernel -> /home/poon/opensource/freertos-git/FreeRTOS-Kernel
-rw-r--r-- 1 poon poon     127 Feb 11 14:42 README.md
lrwxrwxrwx 1 poon poon      93 Feb 11 11:14 RISC-V_XUANTIE_C908_GCC -> /home/poon/opensource/freertos-git/FreeRTOS-Community-Supported-Demos/RISC-V_XUANTIE_C908_GCC
drwxr-xr-x 4 poon poon    4096 Feb 11 15:07 build
```

and create a `CMakelist.txt` in the project directory

```cmake
# File: ~/opensource/freertos-git/Project/CMakeLists.txt
cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_COMPILER   riscv64-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER riscv64-unknown-elf-g++)
set(CMAKE_AR           riscv64-unknown-elf-ar)

project(RISC_V_RV64_XUANTIE_XIAOHUI_Demo C CXX ASM)

# ========================================
# Compiler settings for RISC-V
# ========================================
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -D__ASSEMBLY__")

# ========================================
# Paths
# ========================================
set(DEMO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/RISC-V_XUANTIE_C908_GCC")
set(FREERTOS_KERNEL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS-Kernel")
set(CUSTOM_PORT_PATH "${FREERTOS_KERNEL_PATH}/portable/ThirdParty/Community-Supported-Ports/GCC/RISC-V_XUANTIE_C908")
set(LIBC_PATH "${DEMO_PATH}/bsp/libc_freertos")

# ========================================
# Common Include Paths
# ========================================
set(GLOBAL_INCLUDE_PATHS
    ${CUSTOM_PORT_PATH}/csi_core/include
    ${DEMO_PATH}/bsp/csi/csi2/include
    ${DEMO_PATH}/bsp/csi/csi2/include/drv
    ${DEMO_PATH}/bsp/chip_riscv_dummy/include
    ${DEMO_PATH}/bsp/chip_riscv_dummy/include/asm
    ${DEMO_PATH}/bsp/board_riscv_dummy/include
    ${CUSTOM_PORT_PATH}
    ${FREERTOS_KERNEL_PATH}/include
    ${LIBC_PATH}/include
)

# ========================================
# Common Compile Definitions
# ========================================
set(COMMON_DEFINITIONS
    CONFIG_PLIC_BASE=0x08000000
    CONFIG_ARCH_INTERRUPTSTACK=8192
    CLINT_BASE=0x0c000000
    CONFIG_CLINT_BASE=0x0c000000
    CONFIG_INIT_TASK_STACK_SIZE=4096
    CONFIG_BOARD_XIAOHUI_EVB=1
    configPrimaryCoreID=0
    configNUMBER_OF_CORES=1
    CONFIG_RISCV_FPU_ENABLED=1
    # CONFIG_RISCV_VECTOR_ENABLED=1
)

# ========================================
# freertos_config: FreeRTOS Configuration
# ========================================
if(EXISTS "${DEMO_PATH}/FreeRTOSConfig.h")
    set(FREERTOS_CONFIG_PATH ${DEMO_PATH})
else()
    set(FREERTOS_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    message(WARNING "FreeRTOSConfig.h not found in demo directory, looking in project root")
endif()

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM
    INTERFACE
        ${FREERTOS_CONFIG_PATH}
)

target_compile_definitions(freertos_config
    INTERFACE
        projCOVERAGE_TEST=0
)

# ========================================
# libc_freertos: Minimal C Library for FreeRTOS
# ========================================
file(GLOB LIBC_SOURCES
    "${LIBC_PATH}/*.c"
    # "${FREERTOS_KERNEL_PATH}/Source/portable/MemMang"
    "${FREERTOS_KERNEL_PATH}"
    "${CUSTOM_PORT_PATH}"
)

add_library(libc_freertos STATIC
    ${LIBC_SOURCES}
)

target_include_directories(libc_freertos
    PUBLIC
        ${GLOBAL_INCLUDE_PATHS}
        ${FREERTOS_CONFIG_PATH}
)

target_compile_definitions(libc_freertos
    PRIVATE
        ${COMMON_DEFINITIONS}
)

target_compile_options(libc_freertos
    PRIVATE
        -mcmodel=medany
        -g
        -Os
        -mcpu=c908
)

target_link_libraries(libc_freertos
    PRIVATE
        freertos_config
)


# ========================================
# freertos_kernel_port: Custom Port Configuration
# ========================================

set(FREERTOS_PORT "A_CUSTOM_PORT" CACHE STRING "")
add_library(freertos_kernel_port OBJECT)
file(GLOB PORT_SOURCES
    "${CUSTOM_PORT_PATH}/*.c"
    "${CUSTOM_PORT_PATH}/*.S"
    ${LIBC_SOURCES}
)

target_sources(freertos_kernel_port
    PRIVATE
        ${PORT_SOURCES}
)

target_compile_definitions(freertos_kernel_port
    PUBLIC
        ${COMMON_DEFINITIONS}
)

target_include_directories(freertos_kernel_port
    PRIVATE
        ${FREERTOS_KERNEL_PATH}/include
        ${CUSTOM_PORT_PATH}
        ${FREERTOS_CONFIG_PATH}
    PUBLIC
        ${GLOBAL_INCLUDE_PATHS}
)

add_library(freertos_kernel_port_headers INTERFACE)
target_include_directories(freertos_kernel_port_headers
    INTERFACE
        ${CUSTOM_PORT_PATH}
)

target_link_libraries(freertos_kernel_port
    PRIVATE
        freertos_config
        freertos_kernel_port_headers
        libc_freertos
)

target_compile_options(freertos_kernel_port
    PRIVATE
        -mcmodel=medany
        -g
        -Os
        -mcpu=c908v
)

# ========================================
# FreeRTOS Kernel Configuration
# ========================================

# Set heap implementation
set(FREERTOS_HEAP ${DEMO_PATH}/heap_4.c)

# add FreeRTOS-Kernel as subdirectory
add_subdirectory(${FREERTOS_KERNEL_PATH} FreeRTOS-Kernel)

# ========================================
# demo: User Applications
# ========================================

# Collect demo source files
file(GLOB DEMO_SOURCES
    "${DEMO_PATH}/*.c"
    "${DEMO_PATH}/app/*.c"
    "${DEMO_PATH}/app/Minimal/*.c"
    "${DEMO_PATH}/app/Template/*.c"
    "${DEMO_PATH}/*.S"
    "${DEMO_PATH}/bsp/chip_riscv_dummy/src/sys/*.c"
    "${DEMO_PATH}/bsp/chip_riscv_dummy/src/drivers/*.c"
    "${DEMO_PATH}/bsp/board_riscv_dummy/src/uart/board_uart.c"
)

# Remove specific files
list(REMOVE_ITEM DEMO_SOURCES
    "${DEMO_PATH}/app/Minimal/comtest_strings.c"
    "${DEMO_PATH}/app/Minimal/crhook.c"
    "${DEMO_PATH}/app/Minimal/comtest.c"
    "${DEMO_PATH}/app/Minimal/crflash.c"
    "${DEMO_PATH}/app/Minimal/flash.c"
    "${DEMO_PATH}/app/Minimal/flash_timer.c"
    "${DEMO_PATH}/app/Minimal/sp_flop.c"
)

add_executable(demo
    ${DEMO_SOURCES}
)

target_include_directories(demo
    PRIVATE
        ${DEMO_PATH}
        ${DEMO_PATH}/app
        ${DEMO_PATH}/app/include
        ${DEMO_PATH}/app/Template
        ${DEMO_PATH}/csi_core/include
        ${DEMO_PATH}
    PUBLIC
        ${GLOBAL_INCLUDE_PATHS}
)

target_compile_definitions(demo
    PUBLIC
        ${COMMON_DEFINITIONS}
)

target_compile_options(demo
    PRIVATE
        -mcmodel=medany
        -g
        -Os
        -mcpu=c908v
)

set(LINKER_SCRIPT "${DEMO_PATH}/linker/gcc_flash_xiaohui.ld")

target_link_options(demo
    PRIVATE
        -T${LINKER_SCRIPT}
        -nostartfiles
        -Wl,--gc-sections
        -Wl,-Map=${CMAKE_BINARY_DIR}/demo.map
)

target_link_libraries(demo
    PRIVATE
        freertos_kernel
        freertos_kernel_port
        libc_freertos
)

# ========================================
# Display build information
# ========================================
message(STATUS "================================================")
message(STATUS "FreeRTOS XuanTie RISC-V Demo Configuration:")
message(STATUS "  FreeRTOS Port: ${FREERTOS_PORT}")
message(STATUS "  Custom Port Path: ${CUSTOM_PORT_PATH}")
message(STATUS "  Demo Path: ${DEMO_PATH}")
message(STATUS "  LIBC Path: ${LIBC_PATH}")
message(STATUS "  FreeRTOS Config Path: ${FREERTOS_CONFIG_PATH}")
message(STATUS "  FreeRTOS Heap: ${FREERTOS_HEAP}")
message(STATUS "================================================")

```

### Step-2: Build Project
After setting up your toolchains, create a `build` directory in you `Project` directory, and build it
```sh
# Create build directory
mkdir build
cd build

# Configure and build
cmake .. && make -j$(nproc)
```
- if successful, you will see the executable file `demo` and other artifacts in `build` directory:
```sh
CMakeCache.txt  FreeRTOS-Kernel  cmake_install.cmake  demo.map
CMakeFiles      Makefile         demo                 liblibc_freertos.a
```

### Step-3: Verify with QEMU
```sh
qemu-system-riscv64 -machine xiaohui -nographic -kernel ./build/demo -cpu c908v -m 1G
```
- if successful, you will see the output
```
welcome to FreeRTOS
no Errors
no Errors
no Errors
```