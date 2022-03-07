#!/bin/sh

cmake -S . -B build --toolchain=toolchains/toolchain-arm-none-eabi-gcc.cmake
cmake --build build --target arduino_corstone_system arduino_corstone_test_main --verbose
