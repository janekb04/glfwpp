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
        using handler_type = std::function<void(Args...)>; // TODO: use shallow wrapper for better perf
        using iterator = typename std::list<handler_type>::iterator;

    private:
        std::list<handler_type> _handlers;

    public:
        iterator operator+=(const handler_type& handler)
        {
            _handlers.push_back(handler);
            return std::prev(_handlers.end());
        }
        void operator-=(iterator iter)
        {
            _handlers.erase(iter);
        }
        void operator()(Args... args) const
        {
            for(auto&& handler : _handlers)
            {
                handler(std::forward<Args>(args)...);
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
    void waitEvents(double timeout)
    {
        glfwWaitEventsTimeout(timeout);
    }

    void postEmptyEvent()
    {
        glfwPostEmptyEvent();
    }
}  // namespace glfw

#endif  //GLFWPP_EVENT_H
