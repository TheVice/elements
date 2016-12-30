#ifndef _TONE_SETTINGS_H_
#define _TONE_SETTINGS_H_

#include "ToneVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct ToneSettings : public eps::asset_xml
{
public:
	std::vector<ToneVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_source_1;
	std::string u_source_2;
	float u_exposure;
	float u_gamma;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
