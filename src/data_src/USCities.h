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
				float latit, longit;

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
					elevation = elev;
					population = pop;
					latit = lat;
					longit = lon;
				}


				string getCity() {
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

				string getTimeZone() {
					return time_zone;
				}

				void setTimeZone(string tz){
					time_zone = tz;
				}

				float  getLatitude() {
					return latit;
				}

				void setLatitude(float lat) {
					latit = lat;
				}

				float  getLongitude()  {
					return longit;
				}

				void setLongitude(float lon) {
					longit = lon;
				}
				float  getPopulation()  {
					return population;
				}

				void setPopulation(int pop) {
					population = pop;
				}

				int  getElevation()  {
					return elevation;
				}

				void setElevation(int elev) {
					elevation = elev;
				}

		};
	};
};
#endif
