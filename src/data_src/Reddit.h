#ifndef REDDIT_H

#define REDDIT_H

#include <string>

using std::string;

namespace bridges {
	namespace dataset {

		class Reddit {

			private:
				string title, author, subreddit, url, text;
				int id, score, vote_ratio, comment_count, post_time;

			public:
				Reddit() {
					id = 0;
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
				Reddit (int id = 0, string title = "", string author = "", int score = 0,
					int vote_ratio = 0, int comment_count = 0, string subreddit = "",
					int post_time = 0, string url = "", string text = "")
				{}


				int getID() {
					return id;
				}

				void setID(int i) {
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

				string  getUrl() {
					return url;
				}

				void  setUrl(string u) {
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
