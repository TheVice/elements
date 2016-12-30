#ifndef _VELOCITIES_RESET_UI_H_
#define _VELOCITIES_RESET_UI_H_

#include "VelocitiesResetVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class VelocitiesResetUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(VelocitiesResetUi, UiAsset)

public:
	VelocitiesResetUi(Library::Game& aGame, const std::string& aAssetPath);
	~VelocitiesResetUi();

public:
	VelocitiesResetUi() = delete;
	VelocitiesResetUi(const VelocitiesResetUi& aRhs) = delete;
	VelocitiesResetUi& operator = (const VelocitiesResetUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:

	void SetVertices(const std::vector<VelocitiesResetVertex>& aVertices);
	const std::vector<VelocitiesResetVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	std::vector<VelocitiesResetVertex> mVertices;
};
}

#endif
