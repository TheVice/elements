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

#include "GameComponent.h"
#include <EGL/egl.h>

class OGLES2HelloAPI_LinuxX11 : public Library::GameComponent
{
	RTTI_DECLARATIONS(OGLES2HelloAPI_LinuxX11, GameComponent)

public:
	OGLES2HelloAPI_LinuxX11(Library::Game& aGame, Window aNativeWindow);
	~OGLES2HelloAPI_LinuxX11();

public:
	virtual bool Initialize() override;
	virtual void Update() override;

private:
	void Cleanup();

private:
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
