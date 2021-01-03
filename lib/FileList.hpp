#pragma once

#include <algorithm>
#include <map>
#include <string>
#include "File.hpp"

class FileList
{
    public:
        FileList();

        void insert(File f);

        void execute(bool force);
        void setDestination(std::string dest);
        std::string toString();

        inline FileList operator +(const FileList & other)
        {
            FileList result;

            //TODO: Figure out what to do with excludes
            std::merge(_files.begin(), _files.end(),
                other._files.begin(), other._files.end(),
                std::inserter(result._files, result._files.begin()));

            return result;
        }

    private:

        std::map<FileKey, File> _files;

};
