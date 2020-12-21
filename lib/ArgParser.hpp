#pragma once

#include "ParserBase.hpp"

#include <cxxopts.hpp>
#include <memory>
#include <string>

class ArgParser : public ParserBase
{

public:
    ArgParser(int argc, char ** argv);
    ~ArgParser();

    void Read() override;

    std::string ToString() override;

    bool Force();
    bool DryRun();

private:

    void printHelpMessage();

    std::shared_ptr<cxxopts::Options> _opts;
    std::shared_ptr<cxxopts::ParseResult> _args;

    bool _force = false;
    bool _dryrun = false;

    int _argc = 0;
    char ** _argv = nullptr;

};
