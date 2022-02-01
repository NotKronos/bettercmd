#include "commands.h"
#include <iostream>
#include <filesystem>
#include <Windows.h>

namespace filesystem = std::filesystem;

bool endsWith(std::string const& fullString, std::string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

void cd(int argc, const char* argv) {
	std::string path = filesystem::current_path().string();
	std::string argument(argv);
	if (argument.rfind("..", 0) == 0) {
		filesystem::current_path(argument);
	}
	else {
		filesystem::path location;
		location = filesystem::current_path() / ("C:" + argument);
		if (is_directory(location)) filesystem::current_path(location);
		else std::cout << "Location is not a folder" << std::endl;
	}
}
void ls() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::string path = filesystem::current_path().string();
	std::string file;
	for (const auto& entry : filesystem::directory_iterator(path)) {
		file = entry.path().string();
		file.erase(file.begin(), file.begin() + path.size() + 1);
		if (filesystem::is_directory(entry)) {
			SetConsoleTextAttribute(hConsole, 9);
			std::cout << file + "/" << std::endl;
		}
		else if (endsWith(file, ".exe")) {
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << file << std::endl;
		}
		else {
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << file << std::endl;
		}

	}
	SetConsoleTextAttribute(hConsole, 15);
}