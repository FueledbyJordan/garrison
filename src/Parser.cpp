#include "Parser.hpp"

Parser::Parser(int argc, char ** argv)
{
    _ap = std::unique_ptr<ArgParser>(new ArgParser(argc, argv)); 
    _fp = std::unique_ptr<FileParser>(new FileParser((*_ap)["config"].as<std::string>()));
}

Parser::~Parser(){}

ArgParser & Parser::Cli() const
{
    return *_ap;
}

FileParser & Parser::Cfg() const
{
    return *_fp;
}