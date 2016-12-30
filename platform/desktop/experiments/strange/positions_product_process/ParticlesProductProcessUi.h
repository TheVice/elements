#ifndef _PARTICLES_PRODUCT_PROCESS_UI_H_
#define _PARTICLES_PRODUCT_PROCESS_UI_H_

#include "ParticlesProductProcessVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class ParticlesProductProcessUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(ParticlesProductProcessUi, UiAsset)

public:
	ParticlesProductProcessUi(Library::Game& aGame, const std::string& aAssetPath);
	~ParticlesProductProcessUi();

public:
	ParticlesProductProcessUi() = delete;
	ParticlesProductProcessUi(const ParticlesProductProcessUi& aRhs) = delete;
	ParticlesProductProcessUi& operator = (const ParticlesProductProcessUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_attractor_a(const float& a_u_attractor_a);
	const float& Get_u_attractor_a() const;

	void Set_u_attractor_b(const float& a_u_attractor_b);
	const float& Get_u_attractor_b() const;

	void Set_u_attractor_c(const float& a_u_attractor_c);
	const float& Get_u_attractor_c() const;

	void Set_u_attractor_d(const float& a_u_attractor_d);
	const float& Get_u_attractor_d() const;

	void SetVertices(const std::vector<ParticlesProductProcessVertex>& aVertices);
	const std::vector<ParticlesProductProcessVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	float m_u_attractor_a;
	float m_u_attractor_b;
	float m_u_attractor_c;
	float m_u_attractor_d;
	std::vector<ParticlesProductProcessVertex> mVertices;
};
}

#endif
