
#include "renderer.h"

#include <elements/rendering/effects/clear.h>

namespace Rendering
{
namespace Compass
{

renderer::renderer()
	: passes_()
	, arrow_(nullptr)
	, rose_(nullptr)
{
}

bool renderer::initialize()
{
	// initialize passes
	passes_.initialize(1);

	auto link_clear = passes_.add_pass<eps::rendering::effect::clear>();

	if (auto clear = link_clear.lock())
	{
		clear->set_color(eps::math::vec4(0.392f, 0.584f, 0.929f, 1.0f));
	}
	else
	{
		return false;
	}

	arrow_ = eps::utils::make_unique<arrow>();
	rose_ = eps::utils::make_unique<rose>();
	//
	return true;
}

bool renderer::construct(const eps::math::uvec2 & size)
{
	const auto maxSide = std::min(size.x, size.y) / 2;
	const auto k = static_cast<float>(maxSide) / arrow::defaultSize().y;
	//
	arrow_->size() = eps::math::vec2(arrow::defaultSize().x * k,
									 arrow::defaultSize().y * k);
	arrow_->position() = eps::math::vec2(size.x / 2 - arrow_->size().x / 2,
										 size.y / 2 - arrow_->size().y / 2);

	if (!arrow_->initialize(size))
	{
		return false;
	}

	rose_->radius() = eps::math::vec2(rose::defaultRadius().x * k,
									  rose::defaultRadius().y * k);
	rose_->position() = eps::math::vec2(size.x / 2, size.y / 2);

	if (!rose_->initialize(size))
	{
		return false;
	}

	passes_.construct(size);
	//
	return true;
}

void renderer::render(float dt)
{
	passes_.process(dt);
	//
	rose_->draw(dt);
	arrow_->draw(dt);
}

void renderer::set_rotation(float omega)
{
	arrow_->rotate(omega);
}

}
}
