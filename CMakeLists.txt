cmake_minimum_required(VERSION 3.16)
project(gemu)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)


add_executable(gemu display/Window.cpp)
add_subdirectory(cpu)
set_property(TARGET gemu PROPERTY CXX_STANDARD 20)
target_link_libraries(gemu PRIVATE SDL3::SDL3)
