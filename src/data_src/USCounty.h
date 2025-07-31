#ifndef COUNTY_H
#define COUNTY_H

#include <string>
#include "Color.h"

using std::string;

namespace bridges {
	namespace dataset {

		/**
		 * @brief This object contains US county related information
		 *
		 * This object is used alongside with the USMap object. Each county
		 * has a stroke color and fill color attributes. Each county has a geoid
		 * and FIPS code for identification. The geoid is used as the key in the
		 * USState object to efficiently access the county information using a
		 * hash table
		 *
		 *  See tutorial at  https://bridgesuncc.github.io/tutorials/Map.html
		 *
		 * @author Kalpathi Subramanian, Erik Saule
		 * @date  Last modified Dec 29, 2024
		 */
		class USCounty {
			private:
				string geoid;
				string fips_code;
				string county_name;
				string state_name;
				datastructure::Color  stroke_color;
				float  stroke_width;
				datastructure::Color  fill_color;
				bool hide;			// county visibility

			public:
				/**
				 *
				 * @brief Constructor
				 */
				USCounty() = default;

				/**
				 *
				 * @brief Constructor
				 *
				 * @param id Geoid of county
				 * @param code  FIPS code of county
				 * @param county  county name
				 * @param state   state containing the county
				 *
				 */
				USCounty (string id, string code, string county, string state) {
					geoid = id;
					fips_code = code;
					county_name = county;
					state_name = state;
					stroke_width = 0.5;
					fill_color = datastructure::Color("lightblue");
					stroke_color = datastructure::Color("green");
					hide = false;
				}
				// getters, setters
				string getGeoId() const {
					return geoid;
				}

				string getFipsCode() const {
					return fips_code;
				}

				void setFipsCode(string code) {
					fips_code = code;
				}

				string getStateName() const {
					return state_name;
				}
				void setStateName(string n) {
					state_name = n;
				}
				string getCountyName() const {
					return county_name;
				}
				void setCountyName(string n) {
					county_name = n;
				}

				datastructure::Color getStrokeColor() const {
					return stroke_color;
				}
				void setStrokeColor(datastructure::Color c) {
					stroke_color = c;
				}

				datastructure::Color getFillColor() const {
					return fill_color;
				}
				void setFillColor(datastructure::Color c) {
					fill_color = c;
				}

				float getStrokeWidth() const {
					return stroke_width;
				}
				void setStrokeWidth(float width) {
					stroke_width = width;
				}

				bool getHideFlag() const {
					return hide;
				}
				void setHideFlag(bool flag) {
					hide = flag;
				}

		};
	};
};
#endif
