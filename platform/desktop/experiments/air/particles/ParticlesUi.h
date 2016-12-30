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
	void Set_u_color_speed_down(const eps::math::vec3& a_u_color_speed_down);
	const eps::math::vec3& Get_u_color_speed_down() const;

	void Set_u_color_speed_up(const eps::math::vec3& a_u_color_speed_up);
	const eps::math::vec3& Get_u_color_speed_up() const;

	void SetVertices(const std::vector<ParticlesVertex>& aVertices);
	const std::vector<ParticlesVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::vec3 m_u_color_speed_down;
	eps::math::vec3 m_u_color_speed_up;
	std::vector<ParticlesVertex> mVertices;
};
}

#endif
