# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/ry-d7/src/rpi-pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pwm-motor-test C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pwm-motor-test pwm-motor-test.cpp )

pico_set_program_name(pwm-motor-test "pwm-motor-test")
pico_set_program_version(pwm-motor-test "0.1")

pico_enable_stdio_uart(pwm-motor-test 0)
pico_enable_stdio_usb(pwm-motor-test 1)

# Add the standard library to the build
target_link_libraries(pwm-motor-test pico_stdlib)

# Add any user requested libraries
target_link_libraries(pwm-motor-test
        hardware_timer
        hardware_clocks
        hardware_pwm
        )

pico_add_extra_outputs(pwm-motor-test)

