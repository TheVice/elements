#ifndef _GEOMETRY_SETTINGS_H_
#define _GEOMETRY_SETTINGS_H_

#include "GeometryVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct GeometrySettings : public eps::asset_xml
{
public:
	std::vector<GeometryVertex> mVertices;
	std::vector<unsigned char> mIndices;

	eps::math::mat4 u_matrix_mvp;
	eps::math::mat4 u_matrix_model_view;
	std::string u_map_normal;
	bool u_has_map_normal;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
