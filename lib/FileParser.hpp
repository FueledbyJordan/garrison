#pragma once

#include "ParserBase.hpp"
#include <string>

class FileParser : public ParserBase
{

public:
    FileParser(const std::string & configFilePath);
    ~FileParser();
    void Read() override;

private:
    std::string _configFilePath;
};