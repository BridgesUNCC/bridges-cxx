#ifndef REDDIT_H
#define REDDIT_H

#include <string>

using std::string;

namespace bridges {
	namespace dataset {

		class Reddit {

			private:
		  std::string id, title, author, subreddit, url, text;
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

		  std::string  getTitle() const {
		    return title;
		  }
		  
		  void  setTitle(std::string titl) {
					title = titl;
				}

		  std::string getAuthor() const {
		    return author;
		  }

		  void setAuthor(string auth) {
					author = auth;
				}

		  int getScore() const {
					return score;
				}

				void setScore(int sc){
					score = sc;
				}

				float  getVoteRatio() const {
					return vote_ratio;
				}

				void setVoteRatio(float vr) {
					vote_ratio = vr;
				}

				int  getCommentCount()  const {
					return comment_count;
				}

				void setCommentCount(int cnt) {
					comment_count = cnt;
				}

		  std::string  getSubreddit() const {
					return subreddit;
				}

		  void setSubreddit(std::string sr) {
					subreddit = sr;
				}

				int  getPostTime() const {
					return post_time;
				}

				void  setPostTime(int pt) {
					post_time = pt;
				}

		  std::string  getURL() const {
					return url;
				}

				void  setURL(std::string u) {
					url = u;
				}
		  
		  std::string  getText() const {
					return text;
				}

				void setText(std::string txt) {
					text = txt;
				}
		};
	};
};
#endif
