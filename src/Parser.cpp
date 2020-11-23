#include "Parser.hpp"

Parser::Parser(int argc, char ** argv)
{
    _ap = std::unique_ptr<ArgParser>(new ArgParser(argc, argv)); 
    _cp = std::unique_ptr<ConfigParser>(new ConfigParser(_ap->ConfigFilePath()));

	_force = Cli().Force();
	BuildFileOperations();
}

Parser::~Parser(){}

ArgParser & Parser::Cli() const
{
    return *_ap;
}

ConfigParser & Parser::Cfg() const
{
    return *_cp;
}

std::vector<std::pair<std::string, std::string>> Parser::FileOperations()
{
	return _fileOperations;
}

std::string Parser::ToString()
{
	std::string result = Cfg().ToString() + "\n" + Cli().ToString();
	return result;
}

//TODO: Fix the population of the fileOperations
void Parser::BuildFileOperations()
{
	for (auto l : Cfg().Links())
	{
		_fileOperations.push_back(std::make_pair("Link", l));
	}

	for (auto c : Cfg().Copies())
	{
		_fileOperations.push_back(std::make_pair("Copy", c));
	}

	for (auto e : Cfg().Excludes())
	{
		_fileOperations.push_back(std::make_pair("Exclude", e));
	}

	for (auto l : Cli().Links())
	{
		_fileOperations.push_back(std::make_pair("Link", l));
	}

	for (auto c : Cli().Copies())
	{
		_fileOperations.push_back(std::make_pair("Copy", c));
	}

	for (auto e : Cli().Excludes())
	{
		_fileOperations.push_back(std::make_pair("Exclude", e));
	}
}
