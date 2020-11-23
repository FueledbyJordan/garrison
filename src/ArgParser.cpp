#include "ArgParser.hpp"
#include "GarrisonGlobals.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

ArgParser::ArgParser(int argc, char ** argv) : _argc(argc), _argv(argv)
{
    _opts = std::shared_ptr<cxxopts::Options>(new cxxopts::Options("garrison", "A config file deployment system."));
    _opts->add_options()
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
		bool overwrite_config = false;

		if (Utilities::FileExists("garrison.cfg"))
		{
			std::string config_overwrite_query;
			std::cout << "garrison.cfg already exists... Would you like to overwrite it?\t(Y/N)" << std::endl;
			std::getline(std::cin, config_overwrite_query);
			overwrite_config = didUserRespondYes(config_overwrite_query);
		}

		if (!Utilities::FileExists("garrison.cfg") || overwrite_config)
		{
			//TODO: Generate config
			std::cout << "Generated Garrison config file in current directory." << std::endl;
		}

        exit(Garrison::NO_ERR);
    }

}

bool ArgParser::didUserRespondYes(const std::string & query_response)
{
	bool result;
	std::string response = query_response;

	std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::tolower(c); });
	Utilities::trim(response);

	if (response.compare("y") == 0 || response.compare("yes") == 0)
	{
		result = true;
	} else if (response.compare("n") == 0 || response.compare("no") == 0)
	{
		result = false;
	} else
	{
		std::cout << "Response not valid. Exiting..." << std::endl;
		result = false;
	}

	return result;
}

void ArgParser::printHelpMessage()
{
    std::cout << _opts->help() << std::endl;
}

const cxxopts::OptionValue & ArgParser::operator[](const std::string & option) const
{
    return (*_args)[option];
}
