#ifndef STATE_H
#define STATE_H

#include "County.h"

#include <string>

using std::string;


namespace bridges{
	namespace dataset {

		class State {
				string name;
				string stroke_color;
				bool view_counties;
				float stroke_width;
				string fill_color;
				unordered_map<string, County> counties;

			public:
				State() = default;

				State(string st) {
        			name = st;
					stroke_color = "blue";
					view_counties = true;
					stroke_width = 0.5;
					fill_color = "blue";
				}
				unordered_map<string, County> getCounties() const {
					return counties;
				}
				void setCounties(unordered_map<string, County> & c) {
					counties = c;;
				}
				// getters, setters
				string getStateName() const {
					return name;
				}
				string getStrokeColor() const {
					return stroke_color;
				}
				string getFillColor() const {
					return fill_color;
				}
				float getStrokeWidth() const {
					return stroke_width;
				}
				bool getViewCountiesFlag() const {
					return view_counties;
				}
		};
	};
};
#endif
