#ifndef GLFWPP_HELPER_H
#define GLFWPP_HELPER_H

#include <type_traits>

#define GLFWPP_ENUM_FLAGS_OPERATORS(Enum)                                                                       \
    inline std::underlying_type_t<Enum> operator~(Enum lhs)                                                            \
    {                                                                                                           \
        return ~static_cast<std::underlying_type_t<Enum>>(lhs);                                                 \
    }                                                                                                           \
    inline std::underlying_type_t<Enum> operator&(Enum lhs, Enum rhs)                                                  \
    {                                                                                                           \
        return static_cast<std::underlying_type_t<Enum>>(lhs) & static_cast<std::underlying_type_t<Enum>>(rhs); \
    }                                                                                                           \
    inline std::underlying_type_t<Enum> operator|(Enum lhs, Enum rhs)                                                  \
    {                                                                                                           \
        return static_cast<std::underlying_type_t<Enum>>(lhs) | static_cast<std::underlying_type_t<Enum>>(rhs); \
    }                                                                                                           \
    inline std::underlying_type_t<Enum> operator^(Enum lhs, Enum rhs)                                                  \
    {                                                                                                           \
        return static_cast<std::underlying_type_t<Enum>>(lhs) ^ static_cast<std::underlying_type_t<Enum>>(rhs); \
    }

#endif  //GLFWPP_HELPER_H
