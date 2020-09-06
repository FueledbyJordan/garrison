#pragma once
#include <string>

class Utilities
{

public:
    static void ltrim (std::string &s);
    static void rtrim (std::string &s);
    static void trim (std::string &s);
    static bool FileExists(const std::string & filePath);

    static bool UserHasReadPermissions(const std::string & path);
    static bool GroupHasReadPermissions(const std::string & path);
    static bool OtherHasReadPermissions(const std::string & path);
    static bool UserHasWritePermissions(const std::string & path);
    static bool GroupHasWritePermissions(const std::string & path);
    static bool OtherHasWritePermissions(const std::string & path);
    static bool UserHasExecutePermissions(const std::string & path);
    static bool GroupHasExecutePermissions(const std::string & path);
    static bool OtherHasExecutePermissions(const std::string & path);
private:
    Utilities(){};
    ~Utilities(){};
};