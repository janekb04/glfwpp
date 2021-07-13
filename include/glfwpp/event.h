#ifndef GLFWPP_EVENT_H
#define GLFWPP_EVENT_H

#include <functional>
#include <list>

namespace glfw
{
    template<typename... Args>
    class Event
    {
    private:
        std::function<void(Args...)> _handler;

    public:
        template<typename CallbackT>
        void setCallback(CallbackT&& callback_)
        {
            _handler = std::forward<CallbackT>(callback_);
        }
        void operator()(Args... args_)
        {
            if(_handler)
            {
                _handler(args_...);
            }
        }
    };

    template<typename... Args>
    class StaticEvent
    {
    private:
        static std::function<void(Args...)> _handler;

    public:
        template<typename CallbackT>
        static void setCallback(CallbackT&& callback_)
        {
            _handler = std::forward<CallbackT>(callback_);
        }
        static void call(Args... args_)
        {
            if(_handler)
            {
                _handler(args_...);
            }
        }
    };

    // static
    template<typename... Args>
    std::function<void(Args...)> StaticEvent<Args...>::_handler;

    [[gnu::always_inline]] inline void pollEvents()
    {
        glfwPollEvents();
    }

    [[gnu::always_inline]] inline void waitEvents()
    {
        glfwWaitEvents();
    }

    [[gnu::always_inline]] inline void waitEvents(double timeout_)
    {
        glfwWaitEventsTimeout(timeout_);
    }

    [[gnu::always_inline]] inline void postEmptyEvent()
    {
        glfwPostEmptyEvent();
    }
}  // namespace glfw

#endif  //GLFWPP_EVENT_H
