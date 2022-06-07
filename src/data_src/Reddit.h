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
					self.author = "";
					self.score = 0;
					self.vote_ratio = 0
						self.comment_count = 0;
					subreddit = "";
					self.post_time = 0;
					self.url = "";
					self.text = "";
				}
				Reddit (id = 0, title = "", author = "", score = 0,
					vote_ratio = 0, comment_count = 0, subreddit = "",
					post_time = 0, url = "", text = "")
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

				int getScore(self) {
					return score;
				}

				void setScore(int sc):
					score = sc;

				int  getVoteRatio() {
					return vote_ratio;
				}

				void setVoteRatio(int vr) {
					vote_ratio = vr;
				}

				int  getCommentCount()  {
					return comment_count;
				}

				setCommentCount(int cnt) {
					comment_count = cnt;
				}

				string  getSubReddit():
					return subreddit;

				void setSubReddit(string sr) {
					subreddit = sr;
				}

				int  getPostTime() {
					return post_time;
				}

				void  setPostTime(pt) {
					post_time = pt;
				}

				string  getUrl() {
					return url;
				}

				void  setUrl(u) {
					url = u;
				}

				string  getText() {
					return text;
				}

				setText(string txt) {
					text = txt;
				}
		}
	}
};
