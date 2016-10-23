
#include "compass_renderer.h"
#include "logging.h"

#include <elements/timing/update.h>
#include <elements/metrics/metrics.h>

compass_renderer::compass_renderer()
	: renderer_(nullptr)
	, ui_(nullptr)
	, rate_(60)
	, label_fps_()
{
}

bool compass_renderer::startup(const eps::math::uvec2 & size)
{
	if (!renderer_)
	{
		eps::utils::unique<Rendering::Compass::renderer> local;
		local.reset(new Rendering::Compass::renderer());

		if (!local->initialize())
		{
			LOGE("[Compass] initialize error\n");
			return false;
		}

		renderer_.reset(local.release());
	}

	if (renderer_->construct(size))
	{
		ui_.reset(new eps::ui::system());
		ui_->construct(size);
		//
		/*return */create_diagnostic_ui(size);
	}

	return true;
}

void compass_renderer::render()
{
	if (renderer_)
	{
		renderer_->render(1.0f / 60.0f);

		if (ui_)
		{
			if (auto label = label_fps_.lock())
			{
				char text[16];
				sprintf(text, "FPS: %.2f", rate_.fps());
				label->set_text(text);
			}

			ui_->draw();
		}

	}

	eps::timing::update_and_sleep(rate_);
}

void compass_renderer::set_rotation(float omega)
{
	if (renderer_)
	{
		renderer_->set_rotation(omega);
	}
}

bool compass_renderer::create_diagnostic_ui(const eps::math::uvec2 &)
{
	if (ui_)
	{
		using namespace eps::metric_literals;
		//
		label_fps_ = ui_->add<eps::ui::label>();

		if (auto label = label_fps_.lock())
		{
			label->set_size(128_dp, 18_dp);
			label->set_position(8_dp, 58_dp);
			label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
			label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		}

		return true;
	}

	return false;
}
