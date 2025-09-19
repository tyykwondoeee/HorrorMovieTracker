#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>

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
public:
    explicit Database(const std::string& dbName);
    ~Database();

    bool addMovie(const Movie& movie);
    std::vector<Movie> getAllMovies();
    std::vector<Movie> searchMoviesByTitle(const std::string& title);
    bool deleteMovieByID(int id);
    bool updateMovieByID(int id, const Movie& movie);

private:
    sqlite3* db = nullptr;
};
