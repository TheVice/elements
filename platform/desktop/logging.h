
#if defined(WIN32)
#include <windows.h>
#undef far
#undef near

#define LOGI(aFormat) OutputDebugStringA(aFormat)
#define LOGE(aFormat) LOGI(aFormat)

#elif defined(__linux)
#include <iostream>

#define LOGI(aFormat) std::cout << (aFormat) << std::endl
#define LOGE(aFormat) std::cerr << (aFormat) << std::endl

#endif
