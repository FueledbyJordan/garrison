#pragma once

#include "ArgParser.hpp"
#include "FileParser.hpp"

class Parser
{

public:
    Parser(int argc, char ** argv);
    ~Parser();

private:
    std::shared_ptr<ArgParser> _ap;
    std::shared_ptr<FileParser> _fp;

};