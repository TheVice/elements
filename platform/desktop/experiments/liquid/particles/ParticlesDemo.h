#ifndef _PARTICLES_DEMO_H_
#define _PARTICLES_DEMO_H_

#include "DrawableGameComponent.h"
#include "rendering/core/program.h"
#include "rendering/core/texture.h"
#include "rendering/core/texture_policy.h"
#include "rendering/primitives/square.h"
#include <GL/glew.h>
#ifdef _WIN32
#include <memory>
#include <thread>
#endif

namespace Rendering
{
class ParticlesDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(ParticlesDemo, DrawableGameComponent)

public:
	ParticlesDemo(Library::Game& aGame);
	~ParticlesDemo();

public:
	ParticlesDemo() = delete;
	ParticlesDemo(const ParticlesDemo& aRhs) = delete;
	ParticlesDemo& operator = (const ParticlesDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
#ifdef _WIN32
	virtual void Update(const Library::GameTime& aGameTime) override;
#endif
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	eps::rendering::primitive::square mSquare;
	glm::mat4 mTransform;
	float mSize;
#ifdef _WIN32
	std::unique_ptr<std::thread> mSettingsWindowThread;
#endif
};
}

#endif