#include "FileParser.hpp"
#include "Utilities.hpp"
#include "GarrisonGlobals.hpp"
#include <fstream>
#include <iostream>

FileParser::FileParser(const std::string & configFilePath) : _configFilePath(configFilePath)
{
    this->initialize();
    this->Read();
//    std::cout << this->ToString();
}

FileParser::~FileParser(){}

void FileParser::initialize()
{
    _VALID_CFG_OPS.insert(_VALID_CFG_IO_OPS.begin(), _VALID_CFG_IO_OPS.end());
    _VALID_CFG_OPS.insert(_VALID_CFG_ACTION_OPS.begin(), _VALID_CFG_ACTION_OPS.end());
}

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

std::string FileParser::ToString()
{
    std::string retval = "IO:\n";
    for (auto const & result : _ioDirections)
    {
        retval += result.first + "\t:\t" + result.second + "\n";
    }

    retval += "\nOps:\n";

    for (auto const & result : _fileOperations)
    {
        retval += result.first + "\t:\t" + result.second + "\n";
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

bool FileParser::validConfigOperation(std::string op)
{
    return (_VALID_CFG_OPS.count(op) > 0);
}

bool FileParser::validConfigIoOperation(std::string op)
{
    return (_VALID_CFG_IO_OPS.count(op) > 0);
}

bool FileParser::validConfigActionOperation(std::string op)
{
    return (_VALID_CFG_ACTION_OPS.count(op) > 0);
}