#include "term.h"
#include "commands.h"
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <sstream>

namespace filesystem = std::filesystem;

int main() {
	Terminal term;
	while (true) {
		term.prompt();
		std::string command = term.command();
		if (command == "exit") {
			exit(0);
		}
		else if (command.rfind("cwd", 0) == 0) {
			std::vector <const char*> argv;
			command.erase(0, 4);
			std::string delimiter = " ";
			size_t pos = 0;
			std::string token;
			while ((pos = command.find(delimiter)) != std::string::npos) {
				token = command.substr(0, pos);
				command.erase(0, pos + delimiter.length());
				argv.push_back(token.c_str());
			}
			argv.push_back(command.c_str());
			cd(argv.size(), argv);
		}
		else if (command == "ls") {
			ls();
		}
		else if (command.rfind("makedir", 0) == 0) {
			try {
				std::vector <const char*> argv;
				command.erase(0, 7);
				std::string delimiter = " ";
				size_t pos = 0;
				std::string token;
				while ((pos = command.find(delimiter)) != std::string::npos) {
					token = command.substr(0, pos);
					command.erase(0, pos + delimiter.length());
					argv.push_back(token.c_str());
				}
				mkdir(argv.size(), argv);
			}
			catch (const std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
		else if (command == "help") {
			help();
		}
		else {
			system(command.c_str());
		}
	}
}