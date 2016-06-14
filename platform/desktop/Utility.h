#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <vector>
#include <fstream>

namespace Library
{
namespace Utility
{
std::string path(const char* aPath);
std::string path(std::string aPath);
#ifdef WIN32
void char2wchar(const char* aChar, wchar_t* aWchar, int aLength);
void wchar2char(const wchar_t* aWchar, char* aChar, int aLength);
#endif
}
}

#define P(A) Library::Utility::path(A)

#endif
