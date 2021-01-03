#pragma once

#include "GarrisonGlobals.hpp"
#include <filesystem>
#include <string>

struct FileKey
{
    Garrison::OperationType op;
    std::filesystem::path path;

    bool operator < (const FileKey & rhs) const
    {
        if (op != rhs.op) return op < rhs.op;
        return (path.compare(rhs.path) < 0);
    }

    bool operator == (const FileKey & rhs) const
    {
        return (op != rhs.op && (path.compare(rhs.path) == 0));
    }
};

class File
{
    public:

        bool operator < (const File & rhs) const
        {
            return _fk < rhs._fk;
        }

        File(std::string op, std::string path);

        void execute(bool force = false);
        void setDestination(std::string dest);
        std::string toString();
        Garrison::OperationType operation();
        std::filesystem::path path();

    private:

        friend class FileList;

        void copy(bool force = false);
        void link(bool force = false);
        void remove(bool force = false);

        FileKey _fk;
        std::filesystem::path _dest;

};
