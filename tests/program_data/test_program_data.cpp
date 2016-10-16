
#include <assets/assets_storage.h>
#include <rendering/utils/program_data.h>

#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include <unordered_map>

/*
<shaders> - ok, use default version - "#version 100"
<shaders version="100_es"> - ok, use 100 es - "#version 100"
<shaders version="300_es"> - ok, use 300 es - "#version 300 es"
<shaders version="310_es"> - ok, use 310 es - "#version 310 es"
<shaders version="asdasda"> - error, can't load a shader
*/

const std::unordered_map<std::string, std::pair<std::string, std::string>> tests_map =
{
    {"default_version.prog", std::make_pair<std::string, std::string>("default_version.vs", "default_version.fs")},
    {"100_es_version.prog", std::make_pair<std::string, std::string>("100_es_version.vs", "100_es_version.fs")},
    {"300_es_version.prog", std::make_pair<std::string, std::string>("300_es_version.vs", "300_es_version.fs")},
    {"310_es_version.prog", std::make_pair<std::string, std::string>("310_es_version.vs", "310_es_version.fs")},
    {"asdasda_version.prog", std::make_pair<std::string, std::string>("asdasda_version.vs", "asdasda_version.fs")}
};

void read_from_stream(std::istream & input_stream, std::string & output)
{
    input_stream.seekg(0, std::fstream::end);
    const auto length = input_stream.tellg();

    if (length)
    {
        input_stream.seekg(0, std::fstream::beg);
        output.reserve(length);
        output.resize(length);
        input_stream.read(&output.front(), length);
    }
}

int main()
{
    for (const auto& test : tests_map)
    {
        auto data = eps::assets_storage::instance().read<eps::rendering::program_data>(test.first);

        std::ifstream vs_result(std::get<0>(test.second));

        if (!vs_result.is_open())
        {
            std::cerr << "could not read data from file " << std::get<0>(test.second) << std::endl;
            continue;
        }

        std::string vertex_shader;
        read_from_stream(vs_result, vertex_shader);
        vs_result.close();

        std::ifstream fs_result(std::get<1>(test.second));

        if (!fs_result.is_open())
        {
            std::cerr << "could not read data from file " << std::get<1>(test.second) << std::endl;
            continue;
        }

        std::string fragment_shader;
        read_from_stream(fs_result, fragment_shader);
        fs_result.close();

        if (!data)
        {
            if (vertex_shader.empty() && fragment_shader.empty())
            {
                std::cout << test.first << " with unknown version PASS" << std::endl;
            }
            else
            {
                std::cerr << "could not read data from asset " << test.first << std::endl;
            }

            continue;
        }
        if (vertex_shader.empty() && fragment_shader.empty())
        {
            std::cerr << test.first << " with unknown version FAIL" << std::endl;
        }

        if ((vertex_shader == data.value().v_shader()) && fragment_shader == data.value().f_shader())
        {
            std::cout << test.first << " with known version PASS" << std::endl;
        }
        else
        {
            std::cerr << test.first << " with known version FAIL" << std::endl;
        }
    }
}
