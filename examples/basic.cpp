#include <GL/glew.h>
#include <glfwpp/glfwpp.h>
#include <cmath>

int main()
{
    glfw::GLFWLibrary library = glfw::init();
    glfw::WindowHints{
            .clientAPI = glfw::ClientAPI::OpenGL,
            .contextVersionMajor = 4,
            .contextVersionMinor = 6
    }.apply();
    glfw::Window wnd(800, 600, "GLFWPP basic example");

    if (!glewInit())
    {
        throw std::runtime_error("Could not initialize GLEW");
    }

    glfw::makeContextCurrent(wnd);

    while (!wnd.shouldClose())
    {
        double time = glfw::timer::getTime();
        glClearColor((sin(time) + 1.0) / 2.0, (cos(time) + 1.0) / 2.0, (-sin(time) + 1.0) / 2.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendering code here
        glfw::pollEvents();
        wnd.swapBuffers();
    }
}