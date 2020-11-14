#ifndef GLFWPP_ERROR_H
#define GLFWPP_ERROR_H

#include <stdexcept>

#define _GLFWPP_ERROR_CLASS(NAME, BASE)               \
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
    _GLFWPP_ERROR_CLASS(Error, std::runtime_error)

    _GLFWPP_ERROR_CLASS(NotInitializedError, Error)
    _GLFWPP_ERROR_CLASS(NoCurrentContextError, Error)
    _GLFWPP_ERROR_CLASS(OutOfMemoryError, Error)
    _GLFWPP_ERROR_CLASS(APIUnavailableError, Error)
    _GLFWPP_ERROR_CLASS(VersionUnavailableError, Error)
    _GLFWPP_ERROR_CLASS(PlatformError, Error)
    _GLFWPP_ERROR_CLASS(FormatUnavailableError, Error)
    _GLFWPP_ERROR_CLASS(NoWindowContextError, Error)
}  // namespace glfw

#endif  // GLFWPP_ERROR_H