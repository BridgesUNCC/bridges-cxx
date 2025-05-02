#ifndef MAP_H
#define MAP_H

using namespace rapidjson;
namespace bridges {
	namespace datastructure {

		/**
		 *
		 * @brief Abstract class for Map API
		 *
		 * Defines virtual functions for projection, map overlay and representation
		 *
		 */

		class Map {

			public:
				virtual const string getProjection() const = 0;
				virtual const bool getOverlay() const = 0;

				virtual const string getMapRepresentation() const = 0;
		};
	};
};
#endif
