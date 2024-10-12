#ifndef US_MAP_H

#define US_MAP_H

#include <math.h>
#include <cmath>

#include <algorithm>

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "DataStructure.h"
#include "Map.h"
#include "./data_src/State.h"
#include "./data_src/County.h"
#include <JSONutil.h>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


namespace bridges {
	namespace datastructure {

		using namespace bridges::datastructure;
		using bridges::dataset::State;

		class USMap :  public Map, DataStructure {
			private:
				vector<string> state_names;
				vector<State> state_data;
	
				virtual const string getDataStructureRepresentation ()
												const override {
//				virtual const rapidjson::Document getDataStructureRepresentation ()
//												const override {
//					using namespace rapidjson;
                    using bridges::JSONUtil::JSONencode;

//					Document d;
//					Value key, value;
//					d.setObject();
//						key.SetString("mapdummy");
//						value.SetBool(true);
//						d.AddMember(key, value, d.GetAllocator());

//					return d;
					return JSONencode("mapdummy")+COLON+JSONencode(true)+CLOSE_CURLY;
				}
			public:
				const string getProjection() const override {
					return "albersusa";
				}
				const bool getOverlay() const override {
					return true;
				}

/*
				virtual const string getMapRepresentation () const override  {
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
					cout << "JSON of Map:" + map_str;
//					return map_str;
					return s;
				}
*/
				virtual const string getMapRepresentation () const override{
					using namespace rapidjson;
					StringBuffer sb;
					Writer<StringBuffer> writer(sb);
					writer.StartArray();  // start of states --array
					for (auto& st : state_data) {
						writer.StartObject();   // start of this state
						writer.Key("_state_name"); writer.String(st.getStateName().c_str());
						writer.Key("_stroke_color"); writer.String(st.getStrokeColor().c_str());
						writer.Key("_fill_color"); writer.String(st.getFillColor().c_str());
						writer.Key("_stroke_width"); writer.Double(st.getStrokeWidth());
						writer.Key("_view_counties"); writer.Bool(st.getViewCountiesFlag());
						writer.Key("_counties"); 
						// get all the counties
						writer.StartArray();   // start of counties for this state
						for (auto& c : st.getCounties()) {
							writer.StartObject();	// start of this county
							writer.Key("_geoid"); writer.String(c.second.getGeoId().c_str());
							writer.Key("_fips_code"); writer.String(c.second.getFipsCode().c_str());
							writer.Key("_county_name"); writer.String(c.second.getCountyName().c_str());
							writer.Key("_state_name"); writer.String(c.second.getStateName().c_str());
							writer.Key("_stroke_color"); writer.String(c.second.getStrokeColor().c_str());
							writer.Key("_stroke_width"); writer.Double(c.second.getStrokeWidth());
							writer.Key("_fill_color"); writer.String(c.second.getFillColor().c_str());
							writer.Key("_hide"); writer.Bool(c.second.getHideFlag());
							writer.EndObject();  // end of this county 
						}
						writer.EndArray();  // end of counties for this state
						writer.EndObject(); // end of this state
					}
					writer.EndArray(); // end of states

					return sb.GetString();
				}
			public: 
				USMap(vector<State> st_data) {
					state_data = st_data;
				}

				vector<State>& getStates() {
					return state_data;
				}
	
				virtual const string getDStype() const override {
					return "us_map";
				}
		};
	}
}
#endif
