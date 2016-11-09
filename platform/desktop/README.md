###Overview

In this folder located source files required for build for desktop platform

###Dependencies
* [GLFW](https://github.com/glfw/glfw/releases) - used for cooperation with operation system
* [SwiftShader](https://swiftshader.googlesource.com/SwiftShader) - used as high-performance CPU-based implementation of the OpenGL ES
* Modifier version of [PowerVR_SDK/Examples/Beginner/01_HelloAPI/OGLES2/OGLES2HelloAPI_LinuxX11.cpp](https://swiftshader.googlesource.com/SwiftShader/+/cf3cd8d69d2689c09abf13cef9315cd49b24a7fa/third_party/PowerVR_SDK/Examples/Beginner/01_HelloAPI/OGLES2/OGLES2HelloAPI_LinuxX11.cpp) - used for deal with [EGL](https://www.khronos.org/egl)

###Build from Eclipse (Linux)
* Open terminal (console) and enter into directory where you want to generated project files
* For Debug build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" -DSWIFTSHADER_PATH=<Path to SwiftShader> <Path to project root source directory>```
* For Release build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" -DSWIFTSHADER_PATH=<Path to SwiftShader> <Path to project root source directory>```
* For Profile build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" -DSWIFTSHADER_PATH=<Path to SwiftShader> <Path to project root source directory>```
* Please note that cmake bin directory must be in PATH environment, otherwise you must enter full path to ```cmake```
* Now you can add existing project into ```Eclipse``` workspace to make and run targets from it
* To build project from terminal run ```make -C . -j$(nproc) -s all```
