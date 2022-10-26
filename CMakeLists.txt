cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(uart_echo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17) 

# Initialize the SDK
pico_sdk_init()

add_executable(uart_echo
	main.c
	)

# Pull in our pico_stdlib which pulls in commonl
target_link_libraries(uart_echo pico_stdlib hardware_uart pico_multicore)

# Enable/Disable usb/uart standard output (1 for enable, 0 for disable)
# Serial default baud: 115200
pico_enable_stdio_usb(uart_echo 1)
pico_enable_stdio_uart(uart_echo 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(uart_echo)
