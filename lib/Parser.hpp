#pragma once

#include "ArgParser.hpp"
#include "FileParser.hpp"

class Parser
{

public:
    Parser(int argc, char ** argv);
    ~Parser();

    ArgParser & Cli() const;
    FileParser & Cfg() const;

private:
    std::shared_ptr<ArgParser> _ap;
    std::shared_ptr<FileParser> _fp;

};