#ifdef A
#ifndef _SETTINGS_READER_H_
#define _SETTINGS_READER_H_

#include "assets/asset_xml.h"
#include <glm/glm.hpp>

struct SettingsReader : public eps::asset_xml
{
public:

	float mExposure;
	float mDecay;
	float mDensity;
	float mWeight;
	glm::vec2 mLightPosition;
	bool mIsEmpty;

public:

	using eps::asset_xml::asset_xml;

private:

	bool read(const pugi::xml_document& doc) final;
};

bool load_data(const char* demo_data_asset, SettingsReader& demo_data);

#endif
#endif
