cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(ProjetoFinal_Embarcatech C CXX ASM)

pico_sdk_init()

add_executable(ProjetoFinal_Embarcatech 
    src/ProjetoFinal_Embarcatech.c 
    src/buzzer.c 
    src/display.c 
    src/led_matrix.c 
    src/ssd1306_i2c.c
)

pico_set_program_name(ProjetoFinal_Embarcatech "ProjetoFinal_Embarcatech")
pico_set_program_version(ProjetoFinal_Embarcatech "0.1")

pico_enable_stdio_uart(ProjetoFinal_Embarcatech 0)
pico_enable_stdio_usb(ProjetoFinal_Embarcatech 1)

target_link_libraries(ProjetoFinal_Embarcatech
    pico_stdlib
    hardware_i2c
    hardware_pwm
    hardware_pio
)

target_include_directories(ProjetoFinal_Embarcatech PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
    ${PICO_SDK_PATH}/src/rp2_common/hardware_pwm/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_pio/include
)

pico_add_extra_outputs(ProjetoFinal_Embarcatech)
