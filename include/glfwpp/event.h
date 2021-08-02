#ifndef GLFWPP_EVENT_H
#define GLFWPP_EVENT_H

#include <GLFW/glfw3.h>
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

    inline void pollEvents()
    {
        glfwPollEvents();
    }

    inline void waitEvents()
    {
        glfwWaitEvents();
    }
    inline void waitEvents(double timeout_)
    {
        glfwWaitEventsTimeout(timeout_);
    }

    inline void postEmptyEvent()
    {
        glfwPostEmptyEvent();
    }
}  // namespace glfw

#endif  //GLFWPP_EVENT_H
