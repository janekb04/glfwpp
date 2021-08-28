#ifndef __EMSCRIPTEN__
    #include <GL/glew.h>
#else
    #include <emscripten.h>
#endif
#include <glfwpp/glfwpp.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

void cleanupImgui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

template<typename Func>
void renderImgui(Func&& guiRenderFunc_)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    guiRenderFunc_();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void initImgui(const glfw::Window& wnd)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplGlfw_InitForOpenGL(wnd, true);
    ImGui_ImplOpenGL3_Init();
}

glfw::Window* mainWindow;

int main()
{
    [[maybe_unused]] glfw::GlfwLibrary library = glfw::init();

    glfw::WindowHints hints;
    hints.clientApi = glfw::ClientApi::OpenGl;
    hints.contextVersionMajor = 4;
    hints.contextVersionMinor = 6;
    hints.apply();
    glfw::Window wnd(800, 600, "GLFWPP ImGui integration example");
    mainWindow = &wnd;

    glfw::makeContextCurrent(wnd);

#ifndef __EMSCRIPTEN__
    if(glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Could not initialize GLEW");
    }
#endif

    initImgui(wnd);

    wnd.keyEvent.setCallback([](glfw::Window&, glfw::KeyCode, int, glfw::KeyState, glfw::ModifierKeyBit) {
        std::cout << "hi";
    });

    auto mainLoop = []() {
        glClear(GL_COLOR_BUFFER_BIT);

        renderImgui([]() {
            ImGui::ShowDemoWindow();
        });

        glfw::pollEvents();
        mainWindow->swapBuffers();
    };

#ifndef __EMSCRIPTEN__
    while(!wnd.shouldClose())
    {
        mainLoop();
    }
#else
    emscripten_set_main_loop(mainLoop, 0, true);
#endif

    cleanupImgui();
}
