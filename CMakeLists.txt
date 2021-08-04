cmake_minimum_required (VERSION 3.8)
project (pathtracingrenderer)

find_package(Vulkan)

# get rid of annoying MSVC warnings.
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set (CMAKE_CXX_STANDARD 11)

include_directories(${Vulkan_INCLUDE_DIR})

set(ALL_LIBS  ${Vulkan_LIBRARY} )

add_executable(pathtracingrenderer main.cpp lodepng.cpp)

set_target_properties(pathtracingrenderer PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(pathtracingrenderer ${ALL_LIBS} )