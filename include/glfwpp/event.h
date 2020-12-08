#ifndef GLFWPP_EVENT_H
#define GLFWPP_EVENT_H

#include <functional>
#include <list>

namespace glfw
{
    template<typename... Args>
    class Event
    {
    public:
        using HandlerType = std::function<void(Args...)>;  // TODO: use shallow wrapper for better perf
        using Iterator = typename std::list<HandlerType>::iterator;

    private:
        std::list<HandlerType> _handlers;

    public:
        Iterator operator+=(const HandlerType& handler_)
        {
            _handlers.push_back(handler_);
            return std::prev(_handlers.end());
        }
        void operator-=(Iterator iter_)
        {
            _handlers.erase(iter_);
        }
        void operator()(Args... args_) const
        {
            for(auto&& handler : _handlers)
            {
                handler(std::forward<Args>(args_)...);
            }
        }
    };

    void pollEvents()
    {
        glfwPollEvents();
    }

    void waitEvents()
    {
        glfwWaitEvents();
    }
    void waitEvents(double timeout_)
    {
        glfwWaitEventsTimeout(timeout_);
    }

    void postEmptyEvent()
    {
        glfwPostEmptyEvent();
    }
}  // namespace glfw

#endif  //GLFWPP_EVENT_H
