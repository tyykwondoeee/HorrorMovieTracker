#include "Database.h"
#include <iostream>
#include <limits>

// Prints menu
void printMenu() {
    std::cout << "\n--- Horror Movie Tracker ---\n"
        << "1) Add movie\n"
        << "2) List all movies\n"
        << "3) Search by title\n"
        << "4) Delete by ID\n"
        << "5) Update by ID\n"
        << "0) Exit\n"
        << "Choose: ";
}

int main() {
    // Open database
    Database db("horrormovies.db");

    while (true) {
        printMenu(); // show menu

        int choice;
        // Read user choice
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush invalid input
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush leftover newline

        // Exit
        if (choice == 0) break;

        // Add movie
        if (choice == 1) {
            Movie m;

            std::cout << "Title: ";
            std::getline(std::cin, m.title);

            // Year input
            std::cout << "Year: ";
            while (!(std::cin >> m.year)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter a valid year: ";
            }
            std::cin.ignore();

            std::cout << "Genre: "; std::getline(std::cin, m.genre);
            std::cout << "Director: "; std::getline(std::cin, m.director);
            std::cout << "Subgenre: "; std::getline(std::cin, m.subgenre);
            std::cout << "Actor: "; std::getline(std::cin, m.actor);

            // Add movie to database
            if (db.addMovie(m)) std::cout << "Added successfully.\n";
            else std::cout << "Add failed.\n";
        }

        // List movies
        else if (choice == 2) {
            auto movies = db.getAllMovies();
            for (const auto& m : movies) {
                std::cout << m.id << " | " << m.title << " (" << m.year << ") - " << m.genre
                    << " | Director: " << m.director << " | Actor: " << m.actor << '\n';
            }
            if (movies.empty()) std::cout << "No movies found.\n";
        }

        // Search
        else if (choice == 3) {
            std::string q;
            std::cout << "Search: ";
            std::getline(std::cin, q);

            auto results = db.searchMoviesByTitle(q);
            for (const auto& m : results) {
                std::cout << m.id << " | " << m.title << " (" << m.year << ")\n";
            }
            if (results.empty()) std::cout << "No matches.\n";
        }

        // Delete
        else if (choice == 4) {
            int id;
            std::cout << "ID to delete: ";
            std::cin >> id;
            std::cin.ignore();
            if (db.deleteMovieByID(id)) std::cout << "Deleted.\n";
            else std::cout << "Delete failed.\n";
        }

        // Update
        else if (choice == 5) {
            int id;
            std::cout << "ID to update: ";
            std::cin >> id;
            std::cin.ignore();

            Movie m;
            std::cout << "New Title: "; std::getline(std::cin, m.title);

            // Year input with validation
            std::cout << "New Year: ";
            while (!(std::cin >> m.year)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter a valid year: ";
            }
            std::cin.ignore();

            std::cout << "New Genre: "; std::getline(std::cin, m.genre);
            std::cout << "New Director: "; std::getline(std::cin, m.director);
            std::cout << "New Subgenre: "; std::getline(std::cin, m.subgenre);
            std::cout << "New Actor: "; std::getline(std::cin, m.actor);

            if (db.updateMovieByID(id, m)) std::cout << "Updated.\n";
            else std::cout << "Update failed.\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}

