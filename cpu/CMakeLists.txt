cmake_minimum_required(VERSION 3.10)

# Compile with Clang
#set(CMAKE_C_COMPILER "clang-13")
#set(CMAKE_CXX_COMPILER "clang++-13")

# Set the project name and version
project(OpenPT VERSION 0.0.1)

# Specify the C++ standard
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(OpenPT main.cpp)