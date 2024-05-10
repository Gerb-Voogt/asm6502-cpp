cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Set the build type to debug to compile with symbol information
set(CMAKE_BUILD_TYPE Debug)

project(asm6502 VERSION 0.1)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*/*.cpp)
add_executable(asm6502 src/main.cpp ${SRC_FILES})
target_include_directories(asm6502 PUBLIC ${CMAKE_SOURCE_DIR}/include)
