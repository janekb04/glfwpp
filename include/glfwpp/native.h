#ifndef GLFWPP_NATIVE_H
#define GLFWPP_NATIVE_H

#include <GLFW/glfw3native.h>

namespace glfw
{
    namespace native
    {
#if defined(GLFW_EXPOSE_NATIVE_WIN32)
        [[nodiscard]] const char* getWin32Adapter(const Monitor& monitor_)
        {
            return glfwGetWin32Adapter(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] const char* getWin32Monitor(const Monitor& monitor_)
        {
            return glfwGetWin32Monitor(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] ::HWND getWin32Window(Window& window_)
        {
            return glfwGetWin32Window(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_WGL)
        [[nodiscard]] ::HGLRC getWGLContext(Window& window_)
        {
            return glfwGetWGLContext(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_COCOA)
        [[nodiscard]] ::CGDirectDisplayID getCocoaMonitor(const Monitor& monitor_)
        {
            return glfwGetCocoaMonitor(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] ::id getCocoaWindow(Window& window_)
        {
            return glfwGetCocoaWindow(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_NSGL)
        [[nodiscard]] ::id getNSGLContext(Window& window_)
        {
            return glfwGetNSGLContext(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_X11)
        [[nodiscard]] ::Display* getX11Display()
        {
            return glfwGetX11Display();
        }
        [[nodiscard]] ::RRCrtc getX11Adapter(Monitor& monitor_)
        {
            return glfwGetX11Adapter(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] ::RROutput getX11Monitor(Monitor& monitor_)
        {
            return glfwGetX11Monitor(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] ::Window getX11Window(Window& window_)
        {
            return glfwGetX11Window(static_cast<GLFWwindow*>(window_));
        }
        void setX11SelectionString(const char* string_)
        {
            glfwSetX11SelectionString(string_);
        }
        [[nodiscard]] const char* getX11SelectionString()
        {
            return glfwGetX11SelectionString();
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_GLX)
        [[nodiscard]] ::GLXContext getGLXContext(Window& window_)
        {
            return glfwGetGLXContext(static_cast<GLFWwindow*>(window_));
        }
        [[nodiscard]] ::GLXWindow getGLXWindow(Window& window_)
        {
            return glfwGetGLXWindow(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_WAYLAND)
        [[nodiscard]] ::wl_display* getWaylandDisplay()
        {
            return glfwGetWaylandDisplay();
        }
        [[nodiscard]] ::wl_output* getWaylandMonitor(Monitor& monitor_)
        {
            return glfwGetWaylandMonitor(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] ::wl_surface* getWaylandWindow(Window& window_)
        {
            return glfwGetWaylandWindow(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_EGL)
        [[nodiscard]] ::EGLDisplay getEGLDisplay()
        {
            return glfwGetEGLDisplay();
        }
        [[nodiscard]] ::EGLContext getEGLContext(Window& window_)
        {
            return glfwGetEGLContext(static_cast<GLFWwindow*>(window_));
        }
        [[nodiscard]] ::EGLSurface getEGLSurface(Window& window_)
        {
            return glfwGetEGLSurface(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_OSMESA)
        [[nodiscard]] std::tuple<int, int, int, void*> getOSMesaColorBuffer(Window& window_)
        {
            int width, height, format;
            void* buffer;
            glfwGetOSMesaColorBuffer(static_cast<GLFWwindow*>(window_), &width, &height, &format, &buffer);
            return {width, height, format, buffer};
        }
        [[nodiscard]] std::tuple<int, int, int, void*> getOSMesaDepthBuffer(Window& window_)
        {
            int width, height, bytesPerValue;
            void* buffer;
            glfwGetOSMesaDepthBuffer(static_cast<GLFWwindow*>(window_), &width, &height, &bytesPerValue, &buffer);
            return {width, height, bytesPerValue, buffer};
        }
        [[nodiscard]] ::OSMesaContext getOSMesaContext(Window& window_)
        {
            return glfwGetOSMesaContext(static_cast<GLFWwindow*>(window_));
        }
#endif
    }  // namespace native
}  // namespace glfw

#endif  //GLFWPP_NATIVE_H
