#ifndef WORLD_MAP_H

#define WORLD_MAP_H

#include <math.h>
#include <cmath>

#include <algorithm>

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "DataStructure.h"
#include "Map.h"
#include "./data_src/Country.h"
#include <JSONutil.h>

namespace bridges {
	namespace datastructure {

		using namespace bridges::datastructure;
		using bridges::dataset::Country;

		/**
		 * @brief This class provides an API to building, displaying and
		 * manipulating	 World maps and countries in BRIDGES
		 *
		 * In the current implementation, we can draw a World map  with all country
		 * boundaries, or specify a set of countries  and display the country
		 * boundaries.
		 *
		 * Functions are provided to access each country county and color
		 * its boundary, its interior using stroke and fill color
		 * functions. This lets us build map based applications where the 
		 * fill color can be used to represent different data attributes, such
		 * as population counts, election statistics or any attribute at the country
		 * level. We stop at the country level as each country has its own subdivisions,
		 * such as discticts, states, regions, counties, etc.
		 *
		 * See the Maps tutorials for examples of the usage of the World Map API
		 *  at https://bridgesuncc.github.io/tutorials/Map.html
		 *
         * Authors: Kalpathi Subramanian, Erik Saule
         * Last modified : May 22, 2025
		 */
		class WorldMap :  public Map, public DataStructure {
			private:
				vector<string> country_names;
				vector<Country> country_data;

				virtual const string getDataStructureRepresentation ()
				const override {
					using bridges::JSONUtil::JSONencode;
					return JSONencode("mapdummy") + COLON + JSONencode(true) +
CLOSE_CURLY; } 
			public:
				/** 
				 * @brief Gets the type of map projection. For US map we
				 * currently use albersusa
				 */
				const string getProjection() const override { 
					return "equirectangular"; 
				}
				/**
				 *
				 * @brief Gets the map overlay flag.
				 *
				 */
				const bool getOverlay() const override {
					return true;
				}

				/**
				 * @brief Generates the JSON representation of the World map
				 *
				 * @returns string
				 */
				virtual const string getMapRepresentation () const override  {
					// generates a JSON of the country information
					string map_str = OPEN_BOX;
					using bridges::JSONUtil::JSONencode;
					for (auto& cntry : country_data) {
						map_str += OPEN_CURLY +
							QUOTE + "_country_name" + QUOTE + COLON +
							JSONencode(cntry.getCountryName()) + COMMA +
							QUOTE + "_stroke_color" + QUOTE + COLON + 
							cntry.getStrokeColor().getCSSRepresentation()+COMMA+
							QUOTE +	"_stroke_width" + QUOTE + COLON +
							JSONencode(cntry.getStrokeWidth()) + COMMA +
							QUOTE +	"_fill_color" + QUOTE + COLON +
							cntry.getFillColor().getCSSRepresentation() + COMMA;

						// remove last comma
						if (cntry.getCounties().size()) // case where counties are on
							map_str = map_str.substr(0, map_str.size() - 1);
						map_str += CLOSE_BOX + CLOSE_CURLY +  COMMA;
					}
					// close the countries array
					map_str = map_str.substr(0, map_str.size() - 1) +  CLOSE_BOX;
					return map_str;
				}
			public:
				/*
				 * @brief Constructs a World Map object  with map data
				 *
				 * @param   country_data  data containg country information
				 */
				WorldMap(vector<Country> cntry_data) {
					country_data = cntry_data;
				}

				/*
				 * @brief This function returns the current country data
				 *  in the World map object.
				 *
				 * @return list of country information
				 */
				vector<Country>& getMapData() {
					return country_data;
				}

				/*
				 * @brief This function sets the country data
				 *  in the US map object.
				 *
				 * @param  list of countries
				 */
				void setStateData(vector<USState> cntry_data) {
					country_data = cntry_data;
				}

				/*
				 *
				 * @brief This function gets the data structure type for
				 * the US map,
				 *
				 */
				virtual const string getDStype() const override {
					return "world_map";
				}
		};
	}
}
#endif
