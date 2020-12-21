#include "ParserBase.hpp"

ParserBase::ParserBase(){}

ParserBase::~ParserBase(){}

std::string ParserBase::ToString()
{
    std::string retval = "\tSettings:\n";
    retval += "\t\tConfig Path:\t:\t" +  _configFilePath + "\n";
    retval += "\t\tInput Path: \t:\t" +  _input + "\n";
    retval += "\t\tOutput Path:\t:\t" +  _output + "\n";

    retval += "\n\tFile Operations:\n";
    for (auto i : _links)
    {
        retval += "\t\tlink\t:\t" + i + "\n";
    }
    for (auto c : _copies)
    {
        retval += "\t\tcopy\t:\t" + c + "\n";
    }
    for (auto e : _excludes)
    {
        retval += "\t\texclude\t:\t" + e + "\n";
    }

    return retval;
}

std::string ParserBase::ConfigFilePath()
{
    return _configFilePath;
}

std::string ParserBase::Input()
{
    return _input;
}

std::string ParserBase::Output()
{
    return _output;
}

std::vector<std::string> ParserBase::Links()
{
    return _links;
}

std::vector<std::string> ParserBase::Copies()
{
    return _copies;
}

std::vector<std::string> ParserBase::Excludes()
{
    return _excludes;
}
