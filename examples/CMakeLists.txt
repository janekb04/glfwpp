set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Build Examples
add_executable(glfwpp_example_basic basic.cpp)
target_link_libraries(glfwpp_example_basic PRIVATE libglew_static GLFWPP)
add_executable(glfwpp_example_events events.cpp)
target_link_libraries(glfwpp_example_events PRIVATE libglew_static GLFWPP)

#Target to build all examples at once
add_custom_target(glfwpp_all_examples)
add_dependencies(glfwpp_all_examples glfwpp_example_basic glfwpp_example_events)