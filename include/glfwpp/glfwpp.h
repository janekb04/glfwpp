#ifndef GLFWPP_GLFWPP_H
#define GLFWPP_GLFWPP_H

#include <cassert>

#include <GLFW/glfw3.h>

#include "error.h"
#include "event.h"
#include "joystick.h"
#include "monitor.h"
#include "native.h"
#include "window.h"

namespace glfw
{
    namespace impl
    {
        void errorCallback(int errorCode_, const char* what_)
        {
            // Application programmer errors. See the GLFW docs and fix the code.
            assert(errorCode_ != GLFW_NOT_INITIALIZED);
            assert(errorCode_ != GLFW_NO_CURRENT_CONTEXT);
            assert(errorCode_ != GLFW_NO_WINDOW_CONTEXT);

            // These errors should never occur
            assert(errorCode_ != GLFW_NO_ERROR);
            assert(errorCode_ != GLFW_INVALID_ENUM);
            assert(errorCode_ != GLFW_INVALID_VALUE);

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

        void monitorCallback(GLFWmonitor* monitor_, int eventType_)
        {
            monitorEvent(Monitor{monitor_}, MonitorEventType{eventType_});
        }

        void joystickCallback(int jid_, int eventType_)
        {
            joystickEvent(Joystick{(decltype(Joystick::Joystick1))jid_}, (JoystickEvent)eventType_);
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

            glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, false);
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

    [[nodiscard]] Version getVersion()
    {
        Version version{};
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

    void setClipboardString(const char* content_)
    {
        glfwSetClipboardString(nullptr, content_);
    }

    [[nodiscard]] const char* getClipboardString()
    {
        return glfwGetClipboardString(nullptr);
    }

    [[nodiscard]] bool extensionSupported(const char* extensionName_)
    {
        return glfwExtensionSupported(extensionName_);
    }

    using GlProc = GLFWglproc;
    [[nodiscard]] GlProc getProcAddress(const char* procName_)
    {
        return glfwGetProcAddress(procName_);
    }

    namespace vulkan
    {
        [[nodiscard]] bool supported()
        {
            return glfwVulkanSupported();
        }

        [[nodiscard]] std::vector<const char*> getRequiredInstanceExtensions()
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
        [[nodiscard]] VkProc getInstanceProcAddress(VkInstance instance, const char* procName)
        {
            return glfwGetInstanceProcAddress(instance, procName);
        }

        [[nodiscard]] bool getPhysicalDevicePresentationSupport(
                VkInstance instance,
                VkPhysicalDevice device,
                uint32_t queueFamily)
        {
            return glfwGetPhysicalDevicePresentationSupport(instance, device, queueFamily);
        }
#endif  // VK_VERSION_1_0

#ifdef VULKAN_HPP
        [[nodiscard]] VkProc getInstanceProcAddress(const vk::Instance& instance, const char* procName)
        {
            return getInstanceProcAddress(static_cast<VkInstance>(instance), procName);
        }
        [[nodiscard]] bool getPhysicalDevicePresentationSupport(
                const vk::Instance& instance,
                const vk::PhysicalDevice& device,
                uint32_t queueFamily)
        {
            return getPhysicalDevicePresentationSupport(static_cast<VkInstance>(instance), static_cast<VkPhysicalDevice>(device), queueFamily);
        }
#endif  // VULKAN_HPP
    }  // namespace vulkan

    namespace timer
    {
        [[nodiscard]] double getTime()
        {
            return glfwGetTime();
        }

        void setTime(double time_)
        {
            glfwSetTime(time_);
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
