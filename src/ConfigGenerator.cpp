#include "ConfigGenerator.hpp"
#include "Utilities.hpp"

const std::string ConfigGenerator::_config = "input = \".\"\n"
                                              "output = \"..\"\n"
                                              "link = \"some_folder\"\n"
                                              "copy = \"some_other_folder\"\n"
                                              "exclude = \"some_other_folder/some_hidden_folder\"\n"
                                              "exclude = \"some_other_folder/some_hidden_file\"\n";

void ConfigGenerator::generate()
{
    std::cout << _config << std::endl;
}
