#ifndef VALIDATION_H

#define VALIDATION_H

#include <string>
#include <unordered_set>
#include <regex>


using namespace std;

namespace bridges{
/**
 * 
 * @brief This class performs certain validation checks to ensure the 
 *  robustness of the BRIDGES  system. 

 * Validatoin checks are made for legal specification of visual properties
 * such as color names, element size, opacity values, 
 * the maximum number of BRIDGES elements (currently set at 5000).
 *
 * @author Kalpathi Subramanian(C++ port), 
 *
 * @date 6/22/15 
 *
 **/

class Validation {

	private:
		unordered_set<string> ColorNames, NodeShapes;
		regex ColorPatterns;
					// this variable holds the maximum number of 
					// nodes allowed starting from 0
		int MAX_ELEMENTS_ALLOWED = 5000; 

		static Validation *current;
		
	public:
		Validation() {
			ColorPatterns = "#[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]";
			ColorNames.insert({
					"aliceblue",
					"antiquewhite",
					"aqua",
					"aquamarine",
					"azure",
					"beige",
					"bisque",
					"black",
					"blanchedalmond",
					"blue",
					"blueviolet",
					"brown",
					"burlywood",
					"cadetblue",
					"chartreuse",
					"chocolate",
					"coral",
					"cornflowerblue",
					"cornsilk",
					"crimson",
					"cyan",
					"darkblue",
					"darkcyan",
					"darkgoldenrod",
					"darkgray",
					"darkgreen",
					"darkgrey",
					"darkkhaki",
					"darkmagenta",
					"darkolivegreen",
					"darkorange",
					"darkorchid",
					"darkred",
					"darksalmon",
					"darkseagreen",
					"darkslateblue",
					"darkslategray",
					"darkslategrey",
					"darkturquoise",
					"darkviolet",
					"deeppink",
					"deepskyblue",
					"dimgray",
					"dimgrey",
					"dodgerblue",
					"firebrick",
					"floralwhite",
					"forestgreen",
					"fuchsia",
					"gainsboro",
					"ghostwhite",
					"gold",
					"goldenrod",
					"gray",
					"green",
					"greenyellow",
					"grey",
					"honeydew",
					"hotpink",
					"indianred",
					"indigo",
					"ivory",
					"khaki",
					"lavender",
					"lavenderblush",
					"lawngreen",
					"lemonchiffon",
					"lightblue",
					"lightcoral",
					"lightcyan",
					"lightgoldenrodyellow",
					"lightgray",
					"lightgreen",
					"lightgrey",
					"lightpink",
					"lightsalmon",
					"lightseagreen",
					"lightskyblue",
					"lightslategray",
					"lightslategrey",
					"lightsteelblue",
					"lightyellow",
					"lime",
					"limegreen",
					"linen",
					"magenta",
					"maroon",
					"mediumaquamarine",
					"mediumblue",
					"mediumorchid",
					"mediumpurple",
					"mediumseagreen",
					"mediumslateblue",
					"mediumspringgreen",
					"mediumturquoise",
					"mediumvioletred",
					"midnightblue",
					"mintcream",
					"mistyrose",
					"moccasin",
					"navajowhite",
					"navy",
					"oldlace",
					"olive",
					"olivedrab",
					"orange",
					"orangered",
					"orchid",
					"palegoldenrod",
					"palegreen",
					"paleturquoise",
					"palevioletred",
					"papayawhip",
					"peachpuff",
					"peru",
					"pink",
					"plum",
					"powderblue",
					"purple",
					"red",
					"rosybrown",
					"royalblue",
					"saddlebrown",
					"salmon",
					"sandybrown",
					"seagreen",
					"seashell",
					"sienna",
					"silver",
					"skyblue",
					"slateblue",
					"slategray",
					"slategrey",
					"snow",
					"springgreen",
					"steelblue",
					"tan",
					"teal",
					"thistle",
					"tomato",
					"turquoise",
					"violet",
					"wheat",
					"white",
					"whitesmoke",
					"yellow",
					"yellowgreen"
			});
			NodeShapes.insert({ 
					"circle",
					"square",
					"diamond",
					"cross",
					"triangle-down",
					"triangle-up"
				}
			);
			current = this;
		}

		/** 
		 * 
		 * Gets the current Validation object - used in various other
		 * Bridges classes to do validation of visual properties input
		 * by the  user
		 * 
		 **/
		static Validation *getCurrent() {
			return current;
		}

		/**
		 * Determine if a color is supported by CSS.
		 * 
		 * This method only supports a subject of CSS (yet). 
		 * (1) 173 CSS extended color names, (2) #RRGGBB or #RGB, where 
		 * R, G and B are red, green, blue
		 * values as hexadecimal digits.
		 * 
		 * This method does not check for null because null has special meaning.
		 * 
		 * @param color
		 * 
		 * @return whether the color is valid
		 */
		void validateColor(string color) {
									// check named colors
			if (ColorNames.find(color) != ColorNames.end())
				return;
			else if (regex_match(color, ColorPatterns)) // hex color match?
				return;
			else { 
				string error_str = "Invalid Color.." + color + "..Expected CSS color name, or #RRGGBB or #RGB formats.";
				throw error_str;
			}
		}
		
		/**
		 * Determines if the shape is supported.
		 * 
		 * @param shape
		 */
		void validateShape(string shape) {
			if (NodeShapes.find(shape) != NodeShapes.end()) 
				return;
			else  {
				string error_str = 
					"Invalid shape.." + shape +".\n Must be  one of..";
				for (const auto& elem: NodeShapes)
					error_str += elem + ",";
				error_str += "\n";
				throw error_str;
			}
		}
		
		/**
		 * Determines if the value passed is an acceptable value to 
		 * set the opacity to.
		 * 	
		 * @param val
		 */
		void validateOpacity(double val){
			if(val >= 0.0 && val <= 1.0){
				return;
			}
			else {
				string error_str = "Invalid Opacity Value.. " + 
					to_string(val) + " Must be in the 0.0-1.0 range";
				throw error_str;
			}
		}
		
		/**
		 * Determines if the value passed is an acceptable value to set 
		 * the size to.
		 * 
		 * @param val
		 */
		void validateSize(double val){
			if(val >= 0.0 && val <= 50.0){
				return;
			}
			else{
				string error_str = "Invalid Size Value.. " + 
					to_string(val) + " Must be in the 0.0-50.0 range";
				throw error_str;
			}
		}

		/**
		 * Determines if the value passed is an acceptable value to set 
		 * the thickness to.
		 * 
		 * @param val
		 */
		void validateThickness(double val){
			if(val >= 0.0 && val <= 10.0){
				return;
			}
			else{
				string error_str = "Invalid Thickness Value.. " + 
					to_string(val) + " Must be in the 0.0-10.0 range";
				throw error_str;
			}
		}
		/**
		 * Determines if the value passed is an acceptable value to set 
		 * the weight to - must be positive.
		 * 
		 * @param val
		 */
		void validateWeight(int val){
			if(val >= 0){
				return;
			}
			else{
				string error_str = "Invalid Weight Value.. " + 
					to_string(val) + " Must be positive..";
				throw error_str;
			}
		}
		
		void validate_ADT_size(int max_elements){
			if (max_elements < MAX_ELEMENTS_ALLOWED) 
				return;
			else {
				string error_str = 
					"Max allowed elements (for visualization) exceeded.. " 
					+ to_string(max_elements) + " Must be less than 5000.";
				throw error_str;
			}
		}
};

Validation* Validation::current = NULL;

}
#endif
