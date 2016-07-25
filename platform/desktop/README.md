###Overview

In this folder located source files required for build for desktop platform

###Dependencies
* [GLFW](https://github.com/glfw/glfw/releases) - used for cooperation with operation system
* [SwiftShader](https://swiftshader.googlesource.com/SwiftShader) - used as high-performance CPU-based implementation of the OpenGL ES
* Modifier version of [PowerVR_SDK/Examples/Beginner/01_HelloAPI/OGLES2/OGLES2HelloAPI_LinuxX11.cpp](https://swiftshader.googlesource.com/SwiftShader/+/3a795c66126616037657d03e52020213d91ba164/third_party/PowerVR_SDK/Examples/Beginner/01_HelloAPI/OGLES2/OGLES2HelloAPI_LinuxX11.cpp) - used for deal with [EGL](https://www.khronos.org/egl)
* Other dependence from all project, not specific addition for desktop port do not required
* For Linux build some of this dependence should be installed by package manager of your distributive. Check documentation of your system to know what to install. For Ubuntu dependences may be install by next few commands: ```apt-get install libglfw3-dev```, ```apt-get install libglm-dev```, ```apt-get install libpugixml-dev```, ```apt-get install libpng16-dev```, ```apt-get install libassimp-dev```

###Build from Eclipse (Linux)
* Clone the ```SwiftShader``` repository
* Make sure you are on the [3a795c66126616037657d03e52020213d91ba164](https://swiftshader.googlesource.com/SwiftShader/+/3a795c66126616037657d03e52020213d91ba164) commit: ```git checkout 3a795c66126616037657d03e52020213d91ba164```
* In text editor open ```CMakeLists.txt``` from ```SwiftShader``` project and replace ```CMAKE_SOURCE_DIR``` with ```CMAKE_CURRENT_SOURCE_DIR```
* Save the ```CMakeLists.txt``` from ```SwiftShader```
* Open terminal (console) and enter into directory where you want to generated project files
* For Debug build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" -DSWIFTSHADER_PATH=<Path to SwiftShader> <Path to project root source directory>```
* For Release build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" -DSWIFTSHADER_PATH=<Path to SwiftShader> <Path to project root source directory>```
* For Profile build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" -DSWIFTSHADER_PATH=<Path to SwiftShader> <Path to project root source directory>```
* Please note that cmake bin directory must be in PATH environment, otherwise you must enter full path to ```cmake```
* Now you can add existing project into ```Eclipse``` workspace to make and run targets from it
* To build from terminal:
* Type and execute: ```make -C . -j$(nproc) -s libEGL```
* Type and execute: ```make -C . -j$(nproc) -s libGLESv2```
* Type and execute: ```make -C . -j$(nproc) -s air```
* Type and execute: ```make -C . -j$(nproc) -s character```
* Type and execute: ```make -C . -j$(nproc) -s fire```
* Type and execute: ```make -C . -j$(nproc) -s light```
* Type and execute: ```make -C . -j$(nproc) -s liquid```
* Type and execute: ```make -C . -j$(nproc) -s strange```
