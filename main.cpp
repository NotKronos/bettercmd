#include "term.h"
#include "commands.h"
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>

namespace filesystem = std::filesystem;

int main() {
	Terminal term;
	while (true) {
		term.prompt();
		std::string command = term.command();
		if (command == "exit") {
			exit(0);
		}
		if (command.rfind("cwd", 0) == 0) {
			int counter = 1;
			std::string delimiter = " ";

			size_t pos = 0;
			std::string token;
			while ((pos = command.find(delimiter)) != std::string::npos) {
				token = command.substr(0, pos);
				command.erase(0, pos + delimiter.length());
				counter++;
			}
			if (counter > 2) {
				std::cout << "Too many arguments" << std::endl;
			}
			else if (counter< 2) {
				std::cout << "Not enough arguments" << std::endl;
			}
			else {
				cd(1, command.c_str());
			}
		}
		if (command == "ls") {
			ls();
		}
		else {
			system(command.c_str());
		}
	}
}