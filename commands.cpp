#include "commands.h"
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <vector>

namespace filesystem = std::filesystem;

bool endsWith(std::string const& fullString, std::string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

void cd(int argc, std::vector<const char*> argv) {
	if (argc > 1) {
		std::cout << "Too many arguments" << std::endl;
		return;
	}
	else if (argc < 1) {
		std::cout << "Not enough arguments" << std::endl;
		return;
	}
	std::string path = filesystem::current_path().string();
	std::string argument(argv[0]);
	std::cout << argument << std::endl;
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

void mkdir(int argc, std::vector<const char*> argv) {
	if (argc < 2) {
		std::cout << "Not enough arguments" << std::endl;
	}
	else if (argc == 2) {
		if (filesystem::create_directory(argv[1])) {
			std::cout << "created directory: " << argv[1] << std::endl;
		}
		else {
			std::cout << "Cannot create directory: " << argv[1] << std::endl;
		}
	}
	else {
		for (int i = 1; i < argc; i++) {
			if (filesystem::create_directory(argv[i])) {
				std::cout << "created directory: " << argv[i] << std::endl;
			}
			else {
				std::cout << "Cannot create directory: " << argv[i] << std::endl;
			}
		}
	}
}

void rmdir(int argc, std::vector<const char*> argv) {
	bool rmAll = false;
	std::string recursive = "-R";
	if (argc < 2) {
		std::cout << "Not enough arguments" << std::endl;
	}
	else if (argc == 2) {
		try {
			if (filesystem::is_directory(argv[1])) {
				if (filesystem::remove(argv[1])) {
					std::cout << "Removed directory: " << argv[1] << std::endl;
				}
				else {
					std::cout << "Cannot remove directory: " << argv[1] << std::endl;
				}
			}
			else {
				std::cout << "Failed to remove " << argv[1] << " not a directory" << std::endl;
			}
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	else {
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], recursive.c_str()) == 0) {
				rmAll = true;
			}
			else if (rmAll == false) {
				try {
					if (filesystem::is_directory(argv[i])) {
						if (filesystem::remove(argv[i])) {
							std::cout << "Removed directory: " << argv[i] << std::endl;
						}
						else {
							std::cout << "Cannot remove directory: " << argv[i] << std::endl;
						}
					}
					else {
						std::cout << "Failed to remove " << argv[i] << " not a directory" << std::endl;
					}
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
				}
			}
			else if (rmAll == true && i == 2) {
				try {
					if (filesystem::is_directory(argv[i])) {
						if (filesystem::remove_all(argv[i])) {
							std::cout << "Removed directory: " << argv[i] << std::endl;
						}
						else {
							std::cout << "Cannot remove directory: " << argv[i] << std::endl;
						}
					}
					else {
						std::cout << "Failed to remove " << argv[i] << " Not a directory" << std::endl;
					}
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
				}
			}
		}
	}
}

void help() {
	std::cout << "ls" << std::endl;
	std::cout << "cwd [DIR]" << std::endl;
	std::cout << "makedir [DIR]" << std::endl;
	std::cout << "removedir [DIR]" << std::endl;
}