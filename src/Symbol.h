
#include <string>
#include <vector>

using namespace std;

#include "DataStructure.h"
#include "Color.h"

#ifndef SYMBOL_H

#define SYMBOL_H


namespace bridges {

	/*
	 * @brief This is an abstract class for deriving a
	 *  number of Symbol shape objects, for use in a SymbolCollection.
	 *  Symbols correspond to a simplified subset of SVG paths
	 *  and shapes for custom visual representations in BRIDGES.
	 *
	 *  Currently shapes supported are rectangle, circle, polygon, label; each shape
	 *	has a name, location (x, y) and appropriate geometric and non-geometric attributes
	 *
	 * @author Kalpathi Subramanian
	 * @date 12/24/18
	 *
	*/
	class Symbol {

		private:

			int identifier;
			string name = string();

			string shape_type = "circle"; 	// rect, circle, polygon, label

			// specify default attributes
			// defaults are not sent through JSON

			float 	default_location[2] = {0.0f, 0.0f};
			Color 	default_fill_color{"blue"};
			Color 	default_stroke_color{"white"};
			int 	default_stroke_dash = 1;
			float 	default_opacity = 1.0f;
			float 	default_stroke_width = 1.0f;
			string 	default_symbol = "circle";
			int 	default_font_size = 12;

			// symbol attributes

			string label = string();
			Color fillColor{"blue"},
				  strokeColor{"white"};
			float opacity = 1.0f;
			float strokeWidth = 1.0f;
			int strokeDash = 1;
			int fontSize = 12;
			int textWidth = 100;
			int textHeight = 50;
			// symbol location
			float location[2] = {0.0f, 0.0f};

			/**
			 *
			 *	these functions maintain default attributes for symbols
			 *
			 */

	private:
			int getNewIdentifier() {
				static int ids = 0;
				ids++;

				return ids - 1;
			}
			

		public:

			Symbol() {
				identifier = getNewIdentifier();
			}

			// method to get the JSON representation of the symbol
			virtual const string getSymbolRepresentation() const  = 0;

			// method to get the bounding box (dimensions) of the shape
			virtual vector<float> getDimensions() = 0;

			Symbol(string symb) {
				identifier = getNewIdentifier();
			}
			/**
			 * 	Maintains unique identifiers of symbols
			 * 	and returns the Symbol's unique identifier
			 *
			 * 	@return the identifier
			 */
			int getIdentifier() {
				return identifier;
			}

			/**
			 * This method sets the symbol label
			 *
			 * @param lbl the label to set
			 */
			void setLabel(string lbl) {
				label = lbl;
			}

			string getLabel() const {
				return label;
			}

			void setFillColor(Color c) {
				fillColor = c;
			}
			Color getFillColor() {
				return fillColor;
			}

			void setStrokeColor(Color c) {
				strokeColor = c;
			}

			Color getStrokeColor() {
				return strokeColor;
			}

			void setStrokeWidth(float strk_width) {
				if (strokeWidth <= 0.0f || strokeWidth > 10.0f)
					throw "Stroke width must be between 0 and 10";
				else
					strokeWidth = strk_width;
			}

			float getStrokeWidth() {
				return strokeWidth;
			}

			void setOpacity(float op) {
				if (op <= 0.0f || op > 1.0f)
					throw "Opacity must be between 0 and 1";
				else
					opacity = op;
			}

			float getOpacity() {
				return opacity;
			}

			void setStrokeDash(int dash) {
				if (dash < 0 || dash > 10)
					throw "Dash must be between 0 and 10 (inclusive)";
				else
					strokeDash = dash;
			}

			int getStrokeDash() {
				return strokeDash;
			}

			void setLocation(int x, int y) {
				setLocation(float(x), float(y));
			}

			void setLocation(float x, float y) {
				if ((x > -INFINITY && x < INFINITY) &&
					(y > -INFINITY && y < INFINITY)) {
					location[0] = x;
					location[1] = y;
				}
				else
					throw "Coordinates must be real numbers";
			}
			float *getLocation() {
				return location;
			}

			/**
			 *	This method gets the name of the symbol
			 *
			 *  @return name   shape name
			 */
			string getName()  const {
				return name;
			}

		protected:

			const string getSymbolAttributeRepresentation() const {

				// first get all the non-geometric attributes

				string symbol_attr_json = OPEN_CURLY;

				if (fillColor.getRepresentation() !=
					default_fill_color.getRepresentation()) {
					symbol_attr_json += QUOTE + "fill" + QUOTE + COLON +
						fillColor.getRepresentation() + COMMA;
				}

				if (opacity != default_opacity) {
					symbol_attr_json + QUOTE + "opacity" + QUOTE + COLON +
					to_string(opacity) + COMMA;
				}

				if (strokeColor.getRepresentation() !=
					default_stroke_color.getRepresentation()) {
					symbol_attr_json += QUOTE + "stroke" + QUOTE + COLON +
						strokeColor.getRepresentation() + COMMA;
				}

				if (strokeWidth != default_stroke_width) {
					symbol_attr_json += QUOTE + "stroke-width" + QUOTE + COLON +
						to_string(strokeWidth) + COMMA;
				}

				if (strokeDash != default_stroke_dash) {
					symbol_attr_json += QUOTE + "stroke-dasharray" + QUOTE + COLON +
						to_string(strokeDash) + COMMA;
				}

				if (location[0] != default_location[0] ||
					location[1] != default_location[1]) {
					symbol_attr_json += QUOTE + "location" + QUOTE + COLON +
						OPEN_CURLY +
						QUOTE + "x" + QUOTE + COLON  +
						to_string(location[0]) + COMMA +
						QUOTE + "y" + QUOTE + COLON +
						to_string(location[1]) +
						CLOSE_CURLY   + COMMA;
				}

				return symbol_attr_json;
			}

			const string removeTrailingZeros2(const double& num) const {
			  std::stringstream ss;
			  ss<<num;
			  return ss.str();
			}

	};

} // namespace bridges

#endif
