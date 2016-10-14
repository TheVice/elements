
#include "android_asset_reader.h"
#include "elements/assets/asset_operations.h"
#include "elements/assets/asset_blob.h"
#include "elements/assets/asset_texture.h"
#include "elements/assets/asset_xml.h"
#include "logging.h"

struct asset_content : public eps::asset_read_operation
{
	explicit asset_content(const std::string& content)
		: content_(content)
		, pos_(0)
	{
	}

	size_t read(void* output, size_t size)
	{
		if (pos_ < content_.size())
		{
			if (pos_ + size >= content_.size())
			{
				size = content_.size() - pos_;
			}

			content_.copy(static_cast<char*>(output), size, pos_);
			pos_ += size;
			return size;
		}

		return 0;
	}

	size_t size() const
	{
		return content_.size();
	}

	virtual ~asset_content() {}

private:
	const std::string content_;
	std::string::size_type pos_;
};

android_asset_reader::android_asset_reader()
{
}

bool android_asset_reader::visit(eps::asset_blob& asset)
{
	const auto path = asset.resource();
	asset_content opt(assets_.count(path) ? assets_[path] : "");

	if (asset.load(&opt))
	{
		LOGI("asset_blob loaded %s from %i", path.c_str(), android_asset_reader::assets_.size());
		return true;
	}

	LOGE("asset_blob NOT loaded %s from %i", path.c_str(), android_asset_reader::assets_.size());
	return false;
}

bool android_asset_reader::visit(eps::asset_texture& asset)
{
	const auto path = asset.resource();
	asset_content opt(assets_.count(path) ? assets_[path] : "");

	if (asset.load(&opt))
	{
		LOGI("asset_texture loaded %s from %i", path.c_str(), android_asset_reader::assets_.size());
		return true;
	}

	LOGE("asset_texture NOT loaded %s from %i", path.c_str(), android_asset_reader::assets_.size());
	return false;
}

bool android_asset_reader::visit(eps::asset_xml& asset)
{
	const auto path = asset.resource();
	asset_content opt(assets_.count(path) ? assets_[path] : "");

	if (asset.load(&opt))
	{
		LOGI("asset_xml loaded %s from %i", path.c_str(), android_asset_reader::assets_.size());
		return true;
	}

	LOGE("asset_xml NOT loaded %s from %i", path.c_str(), android_asset_reader::assets_.size());
	return false;
}

std::map<std::string, std::string> android_asset_reader::assets_;
