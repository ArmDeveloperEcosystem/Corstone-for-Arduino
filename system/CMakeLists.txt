#
# Copyright (c) 2021 ARM Limited. All rights reserved.
#
# SPDX-License-Identifier: LGPL-2.1
#

cmake_minimum_required(VERSION 3.21)

include(ExternalProject)
include(FetchContent)

# Declare root and other build paths
set(PRJ_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# Declare the Open IoT SDK  
FetchContent_Declare(
  open_iot_sdk
  GIT_REPOSITORY https://git.gitlab.arm.com/iot/open-iot-sdk/sdk.git
  GIT_TAG        v2022.01
)

# Declare the Open IoT SDK configuration flags
set(IOTSDK_FREERTOS ON)
set(IOTSDK_MDH_ARM ON)
set(FETCHCONTENT_QUIET OFF)
set(CMAKE_SYSTEM_PROCESSOR cortex-m55)

# Set library to std
set(MBED_C_LIB "std")

# Make the Open IoT SDK available 
FetchContent_MakeAvailable(open_iot_sdk)

# libarduino_corstone_system
project(arduino_corstone_system LANGUAGES C CXX ASM)

target_include_directories(freertos-kernel 
    INTERFACE 
        ${PRJ_DIR}/freertos-config
)

add_library(arduino_corstone_system STATIC
    system.c
)

target_link_libraries(arduino_corstone_system
    mcu-driver-hal
    freertos-kernel
    freertos-kernel-heap-3
)

if(TARGET mdh-arm-an547-mps3-startup)
    target_link_libraries(arduino_corstone_system mdh-arm-an547-mps3-startup)
endif()

# test main executable
add_executable(arduino_corstone_test_main system.c test_main.c)

target_link_libraries(arduino_corstone_test_main
    mcu-driver-hal
    freertos-kernel
    freertos-kernel-heap-3
)

if(TARGET mdh-arm-an547-mps3-startup)
    target_link_libraries(arduino_corstone_test_main mdh-arm-an547-mps3-startup)
endif()
