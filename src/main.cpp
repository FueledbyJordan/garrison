#include "Parser.hpp"

int main(int argc, char** argv)
{
    std::unique_ptr<Parser> parser = std::unique_ptr<Parser>(new Parser(argc, argv));

    return 0;
}