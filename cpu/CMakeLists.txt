cmake_minimum_required(VERSION 3.10)

# Set the compiler to Clang (optional)
set(CMAKE_C_COMPILER "clang-13")
set(CMAKE_CXX_COMPILER "clang++-13")

# Set the project name and version
project(OpenPT VERSION 0.0.1)

# Specify the C++ standard
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-Ofast -pthread -fopenmp -Wall -Wextra -Wshadow ${CMAKE_CXX_FLAGS}")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "-Ofast -pthread -fopenmp -Wall -Wextra -Wshadow ${CMAKE_CXX_FLAGS}")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	# Intel's Compiler is OK I guess...
	# TODO: Intel Flags

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	# The worst case is using MSVC, yuck!
	# TODO: MSVC Flags

endif()

# Add the executable
add_executable(OpenPT main.cpp)