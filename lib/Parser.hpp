#pragma once

#include "ArgParser.hpp"
#include "ConfigParser.hpp"

#include <string>
#include <utility>
#include <vector>

class Parser
{

public:
    Parser(int argc, char ** argv);
    ~Parser();

    ArgParser & Cli() const;
    ConfigParser & Cfg() const;

	std::string ToString();
	std::vector<std::pair<std::string, std::string>> FileOperations();

private:
    std::shared_ptr<ArgParser> _ap;
    std::shared_ptr<ConfigParser> _cp;

	std::vector<std::pair<std::string, std::string>> _fileOperations;
	void BuildFileOperations();

	bool _force = false;

};
