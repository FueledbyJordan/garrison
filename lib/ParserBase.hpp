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

    std::string ToString();
    std::unordered_map<std::string, std::string> IoDirections();
    std::vector<std::pair<std::string, std::string>> FileOperations();

protected:

	//TODO: Can possibly convert these two structures to an unordered_multimap, and then they're redundant
    std::unordered_map<std::string, std::string> _ioDirections;
    std::vector<std::pair<std::string, std::string>> _fileOperations;

private:

};
