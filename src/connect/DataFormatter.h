#include <string>
#include <sstream>
#include <regex>
#include "./data_src_dependent/DataSource.h"
#include "./data_src_dependent/EarthquakeUSGS.h"
#include <curl/curl.h>
#include <time.h>

#ifndef DATA_FORMATTER_H

#define DATA_FORMATTER_H

/** This class contains all the methods and interfaces to external datasets; the general
 *	idea is to provide methods that provide end users ease of access to real-world data.
 *  One such dataset, earthquakes from USGS feeds is provided. The method provides
 *  a way to access the latest earthquakes(the current data is stored in a Mongo DB.
 * 
 * @author Kalpathi Subrmanian
 * @date 7/10/16
 *
 */

using namespace std;

						//  method to retrieve data from data source
size_t writeDataFunc(void *contents, size_t size, size_t nmemb, string *s);

namespace bridges {


class DataFormatter {
	private:
						// limit the max retrieved records to 500
		const int MAX_QUAKES = 500;
						// access to class object
		static DataFormatter *current;

	public:

						// constructor
		DataFormatter() {
			current = this;
		}

						// accessors
		static DataFormatter *getCurrent() {
			return current;
		}
		static void setCurrent(DataFormatter *cur) {
			DataFormatter::current = cur;
		}	

		/** 
		 *  Method to extract USGS earthquake data
		 *
		 * @param max quakes requested
		 * @return  an array of EarthquakeUSGS objects
		 *
		 */
		vector<EarthquakeUSGS> *getUSGSEarthquakeData (int max_quakes) {

								// error checking
			if (max_quakes < 0) {
				cerr << "Number of quakes specified is negative! Exiting" 
											<< endl;
				exit(1);
			}
								// limit max quakes to MAX_QUAKES
			max_quakes  = (max_quakes> MAX_QUAKES) ? MAX_QUAKES : max_quakes;

								// retrieve data (JSON strings) - uses CURL library
			string eq_data = getEarthquakeDataFromSource(max_quakes);

							 	// parse data into an array of objets
			return FormatEarthQuakeData(eq_data, max_quakes);
	}

	private:
		/** 
		 *	Retrieve  the earthquake data by an HTTP GET request into a single JSON
		 *  string; uses <regex>
		 *
		 *  @param max_quakes
		 *
		 *  @return JSON string
		 */

		string getEarthquakeDataFromSource(int max_quakes) {

						// retrieve quake data as a string from the DB

						// use CURL get command to get the data
			string eq_data;
			CURL *curl = curl_easy_init();
			char *ptr = new char[10000];
			if (curl) {
				CURLcode res;
							// form the url
				ostringstream oss;
				oss << max_quakes;
				string url = 
					"https://earthquakes-uncc.herokuapp.com/eq/latest/" + oss.str();
cout << "URL : " << url << endl;
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDataFunc);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &eq_data);
				res = curl_easy_perform(curl);
				curl_easy_cleanup(curl);
			}
			return eq_data;
		}
		///////////////////////////////////////////////////////////////
		/** 
		 *	Parse the data retrieved by HTTP Get into a set of individual JSON
		 *  strings and format them into object ; uses <regex>
		 *
		 *  @param max_quakes
		 *
		 *  @return 
		 */
		vector<EarthquakeUSGS> *FormatEarthQuakeData(string eq_data, 
									int max_quakes) {

			int box_parens = 0, curly_parens = 0, parens = 0; 
			int k, j, eq_cnt = 0;

							// first break up the eq records into individual
							// strings
			string *eq_str = new string[max_quakes];

							// scan to first box parens (start of eq data)
			char ch = ' ';
			for (k = 0; k < eq_data.length(); k++) {
				if (eq_data[k] == '[') {
					box_parens++; k++;
					break;
				}
			}
			while (box_parens) {
							// scan to first curly parens-beginning of record
				for (; k < eq_data.length(); k++) {
					if (eq_data[k] == '{') {
						eq_str[eq_cnt].push_back(eq_data[k]);
						curly_parens++, k++;
						break;
					}
					else if (eq_data[k] == ']') { // could be at the end
						box_parens--;
					}
				}
				if (!box_parens)		// done
					break;
						// begin eq record
				j = 0;
				while (curly_parens) {
					switch (eq_data[k]) {
						case '[' : box_parens++; break;
						case '(' : parens++; break;
						case '{' : curly_parens++; break;
						case ']' : box_parens--; break;
						case ')' : parens--; break;
						case '}' : curly_parens--; break;
					}


					if (box_parens == 0)		// done
						break;

					eq_str[eq_cnt].push_back(eq_data[k]);
					k++;
					if (curly_parens == 0) { 	// end of eq record k
						eq_cnt++;
					}
				}
			}
	
					// now have each EQ record as a string, use regular
					// expressions to extract the fields of interest and 
					// put them into objects
					
					// allocate space for earthquake records
			vector<EarthquakeUSGS> *equsgs = new vector<EarthquakeUSGS>(
														max_quakes);

					// we will extract lat/long coords, url, magnitude, title
					// and quake time; use regular expressions for first level
					// parsing

			regex pattern_geom(
				"\"geometry\":\\{([[:digit:]]|[[:alpha:]]|:|,|\"|\\+|-|\\.|\\[|\\])+\\}");
			regex pattern_url("\"url\":\"([[:alnum:]]|\\.|/|:)+\"");
			regex pattern_title("\"title\":\".*\",");
			regex pattern_props("\"properties\":\\{.*\\}");

			std::smatch props, time, time2, 
						place, place2, url, 
						geom, geom2, title, mag, mag2;

			string mag_s, time_s, place_s, title_s, url_s, geom_s, coords_s;
			istringstream iss;

					// finally, parse the EQ strings into objects
			for (int k = 0; k < max_quakes; k++) {
							// get the properties attribute; this contains
							// magnitude, time and location
				std::regex_search(eq_str[k], props, pattern_props);

				time_s.clear(); place_s.clear(); mag_s.clear(); url_s.clear();
				title_s.clear(); coords_s.clear();

							// extract eq magnitude
				size_t found;
				string props_s = props.str(0);
				found = props_s.find("mag");	
				int indx;
				if (found != std::string::npos) {
								// skip to first ':' character
					for (indx = found; props_s[indx] != ':'; indx++);
								// extract the magnitude as a string
					for (int j = indx+1; props_s[j] != ','; j++)
						mag_s.push_back(props_s[j]);
				}


								// get the epoch time
				found = props_s.find("time");	
				if (found != std::string::npos) {
								// skip to first ':' character
					for (indx = found; props_s[indx] != ':'; indx++);
								// skip to first '"' character
					for (; props_s[indx] != '"'; indx++);
								// extract epoch time as a string
					for (int j = indx+1; props_s[j] != '"'; j++)
						time_s.push_back(props_s[j]);
				}

								// get the eq location
				found = props_s.find("place");	
				if (found != std::string::npos) {
								// skip to first ':' character
					for (indx = found; props_s[indx] != ':'; indx++);
								// skip to first '"' character
				for (; props_s[indx] != '"'; indx++);
								// extract the location as a string
				for (int j = indx+1; props_s[j] != '"'; j++)
					place_s.push_back(props_s[j]);
				}

							// get the eq url for more info
				found = props_s.find("url");	
				if (found != std::string::npos) {
								// skip to first ':' character
					for (indx = found; props_s[indx] != ':'; indx++);
								// skip to first '"' character
					for (; props_s[indx] != '"'; indx++);
								// get the url as a string
					for (int j = indx+1; props_s[j] != '"'; j++)
						url_s.push_back(props_s[j]);
				}

							// get the title
				found = props_s.find("title");	
				if (found != std::string::npos) {
								// skip to first ':' character
					for (indx = found; props_s[indx] != ':'; indx++);
								// skip to first '"' character
					for (; props_s[indx] != '"'; indx++);
								// get the title as a string
					for (int j = indx+1; props_s[j] != '"'; j++)
						title_s.push_back(props_s[j]);
				}
		
							// get the Lat/Long coordinates
				std::regex_search(eq_str[k], geom, pattern_geom);

				geom_s = geom.str(0);
				found = geom_s.find("coordinates");	
				if (found != std::string::npos) {
							// array: skip to first '['
					for (indx = found; geom_s[indx] != '['; indx++);
								// scan till first ']'
					for (int j = indx+1; geom_s[j] != ']'; j++)
								// extract lat/long as a string
								// replace comma separators with spaces
						if (geom_s[j] == ',')
							coords_s.push_back(' ');
						else
							coords_s.push_back(geom_s[j]);
				}
		
								// put this in to EarthquakeUSGS object
								// use istringstream to convert types
				double magn;
				float latit, longit;
				long time;

				iss.clear(); iss.str(mag_s); iss >> magn;
				(*equsgs)[k].setMagnitude(magn);

				(*equsgs)[k].setTitle(title_s);
				(*equsgs)[k].setUrl(url_s);

				iss.clear(); iss.str(coords_s); iss >> latit >> longit;
				(*equsgs)[k].setLatit(latit);
				(*equsgs)[k].setLongit(longit);
	
				iss.clear(); iss.str(time_s); iss >> time;
								// convert time to a date string
				time_t rawtime = time/1000;
				struct tm *timeinfo = localtime(&rawtime);
				string time_s = asctime(timeinfo);
				size_t p = time_s.find('\n');	// removing carriage return
				if (p != std::string::npos)
					time_s.erase(p);

				(*equsgs)[k].setTime(time_s);
				(*equsgs)[k].setLocation(place_s);
			}

			return equsgs;
		}
};
	///////////////////////////////////////////////////////////////

} // namespace bridges

							// call back function to store eq data in a string
size_t writeDataFunc(void *contents, size_t size, size_t nmemb, string *s){
	size_t newLength = size*nmemb;
	size_t oldLength = s->size();
	try {
		s->resize(oldLength + newLength);
	}
	catch(std::bad_alloc &e) {
					//handle memory problem
		cout << "Error: resizing buffer! Exiting" << endl;
		return 0;
	}

	std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
	return size*nmemb;
} 

#endif
