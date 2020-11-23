#pragma once

#include <string>
#include <vector>

class ParserBase
{

public:
    ParserBase();
    ~ParserBase();
    virtual void Read() = 0;
    virtual std::string ToString();

	std::string ConfigFilePath();
	std::string Input();
	std::string Output();

	std::vector<std::string> Links();
	std::vector<std::string> Copies();
	std::vector<std::string> Excludes();

protected:

	std::string _configFilePath;
	std::string _input = ".";
	std::string _output = "..";

	std::vector<std::string> _links;
	std::vector<std::string> _copies;
	std::vector<std::string> _excludes;

private:

};
