#pragma once

#include "ParserBase.hpp"
#include <cxxopts.hpp>
#include <memory>

class ArgParser : public ParserBase
{

public:
    ArgParser(int argc, char ** argv);
    ~ArgParser();
    void Read() override;

private:

    void printHelpMessage();

    std::shared_ptr<cxxopts::Options> _opts;// = nullptr;
    std::shared_ptr<cxxopts::ParseResult> _args;// = nullptr;

    int _argc = 0;
    char ** _argv = nullptr;

};