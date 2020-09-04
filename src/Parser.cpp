#include "Parser.hpp"

Parser::Parser(int argc, char ** argv)
{
    _ap = std::unique_ptr<ArgParser>(new ArgParser(argc, argv)); 
}

Parser::~Parser(){}

ArgParser & Parser::CliArgs() const
{
    return * _ap;
}