#pragma once

#include <iostream>
#include <string>

class ConfigGenerator
{

public:
	static void Generate();

private:
	static const std::string _config;

	ConfigGenerator(){};
	~ConfigGenerator(){};

};
