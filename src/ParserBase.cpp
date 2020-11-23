#include "ParserBase.hpp"

ParserBase::ParserBase(){}
ParserBase::~ParserBase(){}

std::unordered_map<std::string, std::string> ParserBase::IoDirections()
{
    return _ioDirections;
}

std::vector<std::pair<std::string, std::string>> ParserBase::FileOperations()
{
    return _fileOperations;
}

std::string ParserBase::ToString()
{
    std::string retval = "\tIO:\n";
    for (auto const & result : _ioDirections)
    {
        retval += "\t\t" + result.first + "\t:\t" + result.second + "\n";
    }

    retval += "\n\tOps:\n";

    for (auto const & result : _fileOperations)
    {
        retval += "\t\t" + result.first + "\t:\t" + result.second + "\n";
    }

    return retval;
}

