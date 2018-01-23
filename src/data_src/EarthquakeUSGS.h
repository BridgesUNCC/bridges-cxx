#ifndef EARTHQUAKEUSGS_H

#define EARTHQUAKEUSGS_H

#include <string>

using namespace std;

namespace bridges {

	class EarthquakeUSGS {
		private:
			double magnitude;		// earthquake magnitude
			double latit;			// earthquake location
			double longit;			// (lat/long)
			string location;		// location of quake
			string title;			// combo info of quake
			string url;				// url for more info
			string time;				// date

		public:

			EarthquakeUSGS() {
				this->magnitude = 0.0;
				this->latit = 0.0;
				this->longit = 0.0;
				this->location = "";
				this->title = "";
				this->url = "";
				this->time = "";
			}

			EarthquakeUSGS(double magnitude, double longit, double latit,
				string location, string title, string url, string time) {
				this->magnitude = magnitude;
				this->time = time;
				this->longit = longit;
				this->latit = latit;
				this->location = location;
				this->title = title;
				this->url = url;
				this->time = "";
			}

			EarthquakeUSGS(EarthquakeUSGS *eq) {
				this->magnitude = eq->magnitude;
				this->latit = eq->latit;
				this->longit = eq->longit;
				this->location = eq->location;
				this->title = eq->getTitle();
				this->url = eq->url;
				this->time = eq->time;
			}

			string getTime() {
				return time;
			}
			
			void getDate (int *year, int *month, int *day, int *hour, 
						int *min, int *sec){

								// get eq's epoch time
				string s = getTime();
				cout << "[getDate]Time String:" << s << endl;
//				time_t eq_time = std::stol(getTime());
				time_t eq_time = std::stol("1514337140");
								// convert to time_t 
//				time (&eq_time)
				
				struct tm *eqt = gmtime(&eq_time);

				*year = eqt->tm_year;
				*month = eqt->tm_mon;
				*day = eqt->tm_mday;
				*hour = eqt->tm_hour;
				*sec = eqt->tm_sec;
				*min = eqt->tm_min;
			}
			string getDate() {
				int y, m, d, h, min, s;
				getDate(&y, &m, &d, &h, &min, &s);
				y += 1900;
				string mstr;
				switch (m) {
					case 1 : mstr = "Jan. "; break;
					case 2 : mstr = "Feb. "; break;
					case 3 : mstr = "Mar. "; break;
					case 4 : mstr = "Apr. "; break;
					case 5 : mstr = "May "; break;
					case 6 : mstr = "Jun. "; break;
					case 7 : mstr = "Jul. "; break;
					case 8 : mstr = "Aug. "; break;
					case 9 : mstr = "Sept. "; break;
					case 10 : mstr = "Oct. "; break;
					case 11 : mstr = "Nov. "; break;
					case 12 : mstr = "Dec. "; break;
				}
						// put into a string
				return "  " + mstr+ to_string(d) + "  " + to_string(y) +
					"  " + to_string(h)+":"+to_string(min)+":" + to_string(s);
			}
					
			void setTime (string tm) {
				// process tm to convert to a date
				time = tm;
			}
			float getLatit() {
				return this->latit;
			}
			void setLatit(float latit) {
				this->latit = latit;
			}
			float getLongit() {
				return longit;
			}
			void setLongit(float longit) {
				this->longit = longit;
			}
			string getLocation() {
				return location;
			}
			void setLocation(string location) {
				this->location = location;
			}
			string getTitle() {
				return this->title;
			}
			void setTitle(string title) {
				this->title = title;
			}
			string getUrl() {
				return url;
			}
			void setUrl(string url) {
				this->url = url;
			}
			double getMagnitude() {
				return this->magnitude;
			}
			void setMagnitude(double magnitude) {
				this->magnitude = magnitude;
			}
	};

} // namespace bridges

#endif
