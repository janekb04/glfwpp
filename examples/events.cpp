#include <GL/glew.h>
#include <cmath>
#include <glfwpp/glfwpp.h>

int main()
{
    [[maybe_unused]] glfw::GlfwLibrary library = glfw::init();

    glfw::WindowHints hints;
    hints.clientApi = glfw::ClientApi::OpenGl;
    hints.contextVersionMajor = 4;
    hints.contextVersionMinor = 6;
    hints.apply();
    glfw::Window wnd(800, 600, "GLFWPP events example");

    glfw::makeContextCurrent(wnd);
    if(glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Could not initialize GLEW");
    }

    wnd.framebufferSizeEvent.setCallback([](int width, int height) {
        glViewport(0, 0, width, height);
    });
    wnd.keyEvent.setCallback([](glfw::KeyCode keyCode_, int scanCode_, glfw::KeyState state_, glfw::ModifierKeyBit modifiers_) {
        float val = 0.5;
        if(modifiers_ & glfw::ModifierKeyBit::Control)
        {
            val += 0.25;
        }
        if(modifiers_ & glfw::ModifierKeyBit::Shift)
        {
            val -= 0.25;
        }
        switch(keyCode_)
        {
            case glfw::KeyCode::R:
                glClearColor(val, 0.0, 0.0, val);
                break;
            case glfw::KeyCode::G:
                glClearColor(0.0, val, 0.0, val);
                break;
            case glfw::KeyCode::B:
                glClearColor(0.0, 0.0, val, val);
                break;
            case glfw::KeyCode::M:
                glClearColor(val, 0.0, val, val);
                break;
            case glfw::KeyCode::C:
                glClearColor(0.0, val, val, val);
                break;
            case glfw::KeyCode::Y:
                glClearColor(val, val, 0.0, val);
                break;
            case glfw::KeyCode::K:
                glClearColor(0.0, 0.0, 0.0, val);
                break;
            default:
                break;
        }
    });

    while(!wnd.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfw::pollEvents();
        wnd.swapBuffers();
    }
}
