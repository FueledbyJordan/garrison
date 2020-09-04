#include "Parser.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    std::unique_ptr<Parser> parser = std::unique_ptr<Parser>(new Parser(argc, argv));

    std::cout << parser->CliArgs().ToString();

    return 0;
}