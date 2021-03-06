#include "ConfigParser.hpp"
#include "Utilities.hpp"
#include "GarrisonGlobals.hpp"
#include <fstream>
#include <iostream>

ConfigParser::ConfigParser(const std::string & configFilePath)
{
    _configFilePath = configFilePath;
    read();
    _fileList.setDestination(_output);
}

ConfigParser::~ConfigParser(){}

void ConfigParser::read()
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
        Utilities::to_lower(parseResult.first);

        //TODO: Only remove outer if no alphanumeric chars are outside
        Utilities::remove_all(parseResult.second, '"');

        _fileList.insert(File(parseResult.first, parseResult.second));

        if (parseResult.first.compare("input") == 0)
        {
            _input = parseResult.second;
        } else if (parseResult.first.compare("output") == 0)
        {
            _output = parseResult.second;
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

std::string ConfigParser::toString()
{
    std::string result = "Config File Parser:\n";
    result += ParserBase::toString();

    return result;
}
