cmake_minimum_required(VERSION 3.13)
project(GLFWPP_EXAMPLES)
set(CMAKE_CXX_STANDARD 17)

include_directories(../include)
link_libraries(glfw libglew_static)
include_directories(../external/glew-cmake/include)

#Build Examples
add_executable(basic basic.cpp)
