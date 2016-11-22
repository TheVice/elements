#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_

#include <elements/ui/control.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/primitives/square.h>

namespace Library
{

class checkbox : public eps::ui::control
{
public:
	enum class state : short
	{
		CHECKED,
		INDETERMINATE,
		UNCHECKED
	};

public:

	explicit checkbox(control* parent = nullptr);

	state get_state() const;
	GLvoid set_state(state argument_state);

	const std::array<eps::math::vec4, 5>& get_colors() const;
	GLvoid set_colors(std::array<eps::math::vec4, 5>& colors);

	void draw() override;
	bool touch(int x, int y, eps::ui::touch_action action, eps::ui::touch_finger finger) override;

private:

	state state_;

	eps::rendering::program program_face_;
	eps::rendering::primitive::square square_;
	std::array<eps::math::vec4, 5> colors_;
};

}

#endif
