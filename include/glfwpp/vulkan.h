#ifndef GLFWPP_VULKAN_H
#define GLFWPP_VULKAN_H

#include <GLFW/glfw3.h>
#include <string>
#include <string_view>
#include <vector>

namespace glfw::vulkan
{
    [[nodiscard]] bool vulkanSupported()
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

    [[nodiscard]] VkResult createWindowSurface(
            VkInstance instance,
            GLFWwindow* window,
            const VkAllocationCallbacks* allocator,
            VkSurfaceKHR* surface)
    {
        return glfwCreateWindowSurface(instance, window, allocator, surface);
    }
#endif  // VK_VERSION_1_0
    //TODO: add Vulkan hpp support
}  // namespace glfw::vulkan

#endif  //GLFWPP_VULKAN_H
