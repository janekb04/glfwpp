# glfwpp 
[![CMake](https://github.com/janekb04/glfwpp/workflows/CMake/badge.svg)](https://github.com/janekb04/glfwpp/actions?query=workflow%3ACMake)
[![clang-format](https://github.com/janekb04/glfwpp/workflows/clang-format/badge.svg)](https://github.com/janekb04/glfwpp/actions?query=workflow%3Aclang-format)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/janekb04/glfwpp.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/janekb04/glfwpp/context:cpp)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/69102e4c9b3744eea1fdd3a5758aee91)](https://www.codacy.com/gh/janekb04/glfwpp/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=janekb04/glfwpp&amp;utm_campaign=Badge_Grade)

A thin modern C++17 header only wrapper for [GLFW 3.3.2](https://www.glfw.org/). From [the official GLFW website](https://www.glfw.org/):

> GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.
> GLFW is written in C and supports Windows, macOS, X11 and Wayland.
> GLFW is licensed under the zlib/libpng license.

I like C++ and OOP, so when I find a C library, I immediately look for a wrapper which offers classes with RAII instead of free `create` and `destroy` functions, identifiers wrapped in `namespace`s, methods instead of free functions, scoped `enum`s instead of macros and exceptions instead of error codes. As I didn't really find a low-level thin and header-only wrapper, so I made one myself.

To use, just clone the repo (recursively) and link against the target `GLFWPP` using CMake. Alternatively, just copy-paste the headers and include `glfwpp.h` (not recommended). Make sure to disable building the examples by setting the option `GLFWPP_BUILD_EXAMPLES` to `OFF`, if you don't want them built, as they are built by default. Also remeber to install [the necessary GLFW dependencies](https://www.glfw.org/docs/latest/compile.html). You can also consult `cmake.yml` to see the complete installation and building process of GLFWPP, its dependecies and the examples on Linux.

Note: `glfw3native.h` is not yet implemented.

# Main features

-   Error handling using exceptions (defined in `error.h`).
-   Scoped enums for all GLFW constants
-   Everything wrapped in namespace `glfw`
-   RAII wrappers for windows (`glfw::Window`), cursors (`glfw::Cursor`), key codes (`glfw::KeyCode`), monitors (`glfw::Monitor`), joysticks (`glfw::Joystick`) and the entire library (`glfw::GlfwLibrary`).
-   `glfw::Event` class to allow to specify any invocable (function, method, lambda, functor, etc.) as a callback. Uses `std::function`.
-   Hints passed through stuctures (`glfw::InitHints` and `glfw::WindowHints`) instead of through functions with an enum constant.
-   Mostly very thin wrapping matching nearly exactly the original GLFW naming which makes it both easier to port and allows to use the official GLFW documentation.
-   Performance overhead should be low, due to the thin nature of the wrapper, with an exception being the use of exceptions and the `glfw::Event` class.
-   Now also compatible with [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp)

# Files

The functionality is split between files, as follows:

-   `error.h` - things related to error handling (exception types etc.). All GLFW errors are detected by the library and thrown as exceptions. The exception type matches [the respective GLFW error code](https://www.glfw.org/docs/latest/group__errors.html).
-   `glfwpp.h` - main header with, includes all other headers. Contains:
    -   [The `init` function](https://www.glfw.org/docs/latest/intro_guide.html#intro_init_init). [Initialization hints](https://www.glfw.org/docs/latest/intro_guide.html#init_hints) are passed with `glfw::InitHints`. The RAII wrapper `glfw::GlfwLibrary` takes care of calling [`glfwTerminate()`](https://www.glfw.org/docs/latest/intro_guide.html#intro_init_terminate).
    -   [Version management](https://www.glfw.org/docs/latest/intro_guide.html#intro_version).
    -   [Time input](https://www.glfw.org/docs/latest/input_guide.html#time).
    -   [Clipboard input and output](https://www.glfw.org/docs/latest/input_guide.html#clipboard).
    -   [Vulkan specific functionality](https://www.glfw.org/docs/latest/vulkan_guide.html). Compatible with both `vulkan.h` and [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp).
-   `event.h` - `glfw::Event` class used for specifying all user callbacks as well as event management functions.
-   `joystick.h` - `glfw::Joystick` class and [functionality related to joystick input](https://www.glfw.org/docs/latest/input_guide.html#joystick)
-   `monitor.h` - `glfw::Monitor` and other functionality related to [monitor management](https://www.glfw.org/docs/latest/monitor_guide.html).
-   `window.h` - `glfw::Window` class, `glfw::Cursor` class, `glfw::KeyCode` class and other functionality related to managing [windows](https://www.glfw.org/docs/latest/window_guide.html), [window contexts](https://www.glfw.org/docs/latest/context_guide.html) and [window input](https://www.glfw.org/docs/latest/input_guide.html) (clipboard and time IO in `glfwpp.h`). [Window hints](https://www.glfw.org/docs/latest/window_guide.html#window_hints) are specified using `glfw::WindowHints`.

# Interoperability

GLFWPP code and GLFW can be mixed with no issues as long as you mind these rules:

-   If GLFW is initialized with `glfw::GlfwLibrary`, you must not call `glfwTerminate` yourself and depend on it being called by the destructor of `glfw::GlfwLibrary`. You may call `glfwInit` though, but it won't have any effect. Also you should not use `glfwSetErrorCallback`, `glfwSetMonitorCallback` nor `glfwSetJoystickCallback` and instead use the appropriate `glfw::XXXXevent`s to register your handlers.
-   If GLFW is initialized with `glfwInit`, you can initialize it again with `glfw::GlfwLibrary`. All the created GLFW objects will remain in a valid and all state will be preserved except that the handlers error callback, monitor callback and joystick callback handlers will be intercepted by GLFWPP and to register your own handlers you will have to use the appropriate `glfw::XXXXevent`.
