#ifndef GLFWPP_WINDOW_H
#define GLFWPP_WINDOW_H

#include "event.h"
#include "monitor.h"
#include <GLFW/glfw3.h>

namespace glfw
{
    constexpr int DontCare = GLFW_DONT_CARE;
    enum class ClientAPI
    {
        OpenGL = GLFW_OPENGL_API,
        OpenGLES = GLFW_OPENGL_ES_API,
        None = GLFW_NO_API
    };
    enum class ContextCreationAPI
    {
        Native = GLFW_NATIVE_CONTEXT_API,
        EGL = GLFW_EGL_CONTEXT_API,
        OSMesa = GLFW_OSMESA_CONTEXT_API
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
    enum class OpenGLProfile
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
        bool centerCursor = true;
        bool transparentFramebuffer = false;
        bool focusOnShow = true;
        bool scaleToMonitor = false;

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
        int refreshRate = DontCare;
        bool stereo = false;
        bool srgbCapable = false;
        bool doubleBuffer = true;

        ClientAPI clientAPI = ClientAPI::OpenGL;
        ContextCreationAPI contextCreationAPI = ContextCreationAPI::Native;
        int contextVersionMajor = 1;
        int contextVersionMinor = 0;
        ContextRobustness contextRobustness = ContextRobustness::NoRobustness;
        ContextReleaseBehavior contextReleaseBehavior = ContextReleaseBehavior::Any;
        bool openglForwardCompat = false;
        bool openglDebugContext = false;
        OpenGLProfile openglProfile = OpenGLProfile::Any;

        bool cocoaRetinaFramebuffer = true;
        const char* cocoaFrameName = "";
        bool cocoaGraphicsSwitching = false;

        const char* x11ClassName = "";
        const char* x11InstanceName = "";

        void apply() const
        {
            glfwWindowHint(GLFW_RESIZABLE, resizable);
            glfwWindowHint(GLFW_VISIBLE, visible);
            glfwWindowHint(GLFW_DECORATED, decorated);
            glfwWindowHint(GLFW_FOCUSED, focused);
            glfwWindowHint(GLFW_AUTO_ICONIFY, autoIconify);
            glfwWindowHint(GLFW_FLOATING, floating);
            glfwWindowHint(GLFW_MAXIMIZED, maximized);
            glfwWindowHint(GLFW_CENTER_CURSOR, centerCursor);
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, transparentFramebuffer);
            glfwWindowHint(GLFW_FOCUS_ON_SHOW, focusOnShow);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, scaleToMonitor);

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

            glfwWindowHint(GLFW_CLIENT_API, (int)clientAPI);
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, (int)contextCreationAPI);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);
            glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, (int)contextRobustness);
            glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, (int)contextReleaseBehavior);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, openglForwardCompat);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, openglDebugContext);
            glfwWindowHint(GLFW_OPENGL_PROFILE, (int)openglProfile);

            glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, cocoaRetinaFramebuffer);
            glfwWindowHintString(GLFW_COCOA_FRAME_NAME, cocoaFrameName);
            glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, cocoaGraphicsSwitching);

            glfwWindowHintString(GLFW_X11_CLASS_NAME, x11ClassName);
            glfwWindowHintString(GLFW_X11_INSTANCE_NAME, x11InstanceName);
        }
    };
    using Image = GLFWimage;
    struct Version
    {
        int major;
        int minor;
        int revision;
    };

    class Cursor
    {
    private:
        GLFWcursor* _handle;

        explicit Cursor(GLFWcursor* handle) :
            _handle{handle}
        {
        }

        friend class Window;

    public:
        [[nodiscard]] static Cursor createCursor(const Image& image, int xHot, int yHot)
        {
            return Cursor{glfwCreateCursor(&image, xHot, yHot)};
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

        ~Cursor()
        {
            glfwDestroyCursor(_handle);
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
        using enum_type = decltype(Unknown);
        enum_type _value;
        friend class Window;

    public:
        KeyCode() = default;
        constexpr KeyCode(enum_type value) :
            _value{value}
        {
        }
        operator enum_type() const
        {
            return _value;
        }
        explicit operator bool() = delete;

    public:
        [[nodiscard]] friend const char* getKeyName(enum_type key)
        {
            return glfwGetKeyName(key, 0);
        }

        [[nodiscard]] const char* getName() const
        {
            return glfwGetKeyName(_value, 0);
        }
        [[nodiscard]] int getScanCode() const
        {
            return glfwGetKeyScancode(_value);
        }
    };
    [[nodiscard]] const char* getKeyName(KeyCode::enum_type);
    [[nodiscard]] const char* getKeyName(int scanCode)
    {
        return glfwGetKeyName(KeyCode::Unknown, scanCode);
    }
    enum class ModifierKeyBit
    {
        Shift = GLFW_MOD_SHIFT,
        Control = GLFW_MOD_CONTROL,
        Alt = GLFW_MOD_ALT,
        Super = GLFW_MOD_SUPER,
        CapsLock = GLFW_MOD_CAPS_LOCK,
        NumLock = GLFW_MOD_NUM_LOCK
    };
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
        GLFWwindow* _handle;
        inline static std::unordered_map<GLFWwindow*, Window*> _windows;

    public:
        Event<int, int> posEvent;
        Event<int, int> sizeEvent;
        Event<> closeEvent;
        Event<> refreshEvent;
        Event<bool> focusEvent;
        Event<bool> iconifyEvent;
        Event<bool> maximizeEvent;
        Event<int, int> framebufferSizeEvent;
        Event<float, float> contentScaleEvent;

    private:
        static void _posCallback(GLFWwindow* window, int xPos, int yPos)
        {
            _windows[window]->posEvent(xPos, yPos);
        }
        static void _sizeCallback(GLFWwindow* window, int width, int height)
        {
            _windows[window]->sizeEvent(width, height);
        }
        static void _closeCallback(GLFWwindow* window)
        {
            _windows[window]->closeEvent();
        }
        static void _refreshCallback(GLFWwindow* window)
        {
            _windows[window]->refreshEvent();
        }
        static void _focusCallback(GLFWwindow* window, int value)
        {
            _windows[window]->focusEvent(value);
        }
        static void _iconifyCallback(GLFWwindow* window, int value)
        {
            _windows[window]->iconifyEvent(value);
        }
        static void _maximizeCallback(GLFWwindow* window, int value)
        {
            _windows[window]->maximizeEvent(value);
        }
        static void _framebufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            _windows[window]->framebufferSizeEvent(width, height);
        }
        static void _contentScaleCallback(GLFWwindow* window, float xScale, float yScale)
        {
            _windows[window]->contentScaleEvent(xScale, yScale);
        }

    public:
        Event<KeyCode, int, KeyState, ModifierKeyBit> keyEvent;
        Event<unsigned int> charEvent;
        Event<MouseButton, MouseButtonState, ModifierKeyBit> mouseButtonEvent;
        Event<double, double> cursorPosEvent;
        Event<bool> cursorEnterEvent;
        Event<double, double> scrollEvent;
        Event<std::vector<std::string_view>> dropEvent;

    private:
        static void _keyCallback(GLFWwindow* window, int key, int scanCode, int state, int mods)
        {
            _windows[window]->keyEvent((KeyCode::enum_type)key, scanCode, (KeyState)state, (ModifierKeyBit)mods);
        }
        static void _charCallback(GLFWwindow* window, unsigned int codePoint)
        {
            _windows[window]->charEvent(codePoint);
        }
        static void _mouseButtonCallback(GLFWwindow* window, int button, int state, int mods)
        {
            _windows[window]->mouseButtonEvent((MouseButton)button, (MouseButtonState)state, (ModifierKeyBit)mods);
        }
        static void _cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
        {
            _windows[window]->cursorPosEvent(xPos, yPos);
        }
        static void _cursorEnterCallback(GLFWwindow* window, int value)
        {
            _windows[window]->cursorEnterEvent((bool)value);
        }
        static void _scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
        {
            _windows[window]->scrollEvent(xOffset, yOffset);
        }
        static void _dropCallback(GLFWwindow* window, int count, const char** pPaths)
        {
            std::vector<std::string_view> paths;
            paths.reserve(count);

            for(int i = 0; i < count; ++i)
            {
                paths.emplace_back(pPaths[i]);
            }

            _windows[window]->dropEvent(paths);
        }

    public:
        Window(int width,
               int height,
               const char* title,
               const Monitor* monitor = nullptr,
               const Window* share = nullptr) :
            _handle{glfwCreateWindow(
                    width,
                    height,
                    title,
                    monitor ? monitor->_handle : nullptr,
                    share ? share->_handle : nullptr)}
        {
            _windows[_handle] = this;

            glfwSetWindowPosCallback(_handle, _posCallback);
            glfwSetWindowSizeCallback(_handle, _sizeCallback);
            glfwSetWindowCloseCallback(_handle, _closeCallback);
            glfwSetWindowRefreshCallback(_handle, _refreshCallback);
            glfwSetWindowFocusCallback(_handle, _focusCallback);
            glfwSetWindowIconifyCallback(_handle, _iconifyCallback);
            glfwSetWindowMaximizeCallback(_handle, _maximizeCallback);
            glfwSetFramebufferSizeCallback(_handle, _framebufferSizeCallback);
            glfwSetWindowContentScaleCallback(_handle, _contentScaleCallback);

            glfwSetKeyCallback(_handle, _keyCallback);
            glfwSetCharCallback(_handle, _charCallback);
            glfwSetMouseButtonCallback(_handle, _mouseButtonCallback);
            glfwSetCursorPosCallback(_handle, _cursorPosCallback);
            glfwSetCursorEnterCallback(_handle, _cursorEnterCallback);
            glfwSetScrollCallback(_handle, _scrollCallback);
            glfwSetDropCallback(_handle, _dropCallback);
        }

        Window(const Window&) = delete;

        ~Window()
        {
            glfwDestroyWindow(_handle);
            _windows.erase(_handle);
        }

        [[nodiscard]] bool shouldClose() const
        {
            return glfwWindowShouldClose(_handle);
        }

        void setShouldClose(bool value)
        {
            glfwSetWindowShouldClose(_handle, true);
        }

        void setTitle(const char* title)
        {
            glfwSetWindowTitle(_handle, title);
        }

        void setIcon(const std::vector<Image>& iconCandidates)
        {
            glfwSetWindowIcon(_handle, iconCandidates.size(), iconCandidates.data());
        }

        [[nodiscard]] std::tuple<int, int> getPos() const
        {
            int xPos, yPos;
            glfwGetWindowPos(_handle, &xPos, &yPos);
            return {xPos, yPos};
        }

        void setPos(int xPos, int yPos)
        {
            glfwSetWindowPos(_handle, xPos, yPos);
        }

        [[nodiscard]] std::tuple<int, int> getSize() const
        {
            int width, height;
            glfwGetWindowSize(_handle, &width, &height);
            return {width, height};
        }

        void setSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight)
        {
            glfwSetWindowSizeLimits(_handle, minWidth, minHeight, maxWidth, maxHeight);
        }

        void setAspectRation(int numerator, int denominator)
        {
            glfwSetWindowAspectRatio(_handle, numerator, denominator);
        }

        void setSize(int width, int height)
        {
            glfwSetWindowSize(_handle, width, height);
        }

        [[nodiscard]] std::tuple<int, int> getFramebufferSize() const
        {
            int width, height;
            glfwGetFramebufferSize(_handle, &width, &height);
            return {width, height};
        }

        [[nodiscard]] std::tuple<float, float> getContentScale() const
        {
            float xScale, yScale;
            glfwGetWindowContentScale(_handle, &xScale, &yScale);
            return {xScale, yScale};
        }

        [[nodiscard]] float getOpacity() const
        {
            return glfwGetWindowOpacity(_handle);
        }

        void setOpacity(float opacity)
        {
            glfwSetWindowOpacity(_handle, opacity);
        }

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

        void requestAttention()
        {
            glfwRequestWindowAttention(_handle);
        }

        [[nodiscard]] Monitor getMonitor() const
        {
            return Monitor{glfwGetWindowMonitor(_handle)};
        }

        void setMonitor(Monitor monitor, int xPos, int yPos, int width, int height, int refreshRate)
        {
            glfwSetWindowMonitor(_handle, monitor._handle, xPos, yPos, width, height, refreshRate);
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

        [[nodiscard]] bool getAttribHovered() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_HOVERED);
        }

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

        [[nodiscard]] bool getAttribTransparentFramebuffer() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_TRANSPARENT_FRAMEBUFFER);
        }

        [[nodiscard]] bool getAttribFocusOnShow() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_FOCUS_ON_SHOW);
        }

        [[nodiscard]] ClientAPI getAttribClientAPI() const
        {
            return (ClientAPI)glfwGetWindowAttrib(_handle, GLFW_CLIENT_API);
        }

        [[nodiscard]] ContextCreationAPI getAttribContextCreationAPI() const
        {
            return (ContextCreationAPI)glfwGetWindowAttrib(_handle, GLFW_CONTEXT_CREATION_API);
        }

        [[nodiscard]] Version getAttribContextVersion() const
        {
            return {
                    glfwGetWindowAttrib(_handle, GLFW_CONTEXT_VERSION_MAJOR),
                    glfwGetWindowAttrib(_handle, GLFW_CONTEXT_VERSION_MINOR),
                    glfwGetWindowAttrib(_handle, GLFW_CONTEXT_REVISION)};
        }

        [[nodiscard]] bool getAttribOpenGLForwardCompat() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_OPENGL_FORWARD_COMPAT);
        }

        [[nodiscard]] bool getAttribOpenGLDebugContext() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_OPENGL_DEBUG_CONTEXT);
        }

        [[nodiscard]] OpenGLProfile getAttribOpenGLProfile() const
        {
            return (OpenGLProfile)glfwGetWindowAttrib(_handle, GLFW_OPENGL_PROFILE);
        }

        [[nodiscard]] ContextReleaseBehavior getAttribContextReleaseBehavior() const
        {
            return (ContextReleaseBehavior)glfwGetWindowAttrib(_handle, GLFW_CONTEXT_RELEASE_BEHAVIOR);
        }

        [[nodiscard]] bool getAttribContextNoError() const
        {
            return glfwGetWindowAttrib(_handle, GLFW_CONTEXT_NO_ERROR);
        }

        [[nodiscard]] ContextRobustness getAttribContextRobustness() const
        {
            return (ContextRobustness)glfwGetWindowAttrib(_handle, GLFW_CONTEXT_ROBUSTNESS);
        }

        void setAttribDecorated(bool value)
        {
            glfwSetWindowAttrib(_handle, GLFW_DECORATED, value);
        }

        void setAttribResizable(bool value)
        {
            glfwSetWindowAttrib(_handle, GLFW_RESIZABLE, value);
        }

        void setAttribFloating(bool value)
        {
            glfwSetWindowAttrib(_handle, GLFW_FLOATING, value);
        }

        void setAttribAutoIconify(bool value)
        {
            glfwSetWindowAttrib(_handle, GLFW_AUTO_ICONIFY, value);
        }

        void setAttribFocusOnShow(bool value)
        {
            glfwSetWindowAttrib(_handle, GLFW_FOCUS_ON_SHOW, value);
        }

        void setUserPointer(void* ptr)
        {
            glfwSetWindowUserPointer(_handle, ptr);
        }

        [[nodiscard]] void* getUserPointer() const
        {
            return glfwGetWindowUserPointer(_handle);
        }

        void swapBuffers()
        {
            glfwSwapBuffers(_handle);
        }

    public:
        friend void makeContextCurrent(const Window& window)
        {
            glfwMakeContextCurrent(window._handle);
        }
        [[nodiscard]] friend Window& getCurrentContext()
        {
            return *_windows[glfwGetCurrentContext()];
        }

    public:
        [[nodiscard]] CursorMode getInputModeCursor() const
        {
            return (CursorMode)glfwGetInputMode(_handle, GLFW_CURSOR);
        }
        [[nodiscard]] bool getInputModeStickyKeys() const
        {
            return glfwGetInputMode(_handle, GLFW_STICKY_KEYS);
        }
        [[nodiscard]] bool getInputModeStickyMouseButtons() const
        {
            return glfwGetInputMode(_handle, GLFW_STICKY_MOUSE_BUTTONS);
        }
        [[nodiscard]] bool getInputModeLockKeyMods() const
        {
            return glfwGetInputMode(_handle, GLFW_LOCK_KEY_MODS);
        }
        [[nodiscard]] bool getInputModeRawMouseMotion() const
        {
            return glfwGetInputMode(_handle, GLFW_RAW_MOUSE_MOTION);
        }

        void setInputModeCursor(CursorMode mode)
        {
            return glfwSetInputMode(_handle, GLFW_CURSOR, (int)mode);
        }
        void setInputModeStickyKeys(bool value)
        {
            return glfwSetInputMode(_handle, GLFW_STICKY_KEYS, value);
        }
        void setInputModeStickyMouseButtons(bool value)
        {
            return glfwSetInputMode(_handle, GLFW_STICKY_MOUSE_BUTTONS, value);
        }
        void setInputModeLockKeyMods(bool value)
        {
            return glfwSetInputMode(_handle, GLFW_LOCK_KEY_MODS, value);
        }
        void setInputModeRawMouseMotion(bool value)
        {
            return glfwSetInputMode(_handle, GLFW_RAW_MOUSE_MOTION, value);
        }

        [[nodiscard]] bool getKey(KeyCode key) const
        {
            return glfwGetKey(_handle, key) != GLFW_RELEASE;
        }
        [[nodiscard]] bool getMouseButton(MouseButton button) const
        {
            return glfwGetMouseButton(_handle, (int)button) != GLFW_RELEASE;
        }

        [[nodiscard]] std::tuple<double, double> getCursorPos() const
        {
            double xPos, yPos;
            glfwGetCursorPos(_handle, &xPos, &yPos);
            return {xPos, yPos};
        }
        void setCursorPos(double xPos, double yPos)
        {
            glfwSetCursorPos(_handle, xPos, yPos);
        }

        void setCursor(const Cursor& cursor)
        {
            glfwSetCursor(_handle, cursor._handle);
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
                const vk::AllocationCallbacks* allocator)
        {
            VkSurfaceKHR surface;
            VkResult result = createSurface(instance, allocator, &surface);
            if (result < 0)
            {
                throw Error("Could not create window surface");
            }
            return surface;
        }
#endif  // VULKAN_HPP
    };
    void makeContextCurrent(const Window& window);
    [[nodiscard]] Window& getCurrentContext();

    void swapInterval(int interval)
    {
        glfwSwapInterval(interval);
    }
}  // namespace glfw

#endif  //GLFWPP_WINDOW_H
