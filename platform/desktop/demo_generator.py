import os
# import re
import sys
# import xml.etree.ElementTree as ET
# sys.path.append('.')
from effect_generator import read_program, extend_program_info


def generate_demo_h(a_program):

    demo_h_template = (
        '#ifndef _{3}_DEMO_H_{0}'
        '#define _{3}_DEMO_H_{0}'
        '{0}'
        '#include "{2}Settings.h"{0}'
        '#include <DrawableGameComponent.h>{0}'
        '#include <elements/utils/std/pointer.h>{0}'
        '#include <elements/utils/std/optional.h>{0}'
        '{0}'
        'namespace eps{0}'
        '{{{0}'
        'namespace rendering{0}'
        '{{{0}'
        'class program;{0}'
        'class texture;{0}'  # TODO:
        '}}{0}'
        '}}{0}'
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        'class {2}Effect;{0}'
        'class {2}Ui;{0}'
        'class {2}Demo : public Library::DrawableGameComponent{0}'
        '{{{0}'
        '{1}RTTI_DECLARATIONS({2}Demo, DrawableGameComponent){0}'
        '{0}'
        'public:{0}'
        '{1}{2}Demo(Library::Game& aGame);{0}'
        '{1}~{2}Demo();{0}'
        '{0}'
        'public:{0}'
        '{1}{2}Demo() = delete;{0}'
        '{1}{2}Demo(const {2}Demo& aRhs) = delete;{0}'
        '{1}{2}Demo& operator = (const {2}Demo& aRhs) = delete;{0}'
        '{0}'
        'public:{0}'
        '{1}virtual bool Initialize() override;{0}'
        '{1}virtual void Update() override;{0}'
        '{1}virtual void Draw() override;{0}'
        '{0}'
        'private:{0}'
        '{1}eps::utils::unique<eps::rendering::program> m{2}Program;{0}'
        '{1}eps::utils::unique<{2}Effect> m{2}Effect;{0}'
        '{4}'
        '{1}eps::utils::optional<{2}Settings> m{2}Settings;{0}'
        '{1}{2}Ui* m{2}Ui;{0}'
        '}};{0}'
        '}}{0}'
        '{0}'
        '#endif{0}'
    )

    uniforms_samplers = []

    for location in a_program['u_locations']:

        if 'std::string' == location[2]:

            uniforms_samplers.append('{}eps::utils::unique<eps::rendering::texture> {};'.format('\t', location[0]))

    uniforms_samplers = os.linesep.join(uniforms_samplers)

    if uniforms_samplers:

        uniforms_samplers = '{}{}'.format(uniforms_samplers, os.linesep)

    return demo_h_template.format(os.linesep, '\t', a_program['class_name'], a_program['head_name'], uniforms_samplers)


def generate_demo_cpp(a_program, a_path_2_xml_shader):

    demo_cpp_template = (
        '{0}'
        '#include "{2}Demo.h"{0}'
        '#include "{2}Effect.h"{0}'
        '#include "{2}Ui.h"{0}'
        '#include <TextureLoader.h>{0}'  # TODO:
        '#include <elements/rendering/core/program.h>{0}'
        '#include <elements/rendering/core/texture.h>{0}'  # TODO:
        '#include <elements/rendering/state/state_macro.h>{0}'
        '#include <elements/rendering/core/texture_maker.h>{0}'  # TODO:
        '#include <elements/rendering/core/texture_policy.h>{0}'  # TODO:
        '#include <elements/rendering/utils/program_loader.h>{0}'
        '#include <elements/assets/asset_texture.h>{0}'  # TODO:
        '#include <elements/assets/assets_storage.h>{0}'
        '#include <elements/utils/std/enum.h>{0}'
        '#include <elements/utils/std/product.h>{0}'
        '#include <Game.h>{0}'  # TODO:
        '#include <array>{0}'  # TODO:
        '{0}'
        'namespace Rendering{0}'
        '{{{0}'
        'RTTI_DEFINITIONS({2}Demo){0}'
        '{0}'
        'enum class program_enum : short{0}'
        '{{{0}'
        '{1}// attributes{0}'
        '{3}'
        '{1}// uniforms{0}'
        '{4}'
        '}};{0}'
        '{0}'
        '{2}Demo::{2}Demo(Library::Game& aGame) :{0}'
        '{1}DrawableGameComponent(aGame),{0}'
        '{1}m{2}Program(nullptr),{0}'
        '{1}m{2}Effect(nullptr),{0}'
        '{5}'                                                                       # texture_uniforms
        '{1}m{2}Settings(),{0}'
        '{1}m{2}Ui(nullptr){0}'
        '{{{0}'
        '}}{0}'
        '{0}'
        '{2}Demo::~{2}Demo() = default;{0}'
        '{0}'
        'bool {2}Demo::Initialize(){0}'
        '{{{0}'
        '{1}// Build the shader program{0}'
        '{1}m{2}Program = eps::utils::make_unique<eps::rendering::program>();{0}'
        '{1}auto assetPath = "{6}";{0}'                                             # path_to_shader
        '{0}'
        '{1}if (!eps::rendering::load_program(assetPath, (*m{2}Program.get()))){0}'
        '{1}{{{0}'
        '{1}{1}return false;{0}'
        '{1}}}{0}'
        '{0}'
        '{1}// Load the settings{0}'
        '{1}assetPath = "{7}";{0}'                                                  # path_to_settings
        '{1}m{2}Settings = eps::assets_storage::instance().read<{2}Settings>(assetPath);{0}'
        '{0}'
        '{1}if (!m{2}Settings || m{2}Settings->mIsEmpty){0}'
        '{1}{{{0}'
        '{1}{1}return false;{0}'
        '{1}}}{0}'
        '{0}'
        '{8}'                                                                       # load_textures
        '{1}// Create the effect{0}'
        '{1}m{2}Effect = eps::utils::make_unique<{2}Effect>(m{2}Settings->mVertices, m{2}Settings->mIndices,{0}'
        '{1}{1}{1}eps::rendering::buffer_usage::STREAM_DRAW);{0}'
        '{1}// Retry the UI service{0}'
        '{1}m{2}Ui = static_cast<Rendering::{2}Ui*>(mGame->GetServices().GetService({0}'
        '{1}{1}{1}Rendering::{2}Ui::TypeIdClass()));{0}'
        '{1}assert(m{2}Ui);{0}'
        '{1}return m{2}Ui != nullptr;{0}'
        '}}{0}'
        '{0}'
        'void {2}Demo::Update(){0}'
        '{{{0}'
        '{1}if (m{2}Ui->IsNeedRestore()){0}'
        '{1}{{{0}'
        '{9}'                                                                       # set_ui_from_settings
        '{1}{1}//{0}'
        '{1}{1}m{2}Ui->SetVertices(m{2}Settings->mVertices);{0}'
        '{1}}}{0}'
        '}}{0}'
        '{0}'
        'void {2}Demo::Draw(){0}'
        '{{{0}'
        '{10}'                                                                      # activate_textures
        '{1}EPS_STATE_PROGRAM(m{2}Program->get_product());{0}'
        '{1}//{0}'
        '{11}'                                                                      # set_uniforms
        '{1}//{0}'
        '{1}m{2}Effect->construct(m{2}Ui->GetVertices());{0}'
        '{12}'                                                                      # attributes_to_construct
        '{13}'                                                                      # deactivate_textures
        '}}{0}'
        '{0}'
        '}}{0}'
        '{0}'
    )

    attributes_location = []
    attributes_to_construct = []

    for location in a_program['a_locations']:

        attributes_location.append('{}{} = {}'.format('\t', location[0], location[1]))
        attributes_to_construct.append('eps::utils::to_int(program_enum::{})'.format(location[0]))

    attributes_location = ',{}'.format(os.linesep).join(attributes_location)
    attributes_location = '{},{}'.format(attributes_location, os.linesep)

    if len(attributes_to_construct) > 1:

        i = len(attributes_to_construct)
        attributes_to_construct = ', '.join(attributes_to_construct)
        attributes_to_construct = 'std::array<short, {}> attributes = {{ {} }};'.format(i, attributes_to_construct)
        template = (
            '{1}{3}{0}'
            '{1}m{2}Effect->render(*m{2}Program.get(), attributes, m{2}Settings->mIndices.size());'
        )

        attributes_to_construct = template.format(os.linesep, '\t', a_program['class_name'], attributes_to_construct)

    else:

        template = (
            '{1}m{2}Effect->render(*m{2}Program.get(), {3}, m{2}Settings->mIndices.size());'
        )
        attributes_to_construct = template.format(os.linesep, '\t',
                                                  a_program['class_name'], ''.join(attributes_to_construct))

    attributes_to_construct = '{}{}'.format(attributes_to_construct, os.linesep)

    load_texture_template = (
        '{1}{2} = eps::utils::make_unique<eps::rendering::texture>();{0}'
        '{1}LOAD_TEXTURE(m{3}Settings->{2}, (*{2}.get()))'
    )

    activate_texture_template = (
        '{1}glActiveTexture(GL_TEXTURE{2});{0}'
        '{1}glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product({3}->get_product()));'
    )

    set_uniform_template = (
        '{0}m{1}Program->uniform_value(eps::utils::to_int(program_enum::{2}), m{1}Ui->Get_{2}());'
    )

    deactivate_texture_template = (
        '{1}glActiveTexture(GL_TEXTURE{2});{0}'
        '{1}glBindTexture(GL_TEXTURE_2D, 0);'
    )

    uniforms_location = []
    uniforms_samplers = []
    load_textures = []
    set_ui_from_settings = []
    activate_textures = []
    i = 0
    set_uniforms = []
    deactivate_textures = []

    for location in a_program['u_locations']:

        uniforms_location.append('{}{} = {}'.format('\t', location[0], location[1]))

        if 'std::string' == location[2]:

            uniforms_samplers.append('{}{}(nullptr),'.format('\t', location[0]))
            load_textures.append(load_texture_template.format(os.linesep, '\t',
                                                              location[0], a_program['class_name']))
            activate_textures.append(activate_texture_template.format(os.linesep, '\t', i, location[0]))
            deactivate_textures.append(deactivate_texture_template.format(os.linesep, '\t', i))
            i += 1

        else:

            set_ui_from_settings.append('{0}{0}m{1}Ui->Set_{2}(m{1}Settings->{2});'.format('\t',
                                                                                           a_program['class_name'],
                                                                                           location[0]))
            set_uniforms.append(set_uniform_template.format('\t', a_program['class_name'], location[0]))

    uniforms_location = ',{}'.format(os.linesep).join(uniforms_location)
    uniforms_location = '{}{}'.format(uniforms_location, os.linesep)
    uniforms_samplers = os.linesep.join(uniforms_samplers)
    set_ui_from_settings = os.linesep.join(set_ui_from_settings)
    set_ui_from_settings = '{}{}'.format(set_ui_from_settings, os.linesep)
    activate_textures = os.linesep.join(activate_textures)
    set_uniforms = os.linesep.join(set_uniforms)
    set_uniforms = '{}{}'.format(set_uniforms, os.linesep)
    deactivate_textures.reverse()
    deactivate_textures = os.linesep.join(deactivate_textures)

    if uniforms_samplers:

        uniforms_samplers = '{}{}'.format(uniforms_samplers, os.linesep)

    path_to_shader = a_path_2_xml_shader.replace(os.path.sep, '/')
    path_to_shader = path_to_shader[path_to_shader.find('assets/'):]
    path_to_settings = path_to_shader.replace('shaders', 'settings')
    path_to_settings = path_to_settings.replace('.prog', '.xml')
    path_to_settings = path_to_settings[path_to_settings.find('assets/'):]

    load_textures = os.linesep.join(load_textures)

    if load_textures:

        load_textures = '{}{}'.format(load_textures, os.linesep)

    if activate_textures:

        activate_textures = '{2}{0}{1}//{0}'.format(os.linesep, '\t', activate_textures)

    if deactivate_textures:

        deactivate_textures = '{0}{1}//{0}{2}{0}'.format(os.linesep, '\t', deactivate_textures)

    return demo_cpp_template.format(os.linesep, '\t', a_program['class_name'],
                                    attributes_location, uniforms_location, uniforms_samplers,
                                    path_to_shader, path_to_settings, load_textures,
                                    set_ui_from_settings, activate_textures, set_uniforms,
                                    attributes_to_construct, deactivate_textures)


def generate_program_cpp(a_program, a_path_2_xml_shader):

    program_cpp_template = (
        '{0}'
        '#include "{2}Demo.h"{0}'
        '#include "{2}Ui.h"{0}'
        '#include <RenderingGame.h>{0}'
        '#include <ClearBackground.h>{0}'
        '{0}'
        '#ifdef WIN32{0}'
        '#if defined(DEBUG) || defined(_DEBUG){0}'
        '#define _CRTDBG_MAP_ALLOC{0}'
        '#include <stdlib.h>{0}'
        '#include <crtdbg.h>{0}'
        '#endif{0}'
        '#include <tchar.h>{0}'
        '#else{0}'
        '#include <iostream>{0}'
        '#endif{0}'
        '{0}'
        '#ifndef WIN32{0}'
        'int main(int argc, char** argv){0}'
        '{{{0}'
        '{1}(void)argc;{0}'
        '{1}(void)argv;{0}'
        '#else{0}'
        'int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow){0}'
        '{{{0}'
        '{1}(void)hInstance;{0}'
        '{1}(void)hPrevInstance;{0}'
        '{1}(void)lpCmdLine;{0}'
        '{1}(void)nCmdShow;{0}'
        '#if defined(DEBUG) || defined(_DEBUG){0}'
        '{1}_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);{0}'
        '#endif{0}'
        '#endif{0}'
        '{1}auto game = std::make_unique<Library::RenderingGame>("{2} [Sources {4}]");{0}'
        '{1}game->addComponent<Library::ClearBackground>();{0}'
        '{1}game->addService<Rendering::{2}Ui>("{3}");{0}'
        '{1}game->addComponent<Rendering::{2}Demo>();{0}'
        '{0}'
        '{1}try{0}'
        '{1}{{{0}'
        '{1}{1}game->Run();{0}'
        '{1}}}{0}'
        '{1}catch (const std::runtime_error& aExc){0}'
        '{1}{{{0}'
        '#ifndef WIN32{0}'
        '{1}{1}std::cerr << aExc.what() << std::endl;{0}'
        '#else{0}'
        '{1}{1}MessageBoxA(game->GetWindowHandle(), aExc.what(),{0}'
        '{1}{1}{1}{1}{1}game->GetWindowTitle().c_str(), MB_ABORTRETRYIGNORE);{0}'
        '#endif{0}'
        '{1}}}{0}'
        '{0}'
        '{1}return 0;{0}'
        '}}{0}'
    )

    path_to_shader = a_path_2_xml_shader.replace(os.path.sep, '/')
    path_to_settings = path_to_shader.replace('shaders', 'settings')
    path_to_settings = path_to_settings.replace('.prog', '.xml')
    path_to_settings = path_to_settings[path_to_settings.find('assets/'):]
    path_to_source = path_to_settings[path_to_settings.find('settings/') + len('settings/'):]
    path_to_source = path_to_source.replace('.xml', '')

    return program_cpp_template.format(os.linesep, '\t', a_program['class_name'], path_to_settings, path_to_source)


if __name__ == '__main__':

    if len(sys.argv) < 2:

        print('Using: {} <shader file>'.format(sys.argv[0]))

    else:

        shader_program = read_program(sys.argv[1])
        shader_program = extend_program_info(shader_program)
        demo_h = generate_demo_h(shader_program)
        demo_cpp = generate_demo_cpp(shader_program, sys.argv[1])
        program_cpp = generate_program_cpp(shader_program, sys.argv[1])

        print('--------------------------------------------------------------------')
        print(demo_h)
        print('--------------------------------------------------------------------')
        print(demo_cpp)
        print('--------------------------------------------------------------------')
        print(program_cpp)
        print('--------------------------------------------------------------------')
