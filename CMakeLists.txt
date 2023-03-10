cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(rtcKeeper C CXX ASM)

pico_sdk_init()

add_executable(rtcKeeper
        main.cpp
    )

pico_enable_stdio_usb(rtcKeeper 1)
pico_enable_stdio_uart(rtcKeeper 0)

target_link_libraries(rtcKeeper pico_stdlib hardware_spi) #hardware_spi hardware_i2c
pico_add_extra_outputs(rtcKeeper)