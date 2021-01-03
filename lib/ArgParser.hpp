#pragma once

#include "ParserBase.hpp"

#include <cxxopts.hpp>
#include <memory>
#include <string>
#include <vector>

class ArgParser : public ParserBase
{

public:
    ArgParser(int argc, char ** argv);
    ~ArgParser();

    std::string toString() override;

    bool force();
    bool dryRun();

private:

    void read() override;

    void printHelpMessage();

    std::shared_ptr<cxxopts::Options> _opts;
    std::shared_ptr<cxxopts::ParseResult> _args;

    std::vector<std::string> _links;
    std::vector<std::string> _copies;
    std::vector<std::string> _excludes;

    bool _force = false;
    bool _dryRun = false;

    int _argc = 0;
    char ** _argv = nullptr;

};
