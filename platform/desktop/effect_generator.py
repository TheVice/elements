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

    program = {}

    for e in ['a_locations', 'u_locations']:
        program[e] = list()

    tree = ET.parse(a_path_2_xml_shader)
    root = tree.getroot()

    if root.tag != 'program':

        raise ValueError('Root elements is not a program at {}.'.format(a_path_2_xml_shader))

    if 'name' not in root.attrib:

        raise ValueError('No name in attribute at program at {}.'.format(a_path_2_xml_shader))

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

    return program


def get_class_name(a_program):

    class_name = a_program['name'].lower()
    class_name = '{}{}'.format(class_name[0].upper(), class_name[1:])
    return class_name


def generate_effect_h(a_program):

    effect_h_template = (
        '#ifndef _{0}_EFFECT_H_{1}'
        '#define _{0}_EFFECT_H_{1}'
        '{1}'
        '#include "ShaderProgram.h"{1}'
        '{1}'
        'namespace Library{1}'
        '{{{1}'
        'class {3}Effect : public ShaderProgram{1}'
        '{{{1}'
        '{2}RTTI_DECLARATIONS({3}Effect, ShaderProgram){1}'
        '{1}'
        '{2}{4}{1}'     # uniform_declaration
        '{1}'
        'public:{1}'
        '{2}{3}Effect();{1}'
        '{1}'
        'public:{1}'
        '{2}{3}Effect(const {3}Effect& aRhs) = delete;{1}'
        '{2}{3}Effect& operator = (const {3}Effect& aRhs) = delete;{1}'
        '{1}'
        'public:{1}'
        '{2}virtual GLvoid Initialize(GLuint aVertexArrayObject) override;{1}'
        '{2}virtual GLuint GetVertexSize() const override;{1}'
        '}};{1}'
        '}}{1}'
        '{1}'
        '#endif{1}'
        '{1}'
    )

    head_name = a_program['name'].upper()
    class_name = get_class_name(a_program)

    uniform_declaration = []

    for location in a_program['u_locations']:

        uniform_declaration.append('SHADER_VARIABLE_DECLARATION({})'.format(location[0], os.linesep))

    uniform_declaration = '{}{}'.format(os.linesep, '\t').join(uniform_declaration)

    return effect_h_template.format(head_name, os.linesep, '\t', class_name, uniform_declaration)


def convert_type_from_glsl_to_cpp(a_type):

    types = {
        'vec2': 'glm::vec2',
        'vec3': 'glm::vec3'
    }

    if a_type not in types.keys():

        raise ValueError('Unknown type passed {}.'.format(a_type))

    return types[a_type]


def get_type_length(a_type):

    types = {
        'glm::vec2': 'glm::vec2().length()',
        'glm::vec3': 'glm::vec3().length()'
    }

    if a_type not in types.keys():

        raise ValueError('Unknown type passed {}.'.format(a_type))

    return types[a_type]


def get_attribute_type(a_attribute, a_vertex):

    pattern_template = 'attribute[ ,\t]*\w+[ ,\t]*{}'
    pattern = pattern_template.format(a_attribute)
    match = re.search(pattern, a_vertex)

    if not match:

        ValueError('Can not find attribute {} at vertex {}'.format(a_attribute, a_vertex))

    attribute_type = match.group(0)
    pos = attribute_type.find('attribute')
    pos += len('attribute')
    attribute_type = attribute_type[pos:]
    attribute_type = attribute_type.replace(a_attribute, '')
    attribute_type = attribute_type.replace(' ', '')
    attribute_type = attribute_type.replace('\t', '')
    attribute_type = convert_type_from_glsl_to_cpp(attribute_type)

    return attribute_type


def generate_effect_cpp(a_program):

    effect_cpp_template = (
        '{0}'
        '#include "{1}Effect.h"{0}'
        '#include "VertexStructure.h"{0}'
        '{0}'
        'namespace Library{0}'
        '{{{0}'
        'RTTI_DEFINITIONS({1}Effect){0}'
        '{0}'
        '{2}{0}'        # uniform_definition
        '{0}'
        '{1}Effect::{1}Effect() :{0}'
        '{3}ShaderProgram(),{0}'
        '{3}{4}'        # uniform_initialization
        '{0}'
        '{{{0}'
        '}}{0}'
        '{0}'
        'GLvoid {1}Effect::Initialize(GLuint aVertexArrayObject){0}'
        '{{{0}'
        '{3}ShaderProgram::Initialize(aVertexArrayObject);{0}'
        '{3}//{0}'
        '{3}{5}{0}'     # uniform_instantiate
        '{3}//{0}'
        '{3}{6}{0}'     # attribute_location
        '{3}//{0}'
        '{7}'           # attribute_pointer
        '}}{0}'
        '{0}'
        'GLuint {1}Effect::GetVertexSize() const{0}'
        '{{{0}'
        '{3}return sizeof(VertexStructure);{0}'
        '}}{0}'
        '{0}'
        '}}{0}'
    )

    attribute_pointer_template = (
        '{0}glVertexAttribPointer(vertexAttribute_{1}, {2}, GL_FLOAT, GL_FALSE,{3}'
        '{0}{0}GetVertexSize(),{3}'
        '{0}{0}reinterpret_cast<GLvoid*>(offsetof(VertexStructure, {1})));{3}'
        '{0}glEnableVertexAttribArray(vertexAttribute_{1});{3}'
    )

    class_name = get_class_name(a_program)

    uniform_definition = []
    uniform_initialization = []
    uniform_instantiate = []
    attribute_location = []
    attribute_pointer = []

    for location in a_program['u_locations']:

        uniform_definition.append('SHADER_VARIABLE_DEFINITION({}Effect, {})'.format(class_name, location[0]))
        uniform_initialization.append('SHADER_VARIABLE_INITIALIZATION({})'.format(location[0]))
        uniform_instantiate.append('SHADER_VARIABLE_INSTANTIATE({})'.format(location[0]))

    uniform_definition = '{}'.format(os.linesep).join(uniform_definition)
    uniform_initialization = '{}{}{}'.format(',', os.linesep, '\t').join(uniform_initialization)
    uniform_instantiate = '{}{}'.format(os.linesep, '\t').join(uniform_instantiate)

    for location in a_program['a_locations']:

        a_location = 'const GLint vertexAttribute_{0} = GetAttrib("{0}");'.format(location[0])
        attribute_location.append(a_location)

        attribute_type = get_attribute_type(location[0], a_program['vertex'])
        attribute_length = get_type_length(attribute_type)

        attribute_pointer.append(attribute_pointer_template.format('\t', location[0], attribute_length, os.linesep))

    attribute_location = '{}{}'.format(os.linesep, '\t').join(attribute_location)
    attribute_pointer = '{}//{}'.format('\t', os.linesep).join(attribute_pointer)

    return effect_cpp_template.format(os.linesep, class_name, uniform_definition,
                                      '\t', uniform_initialization, uniform_instantiate,
                                      attribute_location, attribute_pointer)


def generate_vertex_structure(a_program):

    vertex_structure_template = (
        '#ifndef _VERTEX_STRUCTURE_H_{0}'
        '#define _VERTEX_STRUCTURE_H_{0}'
        '{0}'
        '#include <glm/glm.hpp>{0}'
        '{0}'
        'struct VertexStructure{0}'
        '{{'
        '{0}'
        '{2}{1}{0}'     # structure_member
        '{0}'
        '{2}VertexStructure() :{0}'
        '{2}{2}{3}'     # initialize list, default constructor
        '{0}'
        '{2}{{'
        '{0}'
        '{2}}}'
        '{0}'
        '{0}'
        '{2}VertexStructure({0}{2}{2}{4}) :{0}'
        '{2}{2}{5}'     # initialize list, parameters constructor
        '{0}'
        '{2}{{'
        '{0}'
        '{2}}}'
        '{0}'
        '}};{0}'
        '{0}'
        '#endif{0}'
        '{0}'
    )

    structure_member = []
    initialize_list = []
    argument_list = []
    initialize_list_2nd = []

    for location in a_program['a_locations']:

        attribute_type = get_attribute_type(location[0], a_program['vertex'])

        structure_member.append('{} {};'.format(attribute_type, location[0]))
        initialize_list.append('{}()'.format(location[0]))
        argument_list.append('const {}& argument_{}'.format(attribute_type, location[0]))
        initialize_list_2nd.append('{0}(argument_{0})'.format(location[0]))

    structure_member = '{}{}'.format(os.linesep, '\t').join(structure_member)
    initialize_list = '{}{}{}'.format(',', os.linesep, '\t\t').join(initialize_list)
    argument_list = '{}{}{}'.format(',', os.linesep, '\t\t').join(argument_list)
    initialize_list_2nd = '{}{}{}'.format(',', os.linesep, '\t\t').join(initialize_list_2nd)

    return vertex_structure_template.format(os.linesep, structure_member,
                                            '\t', initialize_list,
                                            argument_list, initialize_list_2nd)


if __name__ == '__main__':

    if len(sys.argv) < 2:

        print('Using: {} <shader file>'.format(sys.argv[0]))

    else:

        shader_program = read_program(sys.argv[1])
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
