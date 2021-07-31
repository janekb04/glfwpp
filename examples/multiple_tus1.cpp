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
    // Or with C++20:
    //glfw::WindowHints{
    //        .clientApi = glfw::ClientApi::OpenGl,
    //        .contextVersionMajor = 4,
    //        .contextVersionMinor = 6}
    //        .apply();
    glfw::Window wnd(800, 600, "GLFWPP basic example");

    glfw::makeContextCurrent(wnd);
    if(glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Could not initialize GLEW");
    }

    while(!wnd.shouldClose())
    {
        double time = glfw::getTime();
        glClearColor((sin(time) + 1.0) / 2.0, (cos(time) + 1.0) / 2.0, (-sin(time) + 1.0) / 2.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfw::pollEvents();
        wnd.swapBuffers();
    }
}
