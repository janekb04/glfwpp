#ifndef GLFWPP_VERSION_H
#define GLFWPP_VERSION_H

#include <GLFW/glfw3.h>

namespace glfw
{
    struct Version
    {
        int major;
        int minor;
        int revision;
    };

    [[nodiscard]] constexpr inline Version getCompileTimeVersion()
    {
        return Version{GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION};
    }

    [[nodiscard]] inline Version getRuntimeVersion()
    {
        Version version{};
        glfwGetVersion(&version.major, &version.minor, &version.revision);
        return version;
    }

    [[nodiscard]] inline const char* getVersionString()
    {
        return glfwGetVersionString();
    }
}  // namespace glfw

#endif  // GLFWPP_VERSION_H