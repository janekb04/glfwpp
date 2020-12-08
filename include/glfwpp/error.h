#ifndef GLFWPP_ERROR_H
#define GLFWPP_ERROR_H

#include <stdexcept>

#define GLFWPP_ERROR_CLASS(NAME, BASE)                \
    class NAME : public BASE                          \
    {                                                 \
    public:                                           \
        explicit NAME(const char* message) noexcept : \
            BASE(message) {}                          \
                                                      \
        const char* what() const noexcept             \
        {                                             \
            return BASE::what();                      \
        }                                             \
    };

namespace glfw
{
    GLFWPP_ERROR_CLASS(Error, std::runtime_error)

    GLFWPP_ERROR_CLASS(APIUnavailableError, Error)
    GLFWPP_ERROR_CLASS(VersionUnavailableError, Error)
    GLFWPP_ERROR_CLASS(PlatformError, Error)
    GLFWPP_ERROR_CLASS(FormatUnavailableError, Error)
}  // namespace glfw

#undef GLFWPP_ERROR_CLASS

#endif  // GLFWPP_ERROR_H