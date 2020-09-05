#include "FileParser.hpp"
#include "Utilities.hpp"
#include "GarrisonGlobals.hpp"
#include <fstream>
#include <iostream>

FileParser::FileParser(const std::string & configFilePath) : _configFilePath(configFilePath)
{
    this->Read();
    std::cout << this->ToString();
}

FileParser::~FileParser(){}

void FileParser::Read()
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
    }

    reader.close();

}

std::string FileParser::ToString()
{
    std::string retval = "";
    for (auto const & result : _parseResults)
    {
        retval += result.first + "(" + std::to_string(result.first.length()) + ")" + "\t:\t" + result.second + "(" + std::to_string(result.second.length()) + ")" + "\n";
    }
    return retval;
}

std::pair<std::string, std::string> FileParser::parseLine(const std::string & line, unsigned int lineNumber)
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