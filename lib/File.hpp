#pragma once

#include "GarrisonGlobals.hpp"
#include <string>

class File
{

public:
    File(std::string source_path, std::string target_path, Garrison::OPERATION_TYPE operation);
    ~File();

    void Execute();

private:
    std::string _sourcePath;
    std::string _targetPath;
    Garrison::OPERATION_TYPE _op;

};