
#ifndef SYMBOL_H

#define SYMBOL_H


#include <string>
#include <vector>
#include <cmath>
#include <memory>

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

				static int ids;

				int identifier;

				string name = string();

				// maintain unique ids for each symbol
				string shape_type = "circle";

				// maintain ids for symbols

				// symbol attributes

				std::unique_ptr<Color> fillColor;
				std::unique_ptr<Color> strokeColor;
				std::unique_ptr<float> strokeWidth;
				std::unique_ptr<int> strokeDash;
				std::unique_ptr<float> opacity;

				// 2D affine transform matrix for the symbol
				float xform[3][3] = {
					{1., 0., 0.},
					{0., 1., 0.},
					{0., 0., 1.}
				};
				// use this flag to refrain from putting it into the JSON
				// as its the default
				bool xform_flag = false;

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
				Symbol() :
						fillColor (new Color),
						strokeColor (new Color),
						strokeWidth(new float),
						strokeDash(new int),
						opacity(new float) {

					identifier = ids;
					xform_flag = false;

					// set id for symbol
					ids++;
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
				int getIdentifier() const {
					return identifier;
				}

				/**
				 * @brief Set the symbol fill color
				 *
				 * @param c the color to set
				 */
				void setFillColor(Color c) {
					*fillColor = c;
				}
				/**
				 * @brief This method sets the symbol fill color
				 *
				 * @param c the named color to set
				 */
				void setFillColor(string c) {
					*fillColor = Color(c);
				}
				/**
				 * @brief This method gets fill color
				 *
				 * @return  fill color
				 */
				Color getFillColor() const {
					return *fillColor;
				}

				/**
				 * This method sets the symbol stroke color
				 *
				 * @param c the color to set
				 */
				void setStrokeColor(Color c) {
					*strokeColor = c;
				}

				/**
				 * @brief This method sets the symbol stroke color
				 *
				 * @param c the named color to set
				 */
				void setStrokeColor(string c) {
					*strokeColor = Color(c);
				}

				/**
				 * @brief This method gets stroke color
				 *
				 * @return  stroke color
				 */
				Color getStrokeColor() {
					return *strokeColor;
				}

				/**
				 * @brief This method sets the symbol stroke width
				 *
				 * @param strk_width the stroke width to set
				 */
				void setStrokeWidth(float strk_width) {
					if (*strokeWidth < 0.0f)
						throw "Stroke width must be positive or null";
					else
						*strokeWidth = strk_width;
				}

				/**
				 * @brief This method gets stroke width
				 *
				 * @return  stroke width
				 */
				float getStrokeWidth() const {
					return *strokeWidth;
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
						*opacity = op;
				}

				/**
				 * @brief This method gets symbol opacity
				 *
				 * @return  symbol opacity
				 */
				float getOpacity() const {
					return *opacity;
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
						*strokeDash = dash;
				}

				/**
				 * @brief This method gets stroke dash level
				 *
				 * @return  stroke dash level
				 */
				int getStrokeDash() const {
					return *strokeDash;
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

					// update current transform matrix
					matMult (xform, transl, result);
					copyMat (result, xform);

					xform_flag = true;
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

					// update current transform matrix
					matMult (xform, scale, result);
					copyMat (result, xform);

					xform_flag = true;
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

					// update current transform matrix
					matMult (xform, rotation, result);
					copyMat (result, xform);

					xform_flag = true;
				}

				/**
				 *  @brief Scale about an arbitrary point (px, py)
				 *
				 *  @param sx, scale factors along X
				 *  @param sy, scale factors along X
				 *  @param px  x coord of point
				 *  @param py  y coord of point
				 */
				void scale(float sx, float sy, float px, float py) {
					float result[3][3], result2[3][3];
					float scale[3][3] = {
						{sx, 0., 0.}, {0., sy, 0.}, {0., 0., 1.}
					};
					float transl1[3][3] = 
						{ {1., 0., -px}, {0., 1., -py}, {0., 0., 1.} };
					float transl2[3][3] = 
						{ {1., 0., px}, {0., 1., py}, {0., 0., 1.} };
					
					// form the composite transform
					matMult (scale, transl1, result);
					matMult (transl2, result, result2);

					// update current transform matrix
					matMult (xform, result2, result);
					copyMat (result, xform);

					xform_flag = true;
				}

				/**
				 *  @brief Rotate a 2D point about an arbitrary point (px, py)
				 *
				 *  @param angle rotation angle in degrees
				 *	@param pt  2D point (px, py)
				 *	 (positive is counter clockwise, negative is clockwise)
				 */
				void rotate(float angle, float px, float py) {
					// compute sin, cos
					float angle_r = angle * M_PI / 180.;
					float c = cos(angle_r);
					float s = sin(angle_r);

					// form the rotation matrix
					float result[3][3], result2[3][3];
					float rotation[3][3] = {
						{c, -s, 0.}, {s, c, 0.}, {0., 0., 1.}
					};
					float transl1[3][3] =  {
						{1., 0., -px}, {0., 1., -py}, {0., 0., 1.}
					};
					float transl2[3][3] =  {
						{1., 0., px}, {0., 1., py}, {0., 0., 1.}
					};

					// form the composite transform
					matMult (rotation, transl1, result);
					matMult (transl2, result, result2);

					// update current transform matrix
					matMult (xform, result2, result);
					copyMat (result, xform);

					xform_flag = true;
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

					symbol_attr_json += QUOTE + "type" + QUOTE + COLON +
							QUOTE + getShapeType() + QUOTE + COMMA + 
							QUOTE + "ID" + QUOTE + COLON +
							QUOTE + to_string(identifier) + QUOTE + COMMA;

					if (fillColor != nullptr) {
						symbol_attr_json += QUOTE + "fill-color" + 
							QUOTE + COLON + fillColor->getCSSRepresentation() 
							+ COMMA;
					}

					if (opacity != nullptr) {
						symbol_attr_json += QUOTE + "opacity" + QUOTE + COLON +
							to_string(*opacity) + COMMA;
					}

					if (strokeColor != nullptr) {
						symbol_attr_json += QUOTE + "stroke-color" + QUOTE + 
							COLON + strokeColor->getCSSRepresentation() + COMMA;
					}

					if (strokeWidth != nullptr) {
						symbol_attr_json += QUOTE + "stroke-width" + QUOTE + 
							COLON + to_string(*strokeWidth) + COMMA;
					}

					if (strokeDash != nullptr) {
						symbol_attr_json += QUOTE + "stroke-dasharray" + QUOTE +
							COLON + to_string(*strokeDash) + COMMA;
					}

					// check transform, if it is not set, ignore
					if (this->xform_flag) {
						symbol_attr_json +=
							QUOTE + "transform" + QUOTE + COLON +
							OPEN_BOX +
							JSONencode(this->xform[0][0]) + COMMA +
							JSONencode(this->xform[1][0]) + COMMA +
							JSONencode(this->xform[0][1]) + COMMA +
							JSONencode(this->xform[1][1]) + COMMA +
							JSONencode(this->xform[0][2]) + COMMA +
							JSONencode(this->xform[1][2]) +
							CLOSE_BOX + COMMA;
					}
					return symbol_attr_json;
				}
		};

		// initialize the id to start at zero
		int Symbol::ids = 0;
	}
} // namespace bridges

#endif
