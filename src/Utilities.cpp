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

void Utilities::remove_all(std::string &s, char c)
{
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
}

void Utilities::Copy(const std::string & srcPath, const std::string & destPath, bool force)
{
    std::string abs_src_path = GetAbsolutePath(srcPath);
    std::string abs_dest_path = BuildOutputPath(abs_src_path, GetAbsolutePath(destPath));
    std::filesystem::path copyTarget = std::filesystem::path(abs_dest_path);

    if (!FileExists(abs_src_path) || !UserHasReadPermissions(abs_src_path))
    {
        std::cout << "Could not copy " << abs_src_path << " because it does not exist or you do not have permissions." << std::endl;
        return;
    }

    if (!UserHasWritePermissions(GetAbsolutePath(destPath)))
    {
        std::cout << "Could not copy to " << abs_dest_path << " because you do not have permissions." << std::endl;
        return;
    }

    if ((FileExists(abs_dest_path) && ! force)) // TODO: add or if directory isn't writeable
    {
        std::cout << "Could not copy to " << abs_dest_path << " because it already exists." << std::endl;
        return;
    }

    std::filesystem::copy_options opts = force ? std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
        : std::filesystem::copy_options::skip_existing | std::filesystem::copy_options::recursive;

    std::cout << std::filesystem::path(abs_src_path) << "\t->\t" << copyTarget << std::endl;
    std::filesystem::copy(std::filesystem::path(abs_src_path), copyTarget, opts);
}

void Utilities::Link(const std::string & srcPath, const std::string & destPath, bool force)
{
    std::string abs_src_path = GetAbsolutePath(srcPath);
    std::filesystem::path linkTarget = std::filesystem::path(destPath);

    if (!FileExists(abs_src_path) || !UserHasReadPermissions(abs_src_path))
    {
        std::cout << "Could not link " << abs_src_path << " because it does not exist or you do not have permissions." << std::endl;
        return;
    }

    if (!UserHasWritePermissions(GetAbsolutePath(destPath)))
    {
        std::cout << "Could not link to " << linkTarget.string() << " because it you do not have permissions." << std::endl;
        return;
    }

    if ((FileExists(linkTarget.string()) && ! force)) // TODO: add or if directory isn't writeable
    {
        std::cout << "Could not link to " << linkTarget.string() << " because it already exists." << std::endl;
        return;
    }

    if (std::filesystem::exists(linkTarget) && force)
        std::filesystem::remove(std::filesystem::path(linkTarget));

    std::cout << std::filesystem::path(abs_src_path) << "\t->\t" << linkTarget << std::endl;

    std::filesystem::create_symlink(std::filesystem::path(abs_src_path), linkTarget);
}

void Utilities::Delete(const std::string & path)
{
    std::string abs_path = GetAbsolutePath(path);

    if (!FileExists(abs_path))
        return;

    if(!UserHasWritePermissions(abs_path))
        return;

    std::filesystem::is_directory(abs_path) ? std::filesystem::remove_all(std::filesystem::path(abs_path))
        : std::filesystem::remove(std::filesystem::path(abs_path));
}

std::string Utilities::FixDots(const std::string & path)
{
    //TODO: Test this well
    std::string subbed_path = std::regex_replace(path, std::regex("\\/\\.\\/"), "/");
    subbed_path = std::regex_replace(subbed_path, std::regex("\\/\\.$"), "");
    subbed_path = std::regex_replace(subbed_path, std::regex("\\/[A-Za-z0-9_]*\\/\\.\\."), "");
    return subbed_path;
}

std::string Utilities::BuildOutputPath(const std::string & inputPath, const std::string & outputPath)
{
    std::string inputFile = GetFileName(inputPath);
    std::string absOutputPath = GetAbsolutePath(outputPath);

    return absOutputPath + "/" + inputFile;
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

    return FixDots(std::filesystem::absolute(subbed_path).string());
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
