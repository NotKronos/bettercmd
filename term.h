#pragma once
#include <iostream>

class Terminal {
public:
	std::string binPath;

	std::string username();
	std::string hostname();
	std::string wd();

	void prompt();
	std::string command();
};