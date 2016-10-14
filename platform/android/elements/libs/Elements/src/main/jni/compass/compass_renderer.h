#ifndef _COMPASS_RENDERER_H_
#define _COMPASS_RENDERER_H_

#include <experiments/compass/renderer.h>
#include <elements/ui/system.h>
#include <elements/ui/controls/label.h>
#include <elements/timing/framerate.h>

class compass_renderer
{
public:
	
	explicit compass_renderer();

	bool startup(const eps::math::uvec2 & size);
	void render();

	void set_rotation(float omega);

private:

	bool create_diagnostic_ui(const eps::math::uvec2 & size);

private:

	eps::utils::unique<Rendering::Compass::renderer> renderer_;
	eps::utils::unique<eps::ui::system> ui_;

	eps::timing::framerate rate_;

	eps::utils::link<eps::ui::label> label_fps_;
};

#endif
