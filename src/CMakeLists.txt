set(SOURCES
    main.cpp
    constants.cpp
    game.cpp
    billgates.cpp
    hand.cpp
)

add_executable(pbg ${SOURCES})

add_custom_command(TARGET pbg PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PunchBillGates_SOURCE_DIR}/assets" "${PunchBillGates_BINARY_DIR}/assets")

target_include_directories(pbg PRIVATE "${PunchBillGates_SOURCE_DIR}/include")
target_link_libraries(pbg SDL2 SDL2_mixer SDL2_image)
