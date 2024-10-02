#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<regex>
void parseWebReq(std::string request,std::string &method,std::string &hostdetail,
	std::string &useragent,std::map<std::string,std::string> &connection) {
	std::istringstream reqBody(request);
	std::string reqtraversal;
	std::getline(reqBody, method);

	while (std::getline(reqBody, reqtraversal)) {
		size_t colonposistion = reqtraversal.find(":");
		std::regex quote ("\"");
		if (colonposistion != std::string::npos) {
			std::string keyval = reqtraversal.substr(0, colonposistion);
			keyval = std::regex_replace(keyval, quote, "");
			std::string entryval = reqtraversal.substr(colonposistion + 1, reqtraversal.size());
			entryval = std::regex_replace(entryval, quote, "");
			connection[keyval] = entryval;
			//std::cout << "*********"<<keyval << connection[keyval] << "\n";
			
		}
	
	}

}