# GLFW C++ wrapper - glfwpp ![logo](logo.png)

[![CMake](https://github.com/janekb04/glfwpp/workflows/CMake/badge.svg)](https://github.com/janekb04/glfwpp/actions?query=workflow%3ACMake)
[![clang-format](https://github.com/janekb04/glfwpp/workflows/clang-format/badge.svg)](https://github.com/janekb04/glfwpp/actions?query=workflow%3Aclang-format)
[![dependabot](https://badgen.net/github/dependabot/janekb04/glfwpp?icon=dependabot&label)](https://github.com/janekb04/glfwpp/network/updates)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/janekb04/glfwpp.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/janekb04/glfwpp/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/janekb04/glfwpp.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/janekb04/glfwpp/context:cpp)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/69102e4c9b3744eea1fdd3a5758aee91)](https://www.codacy.com/gh/janekb04/glfwpp/dashboard?utm_source=github.com&utm_medium=referral&utm_content=janekb04/glfwpp&utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/janekb04/glfwpp/badge/main)](https://www.codefactor.io/repository/github/janekb04/glfwpp/overview/main)
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fjanekb04%2Fglfwpp.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2Fjanekb04%2Fglfwpp?ref=badge_shield)

<p align="center">
  <img src="https://i.stack.imgur.com/cmt94.gif">
</p>

GLFWPP or (GLFW C++ Wrapper) is a thin, modern C++17 layer on top of [GLFW](https://www.glfw.org/). It supports GLFW versions from 3.2 up to the current 3.3.6. From [the official GLFW website](https://www.glfw.org/):

> GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.
> GLFW is written in C and supports Windows, macOS, X11 and Wayland.
> GLFW is licensed under the zlib/libpng license.

I like C++ and OOP, so when I find a C library, I immediately look for a wrapper which offers RAII objects instead of free `create` and `destroy` functions, identifiers wrapped in `namespace`s, methods instead of free functions, scoped `enum`s instead of macros and exceptions instead of error codes. In case of GLFW I didn't really find such a library, so I made one myself.

<hr>

<details><summary>:stopwatch: <b>Quick Start</b></summary><br />

To use, just clone the repo recursively:

```powershell
git clone https://github.com/janekb04/glfwpp
```

Remember to install [the necessary GLFW dependencies](https://www.glfw.org/docs/latest/compile.html), if you're on Linux. Make sure to disable building the examples by setting the option `GLFWPP_BUILD_EXAMPLES` to `OFF` using `set(GLFWPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)` in your `CMakeLists.txt`, if you don't want them built, as they are built by default. If you don't disable them, you will also have to install [the Vulkan SDK](https://vulkan.lunarg.com).

You can then link against the target `GLFWPP` using CMake:

```cmake
add_executable(myExecutable mySource1.cpp mySource2.cpp mySource3.cpp)

set(GLFWPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # disable building GLFWPP examples
add_subdirectory("path/to/glfwpp")
target_link_libraries(myExecutable PRIVATE GLFWPP)
```

Now, you just have to include `glfwpp.h` and you're ready to go:

```cpp
#include <glfwpp/glfwpp.h>
int main()
{
    auto GLFW = glfw::init();
    glfw::Window window{ 640, 480, "Hello GLFWPP"};
    while (!window.shouldClose())
        glfw::pollEvents();
}
```

You can also consult [`cmake.yml`](https://github.com/janekb04/glfwpp/blob/main/.github/workflows/cmake.yml) to see the complete installation and building process of GLFWPP, its dependencies and the examples on Ubuntu, macOS and Windows. Examples may be found in the `/examples` directory. Alternatively, just copy-paste the headers and include `glfwpp.h` (not recommended). 

Note: To use functionality from `glfw3native.h`, `native.h` has to be included separately.

</details>

<details><summary>:pushpin: <b>Main Features</b></summary><br />

-   **Error handling** using exceptions (defined in `error.h`).
-   Strongly typed **scoped enums** for all GLFW constants that catch all `GLFW_INVALID_ENUM` errors at compile time.
-   Everything wrapped in **namespace `glfw`** to avoid name clashing
-   **RAII wrappers** for windows (`glfw::Window`), cursors (`glfw::Cursor`), key codes (`glfw::KeyCode`), monitors (`glfw::Monitor`), joysticks (`glfw::Joystick`) and the entire library (`glfw::GlfwLibrary`) for automatic resource management.
-   `glfw::Event` class to allow to specify **any invocable** (function, method, lambda, functor, etc.) **as a callback**. _Note: it uses `std::function` which is infamous for its poor performance. However, events occur relatively rarely (probably generally no more than a dozen a frame) and as such I wouldn't expect this to be a performance issue. At the same time `std::function` has much greater flexibility than raw function pointers._
-   Hints passed through **structures** (`glfw::InitHints` and `glfw::WindowHints`) instead of through functions with an enum constant.
-   Mostly very thin wrapping matching nearly exactly the original GLFW naming which makes it both easier to port and allows to use the official GLFW documentation.
-   Performance overhead should be low, due to the **thin** nature of the wrapper. _Note: The `glfw::Event` as mentioned above could have a little performance overhead, but it shouldn't be an issue. Another factor is the use of exceptions for error handling. However, most exception implementations have performance penalties only in the exceptional path, which, by definition, happens rarely._
-   Now also **compatible with [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp)**.
-   Now also **compatible with [Emscripten](https://emscripten.org/)**.

</details>
  
<details><summary>:mortar_board: <b>Example</b></summary><br />

Here is a quick comparison of GLFW and GLFWPP. The following code creates a OpenGL 4.6 context and clears the screen.

<table>
  <tr>
    <th>
      GLFW
    </th>
    <th>
      GLFWPP
    </th>
  </tr>
<tr>
<td>
<pre style="background-color:#2b2b2b;color:#a9b7c6;font-family:'JetBrains Mono',monospace;font-size:9.8pt;"><span style="color:#bbb529;">#include </span><span style="color:#0cc21a;">&lt;GLFW/glfw3.h&gt;
</span><span style="color:#0cc21a;">
</span><span style="color:#ed3792;">int </span><span style="color:#ffc66d;font-weight:bold;">main</span><span style="color:#6989bb;">()
</span><span style="color:#6897bb;">{
</span><span style="color:#6897bb;">    </span><span style="color:#ed3792;">if </span><span style="color:#6989bb;">(</span><span style="color:#af3681;">!</span><span style="color:#e0ff76;">glfwInit</span><span style="color:#6989bb;">())
</span><span style="color:#6989bb;">        </span><span style="color:#ed3792;">return </span><span style="color:#af3681;">-</span><span style="color:#0cc21a;">1</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">
</span><span style="color:#af3681;">    </span><span style="color:#e0ff76;">glfwWindowHint</span><span style="color:#6989bb;">(</span><span style="color:#58a517;">GLFW_CONTEXT_VERSION_MAJOR</span><span style="color:#af3681;">, </span><span style="color:#0cc21a;">4</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#e0ff76;">glfwWindowHint</span><span style="color:#6989bb;">(</span><span style="color:#58a517;">GLFW_CONTEXT_VERSION_MINOR</span><span style="color:#af3681;">, </span><span style="color:#0cc21a;">6</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#e0ff76;">glfwWindowHint</span><span style="color:#6989bb;">(</span><span style="color:#58a517;">GLFW_OPENGL_PROFILE</span><span style="color:#af3681;">, </span><span style="color:#58a517;">GLFW_OPENGL_CORE_PROFILE</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#836bc6;">GLFWwindow</span><span style="color:#af3681;">* </span><span style="color:#6dc68c;font-style:italic;">window </span><span style="color:#af3681;">= </span><span style="color:#e0ff76;">glfwCreateWindow</span><span style="color:#6989bb;">(</span><span style="color:#0cc21a;">640</span><span style="color:#af3681;">, </span><span style="color:#0cc21a;">480</span><span style="color:#af3681;">, </span><span style="color:#0cc21a;">&quot;Hello World&quot;</span><span style="color:#af3681;">, </span><span style="color:#ed3792;">nullptr</span><span style="color:#af3681;">, </span><span style="color:#ed3792;">nullptr</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#ed3792;">if </span><span style="color:#6989bb;">(</span><span style="color:#af3681;">!</span><span style="color:#6dc68c;font-style:italic;">window</span><span style="color:#6989bb;">) </span><span style="color:#6897bb;">{
</span><span style="color:#6897bb;">        </span><span style="color:#e0ff76;">glfwTerminate</span><span style="color:#6989bb;">()</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">        </span><span style="color:#ed3792;">return </span><span style="color:#af3681;">-</span><span style="color:#0cc21a;">1</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#6897bb;">}
</span><span style="color:#6897bb;">
</span><span style="color:#6897bb;">    </span><span style="color:#e0ff76;">glfwMakeContextCurrent</span><span style="color:#6989bb;">(</span><span style="color:#6dc68c;font-style:italic;">window</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">
</span><span style="color:#af3681;">    </span><span style="color:#ed3792;">while </span><span style="color:#6989bb;">(</span><span style="color:#af3681;">!</span><span style="color:#e0ff76;">glfwWindowShouldClose</span><span style="color:#6989bb;">(</span><span style="color:#6dc68c;font-style:italic;">window</span><span style="color:#6989bb;">))
</span><span style="color:#6989bb;">    </span><span style="color:#6897bb;">{
</span><span style="color:#6897bb;">        </span><span style="color:#e0ff76;">glClear</span><span style="color:#6989bb;">(</span><span style="color:#58a517;">GL_COLOR_BUFFER_BIT</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">
</span><span style="color:#af3681;">        </span><span style="color:#e0ff76;">glfwSwapBuffers</span><span style="color:#6989bb;">(</span><span style="color:#6dc68c;font-style:italic;">window</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">        </span><span style="color:#e0ff76;">glfwPollEvents</span><span style="color:#6989bb;">()</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#6897bb;">}
</span><span style="color:#6897bb;">
</span><span style="color:#6897bb;">    </span><span style="color:#e0ff76;">glfwTerminate</span><span style="color:#6989bb;">()</span><span style="color:#af3681;">;
</span><span style="color:#6897bb;">}</span></pre>
</td>
<td>
<pre style="background-color:#2b2b2b;color:#a9b7c6;font-family:'JetBrains Mono',monospace;font-size:9.8pt;"><span style="color:#bbb529;">#include </span><span style="color:#0cc21a;">&lt;glfwpp/glfwpp.h&gt;
</span><span style="color:#0cc21a;">
</span><span style="color:#ed3792;">int </span><span style="color:#ffc66d;font-weight:bold;">main</span><span style="color:#6989bb;">()
</span><span style="color:#6897bb;">{
</span><span style="color:#6897bb;">    </span><span style="color:#ed3792;">auto </span><span style="color:#6dc68c;font-style:italic;">GLFW </span><span style="color:#af3681;">= </span><span style="color:#51bcff;">glfw</span><span style="color:#af3681;">::</span><span style="color:#e0ff76;">init</span><span style="color:#6989bb;">()</span><span style="color:#af3681;">;<br>
</span><span style="color:#af3681;">
</span><span style="color:#af3681;">    </span><span style="color:#51bcff;">glfw</span><span style="color:#af3681;">::</span><span style="color:#e0ff76;">WindowHints</span><span style="color:#6897bb;">{  </span><span style="color:#61c669;font-style:italic;">.contextVersionMajor </span><span style="color:#af3681;">= </span><span style="color:#0cc21a;">4</span><span style="color:#af3681;">,
</span><span style="color:#af3681;">                        </span><span style="color:#61c669;font-style:italic;">.contextVersionMinor </span><span style="color:#af3681;">= </span><span style="color:#0cc21a;">6</span><span style="color:#af3681;">,
</span><span style="color:#af3681;">                        </span><span style="color:#61c669;font-style:italic;">.openglProfile </span><span style="color:#af3681;">= </span><span style="color:#51bcff;">glfw</span><span style="color:#af3681;">::</span><span style="color:#5a60c6;">OpenGlProfile</span><span style="color:#af3681;">::</span><span style="color:#0aa516;font-style:italic;">Core </span><span style="color:#6897bb;">}</span><span style="color:#af3681;">.</span><span style="color:#e0ff76;">apply</span><span style="color:#6989bb;">()</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#51bcff;">glfw</span><span style="color:#af3681;">::</span><span style="color:#5a60c6;">Window </span><span style="color:#6dc68c;font-style:italic;">window</span><span style="color:#6897bb;">{</span><span style="color:#0cc21a;">640</span><span style="color:#af3681;">, </span><span style="color:#0cc21a;">480</span><span style="color:#af3681;">, </span><span style="color:#0cc21a;">&quot;Hello World&quot;</span><span style="color:#6897bb;">}</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#808080;">// If window creation fails, an exception is thrown
</span><span style="color:#808080;">
</span><span style="color:#808080;">
</span><span style="color:#808080;">
</span><span style="color:#808080;">
</span><span style="color:#808080;">    </span><span style="color:#51bcff;">glfw</span><span style="color:#af3681;">::</span><span style="color:#e0ff76;">makeContextCurrent</span><span style="color:#6989bb;">(</span><span style="color:#6dc68c;font-style:italic;">window</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">
</span><span style="color:#af3681;">    </span><span style="color:#ed3792;">while </span><span style="color:#6989bb;">(</span><span style="color:#af3681;">!</span><span style="color:#6dc68c;font-style:italic;">window</span><span style="color:#af3681;">.</span><span style="color:#e0ff76;">shouldClose</span><span style="color:#6989bb;">())
</span><span style="color:#6989bb;">    </span><span style="color:#6897bb;">{
</span><span style="color:#6897bb;">        </span><span style="color:#e0ff76;">glClear</span><span style="color:#6989bb;">(</span><span style="color:#58a517;">GL_COLOR_BUFFER_BIT</span><span style="color:#6989bb;">)</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">
</span><span style="color:#af3681;">        </span><span style="color:#6dc68c;font-style:italic;">window</span><span style="color:#af3681;">.</span><span style="color:#e0ff76;">swapBuffers</span><span style="color:#6989bb;">()</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">        </span><span style="color:#51bcff;">glfw</span><span style="color:#af3681;">::</span><span style="color:#e0ff76;">pollEvents</span><span style="color:#6989bb;">()</span><span style="color:#af3681;">;
</span><span style="color:#af3681;">    </span><span style="color:#6897bb;">}
</span><span style="color:#6897bb;">
</span><span style="color:#6897bb;">    </span><span style="color:#808080;">// GlfwLibrary destructor calls glfwTerminate automatically
</span><span style="color:#6897bb;">}</span></pre>
</td>

</tr>
</table>
  
</details>
  
<details><summary>:open_file_folder: <b>File structure</b></summary><br /> 

The functionality is split between files, as follows:

-   `error.h` - things related to error handling (exception types etc.). All GLFW errors are detected by the library and thrown as exceptions. The exception type matches [the respective GLFW error code](https://www.glfw.org/docs/latest/group__errors.html).

-   `glfwpp.h` - main header with, includes all other headers. Contains:
    -   [The `init` function](https://www.glfw.org/docs/latest/intro_guide.html#intro_init_init). [Initialization hints](https://www.glfw.org/docs/latest/intro_guide.html#init_hints) are passed with `glfw::InitHints`. The RAII wrapper `glfw::GlfwLibrary` takes care of calling [`glfwTerminate()`](https://www.glfw.org/docs/latest/intro_guide.html#intro_init_terminate).
    -   [Time input](https://www.glfw.org/docs/latest/input_guide.html#time).
    -   [Clipboard input and output](https://www.glfw.org/docs/latest/input_guide.html#clipboard).
    -   [Vulkan specific functionality](https://www.glfw.org/docs/latest/vulkan_guide.html). Compatible with both `vulkan.h` and [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp).

-   `event.h` - `glfw::Event` class used for specifying all user callbacks as well as event management functions.

-   `joystick.h` - `glfw::Joystick` class and [functionality related to joystick input](https://www.glfw.org/docs/latest/input_guide.html#joystick)

-   `monitor.h` - `glfw::Monitor` and other functionality related to [monitor management](https://www.glfw.org/docs/latest/monitor_guide.html).

-   `window.h` - `glfw::Window` class, `glfw::Cursor` class, `glfw::KeyCode` class and other functionality related to managing [windows](https://www.glfw.org/docs/latest/window_guide.html), [window contexts](https://www.glfw.org/docs/latest/context_guide.html) and [window input](https://www.glfw.org/docs/latest/input_guide.html) (clipboard and time IO in `glfwpp.h`). [Window hints](https://www.glfw.org/docs/latest/window_guide.html#window_hints) are specified using `glfw::WindowHints`.

-   `native.h` - functions for [native access](https://www.glfw.org/docs/latest/group__native.html) wrapping around `glfw3native.h`.

-   `version.h` - function for querying the GLFW runtime and compile time [version](https://www.glfw.org/docs/latest/intro_guide.html#intro_version) and version string.

</details>
  
<details><summary>:link: <b>Interoperability</b></summary><br /> 
  
GLFWPP code and GLFW can be mixed with no issues as long as you mind these rules:

-   If GLFW is initialized with `glfw::GlfwLibrary`, you must not call `glfwTerminate` yourself and depend on it being called by the destructor of `glfw::GlfwLibrary`. You may call `glfwInit` though, but it won't have any effect. Also you should not use `glfwSetErrorCallback`, `glfwSetMonitorCallback` nor `glfwSetJoystickCallback` and instead use the appropriate `glfw::XXXXevent`s to register your handlers.
-   If GLFW is initialized with `glfwInit`, you can initialize it again with `glfw::GlfwLibrary`. All the created GLFW objects will remain in a valid and all state will be preserved except that the handlers error callback, monitor callback and joystick callback handlers will be intercepted by GLFWPP and to register your own handlers you will have to use the appropriate `glfw::XXXXevent`.
-   Where applicable, `glfw::` objects provide conversion operation to and from the underlying `GLFWxxxx*` handles. However it must be noted that the conversion to the underlying handles retains the ownership of those handles. As such, for example, you must not `glfwDestroy` them. At the same time the constructors from handles take the ownership of the given handle and as such in this case you also must not `glfwDestroy` them yourself.

</details>

<details><summary>:balance_scale: <b>License</b></summary><br /> 

[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fjanekb04%2Fglfwpp.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2Fjanekb04%2Fglfwpp?ref=badge_large)
  
</details>
