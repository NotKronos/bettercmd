#include "term.h"
#include <iostream>
#include <filesystem>
#include <windows.h>
#include <lmcons.h>
#include <string>

namespace filesystem = std::filesystem;

std::string Terminal::wd() {
	return filesystem::current_path().string();
}

std::string Terminal::username() {
	TCHAR username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	if (!GetUserName(username, &username_len)) {
		std::cout << "ERROR: Cannot get username";
		exit(0);
	}
	return username;
}

std::string Terminal::hostname() {
	TCHAR  infoBuf[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD  bufCharCount = MAX_COMPUTERNAME_LENGTH + 1;
	if (!GetComputerName(infoBuf, &bufCharCount)) {
		std::cout << "ERROR: Cannot get hostname";
		exit(0);
	}
	return infoBuf;
}

void Terminal::prompt() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::string cwd = wd();
	cwd.erase(cwd.begin(), cwd.begin() + 2);
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << username() + "@" + hostname() + ":";
	SetConsoleTextAttribute(hConsole, 9);
	std::cout << cwd + " $ ";
	SetConsoleTextAttribute(hConsole, 15);
}

std::string Terminal::command() {
	std::string command;
	std::getline(std::cin, command);
	return command;
}