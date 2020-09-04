#pragma once

#include "ArgParser.hpp"

class Parser
{

public:
    Parser(int argc, char ** argv);
    ~Parser();

    ArgParser & CliArgs() const;

private:
    std::shared_ptr<ArgParser> _ap;

};