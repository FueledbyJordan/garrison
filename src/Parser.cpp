#include "Parser.hpp"
#include "GarrisonGlobals.hpp"
#include "Utilities.hpp"

Parser::Parser(int argc, char ** argv)
{
    _ap = std::unique_ptr<ArgParser>(new ArgParser(argc, argv));
    _cp = std::unique_ptr<ConfigParser>(new ConfigParser(_ap->configFilePath()));

    read();
    execute();
}

Parser::~Parser(){}

void Parser::read()
{
    _input  = !_ap->input().empty() ? _ap->input() : _cp->input();
    _output = !_ap->output().empty() ? _ap->output() : _cp->output();

    if (_input.empty() || _output.empty()) exit(Garrison::CLI_ARG_ERR);

    _force = _ap->force();
    _dryRun = _ap->dryRun();

    _fileList = _cp->fileList() + _ap->fileList();
    _fileList.setDestination(_output);
}

void Parser::execute()
{
    if (_dryRun)
    {
        //TODO: PRINT A PRETTY TREE WITH ALL THE FILES
        std::cout << toString() << std::endl;
        return;
    }

    _fileList.execute(_force);
}

std::string Parser::toString()
{
    std::string result = _cp->toString() + "\n" + _ap->toString();
    return result;
}
