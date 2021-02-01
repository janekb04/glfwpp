cmake_minimum_required(VERSION 3.1)
project(GLFWPP CXX)

#Options
option(GLFWPP_BUILD_EXAMPLES "Should examples be built" ON)

if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include")
    message(FATAL_ERROR "GLFW dependency not found in ./external/glfw... !!"
        "\nYou may not have cloned the submodules recursively with --recursive "
        "\n\`git submodule update --init --recursive\` will get the required dependencies"
    )
endif()

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
    if (POLICY CMP0072)
        set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)
    endif()
    add_subdirectory(external/glew-cmake)
    add_subdirectory(external/imgui)
    add_subdirectory(examples)
endif()