#ifndef REDDIT_H

#define REDDIT_H

#include <string>

using std::string;

namespace bridges {
	namespace dataset {

		class Reddit {

			private:
		  string id, title, author, subreddit, url, text;
		  int score, comment_count, post_time;
		  float vote_ratio;

			public:
				Reddit() {
					id = "";
					title = "";
					author = "";
					score = 0;
					vote_ratio = 0;
					comment_count = 0;
					subreddit = "";
					post_time = 0;
					url = "";
					text = "";
				}


		  std::string getID() const {
		    return id;
		  }

		  void setID(std::string i) {
		    id = i;
		  }

				string  getTitle() {
					return title;
				}

				void  setTitle(string titl) {
					title = titl;
				}

				string getAuthor() {
					return author;
				}

				void setAuthor(string auth) {
					author = auth;
				}

				int getScore() {
					return score;
				}

				void setScore(int sc){
					score = sc;
				}

				int  getVoteRatio() {
					return vote_ratio;
				}

				void setVoteRatio(int vr) {
					vote_ratio = vr;
				}

				int  getCommentCount()  {
					return comment_count;
				}

				void setCommentCount(int cnt) {
					comment_count = cnt;
				}

				string  getSubReddit() {
					return subreddit;
				}

				void setSubReddit(string sr) {
					subreddit = sr;
				}

				int  getPostTime() {
					return post_time;
				}

				void  setPostTime(int pt) {
					post_time = pt;
				}

				string  getURL() {
					return url;
				}

				void  setURL(string u) {
					url = u;
				}

				string  getText() {
					return text;
				}

				void setText(string txt) {
					text = txt;
				}
		};
	};
};
#endif
