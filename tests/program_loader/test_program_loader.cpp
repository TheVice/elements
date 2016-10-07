
#include <assets/assets_storage.h>
#include <rendering/utils/program_loader.h>

#include <unordered_map>
#include <string>
#include <iostream>

/*
<shaders> - ok, use default version - "#version 100"
<shaders version="100_es"> - ok, use 100 es - "#version 100"
<shaders version="300_es"> - ok, use 300 es - "#version 300 es"
<shaders version="310_es"> - ok, use 310 es - "#version 310 es"
<shaders version="asdasda"> - error, can't load a shader
*/

const std::unordered_map<std::string, std::pair<std::string, std::string>> tests_map =
{
    {"default_version.prog", std::make_pair<std::string, std::string>("#version 100\n\n            // default vertex\n        ", "#version 100\n\n            // default fragment\n        ")},
    {"100_es_version.prog", std::make_pair<std::string, std::string>("#version 100\n\n            // 100_es vertex\n        ", "#version 100\n\n            // 100_es fragment\n        ")},
    {"300_es_version.prog", std::make_pair<std::string, std::string>("#version 300 es\n\n            // 300_es vertex\n        ", "#version 300 es\n\n            // 300_es fragment\n        ")},
    {"310_es_version.prog", std::make_pair<std::string, std::string>("#version 310 es\n\n            // 310_es vertex\n        ", "#version 310 es\n\n            // 310_es fragment\n        ")},
    {"asdasda_version.prog", std::make_pair<std::string, std::string>("", "")}
};

int main()
{
    for (const auto& test : tests_map)
    {
        auto data = eps::assets_storage::instance().read<eps::rendering::program_data>(test.first);
        if (!data)
        {
            if (std::get<0>(test.second).empty() && std::get<1>(test.second).empty())
            {
                std::cout << test.first << " with unknown version PASS" << std::endl;
            }
            else
            {
                std::cerr << "could not read data from asset " << test.first << std::endl;
            }

            continue;
        }

        /*(std::get<0>(test.second) == data.value().v_shader()) ? (std::cout << test.first << " vertex PASS" << std::endl) : (std::cerr << test.first << " vertex FAIL" << std::endl);
        (std::get<1>(test.second) == data.value().f_shader()) ? (std::cout << test.first << " fragment PASS" << std::endl) : (std::cerr << test.first << " fragment FAIL" << std::endl);*/
        if ((std::get<0>(test.second) == data.value().v_shader()) && (std::get<1>(test.second) == data.value().f_shader()))
        {
            std::cout << test.first << " with known version PASS" << std::endl;
        }
        else
        {
            std::cerr << test.first << " with known version FAIL" << std::endl;
        }
    }
}
