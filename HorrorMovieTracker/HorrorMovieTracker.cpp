#include <iostream>
#include "Database.h"

int main() {
//Adding database
	Database db("HorrorMovies.db");
//Adding movies
	Movie m;
	m.title = "The Shining";
	m.year = 1988;
	m.genre = "Horror";
	m.director = "Stanley Kubrick";
	m.subgenre = "Psychological Horror";
	m.actor = "Jack Nicholson";

	if (db.addMovie(m)) {
		std::cout << "Movie added successfully!" << std::endl;
	} else {
		std::cout << "Failed to add movie." << std::endl;
	}
	return 0;
}