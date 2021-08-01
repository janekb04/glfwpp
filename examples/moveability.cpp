#include <glfwpp/glfwpp.h>

template <typename T>
void test_moveable() noexcept
{
    // test default construction
    // should place object in partially-formed state
    T obj1{};
    // test move construction
    // moved from object should be partially-formed
    T obj2 = std::move(obj1);
    // test move assignment
    obj1 = std::move(obj2);
    // test destruction
}

template<typename T>
void test_copyable() noexcept
{
    // test default construction
    // should place object in partially-formed state
    T obj1{};
    // test copy construction
    // copied from object should be unmodified
    T obj2 = obj1;
    // test copy assignment
    obj1 = obj2;
    // test destruction
}

int main()
{
    [[maybe_unused]] glfw::GlfwLibrary library = glfw::init();

    test_moveable<glfw::Window>();
    test_moveable<glfw::Cursor>();
    test_moveable<glfw::Monitor>();
    test_moveable<glfw::Joystick>();
    test_moveable<glfw::KeyCode>();

    test_copyable<glfw::Monitor>();
    test_copyable<glfw::Joystick>();
    test_copyable<glfw::KeyCode>();
}
