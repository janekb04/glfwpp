#ifndef GLFWPP_GLFWPP_H
#define GLFWPP_GLFWPP_H

#include <cassert>

#include <GLFW/glfw3.h>

#include "error.h"
#include "event.h"
#include "joystick.h"
#include "monitor.h"
#include "version.h"
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
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            assert(errorCode_ != GLFW_NO_ERROR);
#endif
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

        inline void monitorCallback(GLFWmonitor* monitor_, int eventType_)
        {
            monitorEvent(Monitor{monitor_}, MonitorEventType{eventType_});
        }

        inline void joystickCallback(int jid_, int eventType_)
        {
            joystickEvent(Joystick{static_cast<decltype(Joystick::Joystick1)>(jid_)}, static_cast<JoystickEvent>(eventType_));
        }
    }  // namespace impl

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
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
#endif

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

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, false);  // disable deprecated behavior
#endif
            if(!glfwInit())
            {
                throw glfw::Error("Could not initialize GLFW");
            }

            glfwSetMonitorCallback(impl::monitorCallback);
            glfwSetJoystickCallback(impl::joystickCallback);

            return {};
        }
    };

    [[nodiscard]] inline GlfwLibrary init();

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    [[nodiscard]] inline bool rawMouseMotionSupported()
    {
        return glfwRawMouseMotionSupported();
    }
#endif

    inline void setClipboardString(const char* content_)
    {
        glfwSetClipboardString(nullptr, content_);
    }

    [[nodiscard]] inline const char* getClipboardString()
    {
        return glfwGetClipboardString(nullptr);
    }

    [[nodiscard]] inline bool extensionSupported(const char* extensionName_)
    {
        return glfwExtensionSupported(extensionName_);
    }

    using GlProc = GLFWglproc;
    [[nodiscard]] inline GlProc getProcAddress(const char* procName_)
    {
        return glfwGetProcAddress(procName_);
    }

    [[nodiscard]] inline bool vulkanSupported()
    {
        return glfwVulkanSupported();
    }

    [[nodiscard]] inline std::vector<const char*> getRequiredInstanceExtensions()
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
    [[nodiscard]] inline VkProc getInstanceProcAddress(VkInstance instance, const char* procName)
    {
        return glfwGetInstanceProcAddress(instance, procName);
    }

    [[nodiscard]] inline bool getPhysicalDevicePresentationSupport(
            VkInstance instance,
            VkPhysicalDevice device,
            uint32_t queueFamily)
    {
        return glfwGetPhysicalDevicePresentationSupport(instance, device, queueFamily);
    }
#endif  // VK_VERSION_1_0

#ifdef VULKAN_HPP
    [[nodiscard]] inline VkProc getInstanceProcAddress(const vk::Instance& instance, const char* procName)
    {
        return getInstanceProcAddress(static_cast<VkInstance>(instance), procName);
    }
    [[nodiscard]] inline bool getPhysicalDevicePresentationSupport(
            const vk::Instance& instance,
            const vk::PhysicalDevice& device,
            uint32_t queueFamily)
    {
        return getPhysicalDevicePresentationSupport(static_cast<VkInstance>(instance), static_cast<VkPhysicalDevice>(device), queueFamily);
    }
#endif  // VULKAN_HPP

    [[nodiscard]] inline double getTime()
    {
        return glfwGetTime();
    }

    inline void setTime(double time_)
    {
        glfwSetTime(time_);
    }

    [[nodiscard]] inline uint64_t getTimerValue()
    {
        return glfwGetTimerValue();
    }

    [[nodiscard]] inline uint64_t getTimerFrequency()
    {
        return glfwGetTimerFrequency();
    }
}  // namespace glfw

#endif  // GLFWPP_GLFWPP_H
