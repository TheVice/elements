
#include "checkbox.h"
#include <elements/ui/system.h>
#include <elements/rendering/state/state_macro.h>
#include <elements/rendering/core/opengl.h>
#include <elements/rendering/utils/program_loader.h>
#include <elements/utils/std/enum.h>

#define DEFAULT_WIDTH 13
#define DEFAULT_HEIGHT 13

namespace Library
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
	//
	std::vector<std::pair<eps::math::vec4, eps::math::vec4>> pos_and_colors =
	{
		std::make_pair(
			eps::math::vec4(pos.x, pos.y,
		pos.x + get_size().x, pos.y + step.y),
			colors_[0]),
		//
		std::make_pair(
			eps::math::vec4(pos.x + get_size().x - step.x, pos.y + step.y,
		pos.x + get_size().x, pos.y + get_size().y),
			colors_[0]),
		//
		std::make_pair(
			eps::math::vec4(pos.x, pos.y + get_size().y - step.y,
		pos.x + get_size().x - step.x, pos.y + get_size().y),
			colors_[1]),
		//
		std::make_pair(
			eps::math::vec4(pos.x, pos.y + step.y,
		pos.x + step.x, pos.y + get_size().y - step.y),
			colors_[1]),
		//
		std::make_pair(
			eps::math::vec4(pos.x + step.x, pos.y + step.y,
		pos.x + get_size().x - step.x, pos.y + 2 * step.y),
			colors_[2]),
		//
		std::make_pair(
			eps::math::vec4(pos.x + get_size().x - 2 * step.x, pos.y + 2 * step.y,
		pos.x + get_size().x - step.x, pos.y + get_size().y - step.y),
			colors_[2]),
		//
		std::make_pair(
			eps::math::vec4(pos.x + step.x, pos.y + get_size().y - 2 * step.y,
		pos.x + get_size().x - 2 * step.x, pos.y + get_size().y - step.y),
			colors_[3]),
		//
		std::make_pair(
			eps::math::vec4(pos.x + step.x, pos.y + 2 * step.y,
		pos.x + 2 * step.x, pos.y + get_size().y - 2 * step.y),
			colors_[3])
	};

	switch (state_)
	{
		case state::CHECKED:
		{
			std::vector<std::pair<eps::math::vec4, eps::math::vec4>> checked_pos_and_colors =
			{
				std::make_pair(
					eps::math::vec4(pos.x + 3 * step.x, pos.y + 5 * step.y,
				pos.x + 4 * step.x, pos.y + 8 * step.y),
					colors_[4]),
				//
				std::make_pair(
					eps::math::vec4(pos.x + 4 * step.x, pos.y + 4 * step.y,
				pos.x + 5 * step.x, pos.y + 7 * step.y),
					colors_[4]),
				//
				std::make_pair(
					eps::math::vec4(pos.x + 5 * step.x, pos.y + 3 * step.y,
				pos.x + 6 * step.x, pos.y + 6 * step.y),
					colors_[4]),
				//
				std::make_pair(
					eps::math::vec4(pos.x + 6 * step.x, pos.y + 4 * step.y,
				pos.x + 7 * step.x, pos.y + 7 * step.y),
					colors_[4]),
				//
				std::make_pair(
					eps::math::vec4(pos.x + 7 * step.x, pos.y + 5 * step.y,
				pos.x + 8 * step.x, pos.y + 8 * step.y),
					colors_[4]),
				//
				std::make_pair(
					eps::math::vec4(pos.x + 8 * step.x, pos.y + 6 * step.y,
				pos.x + 9 * step.x, pos.y + 9 * step.y),
					colors_[4]),
				//
				std::make_pair(
					eps::math::vec4(pos.x + 9 * step.x, pos.y + 7 * step.y,
				pos.x + 10 * step.x, pos.y + 10 * step.y),
					colors_[4])
			};
			pos_and_colors.insert(pos_and_colors.end(), checked_pos_and_colors.begin(), checked_pos_and_colors.end());
		}
		break;

		case state::INDETERMINATE:
		{
			pos_and_colors.push_back(std::make_pair(
										 eps::math::vec4(pos.x + 3 * step.x, pos.y + 3 * step.y,
												 pos.x + 10 * step.x, pos.y + 10 * step.y),
										 colors_[4]));
		}
		break;

		default:
			break;
	}

	EPS_STATE_BLEND(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	EPS_STATE_PROGRAM(program_face_.get_product());
	program_face_.uniform_value(eps::utils::to_int(program_enum::u_transform), get_system()->transform());

	for (const auto& color_position : pos_and_colors)
	{
		program_face_.uniform_value(eps::utils::to_int(program_enum::u_color), std::get<1>(color_position));
		//
		GLfloat vertices[] =
		{
			std::get<0>(color_position).x, std::get<0>(color_position).y, 0.0f, 1.0f,
			std::get<0>(color_position).z, std::get<0>(color_position).y, 1.0f, 1.0f,
			std::get<0>(color_position).z, std::get<0>(color_position).w, 1.0f, 0.0f,
			std::get<0>(color_position).x, std::get<0>(color_position).w, 0.0f, 0.0f
		};
		//
		square_.construct(vertices);
		square_.render(program_face_, eps::utils::to_int(program_enum::a_vertex_xy),
					   eps::utils::to_int(program_enum::a_vertex_uv));
	}

	control::draw();
}

bool checkbox::touch(int x, int y, eps::ui::touch_action action, eps::ui::touch_finger finger)
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

	if (sys->capture_test(this, finger))
	{
		if (action == eps::ui::touch_action::UP)
		{
			sys->capture_release(finger);
		}

		return true;
	}

	return false;
}

}
