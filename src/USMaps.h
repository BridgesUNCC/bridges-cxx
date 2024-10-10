#ifndef US_MAPS_H

#define US_MAPS_H

#include <math.h>
#include <cmath>

#include <algorithm>

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
					string map_str = OPEN_BOX;
					using bridges::JSONUtil::JSONencode;
					for (auto& st : state_data) {
						map_str += OPEN_CURLY + 
							QUOTE + "_state_name" + QUOTE + COLON + 
								JSONencode(st.getStateName()) + COMMA +
						QUOTE+ "_stroke_color" + QUOTE + COLON 
							+ JSONencode(st.getStrokeColor()) + COMMA +
						QUOTE +	"_stroke_width" + QUOTE + COLON + 
							JSONencode(st.getStrokeWidth()) +COMMA +
						QUOTE +	"_fill_color" + QUOTE + COLON + 
							JSONencode(st.getFillColor()) + COMMA +
						QUOTE +	"_view_counties" + QUOTE + COLON + 
							JSONencode(st.getViewCountiesFlag()) + COMMA +
						QUOTE +	"_counties" + QUOTE + COLON;

						// get all the counties
						map_str += OPEN_BOX;  // array of counties
						for (auto& c : st.getCounties()) {
							map_str +=  OPEN_CURLY +
							QUOTE +	"_geoid" + QUOTE + COLON + 
								JSONencode(c.second.getGeoId())+ COMMA +
							QUOTE +	"_fips_code" + QUOTE + COLON + 
								JSONencode(c.second.getFipsCode())+ COMMA +
							QUOTE +	"_county_name" + QUOTE +COLON + 
								JSONencode(c.second.getCountyName()) + COMMA +
							QUOTE +	"_state_name" + QUOTE +COLON + 
								JSONencode(c.second.getStateName()) + COMMA +
							QUOTE +	"_stroke_color" + QUOTE +COLON + 
								JSONencode(c.second.getStrokeColor())+ COMMA +
							QUOTE +	"_stroke_width" + QUOTE +COLON + 
								JSONencode(c.second.getStrokeWidth()) + COMMA +
							QUOTE +	"_fill_color" + QUOTE +COLON + 
								JSONencode(c.second.getFillColor()) + COMMA +
							QUOTE +	"_hide" + QUOTE + COLON + 
								JSONencode(c.second.getHideFlag()) + 
									CLOSE_CURLY + COMMA;
							}
							// remove last comma
							map_str = map_str.substr(0, map_str.size()-1);
							map_str += CLOSE_BOX + CLOSE_CURLY +  COMMA;
					}
					// close the states array
					map_str = map_str.substr(0, map_str.size()-1) +  CLOSE_BOX;
//					cout << "JSON of Map:" + map_str;
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
				void setMap(vector<State> st_data){
					state_data = st_data;
				}
		};
	}
}
#endif
