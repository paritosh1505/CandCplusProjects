// FileManagemnt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "DirectoryMgmt.h"
#include <vector>
#include "FileMgmt.h"
#include <algorithm>

int main()
{
    DirectoryMgmt dm;
    FileManagement fm;
    std::string choiceType;
    std::vector<std::string> allDirName;
    bool isContinue = true;
    std::string PathLocation = "D:\FileManagement";
    if (!std::filesystem::is_directory(PathLocation)) {
        if (std::filesystem::create_directory(PathLocation)) {
            std::cout << "Root Directory Created Succesfully\n";
        }
        else {
            std::cout << "Error while creating directory\n";
            return 1;
        }
    }
    else {
        std::cout << "Root Directory is already present\n";
    }
    while (isContinue) {
        std::string dirChoice;
        std::string dirName;
        std::string fileChoice;
        std::cout << "Do you want to create File or directory(Enter f for file/Enter d for direcotry): ";
        std::cin >> choiceType;
        if (choiceType == "d") {
            std::cout << "Enter directory name:";
            std::cin >> dirName;

            dm.CreteDirectory(PathLocation, dirName);
            
        }
        else if (choiceType == "f") {
            allDirName = dm.GetAllDirectoryName(PathLocation);
            std::cout << "Where you want to add File \n 1- root folder \n 2- inside Directory";
            std::cin >> fileChoice;
            if (fileChoice == "1") {
                //this will be same operation which is performed in later code hence ignoring it.
            }
            else if (fileChoice == "2") {
                std::string dirName;
                std::string filename;
                std::string fileOption;
                std::string filePath;
                std::string fileLocation;
                std::cout << "Enter directory name where you want to do file operation\n";
                std::cin >> dirName;
               
                auto iterarot = std::find(allDirName.begin(), allDirName.end(), dirName);
                if (iterarot == allDirName.end()) {
                    std::cout << "Invalid directory";
                    return -1;
                }
                else {
                    fileLocation = PathLocation + "\\" + dirName;
                    std::cout << "Welcome to file operation.Now tell me what operation you want to perform in he file\n";
                    std::cout << " 1. Add the content in the file\n 2. Delete the file\n 3. Update the file\n";
                    std::cin >> fileOption;
                    if (fileOption == "1") {
                        std::cout << "Enter file name which you want to add\n";
                        std::cin >> filename;
                        fm.createFile(fileLocation, filename);
                        filePath = fileLocation + "\\" + filename;
                        fm.AddContentFile(filePath);
                    }
                    else if (fileOption == "2") {
                        std::string filetoDelete = "";
                        std::cout << "Name the file you want to delete:\n";
                        std::cin >> filetoDelete;
                        filePath = fileLocation +"\\"+filetoDelete+".txt";
                        fm.DelteFilePermanently(&filePath);
                    }
                    else if (fileOption == "3") {
                        std::string filetoUpdate = "";
                        std::string updateOption = "";
                        std::cout << "Name the file you want to update:\n";
                        std::cin >> filetoUpdate;
                        std::cout << "1. want to override entire content\n 2.Adding new content at the end of file\n 3. Update particular line in existing file\n";
                        std::cin >> updateOption;
                        std::string filepath = fileLocation + "\\" + filetoUpdate + ".txt";
                        if (updateOption == "1") {
                            fm.UpdateEntireFileContent(filepath);
                        }
                        else if (updateOption == "2") {
                            fm.AppendLastFileContent(filepath);
                        }
                        else if (updateOption == "3") {
                           int lineNumber;
                           std::string contentToadd;
                            std::cout << "Enter line no you want to update";
                            std::cin >> lineNumber;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Enter the content which you want to add";
                            std::getline(std::cin, contentToadd);
                            fm.UpdateSpecificLineFileContent(filepath, lineNumber,contentToadd);

                        }
                        else {
                            std::cout << "Invalid option for update";
                            return 1;
                        }
                        
                        
                    }


                }
            }
            else {
                std::cout << "Invalid Choice enter either 1 or 2";
            }
            isContinue = false;
        }
        else {
            std::cout << "Not a valid option - Enter f for file/Enter d for direcotry\n";
        }
    }
    std::cout << "Hello World!\n";
    return 2;
}

