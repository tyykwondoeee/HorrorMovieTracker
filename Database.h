#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "sqlite3.h"

struct Movie {
    int id = 0;
    std::string title;
    int year = 0;
    std::string genre;
    std::string director;
    std::string subgenre;
    std::string actor;
};

class Database {
private:
    sqlite3* db = nullptr;

public:
    explicit Database(const std::string& dbName);
    ~Database();

    bool addMovie(const Movie& movie);
    std::vector<Movie> listMovies();
    std::vector<Movie> searchMovies(const std::string& keyword);
<<<<<<< HEAD
    bool deleteMovie(int id);  // ✅ NEW function for deleting movies
=======
>>>>>>> 826e112 (Add Database class and main program; project builds successfully)
};

#endif
