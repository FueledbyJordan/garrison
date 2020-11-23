#pragma once

#include "ArgParser.hpp"
#include "ConfigParser.hpp"

class Parser
{

public:
    Parser(int argc, char ** argv);
    ~Parser();

    ArgParser & Cli() const;
    ConfigParser & Cfg() const;

private:
    std::shared_ptr<ArgParser> _ap;
    std::shared_ptr<ConfigParser> _cp;

};
