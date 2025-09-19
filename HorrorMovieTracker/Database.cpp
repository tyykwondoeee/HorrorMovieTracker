#include "Database.h"
#include <iostream>
#include <vector>
#include <sqlite3.h>

// ==========================
// Constructor
// ==========================
Database::Database(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS movies ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "Title TEXT NOT NULL,"
        "Year INTEGER,"
        "Genre TEXT,"
        "Director TEXT,"
        "Subgenre TEXT,"
        "Actor TEXT);";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// ==========================
// Add using prepared statement
// ==========================
bool Database::addMovie(const Movie& movie) {
    if (!db) return false;

    const char* sql = "INSERT INTO movies (Title, Year, Genre, Director, Subgenre, Actor) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Prepare failed (add): " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, movie.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, movie.year);
    sqlite3_bind_text(stmt, 3, movie.genre.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, movie.director.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, movie.subgenre.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, movie.actor.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    return true;
}

// ==========================
// Get movies
// ==========================
std::vector<Movie> Database::getAllMovies() {
    std::vector<Movie> movies;
    if (!db) return movies;

    const char* sql = "SELECT ID, Title, Year, Genre, Director, Subgenre, Actor FROM movies ORDER BY Title;";
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Prepare failed (getAll): " << sqlite3_errmsg(db) << std::endl;
        return movies;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Movie m;
        m.id = sqlite3_column_int(stmt, 0);
        const unsigned char* t = sqlite3_column_text(stmt, 1);
        m.title = t ? reinterpret_cast<const char*>(t) : "";
        m.year = sqlite3_column_int(stmt, 2);
        const unsigned char* g = sqlite3_column_text(stmt, 3);
        m.genre = g ? reinterpret_cast<const char*>(g) : "";
        const unsigned char* d = sqlite3_column_text(stmt, 4);
        m.director = d ? reinterpret_cast<const char*>(d) : "";
        const unsigned char* s = sqlite3_column_text(stmt, 5);
        m.subgenre = s ? reinterpret_cast<const char*>(s) : "";
        const unsigned char* a = sqlite3_column_text(stmt, 6);
        m.actor = a ? reinterpret_cast<const char*>(a) : "";

        movies.push_back(m);
    }

    sqlite3_finalize(stmt);
    return movies;
}

// ==========================
// Search by title
// ==========================
std::vector<Movie> Database::searchMoviesByTitle(const std::string& title) {
    std::vector<Movie> results;
    if (!db) return results;

    const char* sql = "SELECT ID, Title, Year, Genre, Director, Subgenre, Actor FROM movies WHERE Title LIKE ? ORDER BY Title;";
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Prepare failed (search): " << sqlite3_errmsg(db) << std::endl;
        return results;
    }

    std::string pattern = "%" + title + "%";
    sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Movie m;
        m.id = sqlite3_column_int(stmt, 0);
        const unsigned char* t = sqlite3_column_text(stmt, 1);
        m.title = t ? reinterpret_cast<const char*>(t) : "";
        m.year = sqlite3_column_int(stmt, 2);
        const unsigned char* g = sqlite3_column_text(stmt, 3);
        m.genre = g ? reinterpret_cast<const char*>(g) : "";
        const unsigned char* d = sqlite3_column_text(stmt, 4);
        m.director = d ? reinterpret_cast<const char*>(d) : "";
        const unsigned char* s = sqlite3_column_text(stmt, 5);
        m.subgenre = s ? reinterpret_cast<const char*>(s) : "";
        const unsigned char* a = sqlite3_column_text(stmt, 6);
        m.actor = a ? reinterpret_cast<const char*>(a) : "";

        results.push_back(m);
    }

    sqlite3_finalize(stmt);
    return results;
}

// ==========================
// Delete by ID
// ==========================
bool Database::deleteMovieByID(int id) {
    if (!db) return false;

    const char* sql = "DELETE FROM movies WHERE ID = ?;";
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Prepare failed (delete): " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

// ==========================
// Update
// ==========================
bool Database::updateMovieByID(int id, const Movie& movie) {
    if (!db) return false;

    const char* sql = "UPDATE movies SET Title = ?, Year = ?, Genre = ?, Director = ?, Subgenre = ?, Actor = ? WHERE ID = ?;";
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Prepare failed (update): " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, movie.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, movie.year);
    sqlite3_bind_text(stmt, 3, movie.genre.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, movie.director.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, movie.subgenre.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, movie.actor.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 7, id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

// ==========================
// Destructor
// ==========================
Database::~Database() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

