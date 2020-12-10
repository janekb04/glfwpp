cmake_minimum_required(VERSION 3.13)
project(GLFWPP CXX)

#Options
option(GLFWPP_BUILD_EXAMPLES "Should examples be built" ON)

#Add GFLW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

#Create library target
add_library(GLFWPP INTERFACE)
target_include_directories(GLFWPP INTERFACE include)
target_compile_features(GLFWPP INTERFACE cxx_std_17)
target_link_libraries(GLFWPP INTERFACE glfw)

#Enable exceptions if Clang-cl
if((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC"))
    target_compile_options(GLFWPP INTERFACE /EHs)
endif()

#Build examples
if (GLFWPP_BUILD_EXAMPLES)
    add_compile_definitions(GLEW_STATIC)
    if (POLICY CMP0072)
        set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)
    endif()
    add_subdirectory(external/glew-cmake)
    add_subdirectory(examples)
endif()