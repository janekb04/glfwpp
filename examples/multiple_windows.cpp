#include <glfwpp/glfwpp.h>
#include <vector>

static void keyboard_callback(glfw::Window& W, glfw::KeyCode K, int, glfw::KeyState S, glfw::ModifierKeyBit)
{
    if(K == glfw::KeyCode::Escape && S == glfw::KeyState::Release)
        W.setShouldClose(true);
}

int main()
{
    std::vector<glfw::Window> DSE{};

    [[maybe_unused]] auto GLFW = glfw::init();

    //DSE.reserve(10);

    DSE.emplace_back(640, 480, "GLFWPP N_1");
    DSE.back().keyEvent.setCallback(keyboard_callback);

    DSE.emplace_back(640, 480, "GLFWPP N_2");
    DSE.back().keyEvent.setCallback(keyboard_callback);

    DSE.emplace_back(640, 480, "GLFWPP N_3");
    DSE.back().keyEvent.setCallback(keyboard_callback);

    while(!DSE.empty())
    {
        for(auto& W : DSE)
        {
            glfw::makeContextCurrent(W);
            glfw::pollEvents();


            if(W.shouldClose())
            {
                auto it = std::find_if(DSE.begin(), DSE.end(), [&W](const auto& cW) { return cW == W; });
                if(it != DSE.end())
                    DSE.erase(it);
            }
        }
    }
}
