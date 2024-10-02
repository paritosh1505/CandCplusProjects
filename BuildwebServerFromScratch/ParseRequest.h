#ifndef Parsing_req
#define Parsing_req

#include<string>
#include<map>
void parseWebReq(std::string request,std::string &methodType,std::string &hostDetail,std::string &useragent,std::map<std::string,std::string> &connection);

#endif // !Parsing_req
