#include "Utilities.hpp"
#include <utility>
#include <algorithm>
#include <filesystem>

void Utilities::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void Utilities::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void Utilities::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

bool Utilities::FileExists(const std::string & filePath)
{
    return std::filesystem::exists(std::filesystem::path(filePath));
}

bool Utilities::UserHasReadPermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::owner_read);
}

bool Utilities::GroupHasReadPermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::group_read);
}

bool Utilities::OtherHasReadPermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::others_read);
}

bool Utilities::UserHasWritePermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::owner_write);
}

bool Utilities::GroupHasWritePermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::group_write);
}

bool Utilities::OtherHasWritePermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::others_write);
}

bool Utilities::UserHasExecutePermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::owner_exec);
}

bool Utilities::GroupHasExecutePermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::group_exec);
}

bool Utilities::OtherHasExecutePermissions(const std::string & path)
{
    return (bool)(std::filesystem::status(path).permissions() & std::filesystem::perms::others_exec);
}