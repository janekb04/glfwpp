#include <glfwpp/glfwpp.h>
#include <type_traits>

template<typename T>
constexpr bool test_moveable() noexcept
{
    return std::is_default_constructible_v<T> && std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>;
}

template<typename T>
constexpr bool test_copyable() noexcept
{
    return std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>;
}

int main()
{
    static_assert(test_moveable<glfw::Window>());
    static_assert(test_moveable<glfw::Cursor>());
    static_assert(test_moveable<glfw::Monitor>());
    static_assert(test_moveable<glfw::Joystick>());
    static_assert(test_moveable<glfw::KeyCode>());

    static_assert(test_copyable<glfw::Monitor>());
    static_assert(test_copyable<glfw::Joystick>());
    static_assert(test_copyable<glfw::KeyCode>());
}
