#include "Parser.hpp"
#include "GarrisonGlobals.hpp"
#include "Utilities.hpp"

Parser::Parser(int argc, char ** argv)
{
    _ap = std::unique_ptr<ArgParser>(new ArgParser(argc, argv));
    _cp = std::unique_ptr<ConfigParser>(new ConfigParser(_ap->ConfigFilePath()));

    _input  = !Cfg().Input().empty() ? Cfg().Input() : Cli().Input();
    _output = !Cfg().Output().empty() ? Cfg().Output() : Cli().Output();

    if (_input.empty() || _output.empty()) exit(Garrison::CLI_ARG_ERR);

    _force = Cli().Force();
    _dryRun = Cli().DryRun();
    BuildFileOperations();

    Execute();
}

Parser::~Parser(){}

void Parser::Execute()
{
    if (_dryRun)
    {
        //TODO: PRINT A PRETTY TREE WITH ALL THE FILES
        std::cout << ToString() << std::endl;
        return;
    }

    //TODO: SOMETHING WITH THE FILE LIST
    for (auto f : _fileOperations) {
        if (f.first.compare("Link") == 0)
        {
            Utilities::Link(f.second, _output, _force);
        } else if (f.first.compare("Copy") == 0)
        {
            Utilities::Copy(f.second, _output, _force);
        }
        //else if (f.first.compare("exclude"))
        //    Utilities::Delete(path);
    }
}

ArgParser & Parser::Cli() const
{
    return *_ap;
}

ConfigParser & Parser::Cfg() const
{
    return *_cp;
}

std::vector<std::pair<std::string, std::string>> Parser::FileOperations()
{
    return _fileOperations;
}

std::string Parser::ToString()
{
    std::string result = Cfg().ToString() + "\n" + Cli().ToString();
    return result;
}

//TODO: This is horribly inefficient... Fix the population of the fileOperations!
void Parser::BuildFileOperations()
{
    for (auto l : Cfg().Links())
    {
        _fileOperations.push_back(std::make_pair("Link", l));
    }

    //TODO: Optimize this O(n^2)
    for (auto c : Cfg().Copies())
    {
        bool is_exclude_in_copy = false;
        for (auto e : Cfg().Excludes())
        {
            if (e == c)
            {
                is_exclude_in_copy = true;
                break;
            }
        }

        for (auto e : Cli().Excludes())
        {
            std::cout << e << std::endl;
            if (e == c)
            {
                is_exclude_in_copy = true;
                break;
            }
        }

        if ( ! is_exclude_in_copy ) _fileOperations.push_back(std::make_pair("Copy", c));
    }

    for (auto l : Cli().Links())
    {
        _fileOperations.push_back(std::make_pair("Link", l));
    }

    //TODO: Optimize this O(n^2)
    for (auto c : Cli().Copies())
    {
        bool is_exclude_in_copy = false;
        for (auto e : Cli().Excludes())
        {
            if (e == c)
            {
                is_exclude_in_copy = true;
                break;
            }
        }

        if ( ! is_exclude_in_copy ) _fileOperations.push_back(std::make_pair("Copy", c));
    }

}
