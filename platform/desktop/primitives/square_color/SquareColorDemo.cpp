
#include "SquareColorDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(SquareColorDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeTextureCoordinate = 1,
	//
	FragmentUniformTransformation = 0,
	FragmentUniformColor = 1
};

SquareColorDemo::SquareColorDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mProgram(),
	  mSquare(),
	  mColor(),
	  mTransform()
{
}

SquareColorDemo::~SquareColorDemo()
{
}

void SquareColorDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("shaders/primitives/square_color.prog", mProgram))
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

void SquareColorDemo::Draw(const Library::GameTime&)
{
	EPS_STATE_PROGRAM(mProgram.get_product());
	mProgram.uniform_value(
		eps::utils::to_int(ProgramEnum::FragmentUniformTransformation), mTransform);
	mProgram.uniform_value(eps::utils::to_int(ProgramEnum::FragmentUniformColor), mColor);
	mSquare.render(mProgram, eps::utils::to_int(ProgramEnum::VertexAttributePosition),
				   eps::utils::to_int(ProgramEnum::VertexAttributeTextureCoordinate));
}

}
