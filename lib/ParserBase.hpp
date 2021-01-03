#pragma once

#include "FileList.hpp"
#include <string>

class ParserBase
{

public:
    ParserBase();
    ~ParserBase();
    virtual std::string toString();

    std::string configFilePath();
    std::string input();
    std::string output();

    FileList fileList();

protected:

    virtual void read() = 0;

    std::string _configFilePath;
    std::string _input = ".";
    std::string _output = "..";

    FileList _fileList;
};
