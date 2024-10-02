#include<iostream>
#include "DataBaseConnectivity.h"
#include<string>
#include<algorithm>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>


sql::mysql::MySQL_Driver* driver;
sql::Connection* connection;
sql::Statement* statement;


void MySqlDatabase::connect()  {
		try {

			driver = sql::mysql::get_driver_instance();
			connection = driver->connect("tcp://127.0.0.1:3306", "root", "root");
			connection->setSchema("cwebserverschema");
		}
		catch (sql::SQLException& e) {
			std::cerr << "Error while doing Sql Connection:" << e.what() << std::endl;
		}

	}

std::string MySqlDatabase::queryfetchUsername(std::string fetchval, std::string table) {
	try {
		//statement = connection->createStatement();
		sql::PreparedStatement* myStatement = connection->prepareStatement("Select username from " + table + " where id = ?");
		myStatement->setString(1, fetchval);
		sql::ResultSet* queryval = myStatement->executeQuery();
		std::string queryResult;
		while (queryval->next()) {
			queryResult = queryval->getString("username");
		}
		delete queryval;
		delete myStatement;
		return queryResult;
	}
	catch (sql::SQLException e) {
		std::cerr << "Error while executing the where clause query" << e.what() << std::endl;
	}

}

std::string MySqlDatabase::queryfetchAddress(std::string fetchval, std::string table) {
	try {
		//statement = connection->createStatement();
		//sql::ResultSet* queryval = statement->executeQuery("Select address from "+table);

		sql::PreparedStatement* sqlval = connection->prepareStatement("Select address from " + table + " where id=?");

		sqlval->setString(1, fetchval);
		sql::ResultSet* queryentry = sqlval->executeQuery();
		std::string queryResult;
		while (queryentry->next()) {
			queryResult = queryentry->getString("address");
		}

		delete queryentry;
		delete sqlval;
		return queryResult;
	}
	catch (sql::SQLException e) {
		std::cerr << "Error while executing the query or no table foud" << e.what() << std::endl;
	}

}

std::string MySqlDatabase::queryPostEntry(std::string address, std::string usrname, std::string tableval) {
	
	
	//std::cout << "username is *****" << usrname<<;
	//std::cout << "address is *****" << address << std::endl;;


	try {
		if (connection->isValid()) {
			std::cout << "valid connection" << "\n";
		}
		else {
			std::cout << "invalid connection" << "\n";
		}
		sql::PreparedStatement* findMaxid = connection->prepareStatement("select max(id) as MAXVAL from user");
		sql::ResultSet *res = findMaxid->executeQuery();
		std::string idval;
		if (res->next()) {
			idval = res->getString("MAXVAL");
		}
		int identry = std::stoi(idval);
		identry = identry + 1;
		idval = std::to_string(identry);
		sql::PreparedStatement *insertQuery = connection->prepareStatement("INSERT into `" + tableval + "` (address,username,id) VALUES(?,?,?)");
		insertQuery->setString(1, address);
		insertQuery->setString(2, usrname);
		insertQuery->setString(3, idval);
		insertQuery->executeUpdate();
		delete insertQuery;
		return "Entry is inserted In DB";
	}
	catch (sql::SQLException &err) {
		std::cerr << "Error while entering the data into the table :" << err.what() << std::endl;
		return "Error while inseritng the Database Entry";
	}
	
	
}
std::string MySqlDatabase::queryDeleteEntry(std::string id, std::string table) {
	try {
		sql::PreparedStatement* deleteEntry = connection->prepareStatement("DELETE from " + table + " where id =?");
		deleteEntry->setString(1, id);
		deleteEntry->executeUpdate();
		delete deleteEntry;
	}
	catch (sql::SQLException error) {
		std::cerr << "Getting error in SQL" << error.what() << std::endl;
	}
	return "Enty is deleted from DB";
}

std::string MySqlDatabase::queryPutEntry(std::string fieldName, std::string fieldval, std::string idval, std::string tableval) {
	try {
		fieldName.erase(std::remove(fieldName.begin(), fieldName.end(), ','), fieldName.end());
		std::cout << "Table: " << tableval << " Field: " << fieldName << std::endl;

		//sql::PreparedStatement* updateEntry = connection->prepareStatement("UPDATE user SET address = ? WHERE id = ?");
		sql::PreparedStatement* updateEntry = connection->prepareStatement("UPDATE " +tableval+ " SET " +fieldName+ " = ? WHERE id = ?");

		updateEntry->setString(1, fieldval);
		updateEntry->setString(2, idval);
		updateEntry->executeUpdate();
		delete updateEntry;
		return "Enty is updated from DB";

	}
	catch (sql::SQLException& error) {
		std::cerr << "Getting error while updating SQL" << error.what() << std::endl;
		return "Error: Failed to update entry in DB";
	}
	

}