#include "Parser.hpp"

Parser::Parser(int argc, char ** argv)
{
    _ap = std::unique_ptr<ArgParser>(new ArgParser(argc, argv)); 
    _cp = std::unique_ptr<ConfigParser>(new ConfigParser((*_ap)["config"].as<std::string>()));
}

Parser::~Parser(){}

ArgParser & Parser::Cli() const
{
    return *_ap;
}

ConfigParser & Parser::Cfg() const
{
    return *_cp;
}
