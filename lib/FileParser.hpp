#pragma once

#include "ParserBase.hpp"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class FileParser : public ParserBase
{

public:
    FileParser(const std::string & configFilePath);
    ~FileParser();
    void Read() override;
    std::unordered_map<std::string, std::string> IoDirections() override;
    std::vector<std::pair<std::string, std::string>> FileOperations() override;

    std::string ToString();

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

	//TODO: Can possibly convert these two structures to an unordered_multimap, and then they're redundant
    std::unordered_map<std::string, std::string> _ioDirections;
    std::vector<std::pair<std::string, std::string>> _fileOperations;

};
