set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Build Examples
add_executable(basic basic.cpp)
target_link_libraries(basic PRIVATE libglew_static GLFWPP)
