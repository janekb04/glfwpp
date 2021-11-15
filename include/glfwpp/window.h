#ifndef GLFWPP_WINDOW_H
#define GLFWPP_WINDOW_H

#include "error.h"
#include "event.h"
#include "helper.h"
#include "monitor.h"
#include "version.h"
#include <GLFW/glfw3.h>
#include <optional>

namespace glfw
{
    inline constexpr int dontCare = GLFW_DONT_CARE;
    enum class ClientApi
    {
        OpenGl = GLFW_OPENGL_API,
        OpenGles = GLFW_OPENGL_ES_API,
        None = GLFW_NO_API
    };
    enum class ContextCreationApi
    {
        Native = GLFW_NATIVE_CONTEXT_API,
        Egl = GLFW_EGL_CONTEXT_API,
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        OsMesa = GLFW_OSMESA_CONTEXT_API
#endif
    };
    enum class ContextRobustness
    {
        NoRobustness = GLFW_NO_ROBUSTNESS,
        NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
        LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET
    };
    enum class ContextReleaseBehavior
    {
        Any = GLFW_ANY_RELEASE_BEHAVIOR,
        Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,
        None = GLFW_RELEASE_BEHAVIOR_NONE
    };
    enum class OpenGlProfile
    {
        Any = GLFW_OPENGL_ANY_PROFILE,
        Compat = GLFW_OPENGL_COMPAT_PROFILE,
        Core = GLFW_OPENGL_CORE_PROFILE
    };
    struct WindowHints
    {
        bool resizable = true;
        bool visible = true;
        bool decorated = true;
        bool focused = true;
        bool autoIconify = true;
        bool floating = false;
        bool maximized = false;
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        bool centerCursor = true;
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        bool transparentFramebuffer = false;
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        bool focusOnShow = true;
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        bool scaleToMonitor = false;
#endif

        int redBits = 8;
        int greenBits = 8;
        int blueBits = 8;
        int alphaBits = 8;
        int depthBits = 24;
        int stencilBits = 8;
        int accumRedBits = 0;
        int accumGreenBits = 0;
        int accumBlueBits = 0;
        int accumAlphaBits = 0;

        int auxBuffers = 0;
        int samples = 0;
        int refreshRate = dontCare;
        bool stereo = false;
        bool srgbCapable = false;
        bool doubleBuffer = true;

        ClientApi clientApi = ClientApi::OpenGl;
        ContextCreationApi contextCreationApi = ContextCreationApi::Native;
        int contextVersionMajor = 1;
        int contextVersionMinor = 0;
        ContextRobustness contextRobustness = ContextRobustness::NoRobustness;
        ContextReleaseBehavior contextReleaseBehavior = ContextReleaseBehavior::Any;
        bool openglForwardCompat = false;
        bool openglDebugContext = false;
        OpenGlProfile openglProfile = OpenGlProfile::Any;

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        bool cocoaRetinaFramebuffer = true;
        const char* cocoaFrameName = "";
        bool cocoaGraphicsSwitching = false;
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        const char* x11ClassName = "";
        const char* x11InstanceName = "";
#endif

        void apply() const
        {
            glfwWindowHint(GLFW_RESIZABLE, resizable);
            glfwWindowHint(GLFW_VISIBLE, visible);
            glfwWindowHint(GLFW_DECORATED, decorated);
            glfwWindowHint(GLFW_FOCUSED, focused);
            glfwWindowHint(GLFW_AUTO_ICONIFY, autoIconify);
            glfwWindowHint(GLFW_FLOATING, floating);
            glfwWindowHint(GLFW_MAXIMIZED, maximized);
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            glfwWindowHint(GLFW_CENTER_CURSOR, centerCursor);
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, transparentFramebuffer);
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            glfwWindowHint(GLFW_FOCUS_ON_SHOW, focusOnShow);
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, scaleToMonitor);
#endif

            glfwWindowHint(GLFW_RED_BITS, redBits);
            glfwWindowHint(GLFW_GREEN_BITS, greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, blueBits);
            glfwWindowHint(GLFW_ALPHA_BITS, alphaBits);
            glfwWindowHint(GLFW_DEPTH_BITS, depthBits);
            glfwWindowHint(GLFW_STENCIL_BITS, stencilBits);
            glfwWindowHint(GLFW_ACCUM_RED_BITS, accumRedBits);
            glfwWindowHint(GLFW_ACCUM_GREEN_BITS, accumGreenBits);
            glfwWindowHint(GLFW_ACCUM_BLUE_BITS, accumBlueBits);
            glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, accumAlphaBits);

            glfwWindowHint(GLFW_AUX_BUFFERS, auxBuffers);
            glfwWindowHint(GLFW_SAMPLES, samples);
            glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
            glfwWindowHint(GLFW_STEREO, stereo);
            glfwWindowHint(GLFW_SRGB_CAPABLE, srgbCapable);
            glfwWindowHint(GLFW_DOUBLEBUFFER, doubleBuffer);

            glfwWindowHint(GLFW_CLIENT_API, static_cast<int>(clientApi));
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, static_cast<int>(contextCreationApi));
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);
            glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, static_cast<int>(contextRobustness));
            glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, static_cast<int>(contextReleaseBehavior));
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, openglForwardCompat);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, openglDebugContext);
            glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(openglProfile));

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, cocoaRetinaFramebuffer);
            glfwWindowHintString(GLFW_COCOA_FRAME_NAME, cocoaFrameName);
            glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, cocoaGraphicsSwitching);
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
            glfwWindowHintString(GLFW_X11_CLASS_NAME, x11ClassName);
            glfwWindowHintString(GLFW_X11_INSTANCE_NAME, x11InstanceName);
#endif
        }
    };
    using Image = GLFWimage;

    class Cursor : public detail::OwningPtr<GLFWcursor>
    {
    public:
        using detail::OwningPtr<GLFWcursor>::OwningPtr;

        Cursor() noexcept = default;
        Cursor(Cursor&&) noexcept = default;

        Cursor& operator=(Cursor&& other) noexcept
        {
            glfwDestroyCursor(static_cast<GLFWcursor*>(*this));
            static_cast<detail::OwningPtr<GLFWcursor>&>(*this) = std::move(other);
            return *this;
        }

        ~Cursor() noexcept
        {
            glfwDestroyCursor(static_cast<GLFWcursor*>(*this));
        }

    public:
        [[nodiscard]] static Cursor createCursor(const Image& image_, int xHot_, int yHot_)
        {
            return Cursor{glfwCreateCursor(&image_, xHot_, yHot_)};
        }
        [[nodiscard]] static Cursor createStandardCursorArrow()
        {
            return Cursor{glfwCreateStandardCursor(GLFW_ARROW_CURSOR)};
        }
        [[nodiscard]] static Cursor createStandardCursorIBeam()
        {
            return Cursor{glfwCreateStandardCursor(GLFW_IBEAM_CURSOR)};
        }
        [[nodiscard]] static Cursor createStandardCursorCrosshair()
        {
            return Cursor{glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR)};
        }
        [[nodiscard]] static Cursor createStandardCursorHand()
        {
            return Cursor{glfwCreateStandardCursor(GLFW_HAND_CURSOR)};
        }
        [[nodiscard]] static Cursor createStandardCursorHorizontalResize()
        {
            return Cursor{glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR)};
        }
        [[nodiscard]] static Cursor createStandardCursorVerticalResize()
        {
            return Cursor{glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR)};
        }
    };
    enum class CursorMode
    {
        Normal = GLFW_CURSOR_NORMAL,
        Disabled = GLFW_CURSOR_DISABLED,
        Hidden = GLFW_CURSOR_HIDDEN
    };
    class KeyCode
    {
    public:
        enum
        {
            Unknown = GLFW_KEY_UNKNOWN,
            Space = GLFW_KEY_SPACE,
            Apostrophe = GLFW_KEY_APOSTROPHE,
            Comma = GLFW_KEY_COMMA,
            Minus = GLFW_KEY_MINUS,
            Period = GLFW_KEY_PERIOD,
            Slash = GLFW_KEY_SLASH,
            Zero = GLFW_KEY_0,
            One = GLFW_KEY_1,
            Two = GLFW_KEY_2,
            Three = GLFW_KEY_3,
            Four = GLFW_KEY_4,
            Five = GLFW_KEY_5,
            Six = GLFW_KEY_6,
            Seven = GLFW_KEY_7,
            Eight = GLFW_KEY_8,
            Nine = GLFW_KEY_9,
            Semicolon = GLFW_KEY_SEMICOLON,
            Equal = GLFW_KEY_EQUAL,
            A = GLFW_KEY_A,
            B = GLFW_KEY_B,
            C = GLFW_KEY_C,
            D = GLFW_KEY_D,
            E = GLFW_KEY_E,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            I = GLFW_KEY_I,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            M = GLFW_KEY_M,
            N = GLFW_KEY_N,
            O = GLFW_KEY_O,
            P = GLFW_KEY_P,
            Q = GLFW_KEY_Q,
            R = GLFW_KEY_R,
            S = GLFW_KEY_S,
            T = GLFW_KEY_T,
            U = GLFW_KEY_U,
            V = GLFW_KEY_V,
            W = GLFW_KEY_W,
            X = GLFW_KEY_X,
            Y = GLFW_KEY_Y,
            Z = GLFW_KEY_Z,
            LeftBracket = GLFW_KEY_LEFT_BRACKET,
            Backslash = GLFW_KEY_BACKSLASH,
            RightBracket = GLFW_KEY_RIGHT_BRACKET,
            GraveAccent = GLFW_KEY_GRAVE_ACCENT,
            World1 = GLFW_KEY_WORLD_1,
            World2 = GLFW_KEY_WORLD_2,
            Escape = GLFW_KEY_ESCAPE,
            Enter = GLFW_KEY_ENTER,
            Tab = GLFW_KEY_TAB,
            Backspace = GLFW_KEY_BACKSPACE,
            Insert = GLFW_KEY_INSERT,
            Delete = GLFW_KEY_DELETE,
            Right = GLFW_KEY_RIGHT,
            Left = GLFW_KEY_LEFT,
            Down = GLFW_KEY_DOWN,
            Up = GLFW_KEY_UP,
            PageUp = GLFW_KEY_PAGE_UP,
            PageDown = GLFW_KEY_PAGE_DOWN,
            Home = GLFW_KEY_HOME,
            End = GLFW_KEY_END,
            CapsLock = GLFW_KEY_CAPS_LOCK,
            ScrollLock = GLFW_KEY_SCROLL_LOCK,
            NumLock = GLFW_KEY_NUM_LOCK,
            PrintScreen = GLFW_KEY_PRINT_SCREEN,
            Pause = GLFW_KEY_PAUSE,
            F1 = GLFW_KEY_F1,
            F2 = GLFW_KEY_F2,
            F3 = GLFW_KEY_F3,
            F4 = GLFW_KEY_F4,
            F5 = GLFW_KEY_F5,
            F6 = GLFW_KEY_F6,
            F7 = GLFW_KEY_F7,
            F8 = GLFW_KEY_F8,
            F9 = GLFW_KEY_F9,
            F10 = GLFW_KEY_F10,
            F11 = GLFW_KEY_F11,
            F12 = GLFW_KEY_F12,
            F13 = GLFW_KEY_F13,
            F14 = GLFW_KEY_F14,
            F15 = GLFW_KEY_F15,
            F16 = GLFW_KEY_F16,
            F17 = GLFW_KEY_F17,
            F18 = GLFW_KEY_F18,
            F19 = GLFW_KEY_F19,
            F20 = GLFW_KEY_F20,
            F21 = GLFW_KEY_F21,
            F22 = GLFW_KEY_F22,
            F23 = GLFW_KEY_F23,
            F24 = GLFW_KEY_F24,
            F25 = GLFW_KEY_F25,
            KeyPad0 = GLFW_KEY_KP_0,
            KeyPad1 = GLFW_KEY_KP_1,
            KeyPad2 = GLFW_KEY_KP_2,
            KeyPad3 = GLFW_KEY_KP_3,
            KeyPad4 = GLFW_KEY_KP_4,
            KeyPad5 = GLFW_KEY_KP_5,
            KeyPad6 = GLFW_KEY_KP_6,
            KeyPad7 = GLFW_KEY_KP_7,
            KeyPad8 = GLFW_KEY_KP_8,
            KeyPad9 = GLFW_KEY_KP_9,
            KeyPadDecimal = GLFW_KEY_KP_DECIMAL,
            KeyPadDivide = GLFW_KEY_KP_DIVIDE,
            KeyPadMultiply = GLFW_KEY_KP_MULTIPLY,
            KeyPadSubtract = GLFW_KEY_KP_SUBTRACT,
            KeyPadAdd = GLFW_KEY_KP_ADD,
            KeyPadEnter = GLFW_KEY_KP_ENTER,
            KeyPadEqual = GLFW_KEY_KP_EQUAL,
            LeftShift = GLFW_KEY_LEFT_SHIFT,
            LeftControl = GLFW_KEY_LEFT_CONTROL,
            LeftAlt = GLFW_KEY_LEFT_ALT,
            LeftSuper = GLFW_KEY_LEFT_SUPER,
            RightShift = GLFW_KEY_RIGHT_SHIFT,
            RightControl = GLFW_KEY_RIGHT_CONTROL,
            RightAlt = GLFW_KEY_RIGHT_ALT,
            RightSuper = GLFW_KEY_RIGHT_SUPER,
            Menu = GLFW_KEY_MENU,
            MaxValue = GLFW_KEY_LAST
        };

    private:
        using EnumType = decltype(Unknown);
        EnumType _value;
        friend class Window;

    public:
        KeyCode() = default;
        constexpr KeyCode(EnumType value_) :
            _value{value_}
        {
        }
        KeyCode(const KeyCode&) = default;
        KeyCode& operator=(const KeyCode&) = default;
        operator EnumType() const
        {
            return _value;
        }
        explicit operator bool() = delete;

    public:
        [[nodiscard]] friend const char* getKeyName(EnumType key_)
        {
            return glfwGetKeyName(key_, 0);
        }

        [[nodiscard]] const char* getName() const
        {
            return glfwGetKeyName(_value, 0);
        }
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] int getScanCode() const
        {
            return glfwGetKeyScancode(_value);
        }
#endif
    };
    [[nodiscard]] inline const char* getKeyName(KeyCode::EnumType);
    [[nodiscard]] inline const char* getKeyName(int scanCode_)
    {
        return glfwGetKeyName(KeyCode::Unknown, scanCode_);
    }
    enum class ModifierKeyBit
    {
        Shift = GLFW_MOD_SHIFT,
        Control = GLFW_MOD_CONTROL,
        Alt = GLFW_MOD_ALT,
        Super = GLFW_MOD_SUPER,
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        CapsLock = GLFW_MOD_CAPS_LOCK,
        NumLock = GLFW_MOD_NUM_LOCK
#endif
    };
    GLFWPP_ENUM_FLAGS_OPERATORS(ModifierKeyBit)
    enum class MouseButton
    {
        One = GLFW_MOUSE_BUTTON_1,
        Two = GLFW_MOUSE_BUTTON_2,
        Three = GLFW_MOUSE_BUTTON_3,
        Four = GLFW_MOUSE_BUTTON_4,
        Five = GLFW_MOUSE_BUTTON_5,
        Six = GLFW_MOUSE_BUTTON_6,
        Seven = GLFW_MOUSE_BUTTON_7,
        Eight = GLFW_MOUSE_BUTTON_8,
        Left = GLFW_MOUSE_BUTTON_LEFT,
        Right = GLFW_MOUSE_BUTTON_RIGHT,
        Middle = GLFW_MOUSE_BUTTON_MIDDLE,
        MaxValue = GLFW_MOUSE_BUTTON_LAST
    };
    enum class KeyState
    {
        Press = GLFW_PRESS,
        Release = GLFW_RELEASE,
        Repeat = GLFW_REPEAT
    };
    enum class MouseButtonState
    {
        Press = GLFW_PRESS,
        Release = GLFW_RELEASE
    };

    class Window
    {
    private:
        class HandleContainer : public detail::OwningPtr<GLFWwindow>
        {
        public:
            using detail::OwningPtr<GLFWwindow>::OwningPtr;

            HandleContainer(HandleContainer&& other) noexcept :
                detail::OwningPtr<GLFWwindow>{std::move(other)}
            {
                // NOTE: We use the fact that _handle is the first member of
                // class Window, which means that its address `this` is equal
                // to the address `this` of its containing Window object.
                // This is done to prevent HandleContainer from needing to have
                // a pointer to the enclosing Window class object.
                if(static_cast<GLFWwindow*>(*this))
                    _setPointerFromHandle(static_cast<GLFWwindow*>(*this), reinterpret_cast<Window*>(this));
            }

            HandleContainer& operator=(HandleContainer&& other) noexcept
            {
                glfwDestroyWindow(static_cast<GLFWwindow*>(*this));
                static_cast<detail::OwningPtr<GLFWwindow>&>(*this) = std::move(other);
                // NOTE: as above
                if(static_cast<GLFWwindow*>(*this))
                    _setPointerFromHandle(static_cast<GLFWwindow*>(*this), reinterpret_cast<Window*>(this));

                return *this;
            }

            ~HandleContainer() noexcept
            {
                glfwDestroyWindow(static_cast<GLFWwindow*>(*this));
            }
        } _handle;
        detail::OwningPtr<void> _userPtr;

    public:
        Event<Window&, int, int> posEvent;
        Event<Window&, int, int> sizeEvent;
        Event<Window&> closeEvent;
        Event<Window&> refreshEvent;
        Event<Window&, bool> focusEvent;
        Event<Window&, bool> iconifyEvent;
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        Event<Window&, bool> maximizeEvent;
#endif
        Event<Window&, int, int> framebufferSizeEvent;
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        Event<Window&, float, float> contentScaleEvent;
#endif

    private:
        static Window& _getWrapperFromHandle(GLFWwindow* handle_)
        {
            return *static_cast<Window*>(glfwGetWindowUserPointer(handle_));
        }
        static void _setPointerFromHandle(GLFWwindow* handle_, Window* ptr_)
        {
            glfwSetWindowUserPointer(handle_, ptr_);
        }

    private:
        static void _posCallback(GLFWwindow* window_, int xPos_, int yPos_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.posEvent(wrapper, xPos_, yPos_);
        }
        static void _sizeCallback(GLFWwindow* window_, int width_, int height_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.sizeEvent(wrapper, width_, height_);
        }
        static void _closeCallback(GLFWwindow* window_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.closeEvent(wrapper);
        }
        static void _refreshCallback(GLFWwindow* window_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.refreshEvent(wrapper);
        }
        static void _focusCallback(GLFWwindow* window_, int value_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.focusEvent(wrapper, value_);
        }
        static void _iconifyCallback(GLFWwindow* window_, int value_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.iconifyEvent(wrapper, value_);
        }
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        static void _maximizeCallback(GLFWwindow* window_, int value_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.maximizeEvent(wrapper, value_);
        }
#endif
        static void _framebufferSizeCallback(GLFWwindow* window_, int width_, int height_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.framebufferSizeEvent(wrapper, width_, height_);
        }
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        static void _contentScaleCallback(GLFWwindow* window_, float xScale_, float yScale_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.contentScaleEvent(wrapper, xScale_, yScale_);
        }
#endif

    public:
        Event<Window&, KeyCode, int, KeyState, ModifierKeyBit> keyEvent;
        Event<Window&, unsigned int> charEvent;
        Event<Window&, MouseButton, MouseButtonState, ModifierKeyBit> mouseButtonEvent;
        Event<Window&, double, double> cursorPosEvent;
        Event<Window&, bool> cursorEnterEvent;
        Event<Window&, double, double> scrollEvent;
        Event<Window&, std::vector<const char*>> dropEvent;

    private:
        static void _keyCallback(GLFWwindow* window_, int key_, int scanCode_, int state_, int mods_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.keyEvent(wrapper, static_cast<KeyCode::EnumType>(key_), scanCode_, static_cast<KeyState>(state_), static_cast<ModifierKeyBit>(mods_));
        }
        static void _charCallback(GLFWwindow* window_, unsigned int codePoint_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.charEvent(wrapper, codePoint_);
        }
        static void _mouseButtonCallback(GLFWwindow* window_, int button_, int state_, int mods_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.mouseButtonEvent(wrapper, static_cast<MouseButton>(button_), static_cast<MouseButtonState>(state_), static_cast<ModifierKeyBit>(mods_));
        }
        static void _cursorPosCallback(GLFWwindow* window_, double xPos_, double yPos_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.cursorPosEvent(wrapper, xPos_, yPos_);
        }
        static void _cursorEnterCallback(GLFWwindow* window_, int value_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.cursorEnterEvent(wrapper, static_cast<bool>(value_));
        }
        static void _scrollCallback(GLFWwindow* window_, double xOffset_, double yOffset_)
        {
            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.scrollEvent(wrapper, xOffset_, yOffset_);
        }
        static void _dropCallback(GLFWwindow* window_, int count_, const char** pPaths_)
        {
            std::vector<const char*> paths;
            paths.reserve(count_);

            for(int i = 0; i < count_; ++i)
            {
                paths.emplace_back(pPaths_[i]);
            }

            Window& wrapper = _getWrapperFromHandle(window_);
            wrapper.dropEvent(wrapper, paths);
        }

    public:
        explicit Window() noexcept = default;
        explicit Window(std::nullptr_t) noexcept :
            Window{}
        {
        }

        //Takes ownership
        explicit Window(GLFWwindow* handle_) :
            _handle{handle_},
            _userPtr{}
        {
            if(_handle)
            {
                _setPointerFromHandle(_handle, this);

                glfwSetWindowPosCallback(_handle, _posCallback);
                glfwSetWindowSizeCallback(_handle, _sizeCallback);
                glfwSetWindowCloseCallback(_handle, _closeCallback);
                glfwSetWindowRefreshCallback(_handle, _refreshCallback);
                glfwSetWindowFocusCallback(_handle, _focusCallback);
                glfwSetWindowIconifyCallback(_handle, _iconifyCallback);
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
                glfwSetWindowMaximizeCallback(_handle, _maximizeCallback);
#endif
                glfwSetFramebufferSizeCallback(_handle, _framebufferSizeCallback);
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
                glfwSetWindowContentScaleCallback(_handle, _contentScaleCallback);
#endif

                glfwSetKeyCallback(_handle, _keyCallback);
                glfwSetCharCallback(_handle, _charCallback);
                glfwSetMouseButtonCallback(_handle, _mouseButtonCallback);
                glfwSetCursorPosCallback(_handle, _cursorPosCallback);
                glfwSetCursorEnterCallback(_handle, _cursorEnterCallback);
                glfwSetScrollCallback(_handle, _scrollCallback);
                glfwSetDropCallback(_handle, _dropCallback);
            }
        }

        Window(int width_,
                int height_,
                const char* title_,
                const Monitor* monitor_ = nullptr,
                const Window* share_ = nullptr) :
            Window{glfwCreateWindow(
                    width_,
                    height_,
                    title_,
                    monitor_ ? static_cast<GLFWmonitor*>(*monitor_) : nullptr,
                    share_ ? static_cast<GLFWwindow*>(share_->_handle) : nullptr)}
        {
        }

        Window(const Window&) = delete;

        Window& operator=(const Window&) = delete;

        Window(Window&& other) noexcept = default;

        Window& operator=(Window&& other) noexcept = default;

        //Retains ownership
        operator GLFWwindow*() const
        {
            return _handle;
        }

        explicit operator bool() const = delete;

        [[nodiscard]] bool shouldClose() const
        {
            return glfwWindowShouldClose(_handle);
        }

        void setShouldClose(bool value_)
        {
            glfwSetWindowShouldClose(_handle, value_);
        }

        void setTitle(const char* title_)
        {
            glfwSetWindowTitle(_handle, title_);
        }

        void setIcon(const std::vector<Image>& iconCandidates_)
        {
            glfwSetWindowIcon(_handle, iconCandidates_.size(), iconCandidates_.data());
        }

        [[nodiscard]] std::tuple<int, int> getPos() const
        {
            int xPos, yPos;
            glfwGetWindowPos(_handle, &xPos, &yPos);
            return {xPos, yPos};
        }

        void setPos(int xPos_, int yPos_)
        {
            glfwSetWindowPos(_handle, xPos_, yPos_);
        }

        [[nodiscard]] std::tuple<int, int> getSize() const
        {
            int width, height;
            glfwGetWindowSize(_handle, &width, &height);
            return {width, height};
        }

        void setSizeLimits(int minWidth_, int minHeight_, int maxWidth_, int maxHeight_)
        {
            glfwSetWindowSizeLimits(_handle, minWidth_, minHeight_, maxWidth_, maxHeight_);
        }

        void setAspectRation(int numerator_, int denominator_)
        {
            glfwSetWindowAspectRatio(_handle, numerator_, denominator_);
        }

        void setSize(int width_, int height_)
        {
            glfwSetWindowSize(_handle, width_, height_);
        }

        [[nodiscard]] std::tuple<int, int> getFramebufferSize() const
        {
            int width, height;
            glfwGetFramebufferSize(_handle, &width, &height);
            return {width, height};
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] std::tuple<float, float> getContentScale() const
        {
            float xScale, yScale;
            glfwGetWindowContentScale(_handle, &xScale, &yScale);
            return {xScale, yScale};
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] float getOpacity() const
        {
            return glfwGetWindowOpacity(_handle);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setOpacity(float opacity_)
        {
            glfwSetWindowOpacity(_handle, opacity_);
        }
#endif

        void iconify()
        {
            glfwIconifyWindow(_handle);
        }

        void restore()
        {
            glfwRestoreWindow(_handle);
        }

        void maximize()
        {
            glfwMaximizeWindow(_handle);
        }

        void show()
        {
            glfwShowWindow(_handle);
        }

        void hide()
        {
            glfwHideWindow(_handle);
        }

        void focus()
        {
            glfwFocusWindow(_handle);
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void requestAttention()
        {
            glfwRequestWindowAttention(_handle);
        }
#endif

        [[nodiscard]] Monitor getMonitor() const
        {
            return Monitor{glfwGetWindowMonitor(_handle)};
        }

        void setMonitor(Monitor monitor_, int xPos_, int yPos_, int width_, int height_, int refreshRate_)
        {
            glfwSetWindowMonitor(_handle, static_cast<GLFWmonitor*>(monitor_), xPos_, yPos_, width_, height_, refreshRate_);
        }

        [[nodiscard]] bool getAttribFocused() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_FOCUSED);
        }

        [[nodiscard]] bool getAttribIconified() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_ICONIFIED);
        }

        [[nodiscard]] bool getAttribMaximized() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_MAXIMIZED);
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] bool getAttribHovered() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_HOVERED);
        }
#endif

        [[nodiscard]] bool getAttribVisible() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_VISIBLE);
        }

        [[nodiscard]] bool getAttribResizable() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_RESIZABLE);
        }

        [[nodiscard]] bool getAttribDecorated() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_DECORATED);
        }

        [[nodiscard]] bool getAttribAutoIconify() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_AUTO_ICONIFY);
        }

        [[nodiscard]] bool getAttribFloating() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_FLOATING);
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] bool getAttribTransparentFramebuffer() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_TRANSPARENT_FRAMEBUFFER);
        }
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] bool getAttribFocusOnShow() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_FOCUS_ON_SHOW);
        }
#endif

        [[nodiscard]] ClientApi getAttribClientApi() const
        {
            return static_cast<ClientApi>(glfwGetWindowAttrib(_handle, GLFW_CLIENT_API));
        }

        [[nodiscard]] ContextCreationApi getAttribContextCreationApi() const
        {
            return static_cast<ContextCreationApi>(glfwGetWindowAttrib(_handle, GLFW_CONTEXT_CREATION_API));
        }

        [[nodiscard]] Version getAttribContextVersion() const
        {
            return {
                    glfwGetWindowAttrib(_handle, GLFW_CONTEXT_VERSION_MAJOR),
                    glfwGetWindowAttrib(_handle, GLFW_CONTEXT_VERSION_MINOR),
                    glfwGetWindowAttrib(_handle, GLFW_CONTEXT_REVISION)};
        }

        [[nodiscard]] bool getAttribOpenGlForwardCompat() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_OPENGL_FORWARD_COMPAT);
        }

        [[nodiscard]] bool getAttribOpenGlDebugContext() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_OPENGL_DEBUG_CONTEXT);
        }

        [[nodiscard]] OpenGlProfile getAttribOpenGlProfile() const
        {
            return static_cast<OpenGlProfile>(glfwGetWindowAttrib(_handle, GLFW_OPENGL_PROFILE));
        }

        [[nodiscard]] ContextReleaseBehavior getAttribContextReleaseBehavior() const
        {
            return static_cast<ContextReleaseBehavior>(glfwGetWindowAttrib(_handle, GLFW_CONTEXT_RELEASE_BEHAVIOR));
        }

        [[nodiscard]] bool getAttribContextNoError() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_CONTEXT_NO_ERROR);
        }

        [[nodiscard]] ContextRobustness getAttribContextRobustness() const
        {
            return static_cast<ContextRobustness>(glfwGetWindowAttrib(_handle, GLFW_CONTEXT_ROBUSTNESS));
        }

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setAttribDecorated(bool value_)
        {
            glfwSetWindowAttrib(_handle, GLFW_DECORATED, value_);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setAttribResizable(bool value_)
        {
            glfwSetWindowAttrib(_handle, GLFW_RESIZABLE, value_);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setAttribFloating(bool value_)
        {
            glfwSetWindowAttrib(_handle, GLFW_FLOATING, value_);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setAttribAutoIconify(bool value_)
        {
            glfwSetWindowAttrib(_handle, GLFW_AUTO_ICONIFY, value_);
        }
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setAttribFocusOnShow(bool value_)
        {
            glfwSetWindowAttrib(_handle, GLFW_FOCUS_ON_SHOW, value_);
        }
#endif

        void setUserPointer(void* ptr_)
        {
            _userPtr = ptr_;
        }

        [[nodiscard]] void* getUserPointer() const
        {
            return _userPtr;
        }

        void swapBuffers()
        {
            glfwSwapBuffers(_handle);
        }

    public:
        friend void makeContextCurrent(const Window& window_)
        {
            glfwMakeContextCurrent(window_._handle);
        }
        [[nodiscard]] friend Window& getCurrentContext()
        {
            return _getWrapperFromHandle(glfwGetCurrentContext());
        }

    public:
        [[nodiscard]] CursorMode getInputModeCursor() const
        {
            return static_cast<CursorMode>(glfwGetInputMode(_handle, GLFW_CURSOR));
        }
        [[nodiscard]] bool getInputModeStickyKeys() const
        {
            return glfwGetInputMode(_handle, GLFW_STICKY_KEYS);
        }
        [[nodiscard]] bool getInputModeStickyMouseButtons() const
        {
            return glfwGetInputMode(_handle, GLFW_STICKY_MOUSE_BUTTONS);
        }
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] bool getInputModeLockKeyMods() const
        {
            return glfwGetInputMode(_handle, GLFW_LOCK_KEY_MODS);
        }
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        [[nodiscard]] bool getInputModeRawMouseMotion() const
        {
            return glfwGetInputMode(_handle, GLFW_RAW_MOUSE_MOTION);
        }
#endif

        void setInputModeCursor(CursorMode mode_)
        {
            return glfwSetInputMode(_handle, GLFW_CURSOR, static_cast<int>(mode_));
        }
        void setInputModeStickyKeys(bool value_)
        {
            return glfwSetInputMode(_handle, GLFW_STICKY_KEYS, value_);
        }
        void setInputModeStickyMouseButtons(bool value_)
        {
            return glfwSetInputMode(_handle, GLFW_STICKY_MOUSE_BUTTONS, value_);
        }
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setInputModeLockKeyMods(bool value_)
        {
            return glfwSetInputMode(_handle, GLFW_LOCK_KEY_MODS, value_);
        }
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        void setInputModeRawMouseMotion(bool value_)
        {
            return glfwSetInputMode(_handle, GLFW_RAW_MOUSE_MOTION, value_);
        }
#endif

        [[nodiscard]] bool getKey(KeyCode key_) const
        {
            return glfwGetKey(_handle, key_) != GLFW_RELEASE;
        }
        [[nodiscard]] bool getMouseButton(MouseButton button_) const
        {
            return glfwGetMouseButton(_handle, static_cast<int>(button_)) != GLFW_RELEASE;
        }

        [[nodiscard]] std::tuple<double, double> getCursorPos() const
        {
            double xPos, yPos;
            glfwGetCursorPos(_handle, &xPos, &yPos);
            return {xPos, yPos};
        }
        void setCursorPos(double xPos_, double yPos_)
        {
            glfwSetCursorPos(_handle, xPos_, yPos_);
        }

        void setCursor(const Cursor& cursor_)
        {
            glfwSetCursor(_handle, static_cast<GLFWcursor*>(cursor_));
        }

#if defined(VK_VERSION_1_0)
        [[nodiscard]] VkResult createSurface(
                VkInstance instance,
                const VkAllocationCallbacks* allocator,
                VkSurfaceKHR* surface)
        {
            return glfwCreateWindowSurface(instance, _handle, allocator, surface);
        }
#endif  // VK_VERSION_1_0
#ifdef VULKAN_HPP
        [[nodiscard]] vk::SurfaceKHR createSurface(
                const vk::Instance& instance,
                const std::optional<vk::AllocationCallbacks>& allocator = std::nullopt)
        {
            VkSurfaceKHR surface;
            VkResult result;
            if(allocator)
            {
                VkAllocationCallbacks allocator_tmp = *allocator;
                result = createSurface(static_cast<VkInstance>(instance), &allocator_tmp, &surface);
            }
            else
            {
                result = createSurface(static_cast<VkInstance>(instance), nullptr, &surface);
            }

            if(result < 0)
            {
                throw Error("Could not create window surface");
            }
            return static_cast<vk::SurfaceKHR>(surface);
        }
#endif  // VULKAN_HPP
    };
    inline void makeContextCurrent(const Window& window_);
    [[nodiscard]] inline Window& getCurrentContext();

    inline void swapInterval(int interval_)
    {
        glfwSwapInterval(interval_);
    }
}  // namespace glfw

#endif  //GLFWPP_WINDOW_H
