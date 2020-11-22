#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class ParserBase
{

public:
    ParserBase();
    ~ParserBase();
    virtual void Read() = 0;
    virtual std::unordered_map<std::string, std::string> IoDirections() = 0;
    virtual std::vector<std::pair<std::string, std::string>> FileOperations() = 0;

protected:

private:

};