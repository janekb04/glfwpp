#ifndef GLFWPP_MONITOR_H
#define GLFWPP_MONITOR_H

#include "event.h"
#include <tuple>
#include <vector>

namespace glfw
{
    using VideoMode = GLFWvidmode;
    using GammaRamp = GLFWgammaramp;

    class Monitor
    {
    private:
        GLFWmonitor* _handle;

    public:
        Monitor() :
            Monitor{nullptr}
        {
        }

        explicit Monitor(GLFWmonitor* handle_) :
            _handle{handle_}
        {
        }

        Monitor(const Monitor&) = default;

        Monitor& operator=(const Monitor&) = default;

        operator GLFWmonitor*() const
        {
            return _handle;
        }

        explicit operator bool() const = delete;

        [[nodiscard]] friend std::vector<Monitor> getMonitors()
        {
            int count;
            auto pMonitors = glfwGetMonitors(&count);

            std::vector<Monitor> monitors;
            monitors.reserve(count);
            for(int i = 0; i < count; ++i)
            {
                monitors.emplace_back(pMonitors[i]);
            }
            return monitors;
        }
        [[nodiscard]] friend Monitor getPrimaryMonitor()
        {
            return Monitor{glfwGetPrimaryMonitor()};
        }

    public:
        [[nodiscard]] std::tuple<int, int> getPos() const
        {
            int x, y;
            glfwGetMonitorPos(_handle, &x, &y);
            return {x, y};
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] std::tuple<int, int, int, int> getWorkArea() const
        {
            int xPos, yPos, width, height;
            glfwGetMonitorWorkarea(_handle, &xPos, &yPos, &width, &height);
            return {xPos, yPos, width, height};
        }
#endif

        [[nodiscard]] std::tuple<int, int> getPhysicalSize() const
        {
            int widthMillimeters, heightMillimeters;
            glfwGetMonitorPhysicalSize(_handle, &widthMillimeters, &heightMillimeters);
            return {widthMillimeters, heightMillimeters};
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] std::tuple<float, float> getContentScale() const
        {
            float xScale, yScale;
            glfwGetMonitorContentScale(_handle, &xScale, &yScale);
            return {xScale, yScale};
        }
#endif

        [[nodiscard]] const char* getName() const
        {
            return glfwGetMonitorName(_handle);
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setUserPointer(void* ptr_)
        {
            glfwSetMonitorUserPointer(_handle, ptr_);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] void* getUserPointer() const
        {
            return glfwGetMonitorUserPointer(_handle);
        }
#endif

        [[nodiscard]] std::vector<VideoMode> getVideoModes() const
        {
            int count;
            auto pModes = glfwGetVideoModes(_handle, &count);

            std::vector<VideoMode> modes;
            modes.reserve(count);
            for(int i = 0; i < count; ++i)
            {
                modes.push_back(pModes[i]);
            }
            return modes;
        }

        [[nodiscard]] VideoMode getVideoMode() const
        {
            return *glfwGetVideoMode(_handle);
        }

        void setGamma(float gamma_)
        {
            glfwSetGamma(_handle, gamma_);
        }

        [[nodiscard]] GammaRamp getGammaRamp() const
        {
            return *glfwGetGammaRamp(_handle);
        }

        void setGammaRamp(const GammaRamp& ramp_)
        {
            glfwSetGammaRamp(_handle, &ramp_);
        }
    };
    [[nodiscard]] inline std::vector<Monitor> getMonitors();
    [[nodiscard]] inline Monitor getPrimaryMonitor();

    enum class MonitorEventType : int
    {
        Connected = GLFW_CONNECTED,
        Disconnected = GLFW_DISCONNECTED
    };
    inline Event<Monitor, MonitorEventType> monitorEvent;
}  // namespace glfw

#endif  //GLFWPP_MONITOR_H
