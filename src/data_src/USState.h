#ifndef STATE_H
#define STATE_H

#include "USCounty.h"
#include "../Color.h"

#include <string>
#include <unordered_map>

using std::string;

namespace bridges {
	namespace dataset {
		/*
		 * @brief This object stores US State and links to information
		 *
		 * This object is used alongside with the USMap object. Each state
		 * has a stroke color and fill color and list of counties of type County
		 *
		 *  See tutorial at  https://bridgesuncc.github.io/tutorials/Map.html
		 *
		 * @author Kalpathi Subramanian, Erik Saule
		 * @date  Last modified Dec 29, 2024
		 */
		class USState {
				string name;
				datastructure::Color stroke_color;
				bool view_counties;  // flag to visualize county boundaries
				float stroke_width;  // boundary color
				datastructure::Color fill_color; // fill color of state
				unordered_map<string, USCounty> counties; // holds county info

			public:
				USState() = default;

				USState(string st) {
					name = st;
					stroke_color = datastructure::Color("red");
					view_counties = true;
					stroke_width = 2.;
					fill_color = datastructure::Color("blue");
				}
				/**
				 * @brief obtain a copy of the county data for that state
				 *
				 * The Counties are indexed by FIPS code. (FIPS code are
				 * defined by the US Federal Government. See list here:
				 * https://transition.fcc.gov/oet/info/maps/census/fips/fips.txt )
				 *
				 */
				unordered_map<string, USCounty> getCounties() const {
					return counties;
				}
				/**
				 * @brief obtain reference to the county data for that state
				 *
				 * This is mostly useful to get direct access to the county data inside of the state for manipulation. For instance
				 * \code{c}
				 * State s;
				 * for (auto& c: s.accessCounties()) {
				 *   c.second.setStrokeColor(Color(50,250,50));
				 *   c.second.setFillColor(Color(0,0,25));
				 * }
				 * \endcode{c}
				 *
				 **/
				unordered_map<string, USCounty>& accessCounties() {
					return counties;
				}

				/**
				 * @brief  sets the counties for this state
				 *
				 * @param c  list o counties of this state
				 */
				void setCounties(unordered_map<string, USCounty> & c) {
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

				/**
				 * @brief this flag lets you turn  on/off counties as needed
				 */
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
