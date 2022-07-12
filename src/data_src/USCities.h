#ifndef US_CITIES_H

#define US_CITIES_H

#include <string>

using std::string;


namespace bridges {
	namespace dataset {

		class USCities {
			/**
			 * @brief Class that holds data of US Cities
 			 * 
			 * A user would not normally create an ElevationData object but 
			 * rather obtain one from calling bridges::DataSource::getUSCities()
			 *
			 * A tutorial on how to use the US Cities dataset is available at: 
			 *  https://bridgesuncc.github.io/tutorials/USCities.html (to be done!)
			 *
			 * Each city contains the city name, state, country, time zone, elevation,
			 *  population and lat/long location information.
			 *
			 * @author Kalpathi Subramanian
			 *
			 * @date 6/7/22
			 */

			private:
				string city, state, country, time_zone;
				int elevation, population;
				float latit, longit;   // city location

			public:
				/**
				 *  Constructors
				 */
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

				int getElevation() {
					return elevation;
				}

				void setElevation(int elev) {
					elevation = elev;
				}

				int getPopulation() {
					return population;
				}

				void setPopulation(int pop) {
					population = pop;
				}
		};
	};
};
#endif
