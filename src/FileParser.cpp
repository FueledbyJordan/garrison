#include "FileParser.hpp"

FileParser::FileParser(const std::string & configFilePath) : _configFilePath(configFilePath)
{
    this->Read();
}

FileParser::~FileParser(){}

void FileParser::Read()
{
    //TODO: check if file exists, and it has read permissions
        // if yes, then read the file
        // do error handling
}