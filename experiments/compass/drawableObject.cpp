
#include "drawableObject.h"
#include <elements/rendering/utils/program_loader.h>
#include <elements/rendering/state/state_macro.h>
#include <elements/utils/std/enum.h>
#include <elements/math/transform.h>

namespace Rendering
{
namespace Compass
{

enum program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_transform = 0,
	u_color = 1
};

drawableObject::drawableObject()
	: shader_path_()
	, vertices_()
	, mDescartesMatrix()
	, mWorldMatrix()
	, isArrow(false)
	, program_face_()
	, square_(eps::rendering::buffer_usage::STREAM_DRAW)
{
}

bool drawableObject::initialize(const eps::math::uvec2 & size)
{
	if (shader_path_.empty() || vertices_.empty())
	{
		return false;
	}

	if (!eps::rendering::load_program(shader_path_.c_str(), program_face_))
	{
		return false;
	}

	mDescartesMatrix = eps::math::translate(-1.0f, -1.0f, 0.0f) *
					   eps::math::scale(2.0f, 2.0f, 1.0f) *
					   eps::math::scale(1.0f / size.x, 1.0f / size.y, 1.0f);
	mWorldMatrix = mDescartesMatrix;

	return true;
}

void drawableObject::draw(float)
{
	EPS_STATE_BLEND(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	EPS_STATE_PROGRAM(program_face_.get_product());
	program_face_.uniform_value(eps::utils::to_int(program_enum::u_transform), mWorldMatrix);

	for (const auto& vertex : vertices_)
	{
		program_face_.uniform_value(eps::utils::to_int(program_enum::u_color), std::get<1>(vertex));

		if (isArrow)
		{
			GLfloat vertices[] =
			{
				std::get<0>(vertex).x, std::get<0>(vertex).y, 0.0f, 1.0f,
				std::get<0>(vertex).z, std::get<0>(vertex).y, 1.0f, 1.0f,
				std::get<0>(vertex).x + (std::get<0>(vertex).z - std::get<0>(vertex).x) / 2, std::get<0>(vertex).w, 1.0f, 0.0f,
				std::get<0>(vertex).x + (std::get<0>(vertex).z - std::get<0>(vertex).x) / 2, std::get<0>(vertex).w, 0.0f, 0.0f
			};

			square_.construct(vertices);
		}
		else
		{
			GLfloat vertices[] =
			{
				std::get<0>(vertex).x, std::get<0>(vertex).y, 0.0f, 1.0f,
				std::get<0>(vertex).z, std::get<0>(vertex).y, 1.0f, 1.0f,
				std::get<0>(vertex).z, std::get<0>(vertex).w, 1.0f, 0.0f,
				std::get<0>(vertex).x, std::get<0>(vertex).w, 0.0f, 0.0f
			};

			square_.construct(vertices);
		}

		square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
					   eps::utils::to_int(program_enum::a_vertex_uv));
	}
}

}
}
