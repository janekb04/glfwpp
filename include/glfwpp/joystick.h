#ifndef GLFWPP_JOYSTICK_H
#define GLFWPP_JOYSTICK_H

#include "helper.h"
#include <GLFW/glfw3.h>
#include <vector>

namespace glfw
{
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    struct GamepadState
    {
        bool buttons[15];
        float axes[6];
    };
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    enum class GamepadAxis
    {
        LeftX = GLFW_GAMEPAD_AXIS_LEFT_X,
        LeftY = GLFW_GAMEPAD_AXIS_LEFT_Y,
        RightX = GLFW_GAMEPAD_AXIS_RIGHT_X,
        RightY = GLFW_GAMEPAD_AXIS_RIGHT_Y,
        LeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
        RightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
        MaxValue = GLFW_GAMEPAD_AXIS_LAST
    };
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    enum class GamepadButton
    {
        A = GLFW_GAMEPAD_BUTTON_A,
        B = GLFW_GAMEPAD_BUTTON_B,
        X = GLFW_GAMEPAD_BUTTON_X,
        Y = GLFW_GAMEPAD_BUTTON_Y,
        LeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
        RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
        Back = GLFW_GAMEPAD_BUTTON_BACK,
        Start = GLFW_GAMEPAD_BUTTON_START,
        Guide = GLFW_GAMEPAD_BUTTON_GUIDE,
        LeftThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
        RightThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
        DpadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,
        DpadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
        DpadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
        DpadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
        Cross = GLFW_GAMEPAD_BUTTON_CROSS,
        Circle = GLFW_GAMEPAD_BUTTON_CIRCLE,
        Square = GLFW_GAMEPAD_BUTTON_SQUARE,
        Triangle = GLFW_GAMEPAD_BUTTON_TRIANGLE,
        MaxValue = GLFW_GAMEPAD_BUTTON_LAST
    };
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    enum class JoystickHatStateBit
    {
        Centered = GLFW_HAT_CENTERED,
        Up = GLFW_HAT_UP,
        Right = GLFW_HAT_RIGHT,
        Down = GLFW_HAT_DOWN,
        Left = GLFW_HAT_LEFT,
        RightUp = GLFW_HAT_RIGHT_UP,
        RightDown = GLFW_HAT_RIGHT_DOWN,
        LeftUp = GLFW_HAT_LEFT_UP,
        LeftDown = GLFW_HAT_LEFT_DOWN
    };
    GLFWPP_ENUM_FLAGS_OPERATORS(JoystickHatStateBit)
#endif
    enum class JoystickEvent
    {
        Connected = GLFW_CONNECTED,
        Disconnected = GLFW_DISCONNECTED
    };

    class Joystick
    {
    public:
        enum
        {
            Joystick1 = GLFW_JOYSTICK_1,
            Joystick2 = GLFW_JOYSTICK_2,
            Joystick3 = GLFW_JOYSTICK_3,
            Joystick4 = GLFW_JOYSTICK_4,
            Joystick5 = GLFW_JOYSTICK_5,
            Joystick6 = GLFW_JOYSTICK_6,
            Joystick7 = GLFW_JOYSTICK_7,
            Joystick8 = GLFW_JOYSTICK_8,
            Joystick9 = GLFW_JOYSTICK_9,
            Joystick10 = GLFW_JOYSTICK_10,
            Joystick11 = GLFW_JOYSTICK_11,
            Joystick12 = GLFW_JOYSTICK_12,
            Joystick13 = GLFW_JOYSTICK_13,
            Joystick14 = GLFW_JOYSTICK_14,
            Joystick15 = GLFW_JOYSTICK_15,
            Joystick16 = GLFW_JOYSTICK_16,
        };

    private:
        using EnumType = decltype(Joystick1);
        EnumType _id;

    public:
        Joystick() = default;
        constexpr Joystick(EnumType jid_) :
            _id{jid_}
        {
        }
        Joystick(const Joystick&) = default;
        Joystick& operator=(const Joystick&) = default;
        operator EnumType() const
        {
            return _id;
        }
        explicit operator bool() = delete;

    public:
        [[nodiscard]] bool isPresent() const
        {
            return glfwJoystickPresent(_id);
        }

        [[nodiscard]] std::vector<float> getAxes() const
        {
            int count;
            auto pAxes = glfwGetJoystickAxes(_id, &count);
            return {pAxes, pAxes + count};
        }

        [[nodiscard]] std::vector<bool> getButtons() const
        {
            int count;
            auto pButtons = glfwGetJoystickButtons(_id, &count);

            std::vector<bool> buttons;
            buttons.reserve(count);
            for(int i = 0; i < count; ++i)
            {
                buttons.push_back(pButtons[i] != GLFW_RELEASE);
            }

            return buttons;
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] std::vector<JoystickHatStateBit> getHats() const
        {
            int count;
            auto pHats = glfwGetJoystickHats(_id, &count);

            std::vector<JoystickHatStateBit> hats;
            hats.reserve(count);
            for(int i = 0; i < count; ++i)
            {
                hats.push_back(static_cast<JoystickHatStateBit>(pHats[i]));
            }
            return hats;
        }
#endif

        [[nodiscard]] const char* getName() const
        {
            return glfwGetJoystickName(_id);
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] const char* getGuid() const
        {
            return glfwGetJoystickGUID(_id);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setUserPointer(void* ptr_)
        {
            glfwSetJoystickUserPointer(_id, ptr_);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] void* getUserPointer() const
        {
            return glfwGetJoystickUserPointer(_id);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] bool isGamepad() const
        {
            return glfwJoystickIsGamepad(_id);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] const char* getGamepadName() const
        {
            return glfwGetGamepadName(_id);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] GamepadState getGamepadState() const
        {
            GLFWgamepadstate state;
            glfwGetGamepadState(_id, &state);

            GamepadState result{};
            {
                int i = 0;
                for(auto&& button : result.buttons)
                {
                    button = state.buttons[i++] != GLFW_RELEASE;
                }
            }
            {
                int i = 0;
                for(auto&& axis : result.axes)
                {
                    axis = state.axes[i++];
                }
            }
            return result;
        }
#endif
    };

    inline Event<Joystick, JoystickEvent> joystickEvent;

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    [[nodiscard]] inline bool updateGamepadMappings(const char* string_)
    {
        return glfwUpdateGamepadMappings(string_);
    }
#endif
}  // namespace glfw

#endif  //GLFWPP_JOYSTICK_H
