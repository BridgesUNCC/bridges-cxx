#ifndef GAME_H

#define GAME_H

#include <string>

using namespace std;

namespace bridges {

class Game {
	private:
		string title;			// game
		string platform;		// game platform type
		double rating;			// game rating
		vector<string> genre;	// game type/category
	
	public:

		Game() {
			title = platform = "";
			rating = 0.0;
		}
	
		Game(string title, string platform, double rating, 
						vector<string> genre) {
			this->title = title;
			this->platform = platform;
			this->rating = rating;
			this->genre = genre;
		}

		string getTitle() {
			return title;	
		}
		void setTitle (string title) {
			this->title = title;
		}

		string getPlatformType() {
			return platform;
		}
		void setPlatformType(string platform) {
			this->platform = platform;
		}

		double getRating() {
			return rating;
		}
		void setRating(double rating) {
			this->rating = rating;
		}
		vector<string> getGameGenre() {
			return genre;
		}
		void setGameGenre(vector<string> genre) {
			this->genre = genre;
		}
};

} // namespace bridges

#endif
