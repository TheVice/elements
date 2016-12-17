import os
import re
import sys
import xml.etree.ElementTree as ET
from effect_generator import read_program, extend_program_info
from ui_generator import to_pretty_xml


class ElementText(ET.Element):

    def __init__(self, *args, text=None):

        ET.Element.__init__(self, *args)
        if text:
            self.text = text


class ElementMatrix(ET.Element):

    def __init__(self, *args, level=None):

        ET.Element.__init__(self, *args)
        if level == 2:
            self.append(ET.Element('r0', {'x': '1.0', 'y': '0.0'}))
            self.append(ET.Element('r1', {'x': '0.0', 'y': '1.0'}))
        elif level == 3:
            self.append(ET.Element('r0', {'x': '1.0', 'y': '0.0', 'z': '0.0'}))
            self.append(ET.Element('r1', {'x': '0.0', 'y': '1.0', 'z': '0.0'}))
            self.append(ET.Element('r2', {'x': '0.0', 'y': '0.0', 'z': '1.0'}))
        elif level == 4:
            self.append(ET.Element('r0', {'x': '1.0', 'y': '0.0', 'z': '0.0', 'w': '0.0'}))
            self.append(ET.Element('r1', {'x': '0.0', 'y': '1.0', 'z': '0.0', 'w': '0.0'}))
            self.append(ET.Element('r2', {'x': '0.0', 'y': '0.0', 'z': '1.0', 'w': '0.0'}))
            self.append(ET.Element('r3', {'x': '0.0', 'y': '0.0', 'z': '0.0', 'w': '1.0'}))


def type_to_xlm_element(a_type, a_name):

    types = {
        'bool': ElementText(a_name, text='true'),
        'float': ElementText(a_name, text='0.0'),
        #
        'eps::math::vec2': ET.Element(a_name, {'x': '0.0', 'y': '0.0'}),
        'eps::math::vec3': ET.Element(a_name, {'x': '0.0', 'y': '0.0', 'z': '0.0'}),
        'eps::math::vec4': ET.Element(a_name, {'x': '0.0', 'y': '0.0', 'z': '0.0', 'w': '0.0'}),
        #
        'eps::math::mat2': ElementMatrix(a_name, level=2),
        'eps::math::mat3': ElementMatrix(a_name, level=3),
        'eps::math::mat4': ElementMatrix(a_name, level=4),
        #
        'std::string': ElementText(a_name, text='This is a std::string')
    }

    if a_type not in types.keys():
        raise ValueError('Convert failed. Unknown type passed {}.'.format(a_type))

    return types[a_type]


def type_to_clean_state(a_type, a_name):

    types = {
        'bool': '{} = true;'.format(a_name),
        'float': '{} = 0.0f;'.format(a_name),
        #
        'eps::math::vec2': '{} = eps::math::vec2();'.format(a_name),
        'eps::math::vec3': '{} = eps::math::vec3();'.format(a_name),
        'eps::math::vec4': '{} = eps::math::vec4();'.format(a_name),
        #
        'eps::math::mat2': '{} = eps::math::mat2();'.format(a_name),
        'eps::math::mat3': '{} = eps::math::mat3();'.format(a_name),
        'eps::math::mat4': '{} = eps::math::mat4();'.format(a_name),
        #
        'std::string': '{}.clear();'.format(a_name)
    }

    if a_type not in types.keys():
        raise ValueError('Convert failed. Unknown type passed {}.'.format(a_type))

    return types[a_type]


def type_to_read(a_type):

    types = {
        'bool': 'Library::ReaderHelpers::read_bool',
        'float': 'Library::ReaderHelpers::read_float',
        #
        'eps::math::vec2': 'Library::ReaderHelpers::read_glm_vec',
        'eps::math::vec3': 'Library::ReaderHelpers::read_glm_vec',
        'eps::math::vec4': 'Library::ReaderHelpers::read_glm_vec',
        #
        'eps::math::mat2': 'Library::ReaderHelpers::read_glm_mat',
        'eps::math::mat3': 'Library::ReaderHelpers::read_glm_mat',
        'eps::math::mat4': 'Library::ReaderHelpers::read_glm_mat',
        #
        'std::string': 'Library::ReaderHelpers::read_std_string'
    }

    if a_type not in types.keys():
        raise ValueError('Convert failed. Unknown type passed {}.'.format(a_type))

    return types[a_type]


def generate_settings_xml(a_program, a_vertex_count):

    settings_node = ET.Element('settings', {'name': a_program['name']})
    vertices_node = ET.Element('vertices')

    for i in range(0, a_vertex_count):

        vertex_node = ET.Element('vertex')

        for location in a_program['a_locations']:

            sub_vertex_node = type_to_xlm_element(location[2], location[0])
            vertex_node.append(sub_vertex_node)

        vertices_node.append(vertex_node)

    settings_node.append(vertices_node)
    indices_node = ET.Element('indices')

    if a_vertex_count == 4:

        for i in [0, 1, 2, 2, 3, 0]:

            index_node = ElementText('index', text=str(i))
            indices_node.append(index_node)

    else:

        index_node = ElementText('index', text=str(-1))
        indices_node.append(index_node)

    settings_node.append(indices_node)

    for location in a_program['u_locations']:

        u_node = type_to_xlm_element(location[2], location[0])
        settings_node.append(u_node)

    return settings_node


def generate_settings_h(a_program):

    settings_h_template = (
        '#ifndef _{1}_SETTINGS_H_{0}'
        '#define _{1}_SETTINGS_H_{0}'
        '{0}'
        '#include "{2}Vertex.h"{0}'
        '#include <elements/math/types.h>{0}'
        '#include <elements/assets/asset_xml.h>{0}'
        '#include <vector>{0}'
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        'struct {2}Settings : public eps::asset_xml{0}'
        '{{{0}'
        'public:{0}'
        '{3}std::vector<{2}Vertex> mVertices;{0}'
        '{3}std::vector<unsigned char> mIndices;{0}'
        '{0}'
        '{4}'                                                                       # uniform_variables
        '{0}'
        '{0}'
        '{3}bool mIsEmpty;{0}'
        '{0}'
        'public:{0}'
        '{3}using eps::asset_xml::asset_xml;{0}'
        '{0}'
        'private:{0}'
        '{3}bool read(const pugi::xml_document& doc) final;{0}'
        '}};{0}'
        '}}{0}'
        '{0}'
        '#endif{0}'
    )

    uniform_variables = []

    for location in a_program['u_locations']:

        uniform_variable = '\t{} {};'.format(location[2], location[0])
        uniform_variables.append(uniform_variable)

    uniform_variables = ('{}'.format(os.linesep)).join(uniform_variables)

    return settings_h_template.format(os.linesep, a_program['head_name'], a_program['class_name'],
                                      '\t', uniform_variables)


def generate_settings_cpp(a_program):

    settings_cpp_template = (
        '{0}'
        '#include "{1}Settings.h"{0}'
        '#include <elements/assets/assets_storage.h>{0}'
        '#include <ReaderHelpers.h>{0}'
        '#include <cstring>{0}'
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        '{0}'
        '#define CLEAR(){2}\\{0}'
        '{2}mVertices.clear();{2}\\{0}'
        '{2}mIndices.clear();{2}\\{0}'
        '{2}\\{0}'
        '{3}{0}'                                                                    # clean_uniform_variables
        '{2}\\{0}'
        '{2}mIsEmpty = true;{0}'
        '{0}'
        'bool {1}Settings::read(const pugi::xml_document& doc){0}'
        '{{{0}'
        '{2}CLEAR(){0}'
        '{2}const auto settings_node = doc.child("settings");{0}'
        '{0}'
        '{2}if (settings_node.empty()){0}'
        '{2}{{{0}'
        '{2}{2}return !mIsEmpty;{0}'
        '{2}}}{0}'
        '{0}'
        '{2}const auto vertices_node = settings_node.child("vertices");{0}'
        '{0}'
        '{2}if (vertices_node.empty()){0}'
        '{2}{{{0}'
        '{2}{2}return !mIsEmpty;{0}'
        '{2}}}{0}'
        '{0}'
        '{2}const auto indices_node = settings_node.child("indices");{0}'
        '{0}'
        '{2}if (indices_node.empty()){0}'
        '{2}{{{0}'
        '{2}{2}return !mIsEmpty;{0}'
        '{2}}}{0}'
        '{0}'
        '{4}'                                                                       # node_uniform_variables
        '{0}'
        '{0}'
        '{2}for (const auto& subNode : vertices_node){0}'
        '{2}{{{0}'
        '{2}{2}if (std::strcmp(subNode.name(), "vertex")){0}'
        '{2}{2}{{{0}'
        '{2}{2}{2}continue;{0}'
        '{2}{2}}}{0}'
        '{0}'
        '{5}'                                                                       # node_attribute_variables
        '{0}'
        '{0}'
        '{6}'                                                                       # read_vertex_data
        '{0}'
        '{0}'
        '{2}{2}const auto vertex = {1}Vertex({7});{0}'                              # vertex_parameters
        '{2}{2}mVertices.push_back(vertex);{0}'
        '{2}}}{0}'
        '{0}'
        '{2}if (mVertices.empty()){0}'
        '{2}{{{0}'
        '{2}{2}return !mIsEmpty;{0}'
        '{2}}}{0}'
        '{0}'
        '{2}if (!Library::ReaderHelpers::read_indices(indices_node, mIndices)){0}'
        '{2}{{{0}'
        '{2}{2}return !mIsEmpty;{0}'
        '{2}}}{0}'
        '{0}'
        '{8}'                                                                       # read_vertex_data
        '{0}'
        '{0}'
        '{2}mIsEmpty = false;{0}'
        '{2}return !mIsEmpty;{0}'
        '}}{0}'
        '{0}'
        '}}{0}'
    )

    node_template = (
        '{1}const auto {2}_node = settings_node.child("{2}");{0}'
        '{0}'
        '{1}if ({2}_node.empty()){0}'
        '{1}{{{0}'
        '{1}{1}return !mIsEmpty;{0}'
        '{1}}}'
    )

    read_data_template = (
        '{1}auto {3}{0}'
        '{0}'
        '{1}if (!{4}({2}_node, {2})){0}'
        '{1}{{{0}'
        '{1}{1}return !mIsEmpty;{0}'
        '{1}}}'
    )

    clean_uniform_variables = []
    node_uniform_variables = []
    read_uniform_variables = []

    for location in a_program['u_locations']:

        clean_uniform_variable = '\t{}\t\\'.format(type_to_clean_state(location[2], location[0]))
        clean_uniform_variables.append(clean_uniform_variable)

        node_uniform_variable = node_template.format(os.linesep, '\t', location[0])
        node_uniform_variables.append(node_uniform_variable)

        read_data = read_data_template.format(os.linesep, '\t', location[0],
                                              type_to_clean_state(location[2], location[0]), type_to_read(location[2]))
        pos = read_data.find(os.linesep) + len(os.linesep)
        pos = read_data.find(os.linesep, pos) + len(os.linesep)
        read_data = read_data[pos:]
        read_uniform_variables.append(read_data)

    clean_uniform_variables = os.linesep.join(clean_uniform_variables)
    node_uniform_variables = ('{0}{0}'.format(os.linesep)).join(node_uniform_variables)
    read_uniform_variables = ('{0}{0}'.format(os.linesep)).join(read_uniform_variables)

    node_attribute_variables = []
    read_vertex_data = []
    vertex_parameters = []

    for location in a_program['a_locations']:

        node_attribute_variable = node_template.format(os.linesep, '\t', location[0])
        node_attribute_variable = node_attribute_variable.replace('_node = settings_node.child(',
                                                                  '_node = subNode.child(')
        node_attribute_variable = node_attribute_variable.replace(os.linesep, '{}\t'.format(os.linesep))
        node_attribute_variable = '\t{}'.format(node_attribute_variable)
        node_attribute_variable = node_attribute_variable.replace('{0}\t{0}'.format(os.linesep),
                                                                  '{0}{0}'.format(os.linesep))
        node_attribute_variables.append(node_attribute_variable)

        read_data = read_data_template.format(os.linesep, '\t', location[0],
                                              type_to_clean_state(location[2], location[0]), type_to_read(location[2]))
        read_data = read_data.replace(os.linesep, '{}\t'.format(os.linesep))
        read_data = '\t{}'.format(read_data)
        read_data = read_data.replace('{0}\t{0}'.format(os.linesep),
                                      '{0}{0}'.format(os.linesep))
        read_vertex_data.append(read_data)

        vertex_parameters.append(location[0])

    node_attribute_variables = ('{0}{0}'.format(os.linesep)).join(node_attribute_variables)
    read_vertex_data = ('{0}{0}'.format(os.linesep)).join(read_vertex_data)
    vertex_parameters = ', '.join(vertex_parameters)

    return settings_cpp_template.format(os.linesep, a_program['class_name'], '\t',
                                        clean_uniform_variables, node_uniform_variables,
                                        node_attribute_variables, read_vertex_data, vertex_parameters,
                                        read_uniform_variables)


if __name__ == '__main__':

    if len(sys.argv) < 2:

        print('Using: {} <shader file>'.format(sys.argv[0]))

    else:

        vertex_count = 4

        shader_program = read_program(sys.argv[1])
        shader_program = extend_program_info(shader_program)
        settings_xml = generate_settings_xml(shader_program, vertex_count)
        settings_h = generate_settings_h(shader_program)
        settings_cpp = generate_settings_cpp(shader_program)

        print('--------------------------------------------------------------------')
        print(to_pretty_xml(settings_xml).decode('utf-8'))
        print('--------------------------------------------------------------------')
        print('--------------------------------------------------------------------')
        print(settings_h)
        print('--------------------------------------------------------------------')
        print(settings_cpp)
        print('--------------------------------------------------------------------')
