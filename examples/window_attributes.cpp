#include <GL/glew.h>
#include <cmath>
#include <glfwpp/glfwpp.h>
#include <string>

int main()
{
    [[maybe_unused]] glfw::GlfwLibrary library = glfw::init();

    glfw::WindowHints hints;
    hints.clientApi = glfw::ClientApi::OpenGl;
    hints.contextVersionMajor = 4;
    hints.contextVersionMinor = 6;
    hints.apply();
    glfw::Window wnd(800, 600, "GLFWPP window pool example");

    glfw::makeContextCurrent(wnd);
    if(glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Could not initialize GLEW");
    }

    wnd.framebufferSizeEvent.setCallback([](glfw::Window&, int width, int height) {
        glViewport(0, 0, width, height);
    });
    wnd.keyEvent.setCallback([&](glfw::Window&, glfw::KeyCode keyCode_, int scanCode_, glfw::KeyState state_, glfw::ModifierKeyBit modifiers_) {
        bool val = true;
        if(modifiers_ & glfw::ModifierKeyBit::Control)
        {
            val = false;
        }
        switch(keyCode_)
        {
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            case glfw::KeyCode::F:
                wnd.setAttribFloating(val);
                break;
            case glfw::KeyCode::R:
                wnd.setAttribResizable(val);
                break;
            case glfw::KeyCode::D:
                wnd.setAttribDecorated(val);
                break;
            default:
                break;
        }
#endif
    });

    while(!wnd.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        wnd.setOpacity((sin(glfw::getTime()) + 1.0) / 2.0);
#endif
        wnd.setTitle(std::to_string(glfw::getTime()).c_str());

        if(!wnd.getAttribFocused())
        {
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            wnd.requestAttention();
#endif
        }

        glfw::pollEvents();
        wnd.swapBuffers();
    }
}
