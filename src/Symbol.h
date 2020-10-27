
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#include "DataStructure.h"
#include "Color.h"

#ifndef SYMBOL_H

#define SYMBOL_H


namespace bridges {
	namespace datastructure {

		/**
		 * @brief This is an abstract class for deriving a
		 *  number of Symbol shape objects, for use in a SymbolCollection.
		 *  Symbols correspond to a simplified subset of SVG paths
		 *  and shapes for custom visual representations in BRIDGES.
		 *
		 *  Currently shapes supported are rectangle, circle, polygon, label; each shape
		 *	has a name, location (x, y) and appropriate geometric and non-geometric attributes
		 *
		 * @author David Burlinson, Kalpathi Subramanian
		 * @date 12/24/18, 7/12/19
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

			private:
				int getNewIdentifier() {
					static int ids = 0;
					ids++;

					return ids - 1;
				}

			protected:
				/**
				 * @brief Set the shape type
				 *
				 * @param s shape type to set
				 */
				void setShapeType (string s) {
					shape_type = s;
				}
				/**
				 * Get the symbol label
				 *
				 * @return  the shape type
				 */
				string getShapeType() const {
					return shape_type;
				}

			public:

				Symbol() {
					identifier = getNewIdentifier();
				}

				/**
				 * 	virtual Method to get the JSON representation of the symbol
				 */
				virtual const string getSymbolRepresentation() const  = 0;

				/**
				 *	method to get the bounding box (dimensions) of the shape
				 */
				virtual vector<float> getDimensions() const = 0;

				/**
				 *	create a symbole of type "symb"
				 */
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

				/**
				 * Get the symbol label
				 *
				 * @return  the label
				 */
				string getLabel() const {
					return label;
				}


				/**
				 * This method sets the symbol fill color
				 *
				 * @param c the color to set
				 */
				void setFillColor(Color c) {
					fillColor = c;
				}
				/**
				 * This method sets the symbol fill color
				 *
				 * @param c the named color to set
				 */
				void setFillColor(string c) {
					fillColor = Color(c);
				}
				/**
				 * This method gets fill color
				 *
				 * @return  fill color
				 */
				Color getFillColor() {
					return fillColor;
				}

				/**
				 * This method sets the symbol stroke color
				 *
				 * @param c the color to set
				 */
				void setStrokeColor(Color c) {
					strokeColor = c;
				}

				/**
				 * This method sets the symbol stroke color
				 *
				 * @param c the named color to set
				 */
				void setStrokeColor(string c) {
					strokeColor = Color(c);
				}

				/**
				 * This method gets stroke color
				 *
				 * @return  stroke color
				 */
				Color getStrokeColor() {
					return strokeColor;
				}

				/**
				 * This method sets the symbol stroke width
				 *
				 * @param strk_width the stroke width to set
				 */
				void setStrokeWidth(float strk_width) {
					if (strokeWidth < 0.0f)
						throw "Stroke width must be positive or null";
					else
						strokeWidth = strk_width;
				}

				/**
				 * This method gets stroke width
				 *
				 * @return  stroke width
				 */
				float getStrokeWidth() {
					return strokeWidth;
				}

				/**
				 * This method sets the symbol opacity
				 *
				 * @param op the opacity to set
				 */
				void setOpacity(float op) {
					if (op < 0.0f || op > 1.0f)
						throw "Opacity must be between 0 and 1";
					else
						opacity = op;
				}

				/**
				 * This method gets symbol opacity
				 *
				 * @return  symbol opacity
				 */
				float getOpacity() {
					return opacity;
				}

				/**
				 * This method sets the stroke dash level
				 *
				 * @param dash dash level
				 */
				void setStrokeDash(int dash) {
					if (dash < 0 || dash > 10)
						throw "Dash must be between 0 and 10 (inclusive)";
					else
						strokeDash = dash;
				}

				/**
				 * This method gets stroke dash level
				 *
				 * @return  stroke dash level
				 */
				int getStrokeDash() {
					return strokeDash;
				}

				/**
				 * This method sets the symbol location
				 *
				 * @param x  x coordinate
				 * @param y  y coordinate
				 */
				void setLocation(int x, int y) {
					setLocation(float(x), float(y));
				}

				/**
				 * This method sets the symbol location
				 *
				 * @param x  x coordinate
				 * @param y  y coordinate
				 */
				void setLocation(double x, double y) {
					setLocation(float(x), float(y));
				}

		  
				/**
				 * This method sets the symbol location
				 *
				 * @param x  x coordinate
				 * @param y  y coordinate
				 */
				void setCenter(float x, float y) {
					setLocation(x, y);
				}

				/**
				 * This method sets the ssymbol location
				 *
				 * @param x  x coordinate
				 * @param y  y coordinate
				 */
				void setLocation(float x, float y) {
					if ((x > -INFINITY && x < INFINITY) &&
						(y > -INFINITY && y < INFINITY)) {
						location[0] = x;
						location[1] = y;
					}
					else
						throw "Coordinates must be real numbers";
				}
				/**
				 * This method gets the symbol location
				 *
				 * @return location (x, y) of the symbol
				 */
				const float *getLocation() const {
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
				/**
				 *  @brief Translate a 2D point
				 *
				 *  @param pt  2D point (x, y)
				 *  @param tx, ty translation vector
				 */
				void translatePoint (float *pt, float tx, float ty) {
					pt[0] += tx;
					pt[1] += ty;
				}

				/**
				 *  @brief Scale a 2D point
				 *
				 *  @param pt  2D point (x, y)
				 *  @param sx, sy scale factors along each axis
				 */
				void scalePoint (float *pt, float sx, float sy) {
					pt[0] *= sx;
					pt[1] *= sy;
				}

				/**
				 *  @brief Rotate a 2D point (about Z)
				 *
				 *	@param pt  2D point (x, y)
				 *  @param angle rotation angle in degrees (positive is counter clockwise, negative is clockwise)
				 */
				void rotatePoint (float *pt, float angle) {
					// compute sin, cos
					float angle_r = angle * M_PI / 180.;
					float c = cos(angle_r);
					float s = sin(angle_r);

					// rotate the point
					float tmp[] = { pt[0]*c - pt[1]*s, tmp[1] = pt[0] * s + pt[1] * c};

					// assign to point
					pt[0] = tmp[0];
					pt[1] = tmp[1];
				}

				/**
				 *	This method gets the JSON representation of all of the
				 *  symbol attributes
				 *
				 *  @return JSON string of symbol attributes
				 */
				const string getSymbolAttributeRepresentation() const {

					// first get all the non-geometric attributes

					string symbol_attr_json = OPEN_CURLY;

					if (fillColor.getRepresentation() !=
						default_fill_color.getRepresentation()) {
						symbol_attr_json += QUOTE + "fill" + QUOTE + COLON +
							fillColor.getCSSRepresentation() + COMMA;
					}

					if (opacity != default_opacity) {
						symbol_attr_json += QUOTE + "opacity" + QUOTE + COLON +
							to_string(opacity) + COMMA;
					}

					if (strokeColor.getRepresentation() !=
						default_stroke_color.getRepresentation()) {
						symbol_attr_json += QUOTE + "stroke" + QUOTE + COLON +
							strokeColor.getCSSRepresentation() + COMMA;
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
		};
	}
} // namespace bridges

#endif
