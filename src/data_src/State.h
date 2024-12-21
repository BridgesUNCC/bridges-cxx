#ifndef STATE_H
#define STATE_H

#include "County.h"
#include "../Color.h"

#include <string>
#include <unordered_map>

// Class that defines a US State and its counties
// Last  modified:  Dec. 20, 2024
// Autho: Kalpathi Subramanian, Erik Saule

using std::string;


namespace bridges{
	namespace dataset {

		class State {
				string name;
				datastructure::Color stroke_color;
				bool view_counties;  // flag to visualize county boundaries
				float stroke_width;
				datastructure::Color fill_color;
				unordered_map<string, County> counties; // holds county info

			public:
				State() = default;

				State(string st) {
        			name = st;
					stroke_color = datastructure::Color("red");
					view_counties = true;
					stroke_width = 0.5;
					fill_color = datastructure::Color("blue");
				}
				unordered_map<string, County> getCounties() const {
					return counties;
				}
				unordered_map<string, County>& accesCounties() {
					return counties;
				}
				void setCounties(unordered_map<string, County> & c) {
					counties = c;
				}

				// getters, setters
				string getStateName() const {
					return name;
				}
				void setStateName(string n) {
					name = n;	
				}

				datastructure::Color getStrokeColor() const {
					return stroke_color;
				}
				void setStrokeColor(datastructure::Color c) {
					stroke_color = c; 
				}

				datastructure::Color getFillColor() const {
					return fill_color;
				}
				void setFillColor(datastructure::Color c) {
					fill_color = c;
				}

				float getStrokeWidth() const {
					return stroke_width;
				}
				void setStrokeWidth(float width) {
					stroke_width = width;
				}

				bool getViewCountiesFlag() const {
					return view_counties;
				}
				void setViewCountiesFlag(bool flag) {
					view_counties = flag;
				}
		};
	};
};
#endif
