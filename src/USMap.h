#ifndef US_MAP_H

#define US_MAP_H

#include <math.h>
#include <cmath>

#include <algorithm>

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

#include "DataStructure.h"
#include "Map.h"
#include "./data_src/USState.h"
#include "./data_src/USCounty.h"
#include <JSONutil.h>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace bridges {
	namespace datastructure {

		using namespace bridges::datastructure;
		using bridges::dataset::USState;

		/**
		 * @brief This class provides an API to building, displaying and
		 * manipulating	 US maps and counties in BRIDGES
		 *
		 * We can draw a US map  with all state
		 * boundaries, a map with all US state and county boundaries, or
		 * specify a set of states  and display the state and/or county
		 * boundaries.
		 *
		 * Functions are provided to access each US state or county and color
		 * its boundary or its interior using the stroke color  and fill color
		 * functions. This lets us build map based applications where the fill
		 * fill color can be used to represent different data attributes, such
		 * population counts, election statistics or any attribute at the state
		 * or county level.
		 *
		 * One can also construct the object with the default constructor, passing no data. And only a simple outline of the states will be rendered.
		 *
		 * See the Maps tutorials for examples of the usage of the US Map API
		 *  at  https://bridgesuncc.github.io/tutorials/Map.html
		 *
		 */
		class USMap :  public Map, public DataStructure {
			private:
				vector<string> state_names;
				vector<USState> state_data;

		  bool all;
		  
				virtual const string getDataStructureRepresentation ()
				const override {
					using bridges::JSONUtil::JSONencode;
					return JSONencode("mapdummy") + COLON + JSONencode(true) + CLOSE_CURLY;
				}
				unordered_map<string, string> state_codes = {
					{"Alabama", "AL"},
					{"Alaska", "AK"},
					{"Arizona", "AZ"},
					{"Arkansas", "AR"},
					{"California", "CA"},
					{"Colorado", "CO"},
					{"Connecticut", "CT"},
					{"Delaware", "DE"},
					{"District of Columbia", "DC"},
					{"Florida", "FL"},
					{"Georgia", "GA"},
					{"Guam", "GU"},
					{"Hawaii", "HI"},
					{"Idaho", "ID"},
					{"Illinois", "IL"},
					{"Indiana", "IN"},
					{"Iowa", "IA"},
					{"Kansas", "KS"},
					{"Kentucky", "KY"},
					{"Louisiana", "LA"},
					{"Maine", "ME"},
					{"Maryland", "MD"},
					{"Massachusetts", "MA"},
					{"Michigan", "MI"},
					{"Minnesota", "MN"},
					{"Mississippi", "MS"},
					{"Missouri", "MO"},
					{"Montana", "MT"},
					{"Nebraska", "NE"},
					{"Nevada", "NV"},
					{"New Hampshire", "NH"},
					{"New Jersey", "NJ"},
					{"New Mexico", "NM"},
					{"New York", "NY"},
					{"North Carolina", "NC"},
					{"North Dakota", "ND"},
					{"Ohio", "OH"},
					{"Oklahoma", "OK"},
					{"Oregon", "OR"},
					{"Pennsylvania", "PA"},
					{"Puerto Rico", "PR"},
					{"Rhode Island", "RI"},
					{"South Carolina", "SC"},
					{"South Dakota", "SD"},
					{"Tennessee", "TN"},
					{"Texas", "TX"},
					{"Utah", "UT"},
					{"Vermont", "VT"},
					{"Virginia", "VA"},
					{"Virgin Islands", "VI"},
					{"Washington", "WA"},
					{"West Virginia", "WV"},
					{"Wisconsin", "WI"},
					{"Wyoming", "WY "}
				};
			public:
				/**
				 * @brief Gets the type of map projection. For US map we
				 *  currently use albersusa
				 *
				 */
				const string getProjection() const override {
					return "albersusa";
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
				 * @brief Generates the JSON representation of the US map
				 *
				 * @returns string
				 */
				virtual const string getMapRepresentation () const override  {
				  if (this->all)
						return "[\"all\"]";

					// generates a JSON of the states with county information
					string map_str = OPEN_BOX;
					using bridges::JSONUtil::JSONencode;
					for (auto& st : state_data) {
						map_str += OPEN_CURLY +
							QUOTE + "_state_name" + QUOTE + COLON +
							JSONencode(st.getStateName()) + COMMA +
							QUOTE + "_state_code" + QUOTE + COLON +
							JSONencode(state_codes.at(st.getStateName())) + COMMA +
							QUOTE + "_stroke_color" + QUOTE + COLON
							+ st.getStrokeColor().getCSSRepresentation() + COMMA +
							QUOTE +	"_stroke_width" + QUOTE + COLON +
							JSONencode(st.getStrokeWidth()) + COMMA +
							QUOTE +	"_fill_color" + QUOTE + COLON +
							st.getFillColor().getCSSRepresentation() + COMMA +
							QUOTE +	"_view_counties" + QUOTE + COLON +
							JSONencode(st.getViewCountiesFlag()) + COMMA +
							QUOTE +	"_counties" + QUOTE + COLON;

						// get all the counties
						map_str += OPEN_BOX;  // array of counties
						for (auto& c : st.getCounties()) {
							map_str +=  OPEN_CURLY +
								QUOTE +	"_geoid" + QUOTE + COLON +
								JSONencode(c.second.getGeoId()) + COMMA +
								QUOTE +	"_fips_code" + QUOTE + COLON +
								JSONencode(c.second.getFipsCode()) + COMMA +
								QUOTE +	"_county_name" + QUOTE + COLON +
								JSONencode(c.second.getCountyName()) + COMMA +
								QUOTE +	"_state_name" + QUOTE + COLON +
								JSONencode(c.second.getStateName()) + COMMA +
								QUOTE +	"_stroke_color" + QUOTE + COLON +
								c.second.getStrokeColor().getCSSRepresentation() + COMMA +
								QUOTE +	"_stroke_width" + QUOTE + COLON +
								JSONencode(c.second.getStrokeWidth()) + COMMA +
								QUOTE +	"_fill_color" + QUOTE + COLON +
								c.second.getFillColor().getCSSRepresentation() + COMMA +
								QUOTE +	"_hide" + QUOTE + COLON +
								JSONencode(c.second.getHideFlag()) +
								CLOSE_CURLY + COMMA;
						}
						// remove last comma
						if (st.getCounties().size()) // case where counties are on
							map_str = map_str.substr(0, map_str.size() - 1);
						map_str += CLOSE_BOX + CLOSE_CURLY +  COMMA;
					}
					// close the states array
					map_str = map_str.substr(0, map_str.size() - 1) +  CLOSE_BOX;
					return map_str;
				}
			public:
		  USMap() {
		    all = true;
		  }
				/*
				 * @brief Constructs a US Map object  with map data
				 *
				 * @param   st_data  data containg state/county information
				 */
				USMap(vector<USState> st_data) {
				  all = false;
					state_data = st_data;
				}

				/*
				 * @brief This function returns the current state/county data
				 *  in the US map object.
				 *
				 * @return list of state information
				 */
				vector<USState>& getMapData() {
					return state_data;
				}

				/*
				 * @brief This function sets the state/county data
				 *  in the US map object.
				 *
				 * @param  list of state information
				 */
				void setStateData(vector<USState> st_data) {
				  all = false;
					state_data = st_data;
				}

				/*
				 *
				 * @brief This function gets the data structure type for
				 * the US map,
				 *
				 */
				virtual const string getDStype() const override {
					return "us_map";
				}
		};
	}
}
#endif
