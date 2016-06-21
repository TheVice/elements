/*
The MIT License (MIT)
Copyright (c) 2016 Alexey Yegorov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#include "renderer.h"

#include "pass_velocities.h"
#include "pass_positions.h"
#include "pass_particles.h"

#include <elements/rendering/effects/clear.h>

namespace eps {
namespace experiment {
namespace air {

bool renderer::initialize()
{
    using namespace rendering;

    // TODO: from xml + register user types

    passes_.initialize(4);

    auto link_clear = passes_.add_pass<effect::clear>();
    if(link_clear.expired())
        return false;

    link_velocities_ = passes_.add_pass<pass_velocities>();
    if(link_velocities_.expired())
        return false;

    link_positions_ = passes_.add_pass<pass_positions>();
    if(link_positions_.expired())
        return false;

    link_particles_ = passes_.add_pass<pass_particles>();
    if(link_particles_.expired())
        return false;

    passes_.add_dependency(link_positions_, link_velocities_, pass_input_slot::input_0);
    passes_.add_dependency(link_particles_, link_positions_, pass_input_slot::input_0);
    passes_.add_dependency(link_particles_, link_velocities_, pass_input_slot::input_1);

    link_clear.lock()->set_color(math::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    return true;
}

void renderer::set_field(sync::future<math::vec2> field)
{
    if(auto link = link_velocities_.lock())
        link->set_field(std::move(field));
}

bool renderer::construct(const math::uvec2 & size, size_t particles_count)
{
    if(particles_count_ != particles_count ||
       size_ != size)
   {
       particles_count_ = particles_count;
       size_ = size;

       if(auto link = link_positions_.lock())
           link->set_count(particles_count);
       if(auto link = link_particles_.lock())
           link->set_count(particles_count);

       passes_.construct(size);
       return true;
   }
   return false;
}

void renderer::render(float dt)
{
    passes_.process(dt);
}

void renderer::set_colors(const math::vec3 & speed_down,
                          const math::vec3 & speed_up)
{
    if(auto link = link_particles_.lock())
        link->set_colors(speed_down, speed_up);
}

} /* air */
} /* experiments */
} /* eps */
