#include "ConfigGenerator.hpp"
#include "Utilities.hpp"

const std::string ConfigGenerator::_config = "input = .\noutput = ..\ninclude = \"some_folder\"\nexclude = \"some_folder/some_private_folder\"\ninclude = \"some_other_folder\"\nexclude = \".*\\/\\.key\"\ncopy = \"some_other_other_folder\"";

void ConfigGenerator::Generate()
{
    std::cout << _config << std::endl;
}
