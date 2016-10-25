# Elements
OpenGL ES 2.0 and C++ experiments.

###Contents
* [Experiments](#experiments)
 * [Deferred Lighting](#deferred-lighting)
 * [Liquid Simulation](#liquid-simulation)
 * [Light Scattered](#light-scattered)
 * [Strange Attractors](#strange-attractors)
 * [Wind Field](#wind-field)
 * [Flame Simualtion](#flame-simulation)
 * [3D Character](#3d-character)
 * [Compass Tool](#Compass Tool)
* [Build](#build)

-----------------------

##Experiments

###Deferred Lighting
![Deferred Lighting](https://raw.githubusercontent.com/PkXwmpgN/elements/master/screenshots/Demo.jpeg)

- Sources experiments/demo
- Preview into [the YouTube](https://youtu.be/GXV0x_QblWg)

###Liquid Simulation 
![Liquid Simulation](https://raw.githubusercontent.com/PkXwmpgN/elements/master/screenshots/liquid.jpeg)

The simulation is based upon the article [Particle-based Viscoelastic Fluid Simulation](http://www.ligum.umontreal.ca/Clavet-2005-PVFS/pvfs.pdf).
- Sources experiments/liquid
- Preview into [the YouTube](https://www.youtube.com/watch?v=Z-z4TH40bM4)
- Demo into [the Google Play](https://play.google.com/store/apps/details?id=com.yegorov.alexey.elements.liquid)

###Light Scattered
![Light Scattered](https://raw.githubusercontent.com/PkXwmpgN/elements/master/screenshots/light.jpeg)

The adaptation of a light scattered effect. Based upon [Volumetric Light Scattering as a Post-Process](http://http.developer.nvidia.com/GPUGems3/gpugems3_ch13.html).
- Sources experiments/light
- Preview into [the YouTube](https://www.youtube.com/watch?v=CSaBSs1KVkA)

###Strange Attractors

![Strange Attractors](https://raw.githubusercontent.com/PkXwmpgN/elements/master/screenshots/strange.jpeg)

The implementation of a dynamic system based on the particles (2^20), called [Strange Attractors](https://en.wikipedia.org/wiki/Attractor). 
- Sources experiments/strange
- Preview into [the YouTube](https://www.youtube.com/watch?v=lx3xy8CakE0)

###Wind Field

![Wind Field preview](https://raw.githubusercontent.com/PkXwmpgN/elements/master/screenshots/air.jpeg)

The implementation of a dynamic system based on the particles (2^20) that handles [Navier-Stokes](http://www.intpowertechcorp.com/GDC03.pdf) and wind Forward-Euler integration.
- Sources experiments/air
- Preview into [the YouTube](https://www.youtube.com/watch?v=n3TOHyJzNDs)

###Flame Simulation

![Fire Simulation preview](https://raw.githubusercontent.com/PkXwmpgN/elements/master/screenshots/fire.jpeg)

The adaptation of a [raymarching](http://iquilezles.org/www/articles/raymarchingdf/raymarchingdf.htm) flame effect.
- Sources experiments/fire
- Preview into [the YouTube](https://www.youtube.com/watch?v=eYFEQRwEKm4)
- Demo into [the Google Play](https://play.google.com/store/apps/details?id=com.yegorov.alexey.elements.fire)

###3D Character
![3D Character preview](https://raw.githubusercontent.com/PkXwmpgN/elements/master/screenshots/character.jpeg)

3D R2-D2 and C-3PO with Android Sensors.
- Source experiments/character
- Preview into [the YouTube](https://youtu.be/PH8TPegPb2k)

###Compass Tool
![Compass preview](https://raw.githubusercontent.com/TheVice/elements/gh-pages/2016.10.14/Compass_Tool_poster.png)

##Build

* Download the required components;
 * ```SDK Tools``` - version 25.2.2: [Linux](http://dl.google.com/android/repository/tools_r25.2.2-linux.zip), [Mac OS X](http://dl.google.com/android/repository/tools_r25.2.2-macosx.zip), [Windows](http://dl.google.com/android/repository/tools_r25.2.2-windows.zip);
 * ```Platform Tools``` - version 24.0.2: [Linux](http://dl.google.com/android/repository/platform-tools_r24.0.2-linux.zip), [Mac OS X](http://dl.google.com/android/repository/platform-tools_r24.0.2-macosx.zip), [Windows](http://dl.google.com/android/repository/platform-tools_r24.0.2-windows.zip);
 * ```Build Tools``` - version 24.0.2: [Linux](http://dl.google.com/android/repository/build-tools_r24.0.2-linux.zip), [Mac OS X](http://dl.google.com/android/repository/build-tools_r24.0.2-macosx.zip), [Windows](http://dl.google.com/android/repository/build-tools_r24.0.2-windows.zip);
 * ```Platform``` - [version 24](http://dl.google.com/android/repository/platform-24_r02.zip);
 * NDK - Revision 10e (May 2015): [Linux 32-bit (x86)](http://dl.google.com/android/ndk/android-ndk-r10e-linux-x86.bin), [Linux 64-bit (x86)](http://dl.google.com/android/ndk/android-ndk-r10e-linux-x86_64.bin), [Mac OS X 32-bit](http://dl.google.com/android/ndk/android-ndk-r10e-darwin-x86.bin), [Mac OS X 64-bit](http://dl.google.com/android/ndk/android-ndk-r10e-darwin-x86_64.bin), [Windows 32-bit](http://dl.google.com/android/ndk/android-ndk-r10e-windows-x86.exe), [Windows 64-bit](http://dl.google.com/android/ndk/android-ndk-r10e-windows-x86_64.exe).
* Create folder ```android-sdk``` with two sub folders ```build-tools``` and  ```platforms```
* Unpack ```SDK Tools``` and ```Platform Tools``` into ```android-sdk```. ```Build Tools``` and ```Platform``` should be unpacked into ```android-sdk/build-tools``` and ```android-sdk/platforms``` corresponding;
* Unpacked ```Build Tools``` and ```Platform``` folder can be renamed ```android-7.0 -> 24.0.2``` and ```android-7.0 -> android-24``` corresponding;
* Unpack ndk in separate folder;
* At ```platform/android/elements``` create ```local.properties``` and put to it paths to sdk and ndk folders;
 * On Windows host it can be next:
  * ```sdk.dir=C\:\\android-sdk```
  * ```ndk.dir=C\:\\android-ndk-r10e-windows-x86_64```
 * On Linux host it can be next:
  * ```sdk.dir=/home/user/android-sdk```
  * ```ndk.dir=/home/user/android-ndk-r10e-linux-x86_64```
* Open terminal (console) and enter into ```platform/android/elements``` folder;
* Type and execute ```gradlew --daemon assembleDebug``` to build apks in debug configuration;
* For release configuration type and execute:
 * ```gradlew --daemon generateKey --q``` if you already do not have key file located in ```platform/android/elements``` folder
 * ```gradlew --daemon assembleRelease```
* All apk will be available in corresponding folder of demos: ```platform/android/elements/<Demo Name>/build/outputs/apk/```.

###Author
Alexey Yegorov.
If you have an idea, feel free to get in touch with me yegorov.alex@gmail.com
