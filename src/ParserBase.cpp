#include "ParserBase.hpp"

ParserBase::ParserBase(){}

ParserBase::~ParserBase(){}

std::string ParserBase::toString()
{
    std::string retval = "\tI/O Settings:\n";
    retval += "\t\tConfig Path:\t:\t" +  _configFilePath + "\n";
    retval += "\t\tInput Path: \t:\t" +  _input + "\n";
    retval += "\t\tOutput Path:\t:\t" +  _output + "\n";

    retval += _fileList.toString();

    return retval;
}

FileList ParserBase::fileList()
{
    return _fileList;
}

std::string ParserBase::configFilePath()
{
    return _configFilePath;
}

std::string ParserBase::input()
{
    return _input;
}

std::string ParserBase::output()
{
    return _output;
}
