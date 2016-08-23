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

                if element.tag not in program:

                    program[element.tag] = list()

                program[element.tag].append(read_location(location))

        else:

            print('Unknown element {}. Ignoring.'.format(element.tag))

    return program


def get_class_name(a_program):

    class_name = a_program['name'].lower()
    class_name = '{}{}'.format(class_name[0].upper(), class_name[1:])
    return class_name


def generate_effect_h(a_program):

    head_template = (
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
    )

    head_name = a_program['name'].upper()
    class_name = get_class_name(a_program)

    head = head_template.format(head_name, os.linesep, '\t', class_name)

    uniform_declaration = ''

    for location in a_program['u_locations']:

        declaration = '{}SHADER_VARIABLE_DECLARATION({}){}'.format('\t', location[0], os.linesep)
        uniform_declaration = '{}{}'.format(uniform_declaration, declaration)

    body_template = (
        '{0}'
        'public:{0}'
        '{1}{2}Effect();{0}'
        '{0}'
        'public:{0}'
        '{1}{2}Effect(const {2}Effect& aRhs) = delete;{0}'
        '{1}{2}Effect& operator = (const {2}Effect& aRhs) = delete;{0}'
        '{0}'
        'public:{0}'
        '{1}virtual GLvoid Initialize(GLuint aVertexArrayObject) override;{0}'
        '{1}virtual GLuint GetVertexSize() const override;{0}'
        '{0}'
    )

    body = body_template.format(os.linesep, '\t', class_name)

    attribute_enumeration = ''

    for location in a_program['a_locations']:

        enumeration = '{0}{0}{1}_location = {2},{3}'.format('\t', location[0], location[1], os.linesep)
        attribute_enumeration = '{}{}'.format(attribute_enumeration, enumeration)

    attribute_template = (
        'private:{0}'
        '{1}enum VertexAttribute{0}'
        '{1}{{{0}'
        '{2}{0}'
        '{1}}};'
    )

    if len(attribute_enumeration) > 0:

        pos = attribute_enumeration.rfind(',')
        attribute_enumeration = attribute_enumeration[:pos]

        attribute_enumeration = attribute_template.format(os.linesep, '\t', attribute_enumeration)

    footer_template = (
        '{0}'
        '}};{0}'
        '}}{0}'
        '{0}'
        '#endif{0}'
        '{0}'
    )

    footer = footer_template.format(os.linesep)

    full_document = '{}{}{}{}{}'.format(head, uniform_declaration, body, attribute_enumeration, footer)

    return full_document


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

    head_template = (
        '{0}'
        '#include "{1}Effect.h"{0}'
        '#include "VertexStructure.h"{0}'
        '{0}'
        'namespace Library{0}'
        '{{{0}'
        'RTTI_DEFINITIONS({1}Effect)'
    )

    class_name = get_class_name(a_program)

    head = head_template.format(os.linesep, class_name)
    uniform_definition = ''

    for location in a_program['u_locations']:

        definition = 'SHADER_VARIABLE_DEFINITION({}Effect, {}){}'.format(class_name, location[0], os.linesep)
        uniform_definition = '{}{}'.format(uniform_definition, definition)

    constructor_template = (
        '{0}Effect::{0}Effect() :{1}'
        '{2}ShaderProgram(){3}{1}'
        '{{{1}'
        '}}'
    )

    uniform_initialization = ''

    for location in a_program['u_locations']:

        initialization = '{}SHADER_VARIABLE_INITIALIZATION({}),{}'.format('\t', location[0], os.linesep)
        uniform_initialization = '{}{}'.format(uniform_initialization, initialization)

    if len(uniform_initialization) > 1:

        pos = uniform_initialization.rfind(',')
        uniform_initialization = uniform_initialization[:pos]
        uniform_initialization = '{}{}{}'.format(',', os.linesep, uniform_initialization)

    constructor = constructor_template.format(class_name, os.linesep, '\t', uniform_initialization)

    initialize_method_template = (
        'GLvoid {0}Effect::Initialize(GLuint aVertexArrayObject){1}'
        '{{{1}'
        '{2}ShaderProgram::Initialize(aVertexArrayObject);{1}'
        '{2}//{1}'
        '{3}'   # uniform_instantiate
        '{2}//{1}'
        '{4}'   # attribute_location
        '{2}//{1}'
        '{5}'   # attribute_pointer
        '}}'
    )

    uniform_instantiate = ''

    for location in a_program['u_locations']:

        instantiate = '{}SHADER_VARIABLE_INSTANTIATE({}){}'.format('\t', location[0], os.linesep)
        uniform_instantiate = '{}{}'.format(uniform_instantiate, instantiate)

    location_template_get_attrib = '{0}const GLint vertexAttribute_{1} = GetAttrib("{1}");{2}'
    location_template = '{0}const GLint vertexAttribute_{1} = {1}_location;{2}'

    attribute_location_get_attrib = ''
    attribute_location = ''

    for location in a_program['a_locations']:

        a_location = location_template_get_attrib.format('\t', location[0], os.linesep)
        attribute_location_get_attrib = '{}{}'.format(attribute_location_get_attrib, a_location)

        a_location = location_template.format('\t', location[0], os.linesep)
        attribute_location = '{}{}'.format(attribute_location, a_location)

    attribute_location = '#ifdef GET_ATTRIB{0}{1}#else{0}{2}#endif{0}'.format(os.linesep,
                                                                              attribute_location_get_attrib,
                                                                              attribute_location)

    attribute_pointer = ''

    for location in a_program['a_locations']:

        attribute_type = get_attribute_type(location[0], a_program['vertex'])
        attribute_length = get_type_length(attribute_type)
        l = '{0}glVertexAttribPointer(vertexAttribute_{1}, {2}, GL_FLOAT, GL_FALSE,{3}'.format('\t',
                                                                                               location[0],
                                                                                               attribute_length,
                                                                                               os.linesep)
        l = '{0}{1}{1}GetVertexSize(),{2}'.format(l, '\t', os.linesep)
        l = '{0}{1}{1}reinterpret_cast<GLvoid*>(offsetof(VertexStructure, {2})));{3}'.format(l,
                                                                                             '\t',
                                                                                             location[0],
                                                                                             os.linesep)
        l = '{0}{1}glEnableVertexAttribArray(vertexAttribute_{2});{3}'.format(l, '\t', location[0], os.linesep)

        attribute_pointer = '{}{}{}//{}'.format(attribute_pointer, l, '\t', os.linesep)

    if len(attribute_pointer) > 0:

        pos = attribute_pointer.rfind('\t')
        attribute_pointer = attribute_pointer[:pos]

    initialize = initialize_method_template.format(class_name,
                                                   os.linesep, '\t',
                                                   uniform_instantiate,
                                                   attribute_location,
                                                   attribute_pointer)

    vertex_size_template = (
        'GLuint {1}Effect::GetVertexSize() const{2}'
        '{{{2}'
        '{0}return sizeof(VertexStructure);{2}'
        '}}'
    )

    vertex_size = vertex_size_template.format('\t', class_name, os.linesep)

    return '{0}{1}{1}{2}{1}{3}{1}{1}{4}{1}{1}{5}{1}{1}}}{1}'.format(head, os.linesep,
                                                                    uniform_definition,
                                                                    constructor,
                                                                    initialize,
                                                                    vertex_size)


def generate_vertex_structure(a_program):

    vertex_structure_template = (
        '#ifndef _VERTEX_STRUCTURE_H_{0}'
        '#define _VERTEX_STRUCTURE_H_{0}'
        '{0}'
        '#include <glm/glm.hpp>{0}'
        '{0}'
        'struct VertexStructure{0}'
        '{{'
        '{1}{0}'   # structure_member
        '{0}'
        '{2}VertexStructure() :{0}'
        '{3}'      # initialize list, default constructor
        '{2}{{'
        '{0}'
        '{2}}}'
        '{0}'
        '{0}'
        '{2}VertexStructure({4}) :{0}'
        '{5}'      # initialize list, parameters constructor
        '{2}{{'
        '{0}'
        '{2}}}'
        '{0}'
        '}};{0}'
        '{0}'
        '#endif{0}'
        '{0}'
    )

    structure_member = ''
    initialize_list = ''
    argument_list = ''
    argument_list_2nd = ''

    for location in a_program['a_locations']:

        attribute_type = get_attribute_type(location[0], a_program['vertex'])
        structure_member = '{}{}{}{} {};'.format(structure_member, os.linesep, '\t', attribute_type, location[0])
        initialize_list = '{}{}{}(),{}'.format(initialize_list, '\t\t', location[0], os.linesep)
        argument_list = '{}{}{}const {}& argument_{},'.format(argument_list, os.linesep, '\t\t\t',
                                                              attribute_type, location[0])
        argument_list_2nd = '{}{}{}(argument_{}),{}'.format(argument_list_2nd, '\t\t', location[0],
                                                            location[0], os.linesep)

    if len(initialize_list) > 0:

        pos = initialize_list.rfind(',')
        initialize_list = initialize_list[:pos]
        initialize_list = '{}{}'.format(initialize_list, os.linesep)

    if len(argument_list) > 0:

        pos = argument_list.rfind(',')
        argument_list = argument_list[:pos]

    if len(argument_list_2nd) > 0:

        pos = argument_list_2nd.rfind(',')
        argument_list_2nd = argument_list_2nd[:pos]
        argument_list_2nd = '{}{}'.format(argument_list_2nd, os.linesep)

    return vertex_structure_template.format(os.linesep, structure_member,
                                            '\t', initialize_list,
                                            argument_list, argument_list_2nd)


if __name__ == '__main__':

    if len(sys.argv) < 2:

        print('Using: {} <prog file>'.format(sys.argv[0]))

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
