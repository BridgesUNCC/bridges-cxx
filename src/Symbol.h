
#ifndef SYMBOL_H

#define SYMBOL_H


#include <string>
#include <vector>
#include <cmath>

using namespace std;

#include "DataStructure.h"
#include "Color.h"

namespace bridges {
	namespace datastructure {

		/**
		 * @brief This is an abstract class for deriving a
		 *  number of Symbol shape objects, for use in a SymbolCollection.
		 *  Symbols correspond to a simplified subset of SVG paths
		 *  and shapes for custom visual representations in BRIDGES.
		 *
		 *  Currently shapes supported are rectangle, circle, polygon, label;
		 *	each shape has a name, location (x, y) and appropriate geometric
		 *	and non-geometric attributes
		 *
		 * @author David Burlinson, Kalpathi Subramanian
		 * @date 12/24/18, 7/12/19, 12/28/20
		 *
		 */
		class Symbol {

			private:

				int identifier;

				string name = string();

				// maintain unique ids for each symbol
				string shape_type = "circle";


				// specify default attributes
				// defaults are not sent through JSON

				float 	default_location[2] = {0.0f, 0.0f};
				Color 	default_fill_color{"blue"};
				Color 	default_stroke_color{"white"};
				int 	default_stroke_dash = 1;
				float 	default_opacity = 1.0f;
				float 	default_stroke_width = 1.0f;
				string 	default_symbol = "circle";

				// symbol attributes

				Color fillColor{"blue"},
					  strokeColor{"white"};
				float opacity = 1.0f;
				float strokeWidth = 1.0f;
				int strokeDash = 1;
				// use this flag to refrain from putting it into the JSON
				// as its the default
				bool identity_matrix = true;

				// symbol location
				float location[2] = {0.0f, 0.0f};

				// matrix methods used for affine transformations on symbols
				void matMult (float m1[][3], float m2[][3], float result[][3])
				const {
					for (int i = 0; i < 3; ++i) {
						for (int j = 0; j < 3; ++j) {
							result[i][j] = 0.;
							for (int k = 0; k < 3; ++k) {
								result[i][j] += m1[i][k] * m2[k][j];
							}
						}
					}
				}
				void identity(float m[][3]) {
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j)
							m[i][j] = (i == j) ? 1. : 0.;
				}

				void copyMat(float m[][3], float copy[][3]) {
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j)
							copy[i][j] = m[i][j];
				}
				void printMat(float m[][3]) {
					for (int i = 0; i < 3; ++i) {
						for (int j = 0; j < 3; ++j)
							cout <<  m[i][j] << ", ";
						cout << "\n";
					}
				}

			public:

				/**
				 * @brief default constructor
				 */
				Symbol() {
					identifier = getIdentifier();
					identity_matrix = true;
				}

				/**
				 *	@brief Create a symbol of type "symb"
				 *
				 * 	@param symb  symbol to create
				 */
				Symbol(string symb) {
					identifier = getIdentifier();
					name = symb;
					identity_matrix = true;
				}

				/**
				 * 	@brief Virtual method to get the JSON representation of the symbol
				 */
				virtual const string getSymbolRepresentation() const  = 0;

				/**
				 *	@brief Virtual method to get the bounding box
				 *		(dimensions) of the shape
				 */
				virtual vector<float> getDimensions() const = 0;

				/**
				 *	@brief return the symbol identifier.
				 *
				 * 	Maintains unique identifiers of symbols
				 * 	and returns the Symbol's unique identifier
				 *
				 * 	@return the identifier
				 */
				int getIdentifier() {
					static int ids = 0;
					ids++;

					return ids - 1;
				}

				/**
				 * @brief Set the symbol fill color
				 *
				 * @param c the color to set
				 */
				void setFillColor(Color c) {
					fillColor = c;
				}
				/**
				 * @brief This method sets the symbol fill color
				 *
				 * @param c the named color to set
				 */
				void setFillColor(string c) {
					fillColor = Color(c);
				}
				/**
				 * @brief This method gets fill color
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
				 * @brief This method sets the symbol stroke color
				 *
				 * @param c the named color to set
				 */
				void setStrokeColor(string c) {
					strokeColor = Color(c);
				}

				/**
				 * @brief This method gets stroke color
				 *
				 * @return  stroke color
				 */
				Color getStrokeColor() {
					return strokeColor;
				}

				/**
				 * @brief This method sets the symbol stroke width
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
				 * @brief This method gets stroke width
				 *
				 * @return  stroke width
				 */
				float getStrokeWidth() {
					return strokeWidth;
				}

				/**
				 * @brief This method sets the symbol opacity
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
				 * @brief This method gets symbol opacity
				 *
				 * @return  symbol opacity
				 */
				float getOpacity() {
					return opacity;
				}

				/**
				 * @brief This method sets the stroke dash level
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
				 * @brief This method gets stroke dash level
				 *
				 * @return  stroke dash level
				 */
				int getStrokeDash() {
					return strokeDash;
				}

				/**
				 * @brief This method sets the symbol location
				 *
				 * @param x  x coordinate
				 * @param y  y coordinate
				 */
				void setLocation(int x, int y) {
					setLocation(float(x), float(y));
				}

				/**
				 * @brief This method sets the symbol location
				 *
				 * @param x  x coordinate
				 * @param y  y coordinate
				 */
				void setLocation(double x, double y) {
					setLocation(float(x), float(y));
				}


				/**
				 * @brief This method sets the symbol location
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
				 * @brief This method gets the symbol location
				 *
				 * @return location (x, y) of the symbol
				 */
				const float *getLocation() const {
					return location;
				}

				/**
				 *	@brief This method gets the name of the symbol
				 *
				 *  @return name   shape name
				 */
				string getName()  const {
					return name;
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
				 * Get the symbol type
				 *
				 * @return  the shape type
				 */
				string getShapeType() const {
					return shape_type;
				}

				// affine transform for symbol or symbol group
				// initialize to identity matrix


				// 2D affine transform matrix for the symbol
				float xform[3][3] = {
					{1., 0., 0.},
					{0., 1., 0.},
					{0., 0., 1.}
				};

			public:
				/**
				 *  @brief Translate a 2D point
				 *
				 *  @param pt  2D point (x, y)
				 *  @param tx, ty translation vector
				 *
				 */
				void translate (float tx, float ty) {
					float result[3][3];
					float transl[3][3] = {
						{1., 0., tx}, {0., 1., ty}, {0., 0., 1.}
					};
					matMult (xform, transl, result);
					copyMat (result, xform);
					identity_matrix = false;
				}

				/**
				 *  @brief Scale a 2D point
				 *
				 *  @param pt  2D point (x, y)
				 *  @param sx, sy scale factors along each axis
				 */
				void scale(float sx, float sy) {
					float result[3][3];
					float scale[3][3] = {
						{sx, 0., 0.}, {0., sy, 0.}, {0., 0., 1.}
					};
					matMult (xform, scale, result);
					copyMat (result, xform);
					identity_matrix = false;
				}

				/**
				 *  @brief Rotate a 2D point (about Z)
				 *
				 *	@param pt  2D point (x, y)
				 *  @param angle rotation angle in degrees
				 *		(positive is counter clockwise, negative is clockwise)
				 */
				void rotate(float angle) {
					// compute sin, cos
					float angle_r = angle * M_PI / 180.;
					float c = cos(angle_r);
					float s = sin(angle_r);

					// form the rotation matrix
					float result[3][3];
					float rotation[3][3] = {
						{c, -s, 0.}, {s, c, 0.}, {0., 0., 1.}
					};
					matMult (rotation, xform, result);
					copyMat (result, xform);
					identity_matrix = false;
				}
			protected:

				/**
				 *  @brief Get the JSON of the symbol representation
				 *
				 *	This method gets the JSON representation of all of the
				 *  symbol attributes
				 *
				 *  @return JSON string of symbol attributes
				 */
				const string getSymbolAttributeRepresentation() const {

					// first get all the non-geometric attributes

					using bridges::JSONUtil::JSONencode;

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

					// check transform, if it is identity, ignore
					if (!this->identity_matrix) {
						symbol_attr_json +=
							QUOTE + "xform" + QUOTE + COLON +
							OPEN_BOX +
							JSONencode(this->xform[0][0]) + COMMA +
							JSONencode(this->xform[1][0]) + COMMA +
							JSONencode(this->xform[0][1]) + COMMA +
							JSONencode(this->xform[1][1]) + COMMA +
							JSONencode(this->xform[0][2]) + COMMA +
							JSONencode(this->xform[1][2]) +
							CLOSE_BOX + COMMA;
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
