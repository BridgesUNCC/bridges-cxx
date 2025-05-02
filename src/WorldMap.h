#ifndef WORLD_MAP_H

#define WORLD_MAP_H

#include <math.h>
#include <cmath>

#include <algorithm>

#include <string>
#include <vector>

#include "DataStructure.h"
#include "Map.h"
#include <JSONutil.h>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace bridges {
	namespace datastructure {

		using namespace bridges::datastructure;

		/** @brief enable visulization of the World Map
		 *
		 *  See tutorial at  https://bridgesuncc.github.io/tutorials/Map.html
		 */
		class WorldMap :  public Map, public DataStructure {
			private:
				virtual const string getDataStructureRepresentation ()
				const override {
					using bridges::JSONUtil::JSONencode;
					return JSONencode("mapdummy") + COLON + JSONencode(true) + CLOSE_CURLY;
				}
			public:
				const string getProjection() const override {
					return "equirectangular";
				}
				const bool getOverlay() const override {
					return true;
				}

				virtual const string getMapRepresentation () const override  {
					return "\"all\"";
				}
			public:
				WorldMap() {
				}

				virtual const string getDStype() const override {
					return "world_map";
				}
		};
	}
}
#endif
