cmake_minimum_required(VERSION 3.1)
project(GLFWPP CXX)

function(add_subdirectory_checked dir)
    if (NOT EXISTS ${dir}/CMakeLists.txt)
        message(FATAL_ERROR
                "Error: Subdirectory " ${dir} " not found\n"
                "You may have cloned the repository without the --recursive flag\n"
                "Use `git submodule update --init --recursive` to get the required dependencies"
                )
    endif ()
    add_subdirectory(${dir})
endfunction()

#Options
option(GLFWPP_BUILD_EXAMPLES "Should examples be built" ON)

#Create library target
add_library(GLFWPP INTERFACE)
target_include_directories(GLFWPP INTERFACE include)
target_compile_features(GLFWPP INTERFACE cxx_std_17)

#Add GFLW
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    target_include_directories(GLFWPP INTERFACE "${EMSCRIPTEN_ROOT_PATH}/system/include")
    set(CMAKE_CXX_LINKER_WRAPPER_FLAG "")
    target_link_options(GLFWPP INTERFACE "LINKER:-sUSE_GLFW=3")
else()
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory_checked(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)
    target_link_libraries(GLFWPP INTERFACE glfw)
endif()

#Enable exceptions if Clang-cl
if ((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC"))
    target_compile_options(GLFWPP INTERFACE /EHs)
endif ()

#Build examples
if (GLFWPP_BUILD_EXAMPLES)
    if (NOT (CMAKE_SYSTEM_NAME STREQUAL "Emscripten"))
        add_subdirectory_checked(${CMAKE_CURRENT_SOURCE_DIR}/external/glew-cmake)
    endif()
    add_subdirectory_checked(${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif ()