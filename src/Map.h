#ifndef MAP_H
#define MAP_H

using namespace rapidjson;
namespace bridges {
	namespace datastructure {

		class Map {

			public:
				virtual const string getProjection() const = 0;
				virtual const bool getOverlay() const = 0;
	
				virtual const string getMapRepresentation() const = 0;
		};
	};
};
#endif
