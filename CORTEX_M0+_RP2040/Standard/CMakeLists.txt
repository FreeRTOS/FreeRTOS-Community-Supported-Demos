cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Pull in FreeRTOS
include(FreeRTOS_Kernel_import.cmake)

if (NOT FREERTOS_DEMO_PATH)
        if (DEFINED ENV{FREERTOS_DEMO_PATH})
                set(FREERTOS_DEMO_PATH $ENV{FREERTOS_DEMO_PATH})
                message("Using FREERTOS_DEMO_PATH from environment ('${FREERTOS_DEMO_PATH}')")
        elseif(EXISTS ${FREERTOS_KERNEL_PATH}/../Demo)
                set(FREERTOS_DEMO_PATH ${FREERTOS_KERNEL_PATH}/../Demo)
        else ()
                message(FATAL_ERROR "FreeRTOS demo path was not specified. Please set FREERTOS_DEMO_PATH.")
        endif ()
endif ()

project(example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(main_full
        main.c
        main_full.c
        IntQueueTimer.c
        RegTest.s
        ${FREERTOS_DEMO_PATH}/Common/Minimal/blocktim.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/countsem.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/dynamic.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/recmutex.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/QueueOverwrite.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/EventGroupsDemo.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/IntSemTest.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/IntQueue.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/TaskNotify.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/TimerDemo.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/GenQTest.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/death.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/semtest.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/BlockQ.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/flop.c
        )

target_compile_definitions(main_full PRIVATE
        mainCREATE_SIMPLE_BLINKY_DEMO_ONLY=0
        )

target_include_directories(main_full PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${FREERTOS_DEMO_PATH}/Common/include)

target_compile_definitions(main_full PRIVATE
        PICO_STDIO_STACK_BUFFER_SIZE=64 # use a small printf on stack buffer
)

target_compile_options( main_full PUBLIC
        ### Gnu/Clang C Options
        $<$<COMPILE_LANG_AND_ID:C,GNU>:-fdiagnostics-color=always>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-fcolor-diagnostics>

        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wall>
        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wextra>
        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Werror>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-Weverything>
        )

target_link_libraries(main_full pico_stdlib FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)
pico_add_extra_outputs(main_full)

add_executable(main_blinky
        main.c
        main_blinky.c
        )

target_compile_definitions(main_blinky PRIVATE
        mainCREATE_SIMPLE_BLINKY_DEMO_ONLY=1
        )

target_include_directories(main_blinky PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${FREERTOS_DEMO_PATH}/Common/include)

target_link_libraries(main_blinky pico_stdlib FreeRTOS-Kernel FreeRTOS-Kernel-Heap1)
pico_add_extra_outputs(main_blinky)
