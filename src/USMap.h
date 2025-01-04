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
		 * In the current implementation, we can draw a US map  with all state
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
		 * See the Maps tutorials for examples of the usage of the US Map API
		 *  at  https://bridgesuncc.github.io/tutorials/Map.html
		 *
		 */
		class USMap :  public Map, public DataStructure {
			private:
				vector<string> state_names;
				vector<USState> state_data;

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
					return JSONencode("mapdummy") + COLON + JSONencode(true) + CLOSE_CURLY;
				}
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
					// generates a JSON of the states with county information
					string map_str = OPEN_BOX;
					using bridges::JSONUtil::JSONencode;
					for (auto& st : state_data) {
						map_str += OPEN_CURLY +
							QUOTE + "_state_name" + QUOTE + COLON +
							JSONencode(st.getStateName()) + COMMA +
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
				/*
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
								virtual const string getMapRepresentation () const override{
									using namespace rapidjson;
									Document d;
									d.SetObject();
									Document::AllocatorType& allocator = d.GetAllocator();
									Value key, value;
									Value st_array(kArrayType);
									for (auto& st : state_data) {
										Value st_obj;
										st_obj.SetObject();
										key.SetString("_state_name", allocator);
										value.SetString(st.getStateName().c_str(), allocator);
										st_obj.AddMember(key, value, allocator);

										key.SetString("_stroke_color", allocator);
										value.SetString(st.getStrokeColor().c_str(), allocator);
										st_obj.AddMember(key, value, allocator);

										key.SetString("_fill_color", allocator);
										value.SetString(st.getFillColor().c_str(), allocator);
										st_obj.AddMember(key, value, allocator);

										key.SetString("stroke_width", allocator);
										value.SetDouble(st.getStrokeWidth());
										st_obj.AddMember(key, value, allocator);

										key.SetString("_view_counties", allocator);
										value.SetBool(st.getViewCountiesFlag());
										st_obj.AddMember(key, value, allocator);

											// put counties into an array
										Value ct_array(kArrayType);
										for (auto& c : st.getCounties()) {
											Value c_obj;
											c_obj.SetObject();

											key.SetString("_geoid", allocator);
											value.SetString(c.second.getGeoId().c_str(), allocator);
											c_obj.AddMember(key, value, allocator);

											key.SetString("_fips_code", allocator);
											value.SetString(c.second.getFipsCode().c_str(), allocator);
											c_obj.AddMember(key, value, allocator);

											key.SetString("_county_name", allocator);
											value.SetString(c.second.getCountyName().c_str(), allocator);
											c_obj.AddMember(key, value, allocator);

											key.SetString("_state_name", allocator);
											value.SetString(c.second.getStateName().c_str(), allocator);
											c_obj.AddMember(key, value, allocator);

											key.SetString("_stroke_color", allocator);
											value.SetString(c.second.getStrokeColor().c_str(), allocator);
											c_obj.AddMember(key, value, allocator);

											key.SetString("_stroke_width", allocator);
											value.SetDouble(c.second.getStrokeWidth());
											c_obj.AddMember(key, value, allocator);

											key.SetString("_fill_color", allocator);
											value.SetString(c.second.getFillColor().c_str(), allocator);
											c_obj.AddMember(key, value, allocator);

											key.SetString("_hide", allocator);
											value.SetBool(c.second.getHideFlag());
											c_obj.AddMember(key, value, allocator);

											ct_array.PushBack(c_obj, allocator);
										}
										st_obj.AddMember("counties", ct_array, allocator);
										st_array.PushBack(st_obj, allocator);
										d.AddMember("states", st_array, allocator);
									}

									// convert to string
									StringBuffer sb;
									Writer<StringBuffer> writer(sb);
									d["states"].Accept(writer);


									string s = sb.GetString();
									string s2 = s.substr(10, s.size()-11);
				cout << "Map String(JSON) " << s << endl;

									return s;
								}
				*/
			public:
				/*
				 * @brief Constructs a US Map object  with map data
				 *
				 * @param   st_data  data containg state/county information
				 */
				USMap(vector<USState> st_data) {
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
