#ifndef EARTHQUAKEUSGS_H

#define EARTHQUAKEUSGS_H

#include <string>
#include "DataSource.h"

using namespace std;

namespace bridges {

class EarthquakeUSGS : public DataSource {
	private:
		double magnitude;		// earthquake magnitude
		float latit;			// earthquake location
		float longit;			// (lat/long)
		string location;		// location of quake
		string title;			// combo info of quake
		string url;				// url for more info
		string time;			// date
	
	public:

	
	EarthquakeUSGS(double magnitude, long time, float longit, 
			float latit, string location, string title, string url) {
		this->magnitude = magnitude;
		this->time = time;
		this->longit = longit;
		this->latit = latit;
		this->location = location;
		this->title = title;
		this->url = url;
	}

	EarthquakeUSGS(EarthquakeUSGS *eq){
		this->magnitude = eq->magnitude;
		this->latit = eq->latit;
		this->longit = eq->longit;
		this->location = eq->location;
		this->title = eq->getTitle();
		this->url = eq->url;
	}
		
	string getTime() {
		return time;	
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
	EarthquakeUSGS() {
		this->magnitude = 0.0;
		this->latit = 0.0;
		this->longit = 0.0;
		this->location = "";
		this->title = "";
		this->url = "";
	}
		
	
};

} // namespace bridges

#endif
