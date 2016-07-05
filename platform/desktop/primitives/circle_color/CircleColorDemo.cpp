
#include "CircleColorDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(CircleColorDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeTextureCoordinate = 1,
	//
	FragmentUniformTransformation = 0,
	FragmentUniformColor = 1
};

CircleColorDemo::CircleColorDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mProgramCircleColor(),
	  mSquare(eps::rendering::buffer_usage::STREAM_DRAW),
	  mColor(),
	  mTransform()
{
}

CircleColorDemo::~CircleColorDemo()
{
}

void CircleColorDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("shaders/primitives/circle_color.prog", mProgramCircleColor))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

	glm::vec2 pos = { 1.0f, 0.0f };
	float offset = size.y * 0.5f;
	glm::vec2 tracker(pos.x + (size.x - offset) * 0.5f, pos.y + (size.y - offset) * 0.5f);
	GLfloat vertices[] =
	{
		(tracker.x), (tracker.y),          0.0f, 1.0f,
		(tracker.x + offset), (tracker.y),          1.0f, 1.0f,
		(tracker.x + offset), (tracker.y + offset), 1.0f, 0.0f,
		(tracker.x), (tracker.y + offset), 0.0f, 0.0f
	};
	mSquare.construct(vertices);
	mColor = { 0.33f, 0.098f, 0.38f, 0.44f };
	mTransform = eps::math::translate(-1.0f, -1.0f, 0.0f) *
				 eps::math::scale(2.0f, 2.0f, 1.0f) *
				 eps::math::scale(1.0f / size.x, 1.0f / size.y, 1.0f);
}

void CircleColorDemo::Draw(const Library::GameTime&)
{
	EPS_STATE_PROGRAM(mProgramCircleColor.get_product());
	mProgramCircleColor.uniform_value(
		eps::utils::to_int(ProgramEnum::FragmentUniformTransformation), mTransform);
	mProgramCircleColor.uniform_value(eps::utils::to_int(ProgramEnum::FragmentUniformColor), mColor);
	mSquare.render(mProgramCircleColor, eps::utils::to_int(ProgramEnum::VertexAttributePosition),
				   eps::utils::to_int(ProgramEnum::VertexAttributeTextureCoordinate));
}

}
