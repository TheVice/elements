#ifndef _VELOCITIES_PROCESS_VERTEX_H_
#define _VELOCITIES_PROCESS_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct VelocitiesProcessVertex
{
	eps::math::vec2 a_field_uv;
	eps::math::vec2 a_field_data;

	VelocitiesProcessVertex() :
		a_field_uv(),
		a_field_data()
	{
	}

	VelocitiesProcessVertex(
		const eps::math::vec2& argument_a_field_uv,
		const eps::math::vec2& argument_a_field_data) :
		a_field_uv(argument_a_field_uv),
		a_field_data(argument_a_field_data)
	{
	}
};
}

#endif

