#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

#include <string>
#include <elements/math/types.h>

namespace eps
{
namespace rendering
{
class texture;
}
}

namespace Library
{
namespace TextureLoader
{

enum class presets : short
{
	color_bars = 0,
	smpte_color_bars,
	smpte_color_bars_hd
};

bool loadFromFile(const std::string& a_path, eps::rendering::texture& a_texture);
bool loadFromPreset(const eps::math::uvec2& a_size, Library::TextureLoader::presets a_preset,
					eps::rendering::texture& a_texture);

#define LOAD_TEXTURE(S, T)																																							\
	if (S == "ColorBars")																																							\
	{																																												\
		if (!Library::TextureLoader::loadFromPreset(eps::math::uvec2(mGame->GetScreenWidth(), mGame->GetScreenHeight()), Library::TextureLoader::presets::color_bars, T))			\
		{																																											\
			return false;																																							\
		}																																											\
	}																																												\
	else if (S == "SmpteColorBars")																																					\
	{																																												\
		if (!Library::TextureLoader::loadFromPreset(eps::math::uvec2(mGame->GetScreenWidth(), mGame->GetScreenHeight()), Library::TextureLoader::presets::smpte_color_bars, T))		\
		{																																											\
			return false;																																							\
		}																																											\
	}																																												\
	else if (S == "SmpteColorBarsHD")																																				\
	{																																												\
		if (!Library::TextureLoader::loadFromPreset(eps::math::uvec2(mGame->GetScreenWidth(), mGame->GetScreenHeight()), Library::TextureLoader::presets::smpte_color_bars_hd, T))	\
		{																																											\
			return false;																																							\
		}																																											\
	}																																												\
	else																																											\
	{																																												\
		if (!Library::TextureLoader::loadFromFile(S, T))																															\
		{																																											\
			return false;																																							\
		}																																											\
	}

}
}

#endif
