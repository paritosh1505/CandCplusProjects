#include<iostream>
#include<string>
#include <cstdio>
#include<sstream>

#include<fstream>
bool isFilePresent(const std::string &fullpath) {
	FILE* file = nullptr;
	fopen_s(&file, fullpath.c_str(), "r");
	if (file) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}

	
}
std::string GetRequestFromFile(std::string documentRoot, std::string fileName) {
	std::string fullpath = documentRoot + "/" + fileName;
	std::string fileContent = "";
	if (isFilePresent(fullpath)) {
		std::ifstream fileContent(fullpath);
		std::stringstream buffferreadFile;
		buffferreadFile << fileContent.rdbuf();
		return buffferreadFile.str();
	}
	else {
		return "";
	}
}
