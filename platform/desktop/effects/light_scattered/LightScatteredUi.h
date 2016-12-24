#ifndef _LIGHT_SCATTERED_UI_H_
#define _LIGHT_SCATTERED_UI_H_

#include "LightScatteredVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class LightScatteredUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(LightScatteredUi, UiAsset)

public:
	LightScatteredUi(Library::Game& aGame, const std::string& aAssetPath);
	~LightScatteredUi();

public:
	LightScatteredUi() = delete;
	LightScatteredUi(const LightScatteredUi& aRhs) = delete;
	LightScatteredUi& operator = (const LightScatteredUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_exposure(const float& a_u_exposure);
	const float& Get_u_exposure() const;

	void Set_u_decay(const float& a_u_decay);
	const float& Get_u_decay() const;

	void Set_u_density(const float& a_u_density);
	const float& Get_u_density() const;

	void Set_u_weight(const float& a_u_weight);
	const float& Get_u_weight() const;

	void Set_u_light_position(const eps::math::vec2& a_u_light_position);
	const eps::math::vec2& Get_u_light_position() const;

	void SetVertices(const std::vector<LightScatteredVertex>& aVertices);
	const std::vector<LightScatteredVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	float m_u_exposure;
	float m_u_decay;
	float m_u_density;
	float m_u_weight;
	eps::math::vec2 m_u_light_position;
	std::vector<LightScatteredVertex> mVertices;
};
}

#endif
