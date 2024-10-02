#ifndef DBHEADER
#define DBHEADER
#include<iostream>
#include<string>
class DataBase {
public:
	virtual void connect() = 0;
	virtual std::string queryfetchUsername(std::string fetchval, std::string table) = 0;
	virtual std::string queryfetchAddress(std::string fetchval, std::string table) = 0;
	virtual std::string queryPostEntry(std::string address, std::string usrname, std::string tableval) = 0;
	virtual std::string queryDeleteEntry(std::string id, std::string tablename)=0;
	virtual std::string queryPutEntry(std::string fieldName, std::string fieldval, std::string idval, std::string tableval) = 0;

};

class MySqlDatabase : public DataBase {
public:
	void connect() override;
	std::string queryfetchUsername(std::string fetchval, std::string table) override;
	std::string queryfetchAddress(std::string fetchval, std::string table) override;
	std::string queryPostEntry(std::string address, std::string usrname, std::string tableval) override;
	std::string queryDeleteEntry(std::string id, std::string tablename) override;
	std::string queryPutEntry(std::string fieldName, std::string fieldval, std::string idval, std::string tableval) override;

};

#endif //DBHEADER

