
#include "CircleColorDemo.h"
#include <elements/rendering/state/state_macro.h>
#include <elements/rendering/utils/program_loader.h>
#include <elements/utils/std/enum.h>
#include <elements/math/transform.h>
#include <Game.h>
#include <algorithm>

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
	  mProgram(nullptr),
	  mSquare(nullptr),
	  mColor(),
	  mTransform(),
	  rate_(60)
{
}

CircleColorDemo::~CircleColorDemo()
{
}

bool CircleColorDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	mSquare = eps::utils::make_unique<eps::rendering::primitive::square>();

	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/primitives/circle_color.prog", (*mProgram.get())))
	{
		return false;
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
	mSquare->construct(vertices);
	mColor = { 0.33f, 0.098f, 0.38f, 1.0f };
	mTransform = eps::math::translate(-1.0f, -1.0f, 0.0f) *
				 eps::math::scale(2.0f, 2.0f, 1.0f) *
				 eps::math::scale(1.0f / size.x, 1.0f / size.y, 1.0f);
	//
	return true;
}

void CircleColorDemo::Update()
{
	float lastTime = rate_.elapsed();

	if (rate_.update() && rate_.elapsed() > lastTime)
	{
		const float elapsedTime = rate_.elapsed() - lastTime;

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_Z))
		{
			mColor.r = std::max(0.0f, mColor.r - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_X))
		{
			mColor.r = std::min(1.0f, mColor.r + 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_C))
		{
			mColor.g = std::max(0.0f, mColor.g - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_V))
		{
			mColor.g = std::min(1.0f, mColor.g + 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_B))
		{
			mColor.b = std::max(0.0f, mColor.b - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_N))
		{
			mColor.b = std::min(1.0f, mColor.b + 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_M))
		{
			mColor.a = std::max(0.0f, mColor.a - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_COMMA))
		{
			mColor.a = std::min(1.0f, mColor.a + 0.0125f * elapsedTime);
		}
	}
}

void CircleColorDemo::Draw()
{
	EPS_STATE_PROGRAM(mProgram->get_product());
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformTransformation), mTransform);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformColor), mColor);
	mSquare->render((*mProgram.get()), eps::utils::to_int(VertexAttributePosition),
					eps::utils::to_int(VertexAttributeTextureCoordinate));
}

}
