#ifndef DMGMT_H
#define DMGMT_H
#include<iostream>
#include<vector>
#include<filesystem>
namespace fs = std::filesystem;
class DirectoryMgmt {
public:
	void CreteDirectory(std::string &Path, std::string &dirName) {
		std::string PathFinal = Path +"\\"+ dirName;
		std::error_code eCode;
		if (std::filesystem::create_directory(PathFinal)) {
			std::cout << "Directory Created Succesfully\n";
		}
		else {
			std::cerr << "Failed to create directory: eother directory is already presetn or there is some another error " << "\n";
		}
	}
	std::vector<std::string> GetAllDirectoryName(std::string directoryPath) {
		std::vector<std::string> directoryName;

		try {
			if ( fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
				for (const auto& filename : fs::directory_iterator(directoryPath)) {
					

					directoryName.push_back(filename.path().filename().string());
		
				}
				}
			
		}
		catch (fs::filesystem_error& error) {
			std::cerr << "Getting error" << error.code();
		}
		return directoryName;
		
	}

	
	

	
};

#endif 
