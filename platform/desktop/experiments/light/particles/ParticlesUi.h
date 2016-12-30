#ifndef _PARTICLES_UI_H_
#define _PARTICLES_UI_H_

#include "ParticlesVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class ParticlesUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(ParticlesUi, UiAsset)

public:
	ParticlesUi(Library::Game& aGame, const std::string& aAssetPath);
	~ParticlesUi();

public:
	ParticlesUi() = delete;
	ParticlesUi(const ParticlesUi& aRhs) = delete;
	ParticlesUi& operator = (const ParticlesUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_texel(const eps::math::vec2& a_u_texel);
	const eps::math::vec2& Get_u_texel() const;

	void Set_u_size(const float& a_u_size);
	const float& Get_u_size() const;

	void SetVertices(const std::vector<ParticlesVertex>& aVertices);
	const std::vector<ParticlesVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::vec2 m_u_texel;
	float m_u_size;
	std::vector<ParticlesVertex> mVertices;
};
}

#endif
