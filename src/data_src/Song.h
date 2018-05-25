/**
 * @brief  A Song object, used along with the Songs data source.
 *
 * This is a convenience class provided for  users who wish to use this
 * data source as part of their application. It provides an API that makes
 * it easy to access the attributes of this data set.
 *
 * Refer to tutorial examples to using this data source in data structure
 * assignments.
 *
 *
 * @author David Burlinson, C++ port: Kalpathi Subramanian
 * @date   5/24/18
 *
 */

#include DataSource.h

#ifndef SONG_H
#define SONG_H


namespace bridges {

	class Song : public  DataSource {
		private:
			string 	artist, // song author			
					song,	// song title
					album,	// album title
					lyrics,	// full lyrics
					release_date;

		public:
			Song() {
				artist = song = album = lyrics = release_date = "";
			}

			Song(string artist, string song, string album, string lyrics, 
									string release_date) {
				this->artist = artist;
				this->song = song;
				this->album = album;
				this->lyrics = lyrics;
				this->release_date = release_date;
			}

			string getArtist() {
				return artist;
			}

			void setArtist (string artist) {
				this->artist = artist;
			}

			string getSongTitle() {
				return song;
			}
			void setSongTitle(string song) {
				this->song = song;
			}

			string getAlbumTitle() {
				return album;
			}
			void setAlbumTitle(string album) {
				this->album = album;
			}

			string getLyrics() {
				return lyrics;
			}
			void setLyrics(string lyrics) {
				this->lyrics = lyrics;
			}

			string getReleaseDate() {
				return release_date;
			}
			void setReleaseDate(string release_date) {
				this->release_date = release_date;
			}
	};

} // namespace bridges
