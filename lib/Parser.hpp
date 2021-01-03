#pragma once

#include "ArgParser.hpp"
#include "ConfigParser.hpp"
#include "FileList.hpp"

#include <string>
#include <utility>

class Parser : public ParserBase
{

public:
    Parser(int argc, char ** argv);
    ~Parser();

private:
    std::shared_ptr<ArgParser> _ap;
    std::shared_ptr<ConfigParser> _cp;

    std::string toString() override;
    void read() override;

    void execute();
    void buildFileOperations();

    bool _force = false;
    bool _dryRun = false;

};
