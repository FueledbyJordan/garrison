#include "File.hpp"
#include <iostream>
#include "Utilities.hpp"

File::File(std::string op, std::string path)
{

    Utilities::to_lower(op);

    //TODO: Only remove outer if no alphanumeric chars are outside
    Utilities::remove_all(op, '"');

    if (op.compare("link") == 0)
    {
        _fk.op = Garrison::LINK;
    } else if (op.compare("exclude") == 0)
    {
        _fk.op = Garrison::EXCLUDE;
    } else if (op.compare("copy") == 0)
    {
        _fk.op = Garrison::COPY;
    } else
    {
        _fk.op = Garrison::NO_OP;
    }

    this->_fk.path = std::filesystem::path(path);
}

void File::execute(bool force)
{
    switch (_fk.op)
    {
        case Garrison::LINK:
            link(force);
            break;
        case Garrison::COPY:
            copy(force);
            break;
        case Garrison::EXCLUDE:
            remove(force);
            break;
    }
}

void File::setDestination(std::string dest)
{
    std::string abs_src_path = Utilities::GetAbsolutePath(_fk.path);
    std::string abs_dest_path = Utilities::BuildOutputPath(abs_src_path, Utilities::GetAbsolutePath(dest));
    std::filesystem::path target = std::filesystem::path(abs_dest_path);

    _dest = target;
}

std::string File::toString()
{
    std::string retVal = _fk.op == Garrison::EXCLUDE ?
        Garrison::OpToString.at(_fk.op) + ":\t" + _fk.path.string() :
        Garrison::OpToString.at(_fk.op) + ":\t" + _fk.path.string() + "\t->\t" + _dest.string();

    return retVal;
}

Garrison::OperationType File::operation()
{
    return _fk.op;
}

std::filesystem::path File::path()
{
    return _fk.path;
}

void File::copy(bool force)
{
    Utilities::Copy(_fk.path.string(), _dest.string(), force);
}

void File::link(bool force)
{
    Utilities::Link(_fk.path.string(), _dest.string(), force);
}

void File::remove(bool force)
{
    Utilities::Delete(_fk.path.string());
}
