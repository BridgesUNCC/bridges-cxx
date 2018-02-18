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

									// access by date
			int year, month, day,  hour, min, sec;

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
				this->time = time;
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
			
			void getDate () {
								// get eq's epoch time
				string s = getTime();

				long epoch_time = std::stol(getTime());
				time_t eq_time = epoch_time/1000;

								// convert to time_t 
				
				struct tm *eqt = gmtime(&eq_time);

				year = eqt->tm_year + 1900;
				month = eqt->tm_mon;
				day = eqt->tm_mday;
				hour = eqt->tm_hour;
				sec = eqt->tm_sec;
				min = eqt->tm_min;
			}

						// returns the real date in a string
			string getDateStr() {
				getDate();
				string mstr;

				switch (month) {
					case 0 : mstr = "Jan. "; break;
					case 1 : mstr = "Feb. "; break;
					case 2 : mstr = "Mar. "; break;
					case 3 : mstr = "Apr. "; break;
					case 4 : mstr = "May "; break;
					case 5 : mstr = "Jun. "; break;
					case 6 : mstr = "Jul. "; break;
					case 7 : mstr = "Aug. "; break;
					case 8 : mstr = "Sept. "; break;
					case 9 : mstr = "Oct. "; break;
					case 10 : mstr = "Nov. "; break;
					case 11 : mstr = "Dec. "; break;
				}

						// put into a string
				string date_str = "  " + mstr+ to_string(day) + "  " + to_string(year) +
					"  " + to_string(hour)+":"+to_string(min)+":" + to_string(sec);

				return date_str;
			}
					
			void setTime (string tm) {
				// process tm to convert to a date
				time = tm;
			}

			int getYear() {
				getDate();

				return year;
			}
			int getMonth() {
				getDate();

				return month;
			}
			int getDay() {
				getDate();

				return day;
			}
			int getHour() {
				getDate();

				return hour;
			}
			int getMinutes() {
				getDate();

				return min;
			}
			int getSeconds() {
				getDate();

				return sec;
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
