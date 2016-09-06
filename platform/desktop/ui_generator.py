import os
import re
import sys
import xml.etree.ElementTree as ET
from xml.dom import minidom
from effect_generator import read_program, get_attribute_type, get_variable_type


class Control(dict):

    control_number = 1

    def __init__(self, *args):

        dict.__init__(dict(), *args)

        self['position_x'] = str(10)
        self['position_y'] = str(20)
        self['size_w'] = str(30)
        self['size_h'] = str(40)
        self['visible'] = 'true'
        self['control_name'] = 'control_name_{}'.format(Control.control_number)

        Control.control_number += 1


class Button(Control):

    def __init__(self, *args):

        Control.__init__(self, *args)

        self['asset_path'] = 'assets/ui/textures/settings.png'
        self['control_name'] = self['control_name'].replace('control_name_', 'button_')


class Label(Control):

    def __init__(self, *args):

        Control.__init__(self, *args)

        self['font_path'] = 'assets/ui/fonts/OpenSans-Regular.ttf'
        self['font_height'] = str(18)
        self['text'] = 'This is label'
        self['color_r'] = str(0.9)
        self['color_g'] = str(0.25)
        self['color_b'] = str(0.2)
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

        self['color_r'] = str(0.9)
        self['color_g'] = str(0.25)
        self['color_b'] = str(0.2)
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
        'glm::mat3': 9 - 3,
        'glm::mat4': 16 - 4,
        #
        'glm::vec2': 2,
        'glm::vec3': 3,
        'glm::vec4': 4
    }

    if a_type not in types.keys():

        raise ValueError('Unknown type passed {}.'.format(a_type))

    return types[a_type]


def generate_controls_by_type(a_type):

    controls = []
    for i in range(0, get_member_count(a_type)):

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

    ui_node = ET.Element('ui', {'name': a_program['name']})
    controls = ET.Element('controls')

    for location in a_program['u_locations']:

        uniform_type = get_variable_type('uniform', location[0], a_program['vertex'])

        if uniform_type == '':

            continue

        cs = generate_controls_by_type(uniform_type)
        process_controls(controls, cs, location[0])

    for i in range(0, a_vertex_count):

        cs = list()
        for location in a_program['a_locations']:

            attribute_type = get_attribute_type(location[0], a_program['vertex'])
            cs.extend(generate_controls_by_type(attribute_type))

        process_controls(controls, cs, 'vertex_{}'.format(i))

    ui_node.append(controls)
    return ui_node


def to_pretty_xml(a_element):

    tree = ET.tostring(a_element, encoding='utf8', method='xml')
    doc = minidom.parseString(tree)
    tree = doc.toprettyxml(encoding='utf8', indent='  ')

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

            if control.tag in ['panel', 'button', 'label']:

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


def generate_controls_h(a_ui_xml):

    controls_h_template = (
        '#ifndef _CONTROLS_H_{0}'
        '#define _CONTROLS_H_{0}'
        '{0}'
        '{1}'
        '{0}'
        '{0}'
        '{2}'
        '{0}'
        '{0}'
        '{3}'
        '{0}'
        '{0}'
        '{4}'
        '{0}'
        '{0}'
        '{5}'
        '{0}'
        '{0}'
        '#endif{0}'
    )

    controls = dict()
    controls['button'] = list()
    controls['panel'] = list()
    controls['slider'] = list()
    controls['label'] = list()

    fill_controls_def(a_ui_xml, controls, '')
    slider_count = '#define SLIDER_MODEL_COUNT\t\t\t{}'.format(len(controls['slider']))

    return controls_h_template.format(os.linesep,
                                      os.linesep.join(controls['button']),
                                      os.linesep.join(controls['panel']),
                                      os.linesep.join(controls['slider']),
                                      slider_count,
                                      os.linesep.join(controls['label'])), controls


def generate_custom_ui_h(a_program):

    custom_ui_h_template = (
        '#ifndef _CUSTOM_UI_H_{0}'
        '#define _CUSTOM_UI_H_{0}'
        '{0}'
        '#include "UiAsset.h"{0}'
        '#include "VertexStructure.h"{0}'
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        'class CustomUi : public Library::UiAsset{0}'
        '{{{0}'
        '{1}RTTI_DECLARATIONS(CustomUi, UiAsset){0}'
        '{0}'
        'public:{0}'
        '{1}CustomUi(Library::Game& aGame, const std::string& aAssetPath);{0}'
        '{1}~CustomUi();{0}'
        '{0}'
        'public:{0}'
        '{1}CustomUi() = delete;{0}'
        '{1}CustomUi(const CustomUi& aRhs) = delete;{0}'
        '{1}CustomUi& operator = (const CustomUi& aRhs) = delete;{0}'
        '{0}'
        'public:{0}'
        '{1}virtual void Initialize() override;{0}'
        '{1}virtual void Update(const Library::GameTime& aGameTime) override;{0}'
        '{0}'
        'public:{0}'
        '{2}'
        '{0}'
        '{1}void SetVertices(const std::vector<VertexStructure>& aVertices);{0}'
        '{1}const std::vector<VertexStructure>& GetVertices() const;{0}'
        '{0}'
        'protected:{0}'
        '{1}virtual Library::SliderModel* GetSliderModel(int aSliderId, float aMin, float aMax) override;{0}'
        '{0}'
        'private:{0}'
        '{3}'
        '{1}std::vector<VertexStructure> mVertices;{0}'
        '{0}'
        '{1}std::vector<Library::SliderModel*> mSliderModels;{0}'
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

        uniform_type = get_variable_type('uniform', location[0], a_program['vertex'])

        if uniform_type == '':

            continue

        uniform_method.append(uniform_method_template.format(os.linesep, '\t', location[0], uniform_type))
        uniform_variable.append(uniform_variable_template.format(os.linesep, '\t', location[0], uniform_type))

    return custom_ui_h_template.format(os.linesep, '\t', os.linesep.join(uniform_method), ''.join(uniform_variable))


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
        'glm::mat4': [
                        '[0][0]', '[0][1]', '[0][2]',
                        '[1][0]', '[1][1]', '[1][2]',
                        '[2][0]', '[2][1]', '[2][2]',
                        '[3][0]', '[3][1]', '[3][2]'
                     ],
        'glm::mat3': [
                        '[0][0]', '[0][1]',
                        '[1][0]', '[1][1]',
                        '[2][0]', '[2][1]'
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

        uniform_type = get_variable_type('uniform', location[0], a_program['vertex'])

        if uniform_type == '':
            continue

        uniform_list = get_uniform_list(uniform_type)
        slider_define = get_def_label(location[0], a_controls, a_define)

        uniforms[location[0]] = list()

        for i in zip(uniform_list, slider_define):

            uniforms[location[0]].append(('m_{}{}'.format(location[0], i[0]), i[1]))

    return uniforms


def get_vertices_with_corresponding_defines(a_program, a_controls, a_vertex_count, a_define):

    vertices = []
    vertex_members = ['x', 'y', 'z']

    for i in range(0, a_vertex_count):

        labels = get_def_label('VERTEX_{}'.format(i), a_controls, a_define)
        label_number = 0

        for location in a_program['a_locations']:

                attribute_type = ''

                try:

                    attribute_type = get_attribute_type(location[0], a_program['vertex'])

                except ValueError:

                    continue

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
        'CustomUi::CustomUi(Library::Game& aGame, const std::string& aAssetPath) :{0}'
        '{1}UiAsset(aGame, aAssetPath),{0}'
        '{2},'          # uniform_variable
        '{0}'
        'mVertices({0}'
        '{{{0}'
        '{3}'           # vertex
        '{0}'
        '}}),{0}'
        'mSliderModels(SLIDER_MODEL_COUNT){0}'
        '{{{0}'
        '}}{0}'
    )

    uniform_variable = []

    for location in a_program['u_locations']:

        uniform_type = get_variable_type('uniform', location[0], a_program['vertex'])

        if uniform_type == '':

            continue

        uniform_variable.append('\tm_{}()'.format(location[0]))

    vertex_structure = []

    for i in range(0, a_vertex_count):

        vertex_structure.append('\tVertexStructure()')

    return constructor_template.format(os.linesep, '\t',
                                       ',{}'.format(os.linesep).join(uniform_variable),
                                       ',{}'.format(os.linesep).join(vertex_structure))


def generate_custom_ui_cpp_initialize(a_controls):

    initialize_template = (
        'void CustomUi::Initialize(){0}'
        '{{{0}'
        '{1}UiAsset::Initialize();{0}'
        '{1}//{0}'
        '{2}'          # is_exist_control
        '{0}'
        '{1}//{0}'
        '{1}IS_ALL_SLIDER_MODELS_SET(mSliderModels){0}'
        '{0}'
        '{3}'          # set_button_click
        '{0}'
        '}}{0}'
    )

    button_template = (
        '{1}if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[{2}].lock())){0}'
        '{1}{{{0}'
        '{1}{1}directButton->set_click([this]{0}'
        '{1}{1}{{{0}'
        '{1}{1}{1}// TODO:{0}'
        '{1}{1}}});{0}'
        '{1}}}{0}'
    )

    is_exist_control = []
    set_button_click = []
    is_button = True

    for controls in [a_controls[1]['button'], a_controls[1]['panel'], a_controls[1]['label']]:

        is_exist_control.append(os.linesep)

        for control in controls:

            control = get_control_from_define(control)
            is_exist_control.append('\tIS_CONTROL_EXIST({}){}'.format(control, os.linesep))

            if is_button:

                set_button_click.append(button_template.format(os.linesep, '\t', control))

        is_button = False

    return initialize_template.format(os.linesep, '\t', ''.join(is_exist_control), os.linesep.join(set_button_click))


def generate_custom_ui_cpp_update(a_program, a_controls, a_vertex_count):

    update_template = (
        'void CustomUi::Update(const Library::GameTime& aGameTime){0}'
        '{{{0}'
        '{1}UiAsset::Update(aGameTime);{0}'
        '{1}//{0}'
        '{2}'           # uniform_variable
        '{0}'
        '{3}'           # vertices_variable
        '}}{0}'
    )

    uniforms = get_uniform_with_corresponding_defines(a_program, a_controls, 'label')
    uniform_variable = []

    for location in a_program['u_locations']:

        if location[0] in uniforms:

            for uniform in uniforms[location[0]]:

                uniform_variable.append('\tDISPLAY_VALUE_AT_LABEL({}, {}){}'.format(uniform[0], uniform[1], os.linesep))

    vertices = get_vertices_with_corresponding_defines(a_program, a_controls, a_vertex_count, 'label')
    vertices_variable = []

    for vertex in vertices:

        vertices_variable.append('\tDISPLAY_VALUE_AT_LABEL({}, {}){}'.format(vertex[0], vertex[1], os.linesep))

    return update_template.format(os.linesep, '\t', ''.join(uniform_variable), ''.join(vertices_variable))


def generate_custom_ui_cpp_uniform_methods(a_program, a_controls):

    uniform_method_template = (
        'void CustomUi::Set_{2}(const {3}& a_{2}){0}'
        '{{{0}'
        '{1}m_{2} = a_{2};{0}'
        '{1}//{0}'
        '{4}'
        '}}{0}'
        '{0}'
        'const {3}& CustomUi::Get_{2}() const{0}'
        '{{{0}'
        '{1}return m_{2};{0}'
        '}}{0}'
    )

    uniforms = get_uniform_with_corresponding_defines(a_program, a_controls, 'slider')
    methods = []

    for location in a_program['u_locations']:

        if location[0] in uniforms:

            uniform_type = get_variable_type('uniform', location[0], a_program['vertex'])

            if uniform_type == '':

                continue

            uniform_variable = []

            for uniform in uniforms[location[0]]:

                uniform_variable.append('\tSET_REAL_SLIDER_VALUE({}, {}){}'.format(uniform[0], uniform[1], os.linesep))

            methods.append(uniform_method_template.format(os.linesep, '\t', location[0],
                                                          uniform_type, ''.join(uniform_variable)))

    return os.linesep.join(methods)


def generate_custom_ui_cpp_vertex_methods(a_program, a_controls, a_vertex_count):

    vertex_method_template = (
        'void CustomUi::SetVertices(const std::vector<VertexStructure>& aVertices){0}'
        '{{{0}'
        '{1}mVertices = aVertices;{0}'
        '{1}//{0}'
        '{2}'
        '}}{0}'
        '{0}'
        'const std::vector<VertexStructure>& CustomUi::GetVertices() const{0}'
        '{{{0}'
        '{1}return mVertices;{0}'
        '}}{0}'
    )

    vertices = get_vertices_with_corresponding_defines(a_program, a_controls, a_vertex_count, 'slider')
    vertices_variable = []

    for vertex in vertices:

        vertices_variable.append('{}SET_REAL_SLIDER_VALUE({}, {}){}'.format('\t',
                                                                            vertex[0],
                                                                            vertex[1],
                                                                            os.linesep))

    return vertex_method_template.format(os.linesep, '\t', ''.join(vertices_variable))


def generate_custom_ui_cpp_get_slider_model(a_program, a_controls, a_vertex_count):

    get_slider_model_template = (
        'Library::SliderModel* CustomUi::GetSliderModel(int aSliderId, float aMin, float aMax){0}'
        '{{{0}'
        '{1}Library::SliderModel* sliderModel = nullptr;{0}'
        '{0}'
        '{1}if (aSliderId > (SLIDER_MODEL_COUNT - 1) || mSliderModels[aSliderId]){0}'
        '{1}{{{0}'
        '{1}{1}return sliderModel;{0}'
        '{1}}}{0}'
        '{0}'
        '{1}float* modelValue = nullptr;{0}'
        '{0}'
        '{1}switch (aSliderId){0}'
        '{1}{{{0}'
        '{2}'
        '{0}'
        '{1}{1}default:{0}'
        '{1}{1}{1}return sliderModel;{0}'
        '{1}}}{0}'
        '{0}'
        '{1}assert(modelValue);{0}'
        '{1}sliderModel = new Library::CustomSliderModel(*modelValue, aMin, aMax);{0}'
        '{1}mSliderModels[aSliderId] = sliderModel;{0}'
        '{1}return sliderModel;{0}'
        '}}{0}'
    )

    uniforms = get_uniform_with_corresponding_defines(a_program, a_controls, 'slider')
    vertices = get_vertices_with_corresponding_defines(a_program, a_controls, a_vertex_count, 'slider')
    case_template = (
        '{1}{1}case {2}:{0}'
        '{1}{1}{1}modelValue = &{3};{0}'
        '{1}{1}{1}break;{0}'
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

    return get_slider_model_template.format(os.linesep, '\t', os.linesep.join(model_switch))


def generate_custom_ui_cpp(a_program, a_controls, a_vertex_count):

    custom_ui_cpp_template = (
        '#include "CustomUi.h"{0}'
        '#include "ui/controls/button.h"{0}'
        '#include "ui/controls/label.h"{0}'
        '#include "ui/controls/panel.h"{0}'
        '#include "SliderModel.h"{0}'
        # '#include "checkbox.h"{0}'
        '#include "Controls.h"{0}'
        '#include <sstream>{0}'
        '#include <iomanip>{0}'
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        'RTTI_DEFINITIONS(CustomUi){0}'
        '{0}'
        '{2}'                                   # constructor
        '{0}'
        'CustomUi::~CustomUi(){0}'
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
        '{7}'                                   # get_slider_model
        '{0}'
        '}}{0}'
    )

    return custom_ui_cpp_template.format(os.linesep, '\t',
                                         generate_custom_ui_cpp_constructor(a_program, a_vertex_count),
                                         generate_custom_ui_cpp_initialize(a_controls),
                                         generate_custom_ui_cpp_update(a_program, a_controls, a_vertex_count),
                                         generate_custom_ui_cpp_uniform_methods(a_program, a_controls),
                                         generate_custom_ui_cpp_vertex_methods(a_program, a_controls, a_vertex_count),
                                         generate_custom_ui_cpp_get_slider_model(a_program, a_controls, a_vertex_count)
                                         )


if __name__ == '__main__':

    if len(sys.argv) < 2:

        print('Using: {} <shader file>'.format(sys.argv[0]))

    else:

        vertex_count = 4

        shader_program = read_program(sys.argv[1])
        ui_xml = generate_ui_xml(shader_program, vertex_count)
        controls_h = generate_controls_h(ui_xml)
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
