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
				string name;		// country name
				string alpha2_id; 	// two letter alphabetic id
				string alpha3_id; 	// three letter alphabetic id
				int numeric3_id; 	// numerical id
				datastructure::Color fill_color; // fill color of country
				datastructure::Color stroke_color; // boundary color
				float stroke_width; // boundary width

			public:
				/**
				 *  @brief constructors
				 */
				Country() = default;

                /**
				 * @brief creates a country object for a specific country
				 *
				 * @param cntry  country name
				 */
				Country(string cntry) {
					name = cntry;
					alpha2_id = "";
					alpha3_id = "";
					numeric3_id = 0;
					stroke_color = datastructure::Color("green");
					stroke_width = 1.;
					fill_color = datastructure::Color("lightblue");
				}

                /**
                 *  @brief  creates a country object with specific parameters
				 *
				 *  @param cntry  country name
				 *  @param alpha2  2 letter alpabet code for country
				 *  @param alpha3  3 letter alpabet code for country
				 *  @param numeric  numeric id
				 *  @param fill_col  fill color 
				 *  @param stroke_col  boundary color
				 *  @param stroke_w  stroke width
				 */ 
				Country (string cntry, string alpha2, string alpha3, int numeric,
					datastructure::Color fill_col, datastructure::Color stroke_col,
					float stroke_w) {
					name = cntry;
					alpha2_id = alpha2;
					alpha3_id = alpha3;
					numeric3_id = numeric;
					fill_color = fill_col;
					stroke_color = stroke_col;
					stroke_width = stroke_w;
				}

				/**
				 *   @brief getters, setters  for class
				 */
				string getCountryName() const {
					return name;
				}
				void setCountryName(string n) {
					name = n;
				}
				string getAlpha2Id() const {
					return alpha2_id;
				}
				void setAlpha2Id(string id) {
					alpha2_id = id;
				}
				string getAlpha3Id() const {
					return alpha3_id;
				}
				void setAlpha3Id(string id) {
					alpha3_id = id;
				}
				int getNumeric3Id() const {
					return numeric3_id;
				}
				void setNumeric3Id(int id) {
					numeric3_id = id;
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
