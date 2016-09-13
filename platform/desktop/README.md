###Overview

In this folder located source files required for build for desktop platforms: Linux, Windows

###Dependencies
* [GLFW](https://github.com/glfw/glfw/releases) - used for cooperation with operation system
* [GLEW](https://github.com/nigels-com/glew/releases) - used for cooperation with OpenGL extensions (please note that for 1.13 version, last on the commit moment, on Windows platform there is currently required [alternative distributive](https://github.com/nigels-com/glew/issues/31#issuecomment-145498979))
* For Linux build some of dependence should be installed by package manager of your distributive. Check documentation of your system to know what to install. For Ubuntu dependences may be install by next few commands: ```apt-get install libglfw3-dev```, ```apt-get install libglm-dev```, ```apt-get install libpugixml-dev```, ```apt-get install libpng16-dev```, ```apt-get install libassimp-dev```

###Build from Eclipse (Linux)
* Open terminal (console) and enter into directory where you want to generated project files
* For Debug build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" <Path to project root source directory>```
* For Release build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" <Path to project root source directory>```
* For Profile build type and execute ```cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j$(nproc) -s" <Path to project root source directory>```
* Please note that cmake bin directory must be in PATH environment, otherwise you must enter full path to ```cmake```
* Now you can add existing project into ```Eclipse``` workspace to make and run targets from it
* To build project from terminal run ```make -C . -j$(nproc) -s all```

###Build from Eclipse (Windows)
* Open terminal (```cmd.exe```) and enter into directory where you want to generated project files
* Make sure that bin directory of MinGW in your PATH environment variable, otherwise cmake may do not found your C++ compiler
* For Debug build type and execute ```cmake -G "Eclipse CDT4 - MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j%NUMBER_OF_PROCESSORS% -s" -DGLFW_PATH=<Path to glfw> -DGLEW_PATH=<Path to glew> <Path to project root source directory>```
* For Release build type and execute ```cmake -G "Eclipse CDT4 - MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j%NUMBER_OF_PROCESSORS% -s" -DGLFW_PATH=<Path to glfw> -DGLEW_PATH=<Path to glew> <Path to project root source directory>```
* For Profile build type and execute ```cmake -G "Eclipse CDT4 - MinGW Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j%NUMBER_OF_PROCESSORS% -s" -DGLFW_PATH=<Path to glfw> -DGLEW_PATH=<Path to glew> <Path to project root source directory>```
* Please note that cmake bin directory must be in PATH environment, otherwise you must enter full path to ```cmake.exe```
* Now you can add existing project into ```Eclipse``` workspace to make and run targets from it
* To build project from terminal run ```mingw32-make -C . -j%NUMBER_OF_PROCESSORS% -s all```
