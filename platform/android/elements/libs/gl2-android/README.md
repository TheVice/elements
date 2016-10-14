
gl2-android

Android Java bindings for OpenGL ES 2.0

This project is a helper library for those poor souls that long for Java bindings to the OpenGL ES 2.0 API on Android. It features a mechanism to determine wheter OGL ES 2.0 is supported. If that is the case you simply instantiate a GLSurfaceView20 and create a AndroidGL20 instance to access all the OpenGL ES 2.0 functions. ~~This project will be obsolete as soon as Android Froyo is released~~. Well turns out these are the only complete OpenGL ES 2.0 bindings even with Froyo out in the wild. More info at http://apistudios.com/hosted/marzec/badlogic/wordpress/?p=760

Update: with the release of Android 2.3 we now finally have fully working Java GLES20 bindings. They are compatible to this bindings for the most part. If you want to also support 2.0 to 2.2 devices you might use the wrapper provided here.

https://code.google.com/archive/p/gl2-android/
