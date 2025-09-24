#include <iostream>
#include <string>
#include "Database.h"

<<<<<<< HEAD
void listMovies(Database& db) {
    auto movies = db.listMovies();
    if (movies.empty()) {
        std::cout << "No movies found.\n";
    }
    else {
        for (const auto& movie : movies) {
            std::cout << movie.id << " | " << movie.title << " (" << movie.year << ") - "
                << movie.genre << " | " << movie.director << " | "
                << movie.subgenre << " | " << movie.actor << "\n";
        }
    }
}

void searchMovies(Database& db) {
    std::string keyword;
    std::cout << "Enter search keyword: ";
    std::getline(std::cin, keyword);

    auto movies = db.searchMovies(keyword);
    if (movies.empty()) {
        std::cout << "No movies match your search.\n";
    }
    else {
        for (const auto& movie : movies) {
            std::cout << movie.id << " | " << movie.title << " (" << movie.year << ") - "
                << movie.genre << " | " << movie.director << " | "
                << movie.subgenre << " | " << movie.actor << "\n";
        }
    }
}

void addMovie(Database& db) {
    Movie m;
    std::cout << "Enter title: ";
    std::getline(std::cin, m.title);
    std::cout << "Enter year: ";
    std::cin >> m.year;
    std::cin.ignore(); // flush newline
    std::cout << "Enter genre: ";
    std::getline(std::cin, m.genre);
    std::cout << "Enter director: ";
    std::getline(std::cin, m.director);
    std::cout << "Enter subgenre: ";
    std::getline(std::cin, m.subgenre);
    std::cout << "Enter lead actor: ";
    std::getline(std::cin, m.actor);

    if (db.addMovie(m)) {
        std::cout << "✅ Movie added successfully!\n";
    }
    else {
        std::cout << "❌ Failed to add movie.\n";
    }
}

void deleteMovie(Database& db) {
    int id;
    std::cout << "Enter the movie ID to delete: ";
    std::cin >> id;
    std::cin.ignore(); // flush newline

    if (db.deleteMovie(id)) {
        std::cout << "✅ Movie deleted successfully!\n";
    }
    else {
        std::cout << "❌ Failed to delete movie (ID may not exist).\n";
    }
}

int main() {
    Database db("HorrorMovies.db");

    while (true) {
        std::cout << "\n--- Horror Movie Tracker ---\n";
        std::cout << "1. Add a movie\n";
        std::cout << "2. List all movies\n";
        std::cout << "3. Search movies\n";
        std::cout << "4. Delete a movie\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        switch (choice) {
        case 1: addMovie(db); break;
        case 2: listMovies(db); break;
        case 3: searchMovies(db); break;
        case 4: deleteMovie(db); break;
        case 5:
            std::cout << "Goodbye!\n";
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
=======
int main() {
    Database db("horrormovies.db");

    Movie m;
    m.title = "The Shining";
    m.year = 1980;
    m.genre = "Horror";
    m.director = "Stanley Kubrick";
    m.subgenre = "Psychological Horror";
    m.actor = "Jack Nicholson";

    if (db.addMovie(m)) std::cout << "Movie added successfully!\n";
    else std::cout << "Failed to add movie.\n";

    return 0;
>>>>>>> 826e112 (Add Database class and main program; project builds successfully)
}
