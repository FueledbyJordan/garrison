#include "ConfigParser.hpp"
#include "Utilities.hpp"
#include "GarrisonGlobals.hpp"
#include <fstream>
#include <iostream>

ConfigParser::ConfigParser(const std::string & configFilePath) : _configFilePath(configFilePath)
{
    this->initialize();
    this->Read();
//    std::cout << this->ToString();
}

ConfigParser::~ConfigParser(){}

void ConfigParser::initialize()
{
    _VALID_CFG_OPS.insert(_VALID_CFG_IO_OPS.begin(), _VALID_CFG_IO_OPS.end());
    _VALID_CFG_OPS.insert(_VALID_CFG_ACTION_OPS.begin(), _VALID_CFG_ACTION_OPS.end());
}

void ConfigParser::Read()
{
    if (!Utilities::FileExists(_configFilePath))
    {
        std::cout << "Error opening the specified config file (" << _configFilePath << ")." << std::endl;
        exit(Garrison::CONFIG_MISSING_ERR);
    }

    std::ifstream reader(_configFilePath);
    std::string line;
    std::pair<std::string, std::string> parseResult;
    unsigned int lineNumber = 0;

    while (std::getline(reader, line))
    {
        parseResult = parseLine(line, lineNumber++);
        if (validConfigOperation(parseResult.first))
        {
            if (validConfigIoOperation(parseResult.first))
            {
                _ioDirections[parseResult.first] = parseResult.second;
            } else if(validConfigActionOperation(parseResult.first))
            {
                _fileOperations.push_back(parseResult);
            }
        }
    }

    reader.close();

}

std::pair<std::string, std::string> ConfigParser::parseLine(const std::string & line, unsigned int lineNumber)
{
    std::string key;
    std::string val;
    int delim_pos = line.find("=");

    if (delim_pos == std::string::npos)
    {
        std::cout << "Config file syntax error on line " << lineNumber << ":\n\t" << line << std::endl;
        exit(Garrison::CONFIG_INVALID_ERR);
    }

    key = line.substr(0, delim_pos);
    val = line.substr(delim_pos + 1);

    Utilities::trim(key);
    Utilities::trim(val);

    return std::pair<std::string, std::string>(key, val);

}

bool ConfigParser::validConfigOperation(std::string op)
{
    return (_VALID_CFG_OPS.count(op) > 0);
}

bool ConfigParser::validConfigIoOperation(std::string op)
{
    return (_VALID_CFG_IO_OPS.count(op) > 0);
}

bool ConfigParser::validConfigActionOperation(std::string op)
{
    return (_VALID_CFG_ACTION_OPS.count(op) > 0);
}
