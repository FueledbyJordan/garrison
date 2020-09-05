#include "Utilities.hpp"
#include <utility>
#include <algorithm>
#include <sys/stat.h>

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
    struct stat buffer;   
    return (stat (filePath.c_str(), &buffer) == 0); 
}