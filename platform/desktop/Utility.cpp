
#include "Utility.h"
#ifdef WIN32
#include <cassert>
#include <windows.h>

#ifndef NDEBUG
#include <tchar.h>
//#include <stdarg.h>

#ifdef _MSC_VER
#define _TRACE(aFormat) \
	{ \
		va_list args; \
		va_start(args, aFormat); \
		TCHAR output[1024]; \
		_vstprintf_s(output, aFormat, args); \
		OutputDebugString(output); \
		va_end(args); \
	}
#else
#include <iostream>
#define _TRACE(aFormat) \
	{ \
		va_list args; \
		va_start(args, aFormat); \
		char output[1024]; \
		sprintf(output, aFormat, args); \
		std::cerr << output << std::endl; \
		va_end(args); \
	}
#endif

inline void TRACE(const TCHAR* const aFormat, ...)
{
	_TRACE(aFormat)
}

#endif

#endif

namespace Library
{
namespace Utility
{

std::string path(const char* aPath)
{
	std::string spath(aPath);
#ifdef WIN32
	const char presentChar = '/';
	const char charToReplace[] = "\\";
#else
	const char presentChar = '\\';
	const char charToReplace[] = "/";
#endif
	std::string::size_type pathSeparator = std::string::npos;

	while (std::string::npos != (pathSeparator = spath.find(presentChar)))
	{
		spath = spath.replace(pathSeparator, 1, charToReplace);
	}

	return spath;
}
#ifdef WIN32
void char2wchar(const char* aChar, wchar_t* aWchar, int aLength)
{
	if (aLength <= 0)
	{
		return;
	}

	assert(aChar);
	assert(aWchar);
	const int ret = MultiByteToWideChar(CP_ACP, 0, aChar, aLength, aWchar, aLength);
#ifndef NDEBUG

	if (!ret)
	{
		const DWORD errorCode = GetLastError();

		switch (errorCode)
		{
			case ERROR_INSUFFICIENT_BUFFER:
				TRACE(TEXT("A supplied buffer size was not large enough, or it was incorrectly set to NULL"));
				break;

			case ERROR_INVALID_FLAGS:
				TRACE(TEXT("The values supplied for flags were not valid"));
				break;

			case ERROR_INVALID_PARAMETER:
				TRACE(TEXT("Any of the parameter values was invalid"));
				break;

			case ERROR_NO_UNICODE_TRANSLATION:
				TRACE(TEXT("Invalid Unicode was found in a string"));
				break;

			default:
				TRACE(TEXT("Unknown error"));
		}
	}

#else
	(void)ret;
#endif
	assert(ret);
}

void wchar2char(const wchar_t* aWchar, char* aChar, int aLength)
{
	if (aLength <= 0)
	{
		return;
	}

	assert(aWchar);
	assert(aChar);
	static const char defaultChar = '?';
	BOOL usedDefaultChar = false;
	int ret = WideCharToMultiByte(CP_ACP, 0, aWchar, aLength, aChar, aLength, &defaultChar, &usedDefaultChar);
#ifndef NDEBUG

	if (!ret)
	{
		const DWORD errorCode = GetLastError();

		switch (errorCode)
		{
			case ERROR_INSUFFICIENT_BUFFER:
				TRACE(TEXT("A supplied buffer size was not large enough, or it was incorrectly set to NULL"));
				break;

			case ERROR_INVALID_FLAGS:
				TRACE(TEXT("The values supplied for flags were not valid"));
				break;

			case ERROR_INVALID_PARAMETER:
				TRACE(TEXT("Any of the parameter values was invalid"));
				break;

			case ERROR_NO_UNICODE_TRANSLATION:
				TRACE(TEXT("Invalid Unicode was found in a string"));
				break;

			default:
				TRACE(TEXT("Unknown error"));
		}
	}

#else
	(void)ret;
#endif
	assert(ret);
	//assert(!usedDefaultChar);
	assert(nullptr == strstr(aChar, "?"));
}
#endif
}

}
