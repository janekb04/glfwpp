#ifndef GLFWPP_GLFWPP_H
#define GLFWPP_GLFWPP_H

#include <GLFW/glfw3.h>

#include "error.h"
#include "helper.h"
#include "joystick.h"
#include "monitor.h"
#include "native.h"
#include "vulkan.h"
#include "window.h"

namespace glfw
{
    namespace _impl
    {
        void errorCallback(int errorCode, const char* what)
        {
            switch(errorCode)
            {
                case GLFW_NOT_INITIALIZED:
                    throw NotInitializedError(what);
                case GLFW_NO_CURRENT_CONTEXT:
                    throw NoCurrentContextError(what);
                case GLFW_OUT_OF_MEMORY:
                    throw OutOfMemoryError(what);
                case GLFW_API_UNAVAILABLE:
                    throw APIUnavailableError(what);
                case GLFW_VERSION_UNAVAILABLE:
                    throw VersionUnavailableError(what);
                case GLFW_PLATFORM_ERROR:
                    throw PlatformError(what);
                case GLFW_FORMAT_UNAVAILABLE:
                    throw FormatUnavailableError(what);
                case GLFW_NO_WINDOW_CONTEXT:
                    throw NoWindowContextError(what);
                default:
                    throw Error(what);
            }
        }

        void monitorCallback(GLFWmonitor* monitor, int eventType)
        {
            monitorEvent(Monitor{monitor}, MonitorEventType{eventType});
        }

        void joystickCallback(int jid, int eventType)
        {
            joystickEvent(Joystick{(decltype(Joystick::Joystick1))jid}, (JoystickEvent)eventType);
        }
    }  // namespace _impl

    struct InitHints
    {
        bool cocoaChdirResources = true;
        bool cocoaMenubar = true;

        void apply() const
        {
            glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, cocoaChdirResources);
            glfwInitHint(GLFW_COCOA_MENUBAR, cocoaMenubar);
        }
    };

    struct GLFWLibrary
    {
    private:
        GLFWLibrary() = default;

    public:
        ~GLFWLibrary()
        {
            glfwTerminate();
        }

        [[nodiscard]] friend GLFWLibrary init()
        {
            glfwSetErrorCallback(_impl::errorCallback);

            glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, false);
            glfwInit();

            glfwSetMonitorCallback(_impl::monitorCallback);
            glfwSetJoystickCallback(_impl::joystickCallback);

            return {};
        }
    };

    [[nodiscard]] GLFWLibrary init();

    [[nodiscard]] Version getVersion()
    {
        Version version;
        glfwGetVersion(&version.major, &version.minor, &version.revision);
        return version;
    }

    [[nodiscard]] const char* getVersionString()
    {
        return glfwGetVersionString();
    }

    [[nodiscard]] bool rawMouseMotionSupported()
    {
        return glfwRawMouseMotionSupported();
    }

    void setClipboardString(const char* content)
    {
        glfwSetClipboardString(nullptr, content);
    }

    [[nodiscard]] const char* getClipboardString()
    {
        return glfwGetClipboardString(nullptr);
    }

    namespace timer
    {
        [[nodiscard]] double getTime()
        {
            return glfwGetTime();
        }

        void setTime(double time)
        {
            glfwSetTime(time);
        }

        [[nodiscard]] uint64_t getValue()
        {
            return glfwGetTimerValue();
        }

        [[nodiscard]] uint64_t getFrequency()
        {
            return glfwGetTimerFrequency();
        }
    }  // namespace timer
}  // namespace glfw

#endif  // GLFWPP_GLFWPP_H