#include <cxxopts.hpp>

int main(int argc, char** argv)
{
  cxxopts::Options options("garrison", "A config file deployment system.");

  options.add_options()
    ("i,input", "The directory where garrison looks for files.", cxxopts::value<std::string>()->default_value("."))
    ("o,output", "This is where garrison places your symlinks.", cxxopts::value<std::string>()->default_value(".."))
    ("c,config", "The config file to use.  Garrison will read the configuration file and then will apply any given input parameters.", cxxopts::value<std::string>()->default_value("garrison.cfg"))
    ("f,force", "Force the operation. This will overwrite existing links and files.", cxxopts::value<bool>()->default_value("false"))
    ("I,include", "Include the files and directories that match the provided regex pattern. This can be called multiple times.", cxxopts::value<std::string>())
    ("E,exclude", "Exclude the files and directories that match the provided regex pattern. This can be called multiple times.", cxxopts::value<std::string>())
    ("C,copy", "Copy the files and directories that match the provided regex pattern. This can be called multiple times.", cxxopts::value<std::string>())
    ("g,generate", "Generate a configuration file.", cxxopts::value<bool>()->default_value("false"))
    ("v,version", "Print version")
    ("h,help", "Print usage");

  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  for (auto parm : result.arguments())
  {
    std::cout << parm.key() << "\t:\t" << parm.value() << std::endl;
  }

  return 0;

}