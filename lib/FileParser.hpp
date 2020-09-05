#pragma once

#include "ParserBase.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class FileParser : public ParserBase
{

public:
    FileParser(const std::string & configFilePath);
    ~FileParser();
    void Read() override;

    std::string ToString();

private:

    std::pair<std::string, std::string> parseLine(const std::string & line, unsigned int lineNumber);

    std::string _configFilePath;
    std::unordered_map<std::string, std::string> _parseResults;
    std::vector<std::pair<std::string, std::string>> _fileOperations;

};