cmake_minimum_required(VERSION 3.10)

# Set the compiler to Clang (optional)
set(CMAKE_C_COMPILER "clang-13")
set(CMAKE_CXX_COMPILER "clang++-13")

# Set the compiler flags
SET(CMAKE_CXX_FLAGS "-Ofast -pthread -fopenmp -Wall -Wextra ${CMAKE_CXX_FLAGS}")

# Set the project name and version
project(OpenPT VERSION 0.0.1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(OpenPT main.cpp)