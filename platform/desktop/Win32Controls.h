#ifndef _WIN32_CONTROLS_H_
#define _WIN32_CONTROLS_H_
#ifdef _WIN32

#include <windows.h>

long GetNumericUpDownValue(HWND aParent, int aUpDownId);
SIZE Text(int aX, int aY, const TCHAR* aText, HWND aParent, int aTextId, HINSTANCE aInstance, HDC aHdc);
HWND MakeWindow(const TCHAR* aClassName, const TCHAR* aWindowTitle, HINSTANCE aInstance, int aX, int aY,
				int aWidth, int aHeight, WNDPROC aProc);
void NumericUpDown(int aX, int aY, int aHeight, int aWidth, HWND aParent, int aEditId, int aUpDownId,
				   HINSTANCE aInstance, long mMin, long mMax, long aValue);

#endif
#endif
