#include "FileList.hpp"

FileList::FileList() { }

void FileList::insert(File f)
{
    _files.insert(std::pair<FileKey, File>(f._fk, f));
}

void FileList::execute(bool force)
{
    for (auto & f : _files)
        f.second.execute(force);
}

void FileList::setDestination(std::string dest)
{
    for (auto & f : _files)
        f.second.setDestination(dest);
}

std::string FileList::toString()
{
    std::string retval;
    retval += "\n\tFile Operations:\n";

    for (auto & f : _files)
        retval += "\t\t" + f.second.toString() + "\n";

    return retval;
}
