cmake_minimum_required(VERSION 2.8)

PROJECT(rosenthal)

get_filename_component(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

subdirs(src)
