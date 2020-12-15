set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Build Examples
add_executable(basic basic.cpp)
target_link_libraries(basic PRIVATE libglew_static GLFWPP)
add_executable(events events.cpp)
target_link_libraries(events PRIVATE libglew_static GLFWPP)
