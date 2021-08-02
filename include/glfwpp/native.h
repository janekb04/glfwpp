#ifndef GLFWPP_NATIVE_H
#define GLFWPP_NATIVE_H

#include <GLFW/glfw3native.h>

namespace glfw
{
    namespace native
    {
#if defined(GLFW_EXPOSE_NATIVE_WIN32)
        [[nodiscard]] inline const char* getWin32Adapter(const Monitor& monitor_)
        {
            return glfwGetWin32Adapter(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] inline const char* getWin32Monitor(const Monitor& monitor_)
        {
            return glfwGetWin32Monitor(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] inline ::HWND getWin32Window(Window& window_)
        {
            return glfwGetWin32Window(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_WGL)
        [[nodiscard]] inline ::HGLRC getWGLContext(Window& window_)
        {
            return glfwGetWGLContext(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_COCOA)
        [[nodiscard]] inline ::CGDirectDisplayID getCocoaMonitor(const Monitor& monitor_)
        {
            return glfwGetCocoaMonitor(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] inline ::id getCocoaWindow(Window& window_)
        {
            return glfwGetCocoaWindow(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_NSGL)
        [[nodiscard]] inline ::id getNSGLContext(Window& window_)
        {
            return glfwGetNSGLContext(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_X11)
        [[nodiscard]] inline ::Display* getX11Display()
        {
            return glfwGetX11Display();
        }
        [[nodiscard]] inline ::RRCrtc getX11Adapter(Monitor& monitor_)
        {
            return glfwGetX11Adapter(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] inline ::RROutput getX11Monitor(Monitor& monitor_)
        {
            return glfwGetX11Monitor(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] inline ::Window getX11Window(Window& window_)
        {
            return glfwGetX11Window(static_cast<GLFWwindow*>(window_));
        }
        inline void setX11SelectionString(const char* string_)
        {
            glfwSetX11SelectionString(string_);
        }
        [[nodiscard]] inline const char* getX11SelectionString()
        {
            return glfwGetX11SelectionString();
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_GLX)
        [[nodiscard]] inline ::GLXContext getGLXContext(Window& window_)
        {
            return glfwGetGLXContext(static_cast<GLFWwindow*>(window_));
        }
        [[nodiscard]] inline ::GLXWindow getGLXWindow(Window& window_)
        {
            return glfwGetGLXWindow(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_WAYLAND)
        [[nodiscard]] inline ::wl_display* getWaylandDisplay()
        {
            return glfwGetWaylandDisplay();
        }
        [[nodiscard]] inline ::wl_output* getWaylandMonitor(Monitor& monitor_)
        {
            return glfwGetWaylandMonitor(static_cast<GLFWmonitor*>(monitor_));
        }
        [[nodiscard]] inline ::wl_surface* getWaylandWindow(Window& window_)
        {
            return glfwGetWaylandWindow(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_EGL)
        [[nodiscard]] inline ::EGLDisplay getEGLDisplay()
        {
            return glfwGetEGLDisplay();
        }
        [[nodiscard]] inline ::EGLContext getEGLContext(Window& window_)
        {
            return glfwGetEGLContext(static_cast<GLFWwindow*>(window_));
        }
        [[nodiscard]] inline ::EGLSurface getEGLSurface(Window& window_)
        {
            return glfwGetEGLSurface(static_cast<GLFWwindow*>(window_));
        }
#endif

#if defined(GLFW_EXPOSE_NATIVE_OSMESA)
        [[nodiscard]] inline std::tuple<int, int, int, void*> getOSMesaColorBuffer(Window& window_)
        {
            int width, height, format;
            void* buffer;
            glfwGetOSMesaColorBuffer(static_cast<GLFWwindow*>(window_), &width, &height, &format, &buffer);
            return {width, height, format, buffer};
        }
        [[nodiscard]] inline std::tuple<int, int, int, void*> getOSMesaDepthBuffer(Window& window_)
        {
            int width, height, bytesPerValue;
            void* buffer;
            glfwGetOSMesaDepthBuffer(static_cast<GLFWwindow*>(window_), &width, &height, &bytesPerValue, &buffer);
            return {width, height, bytesPerValue, buffer};
        }
        [[nodiscard]] inline ::OSMesaContext getOSMesaContext(Window& window_)
        {
            return glfwGetOSMesaContext(static_cast<GLFWwindow*>(window_));
        }
#endif
    }  // namespace native
}  // namespace glfw

#endif  //GLFWPP_NATIVE_H
