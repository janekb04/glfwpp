# glfwpp
A thin modern C++17 header only wrapper for GLFW 3.3. To use, simply include `glfwpp.h`.
# Main features
* Error handling using exceptions (defined in `error.h`).
* Scoped enums for all GLFW constants
* Everything wrapped in namespace `glfw`
* RAII wrappers for windows (`glfw::Window`), cursors (`glfw::Cursor`), key codes (`glfw::KeyCode`), monitors (`glfw::Monitor`), joysticks (`glfw::Joystick`) and the entire library (`glfw::GLFWLibrary`).
* Hints passed through stuctures (`glfw::InitHints` and `glfw::WindowHints`) instead of through functions with an enum constant.
* `glfw::Event` class to allow for multiple subsribers to a single event
* Mostly very thin wrapping matching nearly exactly the original GLFW naming which makes it both easier to port and allows to use the official GLFW documentation.

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
