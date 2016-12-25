import os
import re
import sys
import xml.etree.ElementTree as ET


def read_location(a_location):

    if 'name' not in a_location.attrib:

        raise ValueError('No name in attribute at location {}.'.format(a_location))

    if 'index' not in a_location.attrib:

        raise ValueError('No index in attribute at location {}.'.format(a_location))

    return a_location.attrib['name'], a_location.attrib['index']


def read_program(a_path_2_xml_shader):

    tree = ET.parse(a_path_2_xml_shader)
    root = tree.getroot()

    if root.tag != 'program':

        raise ValueError('Root elements is not a program at {}.'.format(a_path_2_xml_shader))

    if 'name' not in root.attrib:

        raise ValueError('No name in attribute at program at {}.'.format(a_path_2_xml_shader))

    program = dict()
    program['a_locations'] = list()
    program['u_locations'] = list()
    program['name'] = root.attrib['name']

    for element in root:

        if element.tag == 'shaders':

            for shader in element:

                if shader.tag in ['vertex', 'fragment']:

                    program[shader.tag] = shader.text

                else:

                    print('Unknown shader type {}. Ignoring.'.format(shader.tag))

        elif element.tag in ['a_locations', 'u_locations']:

            for location in element:

                program[element.tag].append(read_location(location))

        else:

            print('Unknown element {}. Ignoring.'.format(element.tag))

    if 'vertex' not in program:

        raise ValueError('No vertex section at program at {}.'.format(a_path_2_xml_shader))

    if 'fragment' not in program:

        raise ValueError('No fragment section at program at {}.'.format(a_path_2_xml_shader))

    path_to_shader = a_path_2_xml_shader.replace(os.path.sep, '/')

    if 'assets/' in path_to_shader:

        path_to_shader = path_to_shader[path_to_shader.find('assets/'):]

    program['path_to_shader'] = path_to_shader

    return program


def get_head_name(a_program):

    head_name = a_program['name'].upper()
    return head_name


def get_class_name(a_program):

    class_name = a_program['name'].lower()
    tmp_class_name = []

    already_assigned = False

    for i in range(0, len(class_name) - 1):

        if '_' == class_name[i]:

            tmp_class_name.append(class_name[i + 1].upper())
            already_assigned = True

        elif already_assigned:

            already_assigned = False

        else:

            tmp_class_name.append(class_name[i])

    if tmp_class_name:

        tmp_class_name[0] = tmp_class_name[0].upper()
        tmp_class_name.append(class_name[len(class_name) - 1])
        class_name = ''.join(tmp_class_name)

    return class_name


def convert_type_from_glsl_to_cpp(a_type):

    types = {
        'bool': 'bool',
        'float': 'float',
        #
        'vec2': 'eps::math::vec2',
        'vec3': 'eps::math::vec3',
        'vec4': 'eps::math::vec4',
        #
        'mat2': 'eps::math::mat2',
        'mat3': 'eps::math::mat3',
        'mat4': 'eps::math::mat4',
        #
        'sampler2D': 'std::string'
    }

    if a_type not in types.keys():

        raise ValueError('Convert failed. Unknown type passed {}.'.format(a_type))

    return types[a_type]


def get_type_length(a_type):

    types = {
        'eps::math::vec2': 'eps::math::vec2().length()',
        'eps::math::vec3': 'eps::math::vec3().length()',
        'eps::math::vec4': 'eps::math::vec4().length()'
    }

    if a_type not in types.keys():

        raise ValueError('Can not get length. Unknown type passed {}.'.format(a_type))

    return types[a_type]


def get_variable_type(a_declaration, a_variable, a_source):

    pattern_template = '{}[ ,\t]*\w+[ ,\t]*{}'
    pattern = pattern_template.format(a_declaration, a_variable)
    match = re.search(pattern, a_source)

    if match is None:

        return ''

    variable_type = match.group(0)

    pos = variable_type.find(a_declaration)
    pos += len(a_declaration)

    variable_type = variable_type[pos:]
    variable_type = variable_type.replace(a_variable, '')
    variable_type = variable_type.replace(' ', '')
    variable_type = variable_type.replace('\t', '')
    variable_type = convert_type_from_glsl_to_cpp(variable_type)

    return variable_type


def get_attribute_type(a_attribute, a_vertex):

    for declaration in ['attribute', 'in']:

        attribute_type = get_variable_type(declaration, a_attribute, a_vertex)

        if attribute_type is not '':

            return attribute_type

    raise ValueError('Can not find attribute {} at vertex {}'.format(a_attribute, a_vertex))


def get_uniform_type(a_uniform, a_vertex, a_fragment):

    for declaration in ['uniform', 'uniform lowp', 'uniform mediump', 'uniform highp']:

        uniform_type = get_variable_type(declaration, a_uniform, a_vertex)

        if uniform_type is not '':

            return uniform_type

        else:

            uniform_type = get_variable_type(declaration, a_uniform, a_fragment)

            if uniform_type is not '':

                return uniform_type

    raise ValueError('Can not find uniform {} at vertex {} or at fragment {}'.format(a_uniform, a_vertex, a_fragment))


def extend_program_info(a_program):

    a_program['head_name'] = get_head_name(a_program)
    a_program['class_name'] = get_class_name(a_program)

    for i in range(0, len(a_program['a_locations'])):

        attribute = a_program['a_locations'][i][0]
        attribute_type = get_attribute_type(attribute, a_program['vertex'])
        type_length = get_type_length(attribute_type)
        a_program['a_locations'][i] += (attribute_type, type_length)

    for i in range(0, len(a_program['u_locations'])):

        uniform = a_program['u_locations'][i][0]
        uniform_type = get_uniform_type(uniform, a_program['vertex'], a_program['fragment'])
        a_program['u_locations'][i] += (uniform_type, )

    path_to_settings = a_program['path_to_shader'].replace('shaders', 'settings')
    path_to_settings = path_to_settings.replace('.prog', '.xml')
    path_to_source = path_to_settings.replace('.xml', '')

    if 'settings/' in path_to_source:

        path_to_source = path_to_source[path_to_source.find('settings/'):]
        path_to_source = path_to_source[path_to_source.find('settings/') + len('settings/'):]

    settings_file = path_to_settings

    if '/' in settings_file:

        settings_file = settings_file[settings_file.rfind('/') + len('/'):]

    a_program['path_to_settings'] = path_to_settings
    a_program['path_to_source'] = path_to_source
    a_program['settings_file'] = settings_file

    return a_program


def generate_position_argument(a_locations):

    count = len(a_locations)

    if count < 2:

        return 'short a_position'

    return 'const std::array<short, {}>& a_position'.format(count)


def generate_effect_h(a_program):

    effect_h_template = (
        '#ifndef _{0}_EFFECT_H_{1}'
        '#define _{0}_EFFECT_H_{1}'
        '{1}'
        '#include "{2}Vertex.h"{1}'
        '#include <elements/rendering/core/buffer.h>{1}'
        '#include <vector>{1}'
        '#include <array>{1}'
        '{1}'
        'namespace eps{1}'
        '{{{1}'
        'namespace rendering{1}'
        '{{{1}'
        'class program;{1}'
        '}}{1}'
        '}}{1}'
        '{1}'
        'namespace Rendering{1}'
        '{{{1}'
        'class {2}Effect{1}'
        '{{{1}'
        'public:{1}'
        '{3}explicit {2}Effect(const std::vector<{2}Vertex>& vertices,{1}'
        '{3}{3}{3}const std::vector<GLubyte>& indices,{1}'
        '{3}{3}{3}eps::rendering::buffer_usage usage = eps::rendering::buffer_usage::STATIC_DRAW);{1}'
        '{1}'
        '{3}void construct(const std::vector<{2}Vertex>& vertices);{1}'
        '{4}'
        '{1}'
        'private:{1}'
        '{3}eps::rendering::vertices texture_vertices_;{1}'
        '{3}eps::rendering::indices texture_indices_;{1}'
        '}};{1}'
        '}}{1}'
        '{1}'
        '#endif{1}'
        '{1}'
    )

    render_method = (
        '{}void render(eps::rendering::program& program, {}, short index_count);{}'
    )
    render_method = render_method.format('\t', generate_position_argument(a_program['a_locations']), os.linesep)

    if len(a_program['a_locations']) == 1:

        effect_h_template = effect_h_template.replace('#include <array>', '')

    return effect_h_template.format(a_program['head_name'], os.linesep, a_program['class_name'], '\t', render_method)


def generate_effect_cpp(a_program):

    effect_cpp_template = (
        '{0}'
        '#include "{1}Effect.h"{0}'
        '#include <elements/rendering/core/program.h>{0}'
        '#include <elements/rendering/state/state_macro.h>{0}'
        '#include <cassert>{0}'
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        '{0}'
        '{1}Effect::{1}Effect(const std::vector<{1}Vertex>& vertices,{0}'
        '{2}{2}{2}const std::vector<GLubyte>& indices,{0}'
        '{2}{2}{2}eps::rendering::buffer_usage usage){0}'
        '{2}: texture_vertices_(usage){0}'
        '{2}, texture_indices_(usage){0}'
        '{{{0}'
        '{2}assert(!vertices.empty());{0}'
        '{2}assert(!indices.empty());{0}'
        '{2}// Create the vertex buffer object{0}'
        '{2}texture_vertices_.allocate(&vertices.front(), vertices.size(), sizeof(vertices.front()));{0}'
        '{2}// Create the index buffer object{0}'
        '{2}texture_indices_.allocate(&indices.front(), indices.size(), sizeof(indices.front()));{0}'
        '}}{0}'
        '{0}'
        'void {1}Effect::construct(const std::vector<{1}Vertex>& vertices){0}'
        '{{{0}'
        '{2}assert(!vertices.empty());{0}'
        '{2}// Update vertex buffer object{0}'
        '{2}texture_vertices_.allocate(&vertices.front(), vertices.size(), sizeof(vertices.front()));{0}'
        '}}{0}'
        '{0}'
        '{3}'
        '{{{0}'
        '{2}EPS_STATE_VERTICES(texture_vertices_.get_product());{0}'
        '{2}EPS_STATE_INDICES(texture_indices_.get_product());{0}'
        '{2}//{0}'
        '{4}'
        '{2}//{0}'
        '{2}glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_BYTE, 0);{0}'
        '}}{0}'
        '{0}'
        '}}{0}'
        '{0}'
    )

    render_method = (
        'void {}Effect::render(eps::rendering::program& program, {}, short index_count){}'
    )

    render_method = render_method.format(a_program['class_name'],
                                         generate_position_argument(a_program['a_locations']),
                                         os.linesep)

    attributes = []
    attribute_array = (
        '{0}program.attribute_array({1}, offsetof({5}Vertex, {2}), {3}, sizeof({5}Vertex));{4}'
        '{0}program.attribute_array_enable({1});{4}'
    )

    if len(a_program['a_locations']) < 2:

        for location in a_program['a_locations']:
            attributes.append(attribute_array.format('\t', 'a_position',
                                                     location[0], location[3], os.linesep,
                                                     a_program['class_name']))

    else:

        i = 0
        for location in a_program['a_locations']:

            attributes.append(attribute_array.format('\t', 'std::get<{}>(a_position)'.format(i),
                                                     location[0], location[3], os.linesep,
                                                     a_program['class_name']))
            i += 1

    return effect_cpp_template.format(os.linesep, a_program['class_name'], '\t', render_method, ''.join(attributes))


def generate_vertex_structure(a_program):

    vertex_structure_template = (
        '#ifndef _{6}_VERTEX_H_{0}'
        '#define _{6}_VERTEX_H_{0}'
        '{0}'
        '#include <elements/math/types.h>{0}'
        '{0}'
        'namespace Rendering'
        '{0}'
        '{{'
        '{0}'
        'struct {7}Vertex{0}'
        '{{'
        '{0}'
        '{2}{1}{0}'     # structure_member
        '{0}'
        '{2}{7}Vertex() :{0}'
        '{2}{2}{3}'     # initialize list, default constructor
        '{0}'
        '{2}{{'
        '{0}'
        '{2}}}'
        '{0}'
        '{0}'
        '{2}{7}Vertex({0}{2}{2}{4}) :{0}'
        '{2}{2}{5}'     # initialize list, parameters constructor
        '{0}'
        '{2}{{'
        '{0}'
        '{2}}}'
        '{0}'
        '}};{0}'
        '}}'
        '{0}'
        '{0}'
        '#endif{0}'
        '{0}'
    )

    structure_member = []
    initialize_list = []
    argument_list = []
    initialize_list_2nd = []

    for location in a_program['a_locations']:

        structure_member.append('{} {};'.format(location[2], location[0]))
        initialize_list.append('{}()'.format(location[0]))
        argument_list.append('const {}& argument_{}'.format(location[2], location[0]))
        initialize_list_2nd.append('{0}(argument_{0})'.format(location[0]))

    structure_member = '{}{}'.format(os.linesep, '\t').join(structure_member)
    initialize_list = '{}{}{}'.format(',', os.linesep, '\t\t').join(initialize_list)
    argument_list = '{}{}{}'.format(',', os.linesep, '\t\t').join(argument_list)
    initialize_list_2nd = '{}{}{}'.format(',', os.linesep, '\t\t').join(initialize_list_2nd)

    return vertex_structure_template.format(os.linesep, structure_member,
                                            '\t', initialize_list,
                                            argument_list, initialize_list_2nd,
                                            a_program['head_name'], a_program['class_name'])


if __name__ == '__main__':

    if len(sys.argv) < 2:

        print('Using: {} <shader file>'.format(sys.argv[0]))

    else:

        shader_program = read_program(sys.argv[1])
        shader_program = extend_program_info(shader_program)
        effect_h = generate_effect_h(shader_program)
        effect_cpp = generate_effect_cpp(shader_program)
        vertex_structure = generate_vertex_structure(shader_program)

        print('--------------------------------------------------------------------')
        print(effect_h)
        print('--------------------------------------------------------------------')
        print(effect_cpp)
        print('--------------------------------------------------------------------')
        print(vertex_structure)
        print('--------------------------------------------------------------------')
