#ifndef SHAKESPEARE_H 

#define SHAKESPEARE_H

#include <string>

using namespace std;

namespace bridges {

class Shakespeare {
	private:
		string 	title,			// title of work
				type, 			// play, sonnet, ...
				text;			// content?

	public:
		Shakespeare() {
			title = type = text = "";
		}
		Shakespeare(string title, string type, string text) {
			this->title = title;
			this->type = type;
			this->text = text;
		}
		string getTitle() {
			return title;
		}
		void setTitle (string title) {
			this->title = title;
		}
		string getType() {
			return type;
		}
		void setType (string type) {
			this->type = type;
		}
		string getText() {
			return text;
		}
		void setText (string text) {
			this->text = text;
		}
};

} //namespace bridges

#endif
