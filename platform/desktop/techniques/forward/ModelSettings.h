#ifndef _MODEL_SETTINGS_H_
#define _MODEL_SETTINGS_H_

#include "ModelVertex.h"
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct ModelSettings : public eps::asset_xml
{
public:
	std::vector<ModelVertex> mVertices;
	std::vector<unsigned char> mIndices;

	glm::mat4 mMatrixMvp;
	glm::mat4 mMatrixModelView;
	glm::mat4 mMatrixView;
	glm::mat3 mMatrixNormal;

	glm::vec3 mLightPos;
	glm::vec3 mCameraPos;

	std::string mMapDiffuse;
	std::string mMapSpecular;
	std::string mMapNormal;

	glm::vec3 mLightIntensity;
	float mLightRange;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	void clear();
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
