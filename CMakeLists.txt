set(TARGET_NAME W55RP20_DHT22_Example)


add_executable(${TARGET_NAME}
        ${TARGET_NAME}.c
        dht.c
        )

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TARGET_NAME} PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        TIMER_FILES
        hardware_pio
        )

pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 0)

pico_add_extra_outputs(${TARGET_NAME})