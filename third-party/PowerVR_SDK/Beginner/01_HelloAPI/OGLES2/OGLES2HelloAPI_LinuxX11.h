/*******************************************************************************************************************************************

 @File         OGLES2HelloAPI_LinuxX11.h

 @Title        OpenGL ES 2.0 HelloAPI Tutorial

 @Version

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform

 @Description  Basic Tutorial that shows step-by-step how to initialize OpenGL ES 2.0.

*******************************************************************************************************************************************/

#ifndef _OGLES2HelloAPI_LinuxX11_H_
#define _OGLES2HelloAPI_LinuxX11_H_

#include <EGL/egl.h>

class OGLES2HelloAPI_LinuxX11
{
private:
	bool CreateNativeWindow(Display* nativeDisplay, Window* nativeWindow);

public:
	OGLES2HelloAPI_LinuxX11(const char* aApplicationName, int aWindowWidth, int aWindowHeight);
	~OGLES2HelloAPI_LinuxX11();

	void Update(bool& aWindowShouldClose);
	bool Initialize();
	void Cleanup();

private:
	static void CenterWindow(Display* nativeDisplay, int aWindowWidth, int aWindowHeight, int& aCenterX, int& aCenterY);

private:
	// Name of the application
	const char* mApplicationName;

	// Width and height of the window
	const int mWindowWidth;
	const int mWindowHeight;

	// X11 variables
	Display* mNativeDisplay;
	Window mNativeWindow;

	// EGL variables
	EGLDisplay mEglDisplay;
	EGLConfig mEglConfig;
	EGLSurface mEglSurface;
	EGLContext mEglContext;
};

#endif

/*******************************************************************************************************************************************
 End of file (OGLES2HelloAPI_LinuxX11.h)
*******************************************************************************************************************************************/
