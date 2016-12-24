#ifndef _METABALL_SETTINGS_H_
#define _METABALL_SETTINGS_H_

#include "MetaballVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct MetaballSettings : public eps::asset_xml
{
public:
	std::vector<MetaballVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_source;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
