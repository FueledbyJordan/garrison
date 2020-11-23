#pragma once

#include "ParserBase.hpp"

#include <string>
#include <vector>

class ConfigParser : public ParserBase
{

public:
    ConfigParser(const std::string & configFilePath);
    ~ConfigParser();

    void Read() override;
	std::string ToString() override;

private:

    std::pair<std::string, std::string> parseLine(const std::string & line, unsigned int lineNumber);

};
