#ifndef US_MAPS_H

#define US_MAPS_H

#include <math.h>
#include <cmath>

#include <algorithm>

//should be defined in math.h but VS2017 has a weird behavior here.
#ifndef M_PI
#define M_PI 3.1415926535897
#endif

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "DataStructure.h"
#include "./data_src/State.h"
#include "./data_src/County.h"


namespace bridges {
	namespace datastructure {

using namespace bridges::datastructure;
	class USMaps :  public DataStructure {

		private:
			vector<string> state_names;
			vector<State> state_data;

			virtual const string getDataStructureRepresentation () 
											const override {
				// generates a JSON of the states with county information
				string map_str = OPEN_BOX + OPEN_CURLY; 
				using bridges::JSONUtil::JSONencode;
				for (auto& st : state_data) {
					map_str += "_state_name" + JSONencode(st.getStateName()) + 
						"_stroke_color" + JSONencode(st.getStrokeColor()) + 
						"_stroke_width" + JSONencode(st.getStrokeWidth()) +
						"_fill_color" + JSONencode(st.getFillColor()) + 
						"_view_counties" + JSONencode(st.getViewCountiesFlag()) +
						"_counties" + COLON + OPEN_BOX + OPEN_CURLY;
						// get all the counties
						for (auto& c : st.getCounties()) {
							map_str += 
								"_geoid" + COLON + JSONencode(c.second.getGeoId())+
								"_fips_code" + COLON + JSONencode(c.second.getFipsCode())+
								"_county_name" + COLON + JSONencode(c.second.getCountyName()) +
								"_state_name" + COLON + JSONencode(c.second.getStateName()) +
								"_stroke_color" + JSONencode(c.second.getStrokeColor()) + 
								"_stroke_width" + JSONencode(c.second.getStrokeWidth()) + 
								"_fill_color" + JSONencode(c.second.getFillColor()) + 
								"_hide" + JSONencode(c.second.getHideFlag()) + 
								CLOSE_CURLY + COMMA;
						}
						// remove last comma
						map_str = map_str.substr(0, map_str.size()-1);
						map_str += CLOSE_CURLY + COMMA;
				}
				map_str = map_str.substr(0, map_str.size()-1) +  CLOSE_BOX;
				cout << "JSON of Map:" + map_str;
				return map_str;
			}
		public: 
			USMaps() {
				state_names.clear();
				state_data.clear();
			}

			virtual const string getDStype() const override {
				return "us_map";
			}
			vector<State> setMap(vector<State> st_data){
				state_data = st_data;
			}
	};
}
#endif
