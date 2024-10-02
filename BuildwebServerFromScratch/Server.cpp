#include<iostream>
#include<winsock2.h>
#include "ParseRequest.h"
#include "RequestHandling.h"
#include "DataBaseConnectivity.h"
#include<map>
#include<string>
#include<vector>
#include<sstream>
#pragma comment(lib,"WS2_32.lib")
std::vector<std::string> splitMethod(std::string reqMethod,char seprator) {
	std::vector<std::string> splitval;
	std::stringstream streamval(reqMethod);

	std::string strval;
	while (std::getline(streamval, strval, seprator)) {
		splitval.push_back(strval);
	}
	
	return splitval;
}
int main() {

	WSAData wsadata;
	SOCKET socketValue,clientAccept;
	char buffer[1024],buffer2[1024];
	struct sockaddr_in socketinfo,clientInfo ;
	int sizeClient = sizeof(clientInfo);
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		std::cout << "Error while initializing window socket DLL";
		WSACleanup();
		return 0;
	}
	//socket creation
	socketValue = socket(AF_INET, SOCK_STREAM, 0);

	//giving socket a identity which will helpful for socket binding

	socketinfo.sin_family = AF_INET;
	socketinfo.sin_addr.S_un.S_addr = INADDR_ANY;
	socketinfo.sin_port = htons(4040);
	
	//socket binding
	if (bind(socketValue, (struct sockaddr*)&socketinfo, sizeof(socketinfo))<0) {
		std::cout << "Socket binding failed";
		closesocket(socketValue);
		WSACleanup();
		return 0;
	}
	//now make the socket as listening socket so that socket is ready for listening the connection
	listen(socketValue, 3);
	//now socket is ready for incomiing request
	std::cout << "Watitng for client connection \n";
	clientAccept = accept(socketValue, (struct sockaddr*)&clientInfo, &sizeClient);
	if (clientAccept == INVALID_SOCKET) {
		std::cout << "Error while accepting the connction";
		closesocket(socketValue);
		WSACleanup();
		return 0;
	}
	
	int ClienMSg = recv(clientAccept, buffer, sizeof(buffer) - 1,0);
	if (ClienMSg == SOCKET_ERROR) {
		closesocket(clientAccept);
		closesocket(socketValue);
		std::cout << "Error while receiving the msg";
		return 0;
	}
	buffer[ClienMSg] = '\0';
	//std::cout << "Recieved Message\n"<<buffer;
	std::string methodType,hostDetail,uAgent;
	std::map<std::string, std::string> connectionDetail;
	parseWebReq(buffer,methodType,hostDetail,uAgent, connectionDetail);
	std::cout <<"********************************"<< connectionDetail["address"] << "\n";

	for ( auto& conn : connectionDetail) {
		std::cout << conn.first << "========>" << conn.second<<"\n";
	}
	std::vector<std::string> splitProps =  splitMethod(methodType,' ');
	std::cout << "Method:" << methodType << "\n";
	std::string httpversion = "HTTP/1.1";
	std::string documentRoot = "C:/Users/Lenovo/Downloads/";//web server generally have document root path from where they serve the file
	std::string responseBody = "";
	
	DataBase* db = new MySqlDatabase();
	db->connect();
	if (methodType.find("GET")!=std::string::npos) {
		std::cout << "***********"<<splitProps[0]<<"\n";
		std::string endpoint = splitProps[1];
		size_t fileext = endpoint.find_last_of(".");
		
		if (fileext != std::string :: npos) {
			//call
			//std::string fileLocation = documentRoot + "/" + endpoint;
			std::string ContentValue = GetRequestFromFile(documentRoot,endpoint);
			if (ContentValue != "") {
				responseBody = httpversion + " \r\n"
					"Content-Type:text/html\r\n\r\n" + ContentValue;
					
			}
			else {
		
				responseBody = httpversion + " 404 Not Found\r\n"
					"Content-Type:text/html\r\n\r\n"
					"<html>"
					"<head><title>404 not Found</title></head>"
					"<body>"
					"<p>File Name '" + endpoint + "' not found at document root folder</p>"
					"</body>"
					"</html>";

			}
		}
		else {
			std::cout << "endpoint value" << endpoint<<"\n";
			if (endpoint.length() == 1) {
				responseBody = httpversion + " 404 Not found\r\n"
					"Content-Type:text/html\r\n\r\n"
					"<html>"
					"<body>"
					"<title>404 Not found</title>"
					"<h5><p>Kindly enter a table name. Your Current Url has no endpoint</p></h5>"
					"</body>"
					"</html>";
			}
			else {
				std::vector<std::string> endpointContent = splitMethod(endpoint, '/');
				
				std::string fetchData;
				
				if (endpointContent.size() == 3 and endpointContent[1]=="address") {
					fetchData = db->queryfetchAddress(endpointContent[2], "user");
					std::cout << "pppppppppppp" << fetchData;
				}
				else if (endpointContent.size() == 3 and endpointContent[1]=="username") {
					fetchData = db->queryfetchUsername(endpointContent[2], "user");
					std::cout << "ppppppppppppp" << fetchData;

				}
				else {
					fetchData = "Invalid content. Check your endpoint format";
				}
				responseBody = httpversion + " \r\n"
					"Content-type: text/html\r\n\r\n"
					"<html>"
					"<body>"
					"<h4><p>Content for the given endpoint is '" + fetchData + "'</p></h4>"
					"</body>"
					"</html>";
			}
		}
		const char* resp = responseBody.c_str();
		send(clientAccept, resp, strlen(resp), 0);

	}
	
	else if (methodType.find("POST") != std::string::npos) {
		std::string endpoint = splitProps[1];
		size_t fileext = endpoint.find_last_of(".");
		if (connectionDetail.find("Content-Length") != connectionDetail.end() && std::stoi(connectionDetail["Content-Length"])>0) {
			std::string status = db->queryPostEntry(connectionDetail["address"], connectionDetail["username"], "user");
			responseBody = httpversion + " 404 not found\r\n"
				"Content-Type:text/html\r\n\r\n"
				"<html>"
				"<body>"
				"<title>Insert entries </title>"
				"<h5><p>"+ status +"</p></h5>"
				"</body>"
				"</html>";

		}
		else {
			responseBody = httpversion + " 404 not found\r\n"
				"Content-Type:text/html\r\n\r\n"
				"<html>"
				"<body>"
				"<title>Cant add the entry without reuired entries </title>"
				"<h5><p>POST body is empty . Kindly add post body to enter the data</p></h5>"
				"</body>"
				"</html>";

			std::cout << "POST method is found but body is empty";
		}
	}

	else if (methodType.find("DELETE") != std::string::npos) {
		std::string endpoint = splitProps[1];
		size_t fileext = endpoint.find_last_of(".");
		if (connectionDetail.find("Content-Length") != connectionDetail.end() && std::stoi(connectionDetail["Content-Length"]) > 0) {
			std::string status = db->queryDeleteEntry(connectionDetail["id"], "user");
			responseBody = httpversion + " 404 not found\r\n"
				"Content-Type:text/html\r\n\r\n"
				"<html>"
				"<body>"
				"<title>Insert entries </title>"
				"<h5><p>" + status + "</p></h5>"
				"</body>"
				"</html>";

		}
		else {
			responseBody = httpversion + " 404 not found\r\n"
				"Content-Type:text/html\r\n\r\n"
				"<html>"
				"<body>"
				"<title>Cant add the entry without reuired entries </title>"
				"<h5><p>POST body is empty . Kindly add post body to enter the data</p></h5>"
				"</body>"
				"</html>";

			std::cout << "DELETE method is found but body is empty";
		}
	}
	else if (methodType.find("PUT") != std::string::npos) {
		std::string endpoint = splitProps[1];
		size_t fileext = endpoint.find_last_of(".");
		std::vector<std::string> endpointContent = splitMethod(endpoint, '/');

		if (connectionDetail.find("Content-Length") != connectionDetail.end() && std::stoi(connectionDetail["Content-Length"]) > 0) {
			std::string status = db->queryPutEntry(connectionDetail["fieldUpdate"],connectionDetail["value"],endpointContent[1], "user");
			responseBody = httpversion + " 404 not found\r\n"
				"Content-Type:text/html\r\n\r\n"
				"<html>"
				"<body>"
				"<title>Insert entries </title>"
				"<h5><p>" + status + "</p></h5>"
				"</body>"
				"</html>";

		}
		else {
			responseBody = httpversion + " 404 not found\r\n"
				"Content-Type:text/html\r\n\r\n"
				"<html>"
				"<body>"
				"<title>Cant add the entry without reuired entries </title>"
				"<h5><p>POST body is empty . Kindly add post body to enter the data</p></h5>"
				"</body>"
				"</html>";

			std::cout << "DELETE method is found but body is empty";
		}
	}
	const char* resp = responseBody.c_str();
	send(clientAccept, resp, strlen(resp), 0);
	closesocket(socketValue);
	closesocket(clientAccept);
	WSACleanup();
	return 0;
	}

	 

