#include <glfwpp/glfwpp.h>
#include <string>
#include <vector>

// based on https://github.com/janekb04/glfwpp/issues/136

static void keyboard_callback(glfw::Window& wnd, glfw::KeyCode K, int, glfw::KeyState S, glfw::ModifierKeyBit)
{
    if(K == glfw::KeyCode::Escape && S == glfw::KeyState::Release)
    {
        wnd.setShouldClose(true);
    }
}

int main()
{
    std::vector<glfw::Window> v{};

    [[maybe_unused]] auto GLFW = glfw::init();

    for(int windows = 0; windows < 11; ++windows)
    {
        v.emplace_back(640, 480, ("Window " + std::to_string(windows)).c_str());
        v.back().keyEvent.setCallback(keyboard_callback);
    }

    while(!v.empty())
    {
        glfw::pollEvents();

        v.erase(
                std::remove_if(v.begin(), v.end(), [](const glfw::Window& wnd) {
                    return wnd.shouldClose();
                }),
                v.end());
    }
}
