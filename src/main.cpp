#include "GarrisonGlobals.hpp"
#include "Parser.hpp"

int main(int argc, char** argv)
{
    std::unique_ptr<Parser> parser = std::unique_ptr<Parser>(new Parser(argc, argv));

	std::cout << "Config:" << std::endl;
	std::cout << parser->Cfg().ToString() << std::endl;

	std::cout << "Command Line Options:" << std::endl;
	std::cout << parser->Cli().ToString() << std::endl;

    return Garrison::NO_ERR;
}
