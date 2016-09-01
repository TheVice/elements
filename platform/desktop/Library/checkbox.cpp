
#include "checkbox.h"
#include "ui/system.h"
#include "rendering/state/state_macro.h"
#include "rendering/core/opengl.h"
#include "rendering/utils/program_loader.h"
#include "utils/std/enum.h"

#define DEFAULT_WIDTH 13
#define DEFAULT_HEIGHT 13

namespace Desktop
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

checkbox::checkbox(control* parent)
	: control(parent)
	, state_(state::UNCHECKED)
	, square_(eps::rendering::buffer_usage::STREAM_DRAW)
	, colors_{   eps::math::vec4(1.0f,    1.0f,     1.0f,    1.0f)
			   , eps::math::vec4(0.5f,    0.5f,     0.5f,    1.0f)
			   , eps::math::vec4(0.8314f, 0.81569f, 0.7843f, 1.0f)
			   , eps::math::vec4(0.25f,   0.25f,    0.25f,   1.0f)
			   , eps::math::vec4(0.0f,    0.0f,     0.0f,    1.0f)
			 }
{
	eps::rendering::load_program("assets/shaders/primitives/square_color.prog",
								 program_face_);
}

checkbox::state checkbox::get_state() const
{
	return state_;
}

GLvoid checkbox::set_state(checkbox::state argument_state)
{
	state_ = argument_state;
}

const std::array<eps::math::vec4, 5>& checkbox::get_colors() const
{
	return colors_;
}

GLvoid checkbox::set_colors(std::array<eps::math::vec4, 5>& colors)
{
	colors_ = colors;
}

void checkbox::draw()
{
	const auto pos = global_position();
	const auto step = eps::math::vec2(get_size().x / DEFAULT_WIDTH, get_size().y / DEFAULT_WIDTH);
	EPS_STATE_BLEND(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	EPS_STATE_PROGRAM(program_face_.get_product());
	program_face_.uniform_value(eps::utils::to_int(program_enum::u_transform), get_system()->transform());
	program_face_.uniform_value(eps::utils::to_int(program_enum::u_color), colors_[0]);
	auto minPos = eps::math::vec2(pos.x, pos.y);
	auto maxPos = eps::math::vec2(pos.x + get_size().x, pos.y + step.y);
	{
		GLfloat vertices[] =
		{
			(minPos.x), (minPos.y), 0.0f, 1.0f,
			(maxPos.x), (minPos.y), 1.0f, 1.0f,
			(maxPos.x), (maxPos.y), 1.0f, 0.0f,
			(minPos.x), (maxPos.y), 0.0f, 0.0f
		};
		square_.construct(vertices);
	}
	square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
				   eps::utils::to_int(program_enum::a_vertex_uv));
	minPos = eps::math::vec2(pos.x + get_size().x - step.x, pos.y + step.y);
	maxPos = eps::math::vec2(pos.x + get_size().x, pos.y + get_size().y);
	{
		GLfloat vertices[] =
		{
			(minPos.x), (minPos.y), 0.0f, 1.0f,
			(maxPos.x), (minPos.y), 1.0f, 1.0f,
			(maxPos.x), (maxPos.y), 1.0f, 0.0f,
			(minPos.x), (maxPos.y), 0.0f, 0.0f
		};
		square_.construct(vertices);
	}
	square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
				   eps::utils::to_int(program_enum::a_vertex_uv));
	program_face_.uniform_value(eps::utils::to_int(program_enum::u_color), colors_[1]);
	minPos = eps::math::vec2(pos.x, pos.y + get_size().y - step.y);
	maxPos = eps::math::vec2(pos.x + get_size().x - step.x, pos.y + get_size().y);
	{
		GLfloat vertices[] =
		{
			(minPos.x), (minPos.y), 0.0f, 1.0f,
			(maxPos.x), (minPos.y), 1.0f, 1.0f,
			(maxPos.x), (maxPos.y), 1.0f, 0.0f,
			(minPos.x), (maxPos.y), 0.0f, 0.0f
		};
		square_.construct(vertices);
	}
	square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
				   eps::utils::to_int(program_enum::a_vertex_uv));
	minPos = eps::math::vec2(pos.x, pos.y + step.y);
	maxPos = eps::math::vec2(pos.x + step.x, pos.y + get_size().y - step.y);
	{
		GLfloat vertices[] =
		{
			(minPos.x), (minPos.y), 0.0f, 1.0f,
			(maxPos.x), (minPos.y), 1.0f, 1.0f,
			(maxPos.x), (maxPos.y), 1.0f, 0.0f,
			(minPos.x), (maxPos.y), 0.0f, 0.0f
		};
		square_.construct(vertices);
	}
	square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
				   eps::utils::to_int(program_enum::a_vertex_uv));
	program_face_.uniform_value(eps::utils::to_int(program_enum::u_color), colors_[2]);
	minPos = eps::math::vec2(pos.x + step.x, pos.y + step.y);
	maxPos = eps::math::vec2(pos.x + get_size().x - step.x, pos.y + 2 * step.y);
	{
		GLfloat vertices[] =
		{
			(minPos.x), (minPos.y), 0.0f, 1.0f,
			(maxPos.x), (minPos.y), 1.0f, 1.0f,
			(maxPos.x), (maxPos.y), 1.0f, 0.0f,
			(minPos.x), (maxPos.y), 0.0f, 0.0f
		};
		square_.construct(vertices);
	}
	square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
				   eps::utils::to_int(program_enum::a_vertex_uv));
	minPos = eps::math::vec2(pos.x + get_size().x - 2 * step.x, pos.y + 2 * step.y);
	maxPos = eps::math::vec2(pos.x + get_size().x - step.x, pos.y + get_size().y - step.y);
	{
		GLfloat vertices[] =
		{
			(minPos.x), (minPos.y), 0.0f, 1.0f,
			(maxPos.x), (minPos.y), 1.0f, 1.0f,
			(maxPos.x), (maxPos.y), 1.0f, 0.0f,
			(minPos.x), (maxPos.y), 0.0f, 0.0f
		};
		square_.construct(vertices);
	}
	square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
				   eps::utils::to_int(program_enum::a_vertex_uv));
	program_face_.uniform_value(eps::utils::to_int(program_enum::u_color), colors_[3]);
	minPos = eps::math::vec2(pos.x + step.x, pos.y + get_size().y - 2 * step.y);
	maxPos = eps::math::vec2(pos.x + get_size().x - 2 * step.x, pos.y + get_size().y - step.y);
	{
		GLfloat vertices[] =
		{
			(minPos.x), (minPos.y), 0.0f, 1.0f,
			(maxPos.x), (minPos.y), 1.0f, 1.0f,
			(maxPos.x), (maxPos.y), 1.0f, 0.0f,
			(minPos.x), (maxPos.y), 0.0f, 0.0f
		};
		square_.construct(vertices);
	}
	square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
				   eps::utils::to_int(program_enum::a_vertex_uv));
	minPos = eps::math::vec2(pos.x + step.x, pos.y + 2 * step.y);
	maxPos = eps::math::vec2(pos.x + 2 * step.x, pos.y + get_size().y - 2 * step.y);
	{
		GLfloat vertices[] =
		{
			(minPos.x), (minPos.y), 0.0f, 1.0f,
			(maxPos.x), (minPos.y), 1.0f, 1.0f,
			(maxPos.x), (maxPos.y), 1.0f, 0.0f,
			(minPos.x), (maxPos.y), 0.0f, 0.0f
		};
		square_.construct(vertices);
	}
	square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
				   eps::utils::to_int(program_enum::a_vertex_uv));

	switch (state_)
	{
		case state::CHECKED:
		{
			program_face_.uniform_value(eps::utils::to_int(program_enum::u_color), colors_[4]);
			minPos = eps::math::vec2(pos.x + 3 * step.x, pos.y + 5 * step.y);
			maxPos = eps::math::vec2(pos.x + 4 * step.x, pos.y + 8 * step.y);
			{
				GLfloat vertices[] =
				{
					(minPos.x), (minPos.y), 0.0f, 1.0f,
					(maxPos.x), (minPos.y), 1.0f, 1.0f,
					(maxPos.x), (maxPos.y), 1.0f, 0.0f,
					(minPos.x), (maxPos.y), 0.0f, 0.0f
				};
				square_.construct(vertices);
			}
			square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
						   eps::utils::to_int(program_enum::a_vertex_uv));
			minPos = eps::math::vec2(pos.x + 4 * step.x, pos.y + 4 * step.y);
			maxPos = eps::math::vec2(pos.x + 5 * step.x, pos.y + 7 * step.y);
			{
				GLfloat vertices[] =
				{
					(minPos.x), (minPos.y), 0.0f, 1.0f,
					(maxPos.x), (minPos.y), 1.0f, 1.0f,
					(maxPos.x), (maxPos.y), 1.0f, 0.0f,
					(minPos.x), (maxPos.y), 0.0f, 0.0f
				};
				square_.construct(vertices);
			}
			square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
						   eps::utils::to_int(program_enum::a_vertex_uv));
			minPos = eps::math::vec2(pos.x + 5 * step.x, pos.y + 3 * step.y);
			maxPos = eps::math::vec2(pos.x + 6 * step.x, pos.y + 6 * step.y);
			{
				GLfloat vertices[] =
				{
					(minPos.x), (minPos.y), 0.0f, 1.0f,
					(maxPos.x), (minPos.y), 1.0f, 1.0f,
					(maxPos.x), (maxPos.y), 1.0f, 0.0f,
					(minPos.x), (maxPos.y), 0.0f, 0.0f
				};
				square_.construct(vertices);
			}
			square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
						   eps::utils::to_int(program_enum::a_vertex_uv));
			minPos = eps::math::vec2(pos.x + 6 * step.x, pos.y + 4 * step.y);
			maxPos = eps::math::vec2(pos.x + 7 * step.x, pos.y + 7 * step.y);
			{
				GLfloat vertices[] =
				{
					(minPos.x), (minPos.y), 0.0f, 1.0f,
					(maxPos.x), (minPos.y), 1.0f, 1.0f,
					(maxPos.x), (maxPos.y), 1.0f, 0.0f,
					(minPos.x), (maxPos.y), 0.0f, 0.0f
				};
				square_.construct(vertices);
			}
			square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
						   eps::utils::to_int(program_enum::a_vertex_uv));
			minPos = eps::math::vec2(pos.x + 7 * step.x, pos.y + 5 * step.y);
			maxPos = eps::math::vec2(pos.x + 8 * step.x, pos.y + 8 * step.y);
			{
				GLfloat vertices[] =
				{
					(minPos.x), (minPos.y), 0.0f, 1.0f,
					(maxPos.x), (minPos.y), 1.0f, 1.0f,
					(maxPos.x), (maxPos.y), 1.0f, 0.0f,
					(minPos.x), (maxPos.y), 0.0f, 0.0f
				};
				square_.construct(vertices);
			}
			square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
						   eps::utils::to_int(program_enum::a_vertex_uv));
			minPos = eps::math::vec2(pos.x + 8 * step.x, pos.y + 6 * step.y);
			maxPos = eps::math::vec2(pos.x + 9 * step.x, pos.y + 9 * step.y);
			{
				GLfloat vertices[] =
				{
					(minPos.x), (minPos.y), 0.0f, 1.0f,
					(maxPos.x), (minPos.y), 1.0f, 1.0f,
					(maxPos.x), (maxPos.y), 1.0f, 0.0f,
					(minPos.x), (maxPos.y), 0.0f, 0.0f
				};
				square_.construct(vertices);
			}
			square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
						   eps::utils::to_int(program_enum::a_vertex_uv));
			minPos = eps::math::vec2(pos.x + 9 * step.x, pos.y + 7 * step.y);
			maxPos = eps::math::vec2(pos.x + 10 * step.x, pos.y + 10 * step.y);
			{
				GLfloat vertices[] =
				{
					(minPos.x), (minPos.y), 0.0f, 1.0f,
					(maxPos.x), (minPos.y), 1.0f, 1.0f,
					(maxPos.x), (maxPos.y), 1.0f, 0.0f,
					(minPos.x), (maxPos.y), 0.0f, 0.0f
				};
				square_.construct(vertices);
			}
			square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
						   eps::utils::to_int(program_enum::a_vertex_uv));
		}
		break;

		case state::INDETERMINATE:
		{
			program_face_.uniform_value(eps::utils::to_int(program_enum::u_color), colors_[4]);
			minPos = eps::math::vec2(pos.x + 3 * step.x, pos.y + 3 * step.y);
			maxPos = eps::math::vec2(pos.x + 10 * step.x, pos.y + 10 * step.y);
			{
				GLfloat vertices[] =
				{
					(minPos.x), (minPos.y), 0.0f, 1.0f,
					(maxPos.x), (minPos.y), 1.0f, 1.0f,
					(maxPos.x), (maxPos.y), 1.0f, 0.0f,
					(minPos.x), (maxPos.y), 0.0f, 0.0f
				};
				square_.construct(vertices);
			}
			square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
						   eps::utils::to_int(program_enum::a_vertex_uv));
		}
		break;

		default:
			break;
	}

	control::draw();
}

bool checkbox::touch(int x, int y, eps::ui::touch_action action)
{
	auto sys = get_system();
	const auto pos = global_position();

	if ((pos.x < x && x < pos.x + get_size().x &&
		 (pos.y < y && y < pos.y + get_size().y)))
	{
		if (action == eps::ui::touch_action::UP)
		{
			if ((state_ == state::CHECKED) || (state_ == state::INDETERMINATE))
			{
				state_ = state::UNCHECKED;
			}
			else
			{
				state_ = state::CHECKED;
			}
		}
	}

	if (sys->capture_test(this))
	{
		if (action == eps::ui::touch_action::UP)
		{
			sys->capture_release();
		}

		return true;
	}

	return false;
}

}
