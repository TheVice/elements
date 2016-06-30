###Overview

In this folder located source files required for build for desktop platform

###Dependencies
* [SwiftShader](https://swiftshader.googlesource.com/SwiftShader) - used as high-performance CPU-based implementation of the OpenGL ES
* Modifier version of [https://swiftshader.googlesource.com/SwiftShader/+/3a795c66126616037657d03e52020213d91ba164/third_party/PowerVR_SDK/Examples/Beginner/01_HelloAPI/OGLES2/OGLES2HelloAPI_LinuxX11.cpp](https://github.com/glfw/glfw/releases) - used for cooperation with operation system
* Other dependence from all project, not specific addition for desktop port do not required
* For Linux globally project required install addition dependencies by package manager of your distributive. Check documentation of your system to know what to install. For Ubuntu this dependence may be install by next few commands: ```sudo apt-get install libglm-dev```, ```sudo apt-get install libpugixml-dev```, ```sudo apt-get install libpng16-dev```

###Build from Eclipse (Linux)
* Clone the ```SwiftShader``` repository
* Make sure you are on the [3a795c66126616037657d03e52020213d91ba164](https://swiftshader.googlesource.com/SwiftShader/+/3a795c66126616037657d03e52020213d91ba164) commit: ```git checkout 3a795c66126616037657d03e52020213d91ba164```
* In text editor open ```CMakeLists.txt``` from ```SwiftShader``` project and replace ```CMAKE_SOURCE_DIR``` with ```CMAKE_CURRENT_SOURCE_DIR```
* Save the ```CMakeLists.txt``` from ```SwiftShader```
* Open terminal (console) and enter into directory where you want to generated project files
* For Debug build type and execute ```cmake -DSWIFTSHADER_PATH=<Path to SwiftShader> -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" <Path to project root source directory>```
* For Release build type and execute ```cmake -DSWIFTSHADER_PATH=<Path to SwiftShader> -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" <Path to project root source directory>```
* For Profile build type and execute ```cmake -DSWIFTSHADER_PATH=<Path to SwiftShader> -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" <Path to project root source directory>```
* Please note that cmake bin directory must be in PATH environment, otherwise you must enter full path to ```cmake```
* Now you can add existing project into ```Eclipse``` workspace to make and run targets from it
* ~~To build project from terminal run ```make -C . all -j$(nproc) -s```~~. Not all targets, that added from SwiftShader, able to compile success
* To build from terminal:
* Type and execute: ```make -C . libEGL -j$(nproc) -s```
* Type and execute: ```make -C . libGLESv2 -j$(nproc) -s```. Be patient, complete of this target depend of performance of your PC and may finish in few minutes
* Type and execute: ```make -C . air -j$(nproc) -s```
* Type and execute: ```make -C . fire -j$(nproc) -s```
* Type and execute: ```make -C . liquid -j$(nproc) -s```
* Type and execute: ```make -C . light -j$(nproc) -s```
* Type and execute: ```make -C . strange -j$(nproc) -s```
