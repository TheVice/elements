
#include "TextureLoader.h"
#include "TestCard.h"
#include <elements/assets/asset_texture.h>
#include <elements/assets/assets_storage.h>
#include <elements/rendering/core/texture_maker.h>
#include <elements/rendering/core/texture_policy.h>

namespace Library
{
namespace TextureLoader
{

bool loadFromFile(const std::string& a_path, eps::rendering::texture& a_texture)
{
	const auto asset = eps::assets_storage::instance().read<eps::asset_texture>(a_path);

	if (!asset || !asset->pixels())
	{
		return false;
	}

	auto maker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>();
	a_texture = maker.construct(asset->pixels(), asset->size());
	return true;
}

bool loadFromPreset(const eps::math::uvec2& a_size, Library::TextureLoader::presets a_preset,
					eps::rendering::texture& a_texture)
{
	if (!a_size.x || !a_size.y)
	{
		return false;
	}

	auto data = eps::utils::make_unique<unsigned char[]>(4 * a_size.x * a_size.y);

	switch (a_preset)
	{
		case presets::color_bars:
			Library::TestCard::MakeColorBars(data.get(), a_size.x, a_size.y);
			break;

		case presets::smpte_color_bars:
			Library::TestCard::MakeSmpteColorBars(data.get(), a_size.x, a_size.y);
			break;

		case presets::smpte_color_bars_hd:
			Library::TestCard::MakeSmpteColorBarsHD(data.get(), a_size.x, a_size.y);
			break;

		default:
			return false;
	}

	auto maker = eps::rendering::get_texture_maker<eps::rendering::default_texture_policy>();
	a_texture = maker.construct(data.get(), a_size);
	return true;
}

}
}
