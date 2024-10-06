
#ifndef COUNTY_H
#define COUNTY_H

#include <string>

using std::string;


namespace bridges{
	namespace dataset {

		class County {
			private:
				string geoid;
				string fips_code;
				string county_name;
				string state_name;
				string  stroke_color;
				float stroke_width;
				string  fill_color;
				bool hide;

			public:
				County() = default;
				County (int id, int code, string county, string state) {
        			geoid = id;
					fips_code = code;
					county_name = county;
					state_name = state;
					stroke_width = 0.5;
					fill_color = "blue";
					stroke_color = "blue";
					hide = false;
				}
				// getters, setters
				string getGeoId() {
					return geoid;
				}
				string getFipsCode() {
					return fips_code;
				}
				string getCountyName() {
					return county_name;
				}
				string getStateName() {
					return state_name;
				}
				string getStrokeColor() {
					return stroke_color;
				}
				string getFillColor() {
					return fill_color;
				}
				float getStrokeWidth() {
					return stroke_width;
				}
				bool getHideFlag() {
					return hide;
				}
		};
	};
};
#endif
