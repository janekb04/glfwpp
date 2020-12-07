cmake_minimum_required(VERSION 3.13)
project(GLFWPP CXX)
set(CMAKE_CXX_STANDARD 17)

#Options
option(GLFWPP_BUILD_EXAMPLES "Should examples be built" ON)

#Build GFLW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

#Add include directories
include_directories(external/glfw/include)

#Build examples
if (GLFWPP_BUILD_EXAMPLES)
    add_compile_definitions(GLEW_STATIC)
    if (POLICY CMP0072)
        set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)
    endif()
    add_subdirectory(external/glew-cmake)
    add_subdirectory(examples)
endif()