cmake_minimum_required(VERSION 3.9.1)
project(CHIP-8_Emulator)
set (CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} Chip8.cpp renderer.cpp shader_class.cpp glad.c main.cpp)

target_link_libraries(${PROJECT_NAME} dl GL glfw)