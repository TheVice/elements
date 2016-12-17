import os
import re
import sys
import xml.etree.ElementTree as ET
from xml.dom import minidom
from effect_generator import read_program, extend_program_info


class Control(dict):

    control_number = 1

    def __init__(self, *args):

        dict.__init__(dict(), *args)

        self['position_x'] = str(10)
        self['position_y'] = str(20)
        self['size_w'] = str(75)
        self['size_h'] = str(75)
        self['visible'] = 'true'
        self['control_name'] = 'control_name_{}'.format(Control.control_number)

        Control.control_number += 1


class Button(Control):

    def __init__(self, *args):

        Control.__init__(self, *args)

        self['asset_path'] = 'assets/ui/textures/settings.png'
        self['control_name'] = self['control_name'].replace('control_name_', 'button_')


class Check(Button):

    def __init__(self, *args):

        Button.__init__(self, *args)

        self['asset_path'] = 'assets/ui/textures/light.png'
        self['control_name'] = self['control_name'].replace('button_', 'check_')


class Label(Control):

    def __init__(self, *args):

        Control.__init__(self, *args)

        self['font_path'] = 'assets/ui/fonts/OpenSans-Regular.ttf'
        self['font_height'] = str(18)
        self['text'] = 'This is label'
        self['color_r'] = str(0.0)
        self['color_g'] = str(0.65)
        self['color_b'] = str(0.95)
        self['color_a'] = str(1.0)
        # self['alignment_haling'] = 'RESERVED'
        # self['alignment_valign'] = 'RESERVED'

        if 'size_w' in self:

            del self['size_w']

        if 'size_h' in self:

            del self['size_h']

        self['control_name'] = self['control_name'].replace('control_name_', 'label_')


class Panel(Control):

    def __init__(self, *args):

        Control.__init__(self, *args)

        self['color_r'] = str(0.8)
        self['color_g'] = str(0.8)
        self['color_b'] = str(0.8)
        self['color_a'] = str(0.5)
        self['visible'] = 'false'
        self['control_name'] = self['control_name'].replace('control_name_', 'panel_')


class Slider(Control):

    id = 0

    def __init__(self, *args):

        Control.__init__(self, *args)

        self['color_slider_r'] = str(0.8)
        self['color_slider_g'] = str(0.8)
        self['color_slider_b'] = str(0.8)
        self['color_slider_a'] = str(1.0)
        self['color_tracker_r'] = str(0.0)
        self['color_tracker_g'] = str(0.65)
        self['color_tracker_b'] = str(0.95)
        self['color_tracker_a'] = str(1.0)
        self['id'] = str(Slider.id)
        self['min'] = str(-1.0)
        self['max'] = str(1.0)
        self['control_name'] = self['control_name'].replace('control_name_', 'slider_')

        Slider.id += 1


class Checkbox(Control):

    def __init__(self, *args):

        Control.__init__(self, *args)

        self['state'] = 'Unchecked'
        self['control_name'] = self['control_name'].replace('control_name_', 'checkbox_')


def get_member_count(a_type):

    types = {
        'bool': 1,
        'float': 1,
        #
        'eps::math::vec2': 2,
        'eps::math::vec3': 3,
        'eps::math::vec4': 4,
        #
        'eps::math::mat2': 4 - 2,
        'eps::math::mat3': 9 - 3,
        'eps::math::mat4': 16 - 4
    }

    if a_type not in types.keys():

        raise ValueError('Unknown type passed {}.'.format(a_type))

    return types[a_type]


def generate_controls_by_type(a_type):

    controls = []
    for i in range(0, get_member_count(a_type)):

        if a_type == 'bool':

            controls.append(ET.Element('check', Check()))

        else:

            controls.append(ET.Element('slider', Slider()))
            Control.control_number -= 1
            controls.append(ET.Element('label', Label()))

    return controls


def process_controls(a_controls, a_cs, a_name):

    panel = a_controls

    if len(a_cs) > 1:

        button = ET.Element('button', Button())
        button.attrib['control_name'] = '{}_{}'.format(a_name, button.attrib['control_name'])
        a_controls.append(button)

        panel = ET.Element('panel', Panel())
        panel.attrib['control_name'] = '{}_{}'.format(a_name, panel.attrib['control_name'])
        a_controls.append(panel)

    for control in a_cs:

        control.attrib['control_name'] = '{}_{}'.format(a_name, control.attrib['control_name'])
        panel.append(control)

    if len(a_cs) > 1:

        label = ET.Element('label', Label())
        label.attrib['control_name'] = '{}_{}'.format(a_name, label.attrib['control_name'])
        panel.append(label)


def generate_ui_xml(a_program, a_vertex_count):

    settings_node = ET.Element('settings', {'name': a_program['name']})
    controls = ET.Element('controls')

    restore_button = ET.Element('button', Button())
    restore_button.attrib['asset_path'] = 'assets/ui/textures/restore.png'
    restore_button.attrib['control_name'] = 'restore_button'
    controls.append(restore_button)

    for location in a_program['u_locations']:

        uniform_type = location[2]

        if uniform_type == 'std::string':

            continue

        cs = generate_controls_by_type(uniform_type)
        process_controls(controls, cs, location[0])

    for i in range(0, a_vertex_count):

        cs = list()
        for location in a_program['a_locations']:

            attribute_type = location[2]
            cs.extend(generate_controls_by_type(attribute_type))

        process_controls(controls, cs, 'vertex_{}'.format(i))

    settings_node.append(controls)
    return settings_node


def to_pretty_xml(a_element):

    tree = ET.tostring(a_element, encoding='utf-8', method='xml')
    doc = minidom.parseString(tree)
    tree = doc.toprettyxml(encoding='utf-8', indent='  ')

    return tree


def to_xml_file(a_element, a_file_name):

    tree = ET.ElementTree(a_element)
    tree.write(a_file_name, encoding='utf-8', method='xml', xml_declaration=True)


def to_file(a_file_content, a_file_name):

    opened_file = open(a_file_name, 'wb')
    opened_file.write(a_file_content)
    opened_file.close()


def fill_controls_def(a_ui_xml, a_controls, a_parent):

    for control in a_ui_xml:

        if 'control_name' in control.attrib:

            control_def = ''

            if control.tag in ['panel', 'button', 'check', 'label']:

                if len(a_parent) > 0:

                    control_def = '#define {}\t\t\t"{}/{}"'.format(control.attrib['control_name'].upper(),
                                                                   a_parent,
                                                                   control.attrib['control_name'])

                else:

                    control_def = '#define {}\t\t\t"{}"'.format(control.attrib['control_name'].upper(),
                                                                control.attrib['control_name'])

            elif control.tag == 'slider':

                control_def = '#define {}\t\t\t{}'.format(control.attrib['control_name'].upper(),
                                                          control.attrib['id'])

            if control_def is not '' and control_def not in a_controls[control.tag]:

                a_controls[control.tag].append(control_def)

            fill_controls_def(control, a_controls, control.attrib['control_name'])

        else:

            fill_controls_def(control, a_controls, '')


def generate_controls_h(a_program, a_ui_xml):

    controls_h_template = (
        '#ifndef _{7}_CONTROLS_H_{0}'
        '#define _{7}_CONTROLS_H_{0}'
        '{0}'
        '{1}'                           # button
        '{0}'
        '{0}'
        '{2}'                           # check
        '{0}'
        '{0}'
        '{3}'                           # panel
        '{0}'
        '{0}'
        '{4}'                           # slider
        '{0}'
        '{0}'
        '{5}'                           # slide_count
        '{0}'
        '{0}'
        '{6}'                           # label
        '{0}'
        '{0}'
        '#endif{0}'
    )

    controls = dict()
    controls['button'] = list()
    controls['check'] = list()
    controls['panel'] = list()
    controls['slider'] = list()
    controls['label'] = list()

    fill_controls_def(a_ui_xml, controls, '')
    slider_count = '#define SLIDER_MODEL_COUNT\t\t\t{}'.format(len(controls['slider']))

    return controls_h_template.format(os.linesep,
                                      os.linesep.join(controls['button']),
                                      os.linesep.join(controls['check']),
                                      os.linesep.join(controls['panel']),
                                      os.linesep.join(controls['slider']),
                                      slider_count,
                                      os.linesep.join(controls['label']),
                                      a_program['head_name']), controls


def generate_custom_ui_h(a_program):

    custom_ui_h_template = (
        '#ifndef _{4}_UI_H_{0}'
        '#define _{4}_UI_H_{0}'
        '{0}'
        '#include "{5}Vertex.h"{0}'
        '#include <UiAsset.h>{0}'
        '#include <vector>{0}'
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        'class {5}Ui : public Library::UiAsset{0}'
        '{{{0}'
        '{1}RTTI_DECLARATIONS({5}Ui, UiAsset){0}'
        '{0}'
        'public:{0}'
        '{1}{5}Ui(Library::Game& aGame, const std::string& aAssetPath);{0}'
        '{1}~{5}Ui();{0}'
        '{0}'
        'public:{0}'
        '{1}{5}Ui() = delete;{0}'
        '{1}{5}Ui(const {5}Ui& aRhs) = delete;{0}'
        '{1}{5}Ui& operator = (const {5}Ui& aRhs) = delete;{0}'
        '{0}'
        'public:{0}'
        '{1}virtual bool Initialize() override;{0}'
        '{1}virtual void Update() override;{0}'
        '{0}'
        'public:{0}'
        '{2}'
        '{0}'
        '{1}void SetVertices(const std::vector<{5}Vertex>& aVertices);{0}'
        '{1}const std::vector<{5}Vertex>& GetVertices() const;{0}'
        '{0}'
        '{1}bool IsNeedRestore() const;{0}'
        '{0}'
        'private:{0}'
        '{1}virtual float& GetValueBySliderId(int aSliderId) override;{0}'
        '{0}'
        'private:{0}'
        '{1}bool mIsRestoreNeed;{0}'
        '{3}'
        '{1}std::vector<{5}Vertex> mVertices;{0}'
        '}};{0}'
        '}}{0}'
        '{0}'
        '#endif{0}'
    )

    uniform_method_template = (
        '{1}void Set_{2}(const {3}& a_{2});{0}'
        '{1}const {3}& Get_{2}() const;{0}'
    )

    uniform_variable_template = (
        '{1}{3} m_{2};{0}'
    )

    uniform_method = []
    uniform_variable = []

    for location in a_program['u_locations']:

        uniform_type = location[2]

        if uniform_type == 'std::string':

            continue

        um = uniform_method_template.format(os.linesep, '\t', location[0], uniform_type)

        if uniform_type == 'bool':

            um = um.replace('&', '')
            um = um.replace('const ', '')
            um = '//{}'.format(um)  # check component do not support direct set of state

        uniform_method.append(um)
        uniform_variable.append(uniform_variable_template.format(os.linesep, '\t', location[0], uniform_type))

    return custom_ui_h_template.format(os.linesep, '\t', os.linesep.join(uniform_method), ''.join(uniform_variable),
                                       a_program['head_name'], a_program['class_name'])


def get_control_from_define(a_define):

    pattern = '#define[ ,\t]*\w+[ ,\t]*'
    match = re.search(pattern, a_define)

    if match is None:

        raise ValueError('Unable to find control at given define {}.'.format(a_define))

    control = match.group(0)
    control = control.replace('#define', '')
    control = control.replace('\t', '')
    control = control.replace(' ', '')

    return control


def get_uniform_list(a_type):

    types = {
        'bool': [''],
        'float': [''],
        #
        'eps::math::vec4': [
            '[0]', '[1]', '[2]', '[3]'
        ],
        'eps::math::vec3': [
            '[0]', '[1]', '[2]'
        ],
        'eps::math::vec2': [
            '[0]', '[1]'
        ],
        #
        'eps::math::mat4': [
            '[0][0]', '[0][1]', '[0][2]',
            '[1][0]', '[1][1]', '[1][2]',
            '[2][0]', '[2][1]', '[2][2]',
            '[3][0]', '[3][1]', '[3][2]'
        ],
        'eps::math::mat3': [
            '[0][0]', '[0][1]',
            '[1][0]', '[1][1]',
            '[2][0]', '[2][1]'
        ],
        'eps::math::mat2': [
            '[0][0]',
            '[1][0]'
        ]
    }

    if a_type not in types.keys():

        raise ValueError('Unknown type passed {}.'.format(a_type))

    return types[a_type]


def get_def_label(a_variable, a_controls, a_control_type):

    labels = []

    for control in a_controls[1][a_control_type]:

        try:

            control = get_control_from_define(control)

        except ValueError:

            continue

        if control.find(a_variable.upper()) is not -1:

            labels.append(control)

    return labels


def get_uniform_with_corresponding_defines(a_program, a_controls, a_define):

    uniforms = dict()

    for location in a_program['u_locations']:

        uniform_type = location[2]

        if uniform_type == 'std::string':

            continue

        uniform_list = get_uniform_list(uniform_type)
        slider_define = get_def_label(location[0], a_controls, a_define)

        uniforms[location[0]] = list()

        for i in zip(uniform_list, slider_define):

            uniforms[location[0]].append(('m_{}{}'.format(location[0], i[0]), i[1]))

    return uniforms


def get_vertices_with_corresponding_defines(a_program, a_controls, a_vertex_count, a_define):

    vertices = []
    vertex_members = ['x', 'y', 'z', 'w']

    for i in range(0, a_vertex_count):

        labels = get_def_label('VERTEX_{}'.format(i), a_controls, a_define)
        label_number = 0

        for location in a_program['a_locations']:

                attribute_type = location[2]
                member_count = get_member_count(attribute_type)

                if member_count > len(vertex_members):

                    raise ValueError('Incorrect member count {}.'.format(member_count))

                required_label_number = label_number + member_count - 1

                if required_label_number > len(labels):

                    raise ValueError('Incorrect label count {}. Must be at least {}.'.format(len(labels),
                                                                                             required_label_number))

                for j in range(0, member_count):

                    vertex = 'mVertices[{}].{}.{}'.format(i, location[0], vertex_members[j])
                    define = labels[label_number + j]

                    vertices.append((vertex, define))

                label_number = required_label_number + 1

    return vertices


def generate_custom_ui_cpp_constructor(a_program, a_vertex_count):

    constructor_template = (
        '{4}Ui::{4}Ui(Library::Game& aGame, const std::string& aAssetPath) :{0}'
        '{1}UiAsset(aGame, aAssetPath),{0}'
        '{1}mIsRestoreNeed(true),{0}'
        '{2},'          # uniform_variable
        '{0}'
        'mVertices({0}'
        '{{{0}'
        '{3}'           # vertex
        '{0}'
        '}}){0}'
        '{{{0}'
        '}}{0}'
    )

    uniform_variable = []

    for location in a_program['u_locations']:

        uniform_type = location[2]

        if uniform_type == 'std::string':

            continue

        uniform_variable.append('\tm_{}()'.format(location[0]))

    vertex_structure = []

    for i in range(0, a_vertex_count):

        vertex_structure.append('\t{0}Vertex()'.format(a_program['class_name']))

    return constructor_template.format(os.linesep, '\t',
                                       ',{}'.format(os.linesep).join(uniform_variable),
                                       ',{}'.format(os.linesep).join(vertex_structure),
                                       a_program['class_name'])


def generate_custom_ui_cpp_initialize(a_program, a_controls):

    initialize_template = (
        'bool {4}Ui::Initialize(){0}'
        '{{{0}'
        '{1}if (!UiAsset::Initialize()){0}'
        '{1}{{{0}'
        '{1}{1}return false;{0}'
        '{1}}}{0}'
        '{0}'
        '{2}'          # is_exist_control
        '{1}IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT){0}'
        '{0}'
        '{3}'          # set_button_click
        '{0}'
        '{0}'
        '{1}return true;{0}'
        '}}{0}'
    )

    button_template = (
        '{1}if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[{2}].lock())){0}'
        '{1}{{{0}'
        '{1}{1}directButton->set_click([this](eps::ui::state){0}'
        '{1}{1}{{{0}'
        '{1}{1}{1}// TODO:{0}'
        '{1}{1}}});{0}'
        '{1}}}'
    )

    is_exist_control = []
    set_button_click = []
    is_button = True
    is_check = True

    for controls in [a_controls[1]['button'], a_controls[1]['check'], a_controls[1]['panel'], a_controls[1]['label']]:

        for control in controls:

            control = get_control_from_define(control)
            is_exist_control.append('\tIS_CONTROL_EXIST({}){}'.format(control, os.linesep))

            if is_button or is_check:

                set_button_click.append(button_template.format(os.linesep, '\t', control))

        if is_button is False:

            is_check = False

        is_button = False
        is_exist_control.append('{}{}{}'.format('\t', '//', os.linesep))

    return initialize_template.format(os.linesep, '\t',
                                      ''.join(is_exist_control),
                                      '{0}{0}'.format(os.linesep).join(set_button_click),
                                      a_program['class_name'])


def generate_custom_ui_cpp_update(a_program, a_controls, a_vertex_count):

    update_template = (
        'void {4}Ui::Update(){0}'
        '{{{0}'
        '{1}UiAsset::Update();{0}'
        '{1}//{0}'
        '{2}'           # uniform_variable
        '{1}//{0}'
        '{3}'           # vertices_variable
        '}}{0}'
    )

    uniforms = get_uniform_with_corresponding_defines(a_program, a_controls, 'label')
    uniform_variable = []

    for location in a_program['u_locations']:

        if location[0] in uniforms:

            for uniform in uniforms[location[0]]:

                uniform_variable.append('\tDISPLAY_FLOAT_VALUE_AT_LABEL({}, {}){}'.format(uniform[0], uniform[1], os.linesep))

    vertices = get_vertices_with_corresponding_defines(a_program, a_controls, a_vertex_count, 'label')
    vertices_variable = []

    for vertex in vertices:

        vertices_variable.append('\tDISPLAY_FLOAT_VALUE_AT_LABEL({}, {}){}'.format(vertex[0], vertex[1], os.linesep))

    return update_template.format(os.linesep, '\t', ''.join(uniform_variable),
                                  ''.join(vertices_variable), a_program['class_name'])


def generate_custom_ui_cpp_uniform_methods(a_program, a_controls):

    uniform_method_template = (
        'void {5}Ui::Set_{2}(const {3}& a_{2}){0}'
        '{{{0}'
        '{1}m_{2} = a_{2};{0}'
        '{1}//{0}'
        '{4}'
        '{1}//{0}'
        '{1}mIsRestoreNeed = false;{0}'
        '}}{0}'
        '{0}'
        'const {3}& {5}Ui::Get_{2}() const{0}'
        '{{{0}'
        '{1}return m_{2};{0}'
        '}}{0}'
    )

    uniforms = get_uniform_with_corresponding_defines(a_program, a_controls, 'slider')
    methods = []

    for location in a_program['u_locations']:

        if location[0] in uniforms:

            uniform_type = location[2]
            uniform_variable = []

            for uniform in uniforms[location[0]]:

                uniform_variable.append('\tSET_REAL_VALUE_AT_SLIDER({}, {}){}'.format(uniform[0],
                                                                                      uniform[1],
                                                                                      os.linesep))

            um = uniform_method_template.format(os.linesep, '\t', location[0], uniform_type,
                                                ''.join(uniform_variable), a_program['class_name'])

            if uniform_type == 'bool':

                um = um.replace('&', '')
                um = um.replace('const ', '')
                um = '/*{}'.format(um)  # check component do not support direct set of state
                pos = um.find('{}Ui::Get_'.format(a_program['class_name'])) - len('bool ') - 2 * len(os.linesep)
                new_um = '{}*/{}'.format(um[:pos], um[pos:])
                um = new_um

            methods.append(um)

    return os.linesep.join(methods)


def generate_custom_ui_cpp_vertex_methods(a_program, a_controls, a_vertex_count):

    vertex_method_template = (
        'void {3}Ui::SetVertices(const std::vector<{3}Vertex>& aVertices){0}'
        '{{{0}'
        '{1}mVertices = aVertices;{0}'
        '{1}//{0}'
        '{2}'
        '{1}//{0}'
        '{1}mIsRestoreNeed = false;{0}'
        '}}{0}'
        '{0}'
        'const std::vector<{3}Vertex>& {3}Ui::GetVertices() const{0}'
        '{{{0}'
        '{1}return mVertices;{0}'
        '}}{0}'
    )

    vertices = get_vertices_with_corresponding_defines(a_program, a_controls, a_vertex_count, 'slider')
    vertices_variable = []

    for vertex in vertices:

        vertices_variable.append('{}SET_REAL_VALUE_AT_SLIDER({}, {}){}'.format('\t', vertex[0], vertex[1], os.linesep))

    return vertex_method_template.format(os.linesep, '\t', ''.join(vertices_variable), a_program['class_name'])


def generate_custom_ui_cpp_get_slider_model(a_program, a_controls, a_vertex_count):

    get_slider_model_template = (
        'float& {3}Ui::GetValueBySliderId(int aSliderId){0}'
        '{{{0}'
        '{1}switch (aSliderId){0}'
        '{1}{{{0}'
        '{2}'
        '{0}'
        '{1}{1}default:{0}'
        '{1}{1}{1}assert(false);{0}'
        '{1}}}{0}'
        '{0}'
        '{1}static float modelValue = 0.0f;{0}'
        '{1}return modelValue;{0}'
        '}}{0}'
    )

    uniforms = get_uniform_with_corresponding_defines(a_program, a_controls, 'slider')
    vertices = get_vertices_with_corresponding_defines(a_program, a_controls, a_vertex_count, 'slider')
    case_template = (
        '{1}{1}case {2}:{0}'
        '{1}{1}{1}return {3};{0}'
    )
    model_switch = []

    for location in a_program['u_locations']:

        if location[0] in uniforms:

            for uniform in uniforms[location[0]]:

                case = case_template.format(os.linesep, '\t', uniform[1], uniform[0])
                model_switch.append(case)

    for vertex in vertices:

        case = case_template.format(os.linesep, '\t', vertex[1], vertex[0])
        model_switch.append(case)

    return get_slider_model_template.format(os.linesep, '\t', os.linesep.join(model_switch), a_program['class_name'])


def generate_custom_ui_cpp(a_program, a_controls, a_vertex_count):

    custom_ui_cpp_template = (
        '#include "{8}Ui.h"{0}'
        '#include "{8}Controls.h"{0}'
        '#include <checkbox.h>{0}'
        '#include <SliderModel.h>{0}'
        '#include <elements/ui/controls/button.h>{0}'
        '#include <elements/ui/controls/check.h>{0}'
        '#include <elements/ui/controls/label.h>{0}'
        '#include <elements/ui/controls/panel.h>{0}'
        '#include <elements/ui/controls/slider.h>{0}'
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        'RTTI_DEFINITIONS({8}Ui){0}'
        '{0}'
        '{2}'                                   # constructor
        '{0}'
        '{8}Ui::~{8}Ui(){0}'
        '{{{0}'
        '}}{0}'
        '{0}'
        '{3}'                                   # initialize
        '{0}'
        '{4}'                                   # update
        '{0}'
        '{5}'                                   # uniform_methods
        '{0}'
        '{6}'                                   # vertex_methods
        '{0}'
        'bool {8}Ui::IsNeedRestore() const{0}'
        '{{{0}'
        'return mIsRestoreNeed;{0}'
        '}}{0}'
        '{0}'
        '{7}'                                   # get_slider_model
        '{0}'
        '}}{0}'
    )

    return custom_ui_cpp_template.format(os.linesep, '\t',
                                         generate_custom_ui_cpp_constructor(a_program, a_vertex_count),
                                         generate_custom_ui_cpp_initialize(a_program, a_controls),
                                         generate_custom_ui_cpp_update(a_program, a_controls, a_vertex_count),
                                         generate_custom_ui_cpp_uniform_methods(a_program, a_controls),
                                         generate_custom_ui_cpp_vertex_methods(a_program, a_controls, a_vertex_count),
                                         generate_custom_ui_cpp_get_slider_model(a_program, a_controls, a_vertex_count),
                                         a_program['class_name'])


if __name__ == '__main__':

    if len(sys.argv) < 2:

        print('Using: {} <shader file>'.format(sys.argv[0]))

    else:

        vertex_count = 4

        shader_program = read_program(sys.argv[1])
        shader_program = extend_program_info(shader_program)
        ui_xml = generate_ui_xml(shader_program, vertex_count)
        controls_h = generate_controls_h(shader_program, ui_xml)
        custom_ui_h = generate_custom_ui_h(shader_program)
        custom_ui_cpp = generate_custom_ui_cpp(shader_program, controls_h, vertex_count)

        print('--------------------------------------------------------------------')
        print(to_pretty_xml(ui_xml).decode('utf-8'))
        # to_xml_file(ui_xml, 'ui.xml')
        # to_file(to_pretty_xml(ui_xml), 'ui.xml')
        print('--------------------------------------------------------------------')
        print(controls_h[0])
        print('--------------------------------------------------------------------')
        print(custom_ui_h)
        print('--------------------------------------------------------------------')
        print(custom_ui_cpp)
        print('--------------------------------------------------------------------')
