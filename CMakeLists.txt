cmake_minimum_required(VERSION 3.12)
set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
set(PICO_SDK_INIT_CMAKE_FILE ${PICO_SDK_PATH}/pico_sdk_init.cmake)
include(${PICO_SDK_INIT_CMAKE_FILE})
project(touch_button)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_compile_options(-Wall -Wno-format -Werror -Wno-error=comment -Wno-comment)
aux_source_directory(src SOURCE_LIST)
aux_source_directory(src/touch_button SOURCE_LIST)
include_directories(src/include)
add_executable(touch_button ${SOURCE_LIST})
pico_enable_stdio_usb(touch_button 1)
pico_enable_stdio_uart(touch_button 0)
target_link_libraries(touch_button pico_stdlib hardware_i2c hardware_gpio)
pico_add_extra_outputs(touch_button)
