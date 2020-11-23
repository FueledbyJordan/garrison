#include "ArgParser.hpp"
#include "ConfigGenerator.hpp"
#include "GarrisonGlobals.hpp"
#include "Utilities.hpp"

#include <iostream>

ArgParser::ArgParser(int argc, char ** argv) : _argc(argc), _argv(argv)
{
    _opts = std::shared_ptr<cxxopts::Options>(new cxxopts::Options("garrison", "A config file deployment system."));
    _opts->add_options()
        ("i,input", "The directory where garrison looks for files.", cxxopts::value<std::string>()->default_value("."))
        ("o,output", "This is where garrison places your symlinks.", cxxopts::value<std::string>()->default_value(".."))
        ("config", "The config file to use.  Garrison will read the configuration file and then will apply any given input parameters.", cxxopts::value<std::string>(_configFilePath)->default_value("garrison.cfg"))
        ("f,force", "Force the operation. This will overwrite existing links and files.", cxxopts::value<bool>()->default_value("false"))
        ("l,link", "Link the files and directories that match the provided regex pattern. This can be called multiple times.", cxxopts::value<std::vector<std::string>>(_links))
        ("e,exclude", "Exclude the files and directories that match the provided regex pattern. This can be called multiple times.", cxxopts::value<std::vector<std::string>>(_excludes))
        ("c,copy", "Copy the files and directories that match the provided regex pattern. This can be called multiple times.", cxxopts::value<std::vector<std::string>>(_copies))
        ("generate", "Generate a configuration file.", cxxopts::value<bool>()->default_value("false"))
        ("v,version", "Print version")
        ("h,help", "Print usage");

    this->Read();

}

ArgParser::~ArgParser()
{

}

void ArgParser::Read()
{
    try
    {
        _args = std::make_unique<cxxopts::ParseResult>(_opts->parse(_argc, _argv));
    } catch(cxxopts::OptionParseException)
    {
        std::cout << "Error, usage is:" << std::endl << std::endl;
        this->printHelpMessage();
        exit(Garrison::CLI_ARG_ERR);
    }

    if (_args->count("help"))
    {
        this->printHelpMessage();
        exit(Garrison::NO_ERR);
    }

    if (_args->count("version"))
    {
		std::cout << "Garrison Version:\t" << Garrison::VERSION << std::endl;
        exit(Garrison::NO_ERR);
    }

    if (_args->count("generate"))
    {
		ConfigGenerator::Generate();
        exit(Garrison::NO_ERR);
    }

    if (_args->count("force"))
		this->_force = true;

	for (auto item : _links)
	{
		std::cout << item << std::endl;
	}

}

std::string ArgParser::ToString()
{
	std::string result = "Command Line Parser:\n";
	result += ParserBase::ToString();

	return result;
}

void ArgParser::printHelpMessage()
{
    std::cout << _opts->help() << std::endl;
}

bool ArgParser::Force()
{
	return _force;
}
