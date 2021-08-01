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
    glfw::Window wnd(800, 600, "GLFWPP test compilation with multiple TUs");

    glfw::makeContextCurrent(wnd);
    if(glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Could not initialize GLEW");
    }

    while(!wnd.shouldClose())
    {
        glfw::pollEvents();
        wnd.swapBuffers();
    }
}
