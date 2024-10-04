#ifndef STATE_H
#define STATE_H

#include "County.h"

#include <string>

using std::string;


namespace bridges{
	namespace dataset {

		class State {
				string name;
				Color stroke_color;
				bool view_counties;
				float stroke_width;
				Color fill_color;
				unordered_map<int, County> counties;

			public:
				State(string st) {
        			name = st;
					stroke_color = Color("blue");
					view_counties = true;
					stroke_width = 0.5;
					fill_color = Color("blue");
				}
				unordered_map<int, County> getCounties() {
					return counties;
				}
				void setCounties(unordered_map<int, County> & c) {
					counties = c;;
				}
				// getters, setters
				string getStateName() {
					return name;
				}
		};
	};
}
/*
    @property
    def state_name(self):
        return self._state_name

    @state_name.setter
    def state_name(self, value):
        self._state_name = value

    @property
    def stroke_color(self):
        return self._stroke_color

    @stroke_color.setter
    def stroke_color(self, value):
        self._stroke_color = value

    @property
    def counties(self):
        return self._counties

    @counties.setter
    def counties(self, value):
        self._counties = value

    @property
    def view_counties(self):
        return self._view_counties

    @view_counties.setter
    def view_counties(self, value):
        self._view_counties = value

    @property
    def stroke_width(self):
        return self._stroke_width

    @stroke_width.setter
    def stroke_width(self, value):
        self._stroke_width = value

    @property
    def fill_color(self):
        return self._fill_color

    @fill_color.setter
    def fill_color(self, value):
        self._fill_color = value
*/


#endif
