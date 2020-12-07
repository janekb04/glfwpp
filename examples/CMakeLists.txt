cmake_minimum_required(VERSION 3.13)
project(GLFWPP_EXAMPLES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(../include)
link_libraries(glfw libglew_static)
include_directories(../external/glew-cmake/include)

#if Clang-cl
if((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC"))
    add_compile_options(/EHs)
endif()

#Build Examples
add_executable(basic basic.cpp)
