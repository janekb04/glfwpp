#include <GL/glew.h>
#include <glfwpp/glfwpp.h>

#include <cmath>
#include <string>

int main()
{
    [[maybe_unused]] glfw::GlfwLibrary library = glfw::init();

    glfw::WindowHints hints;
    hints.clientApi = glfw::ClientApi::OpenGl;
    hints.contextVersionMajor = 4;
    hints.contextVersionMinor = 6;
    hints.apply();
    // Or with C++20:
    // glfw::WindowHints{
    //        .clientApi = glfw::ClientApi::OpenGl,
    //        .contextVersionMajor = 4,
    //        .contextVersionMinor = 6}
    //        .apply();
    glfw::Window wnd(800, 600, "GLFWPP basic example");

    glfw::makeContextCurrent(wnd);
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        std::string err_string = "Could not initialize GLEW: ";
        err_string.append(reinterpret_cast<const char*>(glewGetErrorString(err)));
        throw std::runtime_error(err_string);
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
