
#ifdef _WIN32

#include "Win32Controls.h"
#include <commctrl.h>
#include <iostream>

long GetNumericUpDownValue(HWND aParent, int aUpDownId)
{
	return SendDlgItemMessage(aParent, aUpDownId, UDM_GETPOS32, 0, 0);
}

SIZE Text(int aX, int aY, const TCHAR* aText, HWND aParent, int aTextId, HINSTANCE aInstance, HDC aHdc)
{
	const DWORD dwExStyle = 0;
	//
	SIZE size;
	GetTextExtentPoint32(aHdc, aText, lstrlen(aText), &size);
	//
	CreateWindowEx(dwExStyle,
				   WC_STATIC, aText,
				   WS_CHILD | WS_VISIBLE,
				   aX, aY, size.cx, size.cy,
				   aParent,
				   (HMENU)aTextId,
				   aInstance,
				   nullptr);
	//
	return size;
}

HWND MakeWindow(const TCHAR* aClassName, const TCHAR* aWindowTitle, HINSTANCE aInstance, int aX, int aY,
				int aWidth, int aHeight, WNDPROC aProc)
{
	const DWORD dwStyle = WS_CAPTION | WS_POPUPWINDOW;
	const DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	HWND hWnd = HWND_DESKTOP;
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = aProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = aInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = aClassName;
	wc.hIconSm = nullptr;

	if (!RegisterClassEx(&wc))
	{
		return hWnd;
	}

	RECT windowRect;
	memset(&windowRect, 0, sizeof(windowRect));
	windowRect.left = 0L;
	windowRect.right = aWidth;
	windowRect.top = 0L;
	windowRect.bottom = aHeight;
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
	hWnd = CreateWindowEx(dwExStyle, aClassName, aWindowTitle, dwStyle,
						  aX, aY, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
						  HWND_DESKTOP, nullptr, aInstance, nullptr);
	return hWnd;
}

void NumericUpDown(int aX, int aY, int aHeight, int aWidth, HWND aParent, int aEditId, int aUpDownId,
				   HINSTANCE aInstance, long mMin, long mMax, long aValue)
{
	const DWORD dwExStyle = 0;
	//
	CreateWindowEx(WS_EX_CLIENTEDGE,
				   WC_EDIT,
				   TEXT(""),
				   WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_TABSTOP | WS_GROUP,
				   aX, aY, aHeight, aWidth,
				   aParent,
				   (HMENU)(aEditId),
				   aInstance,
				   nullptr);
	//
	CreateWindowEx(dwExStyle,
				   UPDOWN_CLASS, TEXT("SPIN"),
				   UDS_AUTOBUDDY | UDS_ALIGNRIGHT | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
				   aX, aY, 20, 20,
				   aParent,
				   (HMENU)aUpDownId,
				   aInstance,
				   nullptr);
	//
	SendDlgItemMessage(aParent, aUpDownId, UDM_SETRANGE32, mMin, mMax);
	SendDlgItemMessage(aParent, aUpDownId, UDM_SETPOS32, 0, aValue);
}

#endif
