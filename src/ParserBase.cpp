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
    std::string retval = "IO:\n";
    for (auto const & result : _ioDirections)
    {
        retval += result.first + "\t:\t" + result.second + "\n";
    }

    retval += "\nOps:\n";

    for (auto const & result : _fileOperations)
    {
        retval += result.first + "\t:\t" + result.second + "\n";
    }

    return retval;
}

