#pragma once

#include "ParserBase.hpp"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class ConfigParser : public ParserBase
{

public:
    ConfigParser(const std::string & configFilePath);
    ~ConfigParser();

    void Read() override;
	std::string ToString() override;

private:

    std::unordered_set<std::string> _VALID_CFG_IO_OPS = {"input", "output"};
    std::unordered_set<std::string> _VALID_CFG_ACTION_OPS = {"include", "exclude", "copy"};
    std::unordered_set<std::string> _VALID_CFG_OPS;

    void initialize();

    bool validConfigOperation(std::string op);
    bool validConfigActionOperation(std::string op);
    bool validConfigIoOperation(std::string op);

    std::pair<std::string, std::string> parseLine(const std::string & line, unsigned int lineNumber);

    std::string _configFilePath;

};
