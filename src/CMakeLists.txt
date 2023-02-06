set(SOURCES
    main.cpp
    constants.cpp
    game.cpp
)

add_executable(pbg ${SOURCES})

target_include_directories(pbg PRIVATE "${PunchBillGates_SOURCE_DIR}/include")
target_link_libraries(pbg SDL2)
