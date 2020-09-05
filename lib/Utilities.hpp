#pragma once
#include <string>

class Utilities
{

public:
    static void ltrim (std::string &s);
    static void rtrim (std::string &s);
    static void trim (std::string &s);
    static bool FileExists(const std::string & filePath);
private:
    Utilities(){};
    ~Utilities(){};
};