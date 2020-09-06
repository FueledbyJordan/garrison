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

    //TODO: implement these
    std::unordered_map<std::string, std::string> IoDirections() override{};
    std::vector<std::pair<std::string, std::string>> FileOperations() override{};

    std::string ToString();

    const cxxopts::OptionValue & operator[](const std::string & option) const;

private:

    void printHelpMessage();

    std::shared_ptr<cxxopts::Options> _opts;
    std::shared_ptr<cxxopts::ParseResult> _args;

    int _argc = 0;
    char ** _argv = nullptr;

};