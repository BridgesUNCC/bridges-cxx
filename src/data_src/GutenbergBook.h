#ifndef GUTENBERG_BOOK_H

#define GUTENBERG_BOOK_H
#include <string>
using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 * @brief  A Gutenberg Book object metadata only, used along with the
		 * 	books data source.
		 *
		 * This is a convenience class provided for  users who wish to use this
		 *	data source as part of their application. It provides an API that makes
		 *  it easy to access the attributes of this data set.
		 *
		 * Refer to tutorial examples to using this data source in data structure
		 *  assignments.
		 *
		 * @author Kalpathi Subramanian
		 * @date   2/1/17, 12/28/20
		 *
		 */

		class GutenbergBook {
				string authorName;
				int authorBirth,
					authorDeath;
				string title;
				vector<string> lang, genre, subject;
				int numChars, numWords, numSentences, numDifficultWords;
				string url;
				int downloads;

			public:
				/** 
				 * Default Constructor
				 */
				GutenbergBook ()
					: authorName(""), authorBirth(0), authorDeath(0),
					  title(""), lang(), genre(), subject(),
					  numChars(0), numWords(0), numSentences(0), numDifficultWords(0),
					  url(""), downloads(0) {
				}

				/** 
				 * Constructor
				 *
				 * @param authorName   	name of author
				 * @param authorBirth  	birthdate
				 * @param authorDeath  	date of death
				 * @param title 	   	book title
				 * @param lang         	language
				 * @param genre			genres of book
				 * @param subject		subject of book
				 * @param numChars		number of characters in book
				 * @param numWords      number of words in book
				 * @param numSentences 	number of sentences in book
				 * @param numDifficultWords number of difficult words in book
				 * @param url			url for more information
				 * @param downloads     number of downloads of this book
				 */
				GutenbergBook(const string& authorName, int authorBirth, int authorDeath,
					const string& title, const vector<string>& lang, const vector<string>& genre,
					const vector<string>& subject, int numChars, int numWords,
					int numSentences, int numDifficultWords, const string& url,
					int downloads)
					: authorName(authorName), authorBirth(authorBirth), authorDeath(authorDeath),
					  title(title), lang(lang), genre(genre), subject(subject),
					  numChars(numChars), numWords(numWords), numSentences(numSentences), numDifficultWords(numDifficultWords),
					  url(url), downloads(downloads) {
				}

				/** 
				 * get name of author
				 * @return authorName 
				 */
				string getAuthorName() const {
					return authorName;
				}
				/** 
				 * set name of author
				 * @param authorName   	name of author
				 */
				void setAuthorName(const string& authorName) {
					this->authorName = authorName;
				}

				/** 
				 * get birthdate of author
				 * @return birthdate 
				 */
				int getAuthorBirth() const {
					return authorBirth;
				}
				/** 
				 * set birth date  of author
				 * @param authorBirth  birthdate of author to set
				 */
				void setAuthorBirth(int authorBirth) {
					this->authorBirth = authorBirth;
				}

				/** 
				 * get date of death of author
				 * @return author's date of death
				 */
				int getAuthorDeath() const {
					return authorDeath;
				}
				/** 
				 * set author's date of death
				 * @param authorDeath  date of death to set
				 */
				void setAuthorDeath(int authorDeath) {
					this->authorDeath = authorDeath;
				}

				/** 
				 * get  book title
				 * @return   book's title
				 */
				string getTitle() const {
					return title;
				}
				/** 
				 * set book title
				 * @param title  title of book to set
				 */
				void setTitle(const string& title) {
					this->title = title;
				}

				/** 
				 * get book's language
				 * @return language of book
				 */
				vector<string>  getLang() const {
					return lang;
				}
				/** 
				 * set book's language
				 * @param lang   	book's language to be set
				 */
				void setLang(const vector<string>& lang)  {
					this->lang = lang;
				}

				/** 
				 * get book's genres
				 * @return genres of book
				 */
				vector<string>  getGenre() const {
					return genre;
				}
				/** 
				 * set book's genres
				 * @param genre genres of book to be set
				 */
				void setGenre(const vector<string>& genre)  {
					this->genre = genre;
				}

				/** 
				 * set book's subjects
				 * @return subjects covered by the book
				 */
				vector<string>  getSubject() const {
					return subject;
				}
				/** 
				 * set book's subjects
				 * @param subject   subjects of book to be set
				 */
				void setSubject(const vector<string>& subject)  {
					this->subject = subject;
				}

				/** 
				 * get url of book for more info
				 * @return url of book
				 */
				string getURL() const {
					return url;
				}
				/** 
				 * set url of book for more info 
				 * @param url   url of book to be set
				 */
				void setURL(const string& url) {
					this->url = url;
				}

				/** 
				 * get total number of characters in book
				 * @return total characters in book
				 */
				int getNumChars() const {
					return numChars;
				}
				/** 
				 * set total number of characters  in book
				 * @param numChars   total characters to be set for this book
				 */
				void setNumChars(int numChars) {
					this->numChars = numChars;
				}

				/** 
				 * get total number of words in book
				 * @return total words in book
				 */
				int getNumWords() const {
					return numWords;
				}
				/** 
				 * set total number of words  in book
				 * @param numWords   total words to be set for this book
				 */
				void setNumWords(int numWords) {
					this->numWords = numWords;
				}

				/** 
				 * get total number of sentences in book
				 * @return total sentences in book
				 */
				int getNumSentences() const {
					return numSentences;
				}
				/** 
				 * set total number of sentences  in book
				 * @param numSentences   total sentences to be set for this book
				 */
				void setNumSentences(int numSentences) {
					this->numSentences = numSentences;
				}

				/** 
				 * get total number of difficult words in book
				 * @return total difficult words in book
				 */
				int getNumDifficultWords() const {
					return numDifficultWords;
				}
				/** 
				 * set total number of difficult words  in book
				 * @param numDiffiultWords   total difficult words to 
				 *						be set for this book
				 */
				void setNumDifficultWords(int numDifficultWords) {
					this->numDifficultWords = numDifficultWords;
				}
				/** 
				 * get total number of downloads of this book
				 * @return total downloads of this book
				 */
				int getNumDownloads() const {
					return downloads;
				}
				/** 
				 * set total number of downloads 
				 * @param dl   total downloads of this book to be set
				 */
				void setNumDownloads(int dl) {
					this->downloads = dl;
				}
		};

	}
}// namespace bridges

#endif

