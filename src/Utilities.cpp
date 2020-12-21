#include "Utilities.hpp"
#include <utility>
#include <algorithm>
#include <filesystem>
#include <cstdlib>
#include <regex>

#include <iostream>

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

void Utilities::to_lower(std::string &s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
}

void Utilities::Copy(const std::string & srcPath, const std::string & destPath, bool force)
{
    if (!(FileExists(srcPath) && UserHasReadPermissions(srcPath)))
        return;

    if (!(FileExists(destPath) && std::filesystem::is_directory(destPath) && UserHasWritePermissions(destPath)))
        return;

    std::filesystem::copy_options opts = force ? std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
        : std::filesystem::copy_options::skip_existing | std::filesystem::copy_options::recursive;

    std::filesystem::copy(std::filesystem::path(srcPath), std::filesystem::path(destPath), opts);
}

void Utilities::Link(const std::string & srcPath, const std::string & destPath, bool force)
{
    if (!(FileExists(srcPath) && UserHasReadPermissions(srcPath)))
        return;

    if (!(FileExists(destPath) && std::filesystem::is_directory(destPath) && UserHasWritePermissions(destPath)))
        return;

    std::filesystem::path linkTarget = std::filesystem::path(destPath);

    if (std::filesystem::is_directory(std::filesystem::path(srcPath)))
    {
        std::string file = GetFileName(srcPath);
        linkTarget /= std::filesystem::path(file);
    }

    if ((std::filesystem::exists(linkTarget.string()) && force) || !std::filesystem::exists(linkTarget))
        std::filesystem::create_symlink(std::filesystem::path(srcPath), linkTarget);
}

void Utilities::Delete(const std::string & path)
{
    if (!FileExists(path))
        return;

    if(!UserHasWritePermissions(path))
        return;

    std::filesystem::is_directory(path) ? std::filesystem::remove_all(std::filesystem::path(path))
        : std::filesystem::remove(std::filesystem::path(path));
}

std::string Utilities::GetAbsolutePath(const std::string & path)
{
    std::string subbed_path = std::regex_replace(path, std::regex("^~\\/"), "$HOME/");
    std::smatch match;
    while (std::regex_search(subbed_path, match, std::regex("\\$[A-Za-z0-9_]*")))
    {
        std::string env_var = match.str().substr(1, match.str().length() - 1);
        subbed_path.replace(match.position(), match.length(), std::getenv(env_var.c_str()));
    }

    return std::filesystem::absolute(subbed_path).string();
}

std::string Utilities::GetFileName(const std::string & path)
{
    return std::filesystem::path(path).filename().string();
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
