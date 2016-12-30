import sys
import pathlib
from effect_generator import read_program, extend_program_info, generate_effect_h, generate_effect_cpp, generate_vertex_structure
from ui_generator import generate_ui_xml, generate_controls_h, generate_custom_ui_h, generate_custom_ui_cpp, customize_ui_xml, to_pretty_xml, to_file, from_file
from settings_generator import generate_settings_xml, generate_settings_h, generate_settings_cpp
from demo_generator import generate_demo_h, generate_demo_cpp, generate_program_cpp


if __name__ == '__main__':

    if len(sys.argv) < 3:

        print('Using: {} <shader file> <folder where write cpp source files>'.format(sys.argv[0]))

    else:

        path_2_xml_shader = pathlib.Path(sys.argv[1]).absolute()

        if not path_2_xml_shader.exists() or not path_2_xml_shader.is_file():

            raise ValueError('{} is not exists or not a file'.format(path_2_xml_shader))

        path_to_folder_with_cpp_files = pathlib.Path(sys.argv[2]).absolute()

        if not path_to_folder_with_cpp_files.exists() or not path_to_folder_with_cpp_files.is_dir():

            raise ValueError('{} is not exists or not a directory'.format(path_to_folder_with_cpp_files))

        vertex_count = 4

        shader_program = read_program(str(path_2_xml_shader))
        shader_program = extend_program_info(shader_program)

        files_content = dict()

        files_content['{}Effect.h'.format(shader_program['class_name'])] = generate_effect_h(shader_program)
        files_content['{}Effect.cpp'.format(shader_program['class_name'])] = generate_effect_cpp(shader_program)
        files_content['{}Vertex.h'.format(shader_program['class_name'])] = generate_vertex_structure(shader_program)

        ui_xml = generate_ui_xml(shader_program, vertex_count)
        controls_h = generate_controls_h(shader_program, ui_xml)
        files_content['{}Controls.h'.format(shader_program['class_name'])] = controls_h[0]
        files_content['{}Ui.h'.format(shader_program['class_name'])] = generate_custom_ui_h(shader_program)
        files_content['{}Ui.cpp'.format(shader_program['class_name'])] = generate_custom_ui_cpp(shader_program,
                                                                                                controls_h,
                                                                                                vertex_count)
        ui_xml = customize_ui_xml(ui_xml, vertex_count)

        settings_xml = generate_settings_xml(shader_program, vertex_count)
        settings_xml.append(ui_xml)
        files_content[shader_program['settings_file']] = to_pretty_xml(settings_xml).decode('utf-8')
        files_content['{}Settings.h'.format(shader_program['class_name'])] = generate_settings_h(shader_program)
        files_content['{}Settings.cpp'.format(shader_program['class_name'])] = generate_settings_cpp(shader_program)

        files_content['{}Demo.h'.format(shader_program['class_name'])] = generate_demo_h(shader_program)
        files_content['{}Demo.cpp'.format(shader_program['class_name'])] = generate_demo_cpp(shader_program)
        files_content['Program.cpp'] = generate_program_cpp(shader_program)

        for file_name in files_content.keys():

            full_file_path = path_to_folder_with_cpp_files.joinpath(file_name)

            if full_file_path.exists():

                file_content = from_file(str(full_file_path))

                if file_content == files_content[file_name]:

                    print('File {} exist with same content. Skip.'.format(full_file_path))

                else:

                    to_file(files_content[file_name].encode(), str(full_file_path))
                    print('File {} exist. Content different. Overwritten.'.format(full_file_path))

            else:

                to_file(files_content[file_name].encode(), str(full_file_path))
                print('Created {} file.'.format(full_file_path))
