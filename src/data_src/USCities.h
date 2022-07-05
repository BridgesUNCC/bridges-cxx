#ifndef US_CITIES_H

#define US_CITIES_H

#include <string>

using std::string;

namespace bridges {
	namespace dataset {

		class USCities {

			private:
				string city, state, country, time_zone;
				int elevation, population;
				float latit, lonit;

			public:
				USCities() {
					city = state = country = time_zone = string();
					elevation = population = 0;
					latit = longit = 0.;
				}
				USCities (string cty, string st, string cntry, string tm_zone,
						int elev, int pop, float lat, float lon) {
					city = cty;
					state = st;
					country = cntry;
					time_zone = tm_zone;
					latit = lat;
					longit = lon;
				}


				int getCity() {
					return city;
				}

				void setCity(string c) {
					city = c;
				}

				string  getState() {
					return state;
				}

				void  setState(string st) {
					state = st;;
				}

				string getCountry() {
					return country;
				}

				void setCountry(string cntry) {
					country = cntry;
				}

				int getTimeZone() {
					return time_zone;
				}

				void setTimeZone(int tz){
					time_zone = tz;
				}

				int  getLatitude() {
					return latit;
				}

				void setLatitude(float lat) {
					latit = lat;
				}

				int  getLongitude()  {
					return longit;
				}

				void setLongitude(float lon) {
					longit = lon;
				}

		};
	};
};
#endif
