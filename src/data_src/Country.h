#ifndef COUNTRY_H
#define COUNTRY_H

#include "../Color.h"

#include <string>
#include <unordered_map>

using std::string;

namespace bridges {
	namespace dataset {
		/*
		 * @brief This object stores a Country and links to information
		 *
		 * This object is used alongside with the WorldMap object. Each country
		 * has a stroke color and fill color.
		 *
		 *  See tutorial at  https://bridgesuncc.github.io/tutorials/Map.html
		 *
		 * @author Kalpathi Subramanian, Erik Saule
		 * @date  Last modified May 22, 2025
		 */
		class Country {
				string name;
				datastructure::Color stroke_color;
				float stroke_width;  // boundary color
				datastructure::Color fill_color; // fill color of state

			public:
				Country() = default;

				Country(string cntry) {
					name = cntry;
					stroke_color = datastructure::Color("red");
					stroke_width = 2.;
					fill_color = datastructure::Color("blue");
				}

				// getters, setters
				string getCountryName() const {
					return name;
				}
				void setCountryName(string n) {
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
		};
	};
};
#endif
