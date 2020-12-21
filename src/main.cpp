#include "GarrisonGlobals.hpp"
#include "Parser.hpp"

int main(int argc, char** argv)
{
    std::unique_ptr<Parser> parser = std::unique_ptr<Parser>(new Parser(argc, argv));
    std::cout << parser->ToString() << std::endl;

    return Garrison::NO_ERR;
}
