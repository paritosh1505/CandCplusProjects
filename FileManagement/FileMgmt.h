#ifndef FMGMT_H
#define FMGMT_H
#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
class FileManagement {
	std::ofstream fileval;
	
public:
	void createFile(std::string filePath, std::string fileName) {
		std::string fileLocation = filePath + "\\" + fileName+".txt";
		fileval.open(fileLocation);
		fileval.close();
	}
	void AddContentFile(std::string filepath) {
		//add the content to the file if there is already some content in the file append it
		//std::ofstream fileval;
		std::string fileLocation = filepath + ".txt";
		std::cout << fileLocation;
		fileval.open(fileLocation, std::iostream::out | std::iostream::app);
		if (fileval.is_open()) {
			std::string userEntry;
			std::cout << "******Enter your content in the file. Type (exit) if you want to close the file********\n";
			while (true) {
				std::getline(std::cin, userEntry);
				if (userEntry == "exit") {
					break;
				}
				fileval << userEntry << "\n";

			}
		}
		
		fileval.close();
		std::cout << "Content is added to the file";
	}

	void DelteFilePermanently(std::string *filepath) {
		const char *remoPointer = filepath->c_str();
		if (remove(remoPointer) == 0) {
			std::cout << "File deleted Successfully";
		}
		else {
			std::cerr << "File is not present";
			return;
		}
	}
	void UpdateEntireFileContent(std::string filepath) {
		fileval.open(filepath, std::ios::out);
		if (fileval.is_open()) {
			std::string content;
			std::cout << "Type (exit) for exitiing the file\n";
			while (true)
			{
				std::getline(std::cin, content);
				
				if (content == "exit") {
					break;
				}
				fileval << content <<"\n";
			}
		}
		else {
			std::cout << "Error in the file.";
			return;
		}
		fileval.close();
	}
	void AppendLastFileContent(std::string filepath) {
		fileval.open(filepath, std::ios::app);
		if (fileval.is_open()) {
			std::cout << "Add the content of file. Type (exit) for closing the file file content";
			std::string content;
			while (true) {
				std::getline(std::cin, content);
				if (content == "exit") {
					break;
				}
				fileval << content << "\n";
			}
		}
		else {
			std :: cout << "Erro ehile opening the file";
		}
		fileval.close();
	}
	void UpdateSpecificLineFileContent(std::string filepath,int lineNumber,std::string contenttoadd) {
		std::ifstream fiileEntry(filepath);
		
		int linecount=0;
		//fileval.open(filepath, std::ios::app | std::ios::out);
		if (fiileEntry.is_open()) {
			std::string lineval;
			while (std::getline(fiileEntry,lineval)) {
				linecount++;
			}
			fiileEntry.clear();
			fiileEntry.seekg(0, std::ios::beg);
			if (lineNumber <= linecount) {
				int appendline = 0;
				std::string content;
				std::string datatoUpdate;
				std::stringstream bufferdata;
				while (std::getline(fiileEntry, content)) {
					if (appendline == lineNumber) {
						bufferdata << contenttoadd <<"\n";
						appendline++;
					}
					else {
						bufferdata << content<<"\n";
						appendline++;
					}
				}
				std::ofstream filetoupdate(filepath);
				if (filetoupdate.is_open()) {
					filetoupdate << bufferdata.str();
				}
				else {
					std::cout << "Failed to update the file";
				}
				filetoupdate.close();

			}
			else {
				std::cout << "Invalid line number to update . fie have less no of line";
				return;
			}
		}
		fiileEntry.close();

	}
};
#endif // !1
