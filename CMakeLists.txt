cmake_minimum_required(VERSION 3.1)
project(GLFWPP CXX)

function(verify_subdirectory_presence dir)
    if (NOT IS_DIRECTORY ${dir})
        message(FATAL_ERROR
                "Error: subdirectory " ${dir} " not found\n"
                "You may have cloned the repository without the --recursive flag"
                "Use `git submodule update --init --recursive` to get the required dependencies"
                )
    endif ()
endfunction()

#Options
option(GLFWPP_BUILD_EXAMPLES "Should examples be built" ON)

#Add GFLW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
verify_subdirectory_presence("${CMAKE_CURRENT_SOURCE_DIR}/external/glfw")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

#Create library target
add_library(GLFWPP INTERFACE)
target_include_directories(GLFWPP INTERFACE include)
target_compile_features(GLFWPP INTERFACE cxx_std_17)
target_link_libraries(GLFWPP INTERFACE glfw)

#Enable exceptions if Clang-cl
if ((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC"))
    target_compile_options(GLFWPP INTERFACE /EHs)
endif ()

#Build examples
if (GLFWPP_BUILD_EXAMPLES)
    verify_subdirectory_presence("${CMAKE_CURRENT_SOURCE_DIR}/external/glew-cmake")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glew-cmake)
    verify_subdirectory_presence("${CMAKE_CURRENT_SOURCE_DIR}/external/imgui")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif ()