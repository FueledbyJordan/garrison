#include "GarrisonGlobals.hpp"
#include "Parser.hpp"

int main(int argc, char** argv)
{
    std::unique_ptr<Parser> parser = std::unique_ptr<Parser>(new Parser(argc, argv));

    //std::cout << parser->ToString() << std::endl;
    for (auto a : parser->FileOperations())
    {
        std::cout << a.first << "\t:\t" << a.second << std::endl;
    }

    return Garrison::NO_ERR;
}
