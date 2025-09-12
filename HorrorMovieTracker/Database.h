#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "sqlite3.h"

struct Movie {
    int id;
    std::string title;
    int year;
    std::string genre;
    std::string director;
    std::string subgenre;
    std::string actor;
};

// Class Declaration
class Database {
private:
    sqlite3* db;

public:
    Database(const std::string& dbName);
    ~Database();

    // Method Declarations
    bool addMovie(const Movie& movie);
    std::vector<Movie> listMovies();
    std::vector<Movie> searchMovies(const std::string& keyword);
    std::vector<Movie> recommendMovies(const std::string& mood, int year = 0, const std::string& genre = "");
};

#endif

