# glfwpp
A thin modern C++17 header only wrapper for [GLFW 3.3](https://www.glfw.org/). To use, simply include `glfwpp.h`. From [the official GLFW website](https://www.glfw.org/):
>GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and >surfaces, receiving input and events.
>GLFW is written in C and supports Windows, macOS, X11 and Wayland.
>GLFW is licensed under the zlib/libpng license.

I like C++ and OOP, so when I find a C library, I immediately look for a wrapper which offers classes with RAII instead of free `create` and `destroy` functions, identifiers wrapped in `namespace`s, methods instead of free functions, scoped `enum`s instead of macros and exceptions instead of error codes. As I didn't really find a low-level thin and header-only wrapper, so I made one myself.
# Main features
* Error handling using exceptions (defined in `error.h`).
* Scoped enums for all GLFW constants
* Everything wrapped in namespace `glfw`
* RAII wrappers for windows (`glfw::Window`), cursors (`glfw::Cursor`), key codes (`glfw::KeyCode`), monitors (`glfw::Monitor`), joysticks (`glfw::Joystick`) and the entire library (`glfw::GLFWLibrary`).
* Hints passed through stuctures (`glfw::InitHints` and `glfw::WindowHints`) instead of through functions with an enum constant.
* `glfw::Event` class to allow for multiple subsribers to a single event
* Mostly very thin wrapping matching nearly exactly the original GLFW naming which makes it both easier to port and allows to use the official GLFW documentation.
* Performance overhead should be low, due to the thin nature of the wrapper, with an exception being the use of exceptions and the `glfw:Event` class.
# Files

The functionality is split between files, as follows:
* `error.h` - things related to error handling (exception types etc.). All GLFW errors are detected by the library and thrown as exceptions. The exception type matches [the respective GLFW error code](https://www.glfw.org/docs/latest/group__errors.html).
* `glfwpp.h` - main header with, includes all other headers. Contains:
    
    * [The `init` function](https://www.glfw.org/docs/latest/intro_guide.html#intro_init_init). [Initialization hints](https://www.glfw.org/docs/latest/intro_guide.html#init_hints) are passed with `glfw::InitHints`. The RAII wrapper `glfw::GLFWLibrary` takes care of calling [`glfwTerminate()`](https://www.glfw.org/docs/latest/intro_guide.html#intro_init_terminate).
    * [Version management](https://www.glfw.org/docs/latest/intro_guide.html#intro_version).
    * namespace `glfw::timer` for [time input](https://www.glfw.org/docs/latest/input_guide.html#time).
    * [Clipboard input and output](https://www.glfw.org/docs/latest/input_guide.html#clipboard).
* `helper.h` - `glfw::Event` class used for specifying all user callbacks.
* `joystick.h` - `glfw::Joystick` class and [functionality related to joystick input](https://www.glfw.org/docs/latest/input_guide.html#joystick)
* `monitor.h` - `glfw::Monitor` and other functionality related to [monitor management](https://www.glfw.org/docs/latest/monitor_guide.html).
* `native.h` - [platform specific functionality](https://www.glfw.org/docs/latest/group__native.html). **Not Yet Implemented**.
* `vulkan.h` - `glfw::vulkan` namespace for [Vulkan specific functionality](https://www.glfw.org/docs/latest/vulkan_guide.html).
* `window.h` - `glfw::Window` class, `glfw::Cursor` class, `glfw::KeyCode` class and other functionality related to managing [windows](https://www.glfw.org/docs/latest/window_guide.html), [window contexts](https://www.glfw.org/docs/latest/context_guide.html) and [window input](https://www.glfw.org/docs/latest/input_guide.html) (clipboard and time IO in `glfwpp.h`). [Window hints](https://www.glfw.org/docs/latest/window_guide.html#window_hints) are specified using `glfw::WindowHints`.

# Interoperability
GLFWPP code and GLFW can be mixed with no issues as long as you mind these rules:
* If GLFW is initialized with `glfw::GLFWLibrary`, you must not call `glfwTerminate` yourself and depend on it being called by the destructor of `glfw::GLFWLibrary`. You may call `glfwInit` though, but it won't have any effect. Also you should not use `glfwSetErrorCallback`, `glfwSetMonitorCallback` nor `glfwSetJoystickCallback` and instead use the appropriate `glfw::XXXXevent`s to register your handlers.
* If GLFW is initialized with `glfwInit`, you can initialize it again with `glfw::GLFWLibrary`. All the created GLFW objects will remain in a valid and all state will be preserved except that the handlers error callback, monitor callback and joystick callback handlers will be intercepted by GLFWPP and to register your own handlers you will have to use the appropriate `glfw::XXXXevent`.
