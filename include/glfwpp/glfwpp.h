#ifndef GLFWPP_GLFWPP_H
#define GLFWPP_GLFWPP_H

#include <cassert>

#include <GLFW/glfw3.h>

#include "error.h"
#include "event.h"
#include "joystick.h"
#include "monitor.h"
#include "window.h"

namespace glfw
{
    namespace impl
    {
        inline void errorCallback(int errorCode_, const char* what_)
        {
            // Error handling philosophy as per http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0709r4.pdf (section 1.1)

            // Application programmer errors. See the GLFW docs and fix the code.
            assert(errorCode_ != GLFW_NOT_INITIALIZED);
            assert(errorCode_ != GLFW_NO_CURRENT_CONTEXT);
            assert(errorCode_ != GLFW_NO_WINDOW_CONTEXT);
            assert(errorCode_ != GLFW_INVALID_VALUE);

            // These errors should never occur
            assert(errorCode_ != GLFW_NO_ERROR);
            assert(errorCode_ != GLFW_INVALID_ENUM);

            // Allocation failure must be treated separately
            if(errorCode_ == GLFW_OUT_OF_MEMORY)
            {
                throw std::bad_alloc();
            }

            switch(errorCode_)
            {
                case GLFW_API_UNAVAILABLE:
                    throw APIUnavailableError(what_);
                case GLFW_VERSION_UNAVAILABLE:
                    throw VersionUnavailableError(what_);
                case GLFW_PLATFORM_ERROR:
                    throw PlatformError(what_);
                case GLFW_FORMAT_UNAVAILABLE:
                    throw FormatUnavailableError(what_);
                default:
                    // There should be no other error possible
                    assert(false);
            }
        }

        [[gnu::always_inline]] inline void monitorCallback(GLFWmonitor* monitor_, int eventType_)
        {
            monitorEvent::call(Monitor{monitor_}, MonitorEventType{eventType_});
        }

        [[gnu::always_inline]] inline void joystickCallback(int jid_, int eventType_)
        {
            joystickEvent::call(Joystick{static_cast<decltype(Joystick::Joystick1)>(jid_)}, static_cast<JoystickEvent>(eventType_));
        }
    }  // namespace impl

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

    struct GlfwLibrary
    {
    private:
        GlfwLibrary() = default;

    public:
        ~GlfwLibrary()
        {
            glfwTerminate();
        }

        [[nodiscard]] friend GlfwLibrary init()
        {
            glfwSetErrorCallback(impl::errorCallback);

            glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, false);  // disable deprecated behavior
            if(!glfwInit())
            {
                throw glfw::Error("Could not initialize GLFW");
            }

            glfwSetMonitorCallback(impl::monitorCallback);
            glfwSetJoystickCallback(impl::joystickCallback);

            return {};
        }
    };

    [[nodiscard]] GlfwLibrary init();

    [[nodiscard, gnu::always_inline]] inline Version getVersion()
    {
        Version version{};
        glfwGetVersion(&version.major, &version.minor, &version.revision);
        return version;
    }

    [[nodiscard, gnu::always_inline]] inline const char* getVersionString()
    {
        return glfwGetVersionString();
    }

    [[nodiscard, gnu::always_inline]] inline bool rawMouseMotionSupported()
    {
        return glfwRawMouseMotionSupported();
    }

    [[gnu::always_inline]] inline void setClipboardString(const char* content_)
    {
        glfwSetClipboardString(nullptr, content_);
    }

    [[nodiscard, gnu::always_inline]] inline const char* getClipboardString()
    {
        return glfwGetClipboardString(nullptr);
    }

    [[nodiscard, gnu::always_inline]] inline bool extensionSupported(const char* extensionName_)
    {
        return glfwExtensionSupported(extensionName_);
    }

    using GlProc = GLFWglproc;
    [[nodiscard, gnu::always_inline]] inline GlProc getProcAddress(const char* procName_)
    {
        return glfwGetProcAddress(procName_);
    }

    [[nodiscard, gnu::always_inline]] inline bool vulkanSupported()
    {
        return glfwVulkanSupported();
    }

    [[nodiscard, gnu::always_inline]] inline std::vector<const char*> getRequiredInstanceExtensions()
    {
        unsigned count;
        auto pExtensionNames = glfwGetRequiredInstanceExtensions(&count);

        std::vector<const char*> extensionNames;
        extensionNames.reserve(count);
        for(int i = 0; i < count; ++i)
        {
            extensionNames.push_back(pExtensionNames[i]);
        }
        return extensionNames;
    }
    using VkProc = GLFWvkproc;
#if defined(VK_VERSION_1_0)
    [[nodiscard, gnu::always_inline]] inline VkProc getInstanceProcAddress(VkInstance instance, const char* procName)
    {
        return glfwGetInstanceProcAddress(instance, procName);
    }

    [[nodiscard, gnu::always_inline]] inline bool getPhysicalDevicePresentationSupport(
            VkInstance instance,
            VkPhysicalDevice device,
            uint32_t queueFamily)
    {
        return glfwGetPhysicalDevicePresentationSupport(instance, device, queueFamily);
    }
#endif  // VK_VERSION_1_0

#ifdef VULKAN_HPP
    [[nodiscard, gnu::always_inline]] inline VkProc getInstanceProcAddress(const vk::Instance& instance, const char* procName)
    {
        return getInstanceProcAddress(static_cast<VkInstance>(instance), procName);
    }
    [[nodiscard, gnu::always_inline]] inline bool getPhysicalDevicePresentationSupport(
            const vk::Instance& instance,
            const vk::PhysicalDevice& device,
            uint32_t queueFamily)
    {
        return getPhysicalDevicePresentationSupport(static_cast<VkInstance>(instance), static_cast<VkPhysicalDevice>(device), queueFamily);
    }
#endif  // VULKAN_HPP

    [[nodiscard, gnu::always_inline]] inline double getTime()
    {
        return glfwGetTime();
    }

    [[gnu::always_inline]] inline void setTime(double time_)
    {
        glfwSetTime(time_);
    }

    [[nodiscard, gnu::always_inline]] inline uint64_t getTimerValue()
    {
        return glfwGetTimerValue();
    }

    [[nodiscard, gnu::always_inline]] inline uint64_t getTimerFrequency()
    {
        return glfwGetTimerFrequency();
    }
}  // namespace glfw

#endif  // GLFWPP_GLFWPP_H
