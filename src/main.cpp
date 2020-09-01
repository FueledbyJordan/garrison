#include "ArgParser.hpp"

int main(int argc, char** argv)
{
    std::unique_ptr<ArgParser> ap = std::unique_ptr<ArgParser>(new ArgParser(argc, argv));

    return 0;
}