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

#include "program_loader.h"

#include "rendering/core/shader.h"
#include "rendering/core/program.h"

#include "assets/assets_storage.h"

#include <sstream>

namespace eps {
namespace rendering {

bool program_data::read(const pugi::xml_document & doc)
{
    pugi::xml_node root_node = doc.child("program");
    if(root_node.empty())
        return false;

    pugi::xml_node vertex_node = root_node.child("shaders").child("vertex");
    if(vertex_node.text().empty())
        return false;
    pugi::xml_node fragment_node = root_node.child("shaders").child("fragment");
    if(fragment_node.text().empty())
        return false;

    v_shader_ = vertex_node.text().get();
    f_shader_ = fragment_node.text().get();

    const auto shaders_version = root_node.child("shaders").attribute("version");
    if (!shaders_version.empty())
    {
        const auto shaders_version_str = shaders_version.as_string();

        if (!std::strcmp(shaders_version_str, "300 es"))
        {
            version_ = 300;
        }
        else if (!std::strcmp(shaders_version_str, "310 es"))
        {
            version_ = 310;
        }
    }

    pugi::xml_node a_locations_node = root_node.child("a_locations");
    for(const auto & value : a_locations_node.children("location"))
    {
        attribute_locations_.emplace_back(value.attribute("name").value(),
                                          value.attribute("index").as_int());
    }

    pugi::xml_node u_locations_node = root_node.child("u_locations");
    for(const auto & value : u_locations_node.children("location"))
    {
        uniform_locations_.emplace_back(value.attribute("name").value(),
                                        value.attribute("index").as_int());
    }

    return true;
}

bool load_program(const char * asset_program, program & result)
{
    auto data = assets_storage::instance().read<program_data>(asset_program);
    if(!data)
        return false;

    if(!data.value().v_shader() || !data.value().f_shader())
        return false;

    std::ostringstream vertex_shader_source;
    vertex_shader_source << "#version " << data.value().version() << std::endl;
    vertex_shader_source << data.value().v_shader();

    shader v_shader(vertex_shader_source.str().c_str(), shader_type::VERTEX);
    if(!v_shader.compile())
        return false;

    std::ostringstream fragment_shader_source;
    fragment_shader_source << "#version " << data.value().version() << std::endl;
    fragment_shader_source << data.value().f_shader();

    shader f_shader(fragment_shader_source.str().c_str(), shader_type::FRAGMENT);
    if(!f_shader.compile())
        return false;

    result.attach(v_shader);
    result.attach(f_shader);
    if(!result.link())
        return false;

    for(const auto & location : data.value().a_locations())
        result.attribute_location(location.name, location.index);

    for(const auto & location : data.value().u_locations())
        result.uniform_location(location.name, location.index);

    return true;
}

} /* rendering */
} /* eps */
