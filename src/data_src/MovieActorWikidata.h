#ifndef MOVIEACTOR_WIKIDATA_H
#define MOVIEACTOR_WIKIDATA_H

namespace bridges {
	namespace dataset {

		//Since the data always comes from wikidata, we could strip the prefix http://www.wikidata.org/entity/ from the entities to gain memory. Should we?
		class MovieActorWikidata {
				std::string movieURI;
				std::string actorURI;
				std::string movieName;
				std::string actorName;

			public:
				MovieActorWikidata() {
				}

				void setMovieURI (std::string mu) {
					movieURI = mu;
				}

				void setActorURI (std::string au) {
					actorURI = au;
				}

				void setMovieName (std::string mn) {
					movieName = mn;
				}

				void setActorName (std::string an) {
					actorName = an;
				}

				const std::string& getMovieURI() const {
					return movieURI;
				}

				const std::string& getActorURI() const {
					return actorURI;
				}

				const std::string& getMovieName() const {
					return movieName;
				}

				const std::string& getActorName() const {
					return actorName;
				}
		};
	}
}


#endif
