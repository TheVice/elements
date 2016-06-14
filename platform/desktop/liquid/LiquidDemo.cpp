
#include "LiquidDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
//#include "elements/simulation/liquid/system.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(LiquidDemo)

LiquidDemo::LiquidDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  //	  mSystem(nullptr),
	  mRenderer(nullptr),
	  mParticlesCount(10)
{
}

LiquidDemo::~LiquidDemo()
{
}

void LiquidDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	// create simulation subsystem
	//	mSystem = std::make_unique<eps::simulation::liquid::system>();
	// construct with window size
	//	mSystem->construct(size, mParticlesCount);
	//
	//    void set_gravity(const math::vec2 & value) { config_.gravity(value); }
	//    void set_density(float value) { config_.density(value); }
	//    void set_viscosity(float sigma, float beta) { config_.viscosty(sigma, beta); }
	//    void set_pressure(float value, float near) { config_.pressure(value, near); }
	//    void set_elasticity(float value) { config_.spring(value); }
	//
	//	mRenderer = std::make_unique<eps::experiment::liquid::renderer>();
	//	//
	//	if (!mRenderer->initialize())
	//	{
	//		throw std::runtime_error("mRenderer->initialize() failed");
	//	}
	//    void set_particles(sync::future<math::vec2> particles);
	//    bool set_surface_background(const std::string & asset_name);
	//    void set_surface_color(const math::vec4 & color);
	//    bool construct(const math::uvec2 & size, const math::uvec2 & sim_size, size_t texture_size);
}

void LiquidDemo::Draw(const Library::GameTime&)
{
	//	mRenderer->render();
}

}
