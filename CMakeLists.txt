cmake_minimum_required(VERSION 3.25)
project(PunchBillGates LANGUAGES CXX)

find_package(SDL2 REQUIRED)

add_subdirectory("${PunchBillGates_SOURCE_DIR}/src")
