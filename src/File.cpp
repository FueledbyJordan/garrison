#include "File.hpp"
#include "Utilities.hpp"
#include <iostream>

File::File(std::string source_path, std::string target_path, Garrison::OPERATION_TYPE operation)
{
    if (Utilities::FileExists(source_path) && Utilities::UserHasReadPermissions(source_path))
    {
        _sourcePath = source_path;
    } else
    {
        // skip this file
        _op = Garrison::NO_OP;
        //TODO: Add logging about why this file was missed.
        //TODO: Look into using Garrison::ERR_TYPES or maybe making Garrison::WARN_TYPES

        return;
    }

    if(!Utilities::FileExists(target_path))
    {
        _targetPath = target_path;
    }

    _op = operation;
}

File::~File()
{

}

void File::Execute()
{
    switch (_op)
    {
        case Garrison::NO_OP:
            //do something
            break;
        case Garrison::LINK:
            //symlink file (use Utilities::link)
            break;
        case Garrison::COPY:
            //copy file (use Utilities::copy)
            break;
        default:
            break;
    }
}