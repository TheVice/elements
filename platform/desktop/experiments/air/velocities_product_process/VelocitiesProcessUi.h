#ifndef _VELOCITIES_PROCESS_UI_H_
#define _VELOCITIES_PROCESS_UI_H_

#include "VelocitiesProcessVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class VelocitiesProcessUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(VelocitiesProcessUi, UiAsset)

public:
	VelocitiesProcessUi(Library::Game& aGame, const std::string& aAssetPath);
	~VelocitiesProcessUi();

public:
	VelocitiesProcessUi() = delete;
	VelocitiesProcessUi(const VelocitiesProcessUi& aRhs) = delete;
	VelocitiesProcessUi& operator = (const VelocitiesProcessUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_dt(const float& a_u_dt);
	const float& Get_u_dt() const;

	void SetVertices(const std::vector<VelocitiesProcessVertex>& aVertices);
	const std::vector<VelocitiesProcessVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	float m_u_dt;
	std::vector<VelocitiesProcessVertex> mVertices;
};
}

#endif
