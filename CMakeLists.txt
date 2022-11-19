cmake_minimum_required(VERSION 3.14...3.25)
project(GLFWPP CXX)

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
    # try to find with cmake
    find_package(glfw3 CONFIG)
    if(glfw3_FOUND)
        target_link_libraries(GLFWPP INTERFACE glfw)
    else()
        # then try with pkg-config (in case cmake config files are missing for some reason)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GLFW IMPORTED_TARGET glfw3)
        if(GLFW_FOUND)
            target_link_libraries(GLFWPP INTERFACE glfw)
        else()
            # then build from source if needed
            include(FetchContent)
            FetchContent_Declare(
                glfw
                GIT_REPOSITORY https://github.com/glfw/glfw.git
                GIT_TAG 3.3.8)
            set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
            set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
            set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
            FetchContent_MakeAvailable(glfw)
            target_link_libraries(GLFWPP INTERFACE glfw)
        endif()
    endif()
endif()

#Build examples
if (GLFWPP_BUILD_EXAMPLES)
    if (NOT (CMAKE_SYSTEM_NAME STREQUAL "Emscripten"))
        include(FetchContent)
        FetchContent_Declare(glew-cmake
            GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
            GIT_TAG 7c2b7514f64234756f7df051b9316f1e46f5a6e7)
        FetchContent_MakeAvailable(glew-cmake)
    endif()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif ()
