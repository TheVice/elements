#ifndef _METABALL_UI_H_
#define _METABALL_UI_H_

#include "MetaballVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class MetaballUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(MetaballUi, UiAsset)

public:
	MetaballUi(Library::Game& aGame, const std::string& aAssetPath);
	~MetaballUi();

public:
	MetaballUi() = delete;
	MetaballUi(const MetaballUi& aRhs) = delete;
	MetaballUi& operator = (const MetaballUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:

	void SetVertices(const std::vector<MetaballVertex>& aVertices);
	const std::vector<MetaballVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	std::vector<MetaballVertex> mVertices;
};
}

#endif
