#include "Database.h"
#include <iostream>

//Constructor
Database::Database(const std::string& dbName) {
	int rc = sqlite3_open(dbName.c_str(), &db);
	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		db = nullptr;
	}
	else {
		std::cout << "Database opened successfully!" << std::endl;
	}

	const char* sql = "CREATE TABLE IF NOT EXISTS movies ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"Title TEXT NOT NULL,"
		"Year INTEGER,"
		"Genre TEXT,"
		"Director TEXT,"
		"Subgenre TEXT,"
		"Actor TEXT);";

	// create SQL table

	char* errMsg = nullptr;
	rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	else {
		std::cout << "Movies table ready!" << std::endl;
	}
}
	// Destructor
Database::~Database() {
	if (db) {
		sqlite3_close(db);
		std::cout << "Database closed." << std::endl;
	}
}
