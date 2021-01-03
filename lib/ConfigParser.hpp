#pragma once

#include "ParserBase.hpp"

#include <string>

class ConfigParser : public ParserBase
{

public:
    ConfigParser(const std::string & configFilePath);
    ~ConfigParser();
    void read() override;

    std::string toString() override;

private:

    std::pair<std::string, std::string> parseLine(const std::string & line, unsigned int lineNumber);

};
