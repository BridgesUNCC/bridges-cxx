
#include <string>
#include <vector>

using namespace std;

#include "DataStructure.h"
#include "Color.h"

#ifndef SYMBOL_H

#define SYMBOL_H


namespace bridges {

	/*
	 * @brief This is a class BRIDGES for deriving a
	 *  number of Symbol objects for use in a SymbolCollection.
	 *  Symbols correspond to a simplified subset of SVG paths
	 *  and shapes for custom visual representations in BRIDGES.
	 *
	 * @author Kalpathi Subramanian
	 * @date 10/8/18
	 *
	*/
	class Symbol {

		private:

			int identifier;
			string name = string();

			string shape_type; 			// rect, circle, polygon, label

										// geoemtric properties of symbol
			struct geometry {
				int size = 10;			// size of shape
				int	width = 10,
					height = 10;		// height, width of bound box of symbol
				int radius = size; 		// radius of shape - from center
				float location[2];		// symbol location
				vector<float> *points = nullptr;// points list for polylines
			} geom_properties;


								// non-geometric properties of symbol
			struct attributes {
				string label = string();
				Color fillColor, strokeColor;
				float opacity;
				float strokeWidth;
				int strokeDash;
				int fontSize = 12;
				int textWidth = 100;
				int textHeight = 50;


			} attributes;

			/**
			 *
			 *	these functions maintain default attributes for symbols
			 *
			 */

			float *getDefaultLocation() const {
				static float default_location[2] = {0.0f, 0.0f};

				return default_location;
			}

			Color getDefaultFillColor() const {
				static Color default_fill_color("blue");

				return default_fill_color;
			}
			Color getDefaultStrokeColor() const {
				static Color default_stroke_color("white");

				return default_stroke_color;
			}
			float getDefaultOpacity() const {
				static float default_opacity = 1.0f;

				return default_opacity;
			}

			float getDefaultStrokeWidth() const {
				static float default_stroke_width = 1.0f;

				return default_stroke_width;
			}

			int getDefaultStrokeDash() const {
				static int default_stroke_dash = 1;

				return default_stroke_dash;
			}
			string getDefaultSymbol() {
                static string default_symbol = "circle";

                return default_symbol;
            }
			int getDefaultFontSize() const {
				static int default_font_size = 12;

				return default_font_size;
			}

		public:
			Symbol() {
				identifier = getIdentifier();
				setSymbol(getDefaultSymbol());
			}

			Symbol(string symb) {
				identifier = getIdentifier();
				setSymbol(symb);
			}
			/**
			 * 	Maintains unique identifiers of symbols
			 * 	and returns the Symbol's unique identifier
			 *
			 * 	@return the string identifier
			 */
			int getIdentifier() {
				static int ids = 0;
				ids++;

				return ids - 1;
			}
			/**
			 * This method sets the Shape
			 *
			 * @param Shape the Shape to draw
			 */
			void setSymbol(string shape_name) {
				shape_type = shape_name;
				float *loc = getDefaultLocation();
				geom_properties.location[0] = loc[0];
				geom_properties.location[1] = loc[1];
				attributes.fillColor = getDefaultFillColor();
				attributes.opacity = getDefaultOpacity();
				attributes.strokeColor = getDefaultStrokeColor();
				attributes.strokeWidth = getDefaultStrokeWidth();
				attributes.strokeDash = getDefaultStrokeDash();
				attributes.label = string();

				transform(name.begin(), name.end(), name.begin(), ::tolower);
				if (shape_name == "circle") {
					shape_type = "circle";
					geom_properties.radius = geom_properties.size/2;
				}
				else if (shape_name == "rectangle") {
					shape_type = "rect";
					geom_properties.width = geom_properties.size;
					geom_properties.height = geom_properties.size;
				}
				else if (shape_name == "polygon") {
					shape_type = "polygon";
					geom_properties.points = new vector<float>;
				}
				else if (shape_name == "label") {
					shape_type = "text";
					attributes.textWidth  = 100;
					attributes.textHeight  = 50;
					attributes.fontSize  = 12;
					attributes.label = "";
				}
				else {
					throw "Invalid Bridges shape : ` + name + '. Try circle, rectangle, polygon or label.";
				}
			}

			/**
			 * This method sets the label
			 *
			 * @param lbl the label to set
			 */
			void setLabel(string lbl) {
				attributes.label = lbl;
			}

			string getLabel() {
				return attributes.label;
			}

			void setColor(Color c) {
				attributes.fillColor = c;
			}
			Color getColor() {
				return attributes.fillColor;
			}

			void setStrokeColor(Color c) {
				attributes.strokeColor = c;
			}

			Color getStrokeColor() {
				return attributes.strokeColor;
			}

			void setStrokeWidth(float strk_width) {
				if (attributes.strokeWidth <= 0.0f || attributes.strokeWidth > 10.0f)
					throw "Stroke width must be between 0 and 10";
				else
					attributes.strokeWidth = strk_width;
			}

			float getStrokeWidth() {
				return attributes.strokeWidth;
			}

			void setOpacity(float o) {
				if (o <= 0.0f || o > 1.0f)
					throw "Opacity must be between 0 and 1";
				else
					attributes.opacity = o;
			}

			float getOpacity() {
				return attributes.opacity;
			}

			void setStrokeDash(int dash) {
				if (dash < 0 || dash > 10)
					throw "Dash must be between 0 and 10 (inclusive)";
				else
					attributes.strokeDash = dash;
			}

			int getStrokeDash() {
				return attributes.strokeDash;
			}

			void setLocation(int x, int y) {
				setLocation(float(x), float(y));
			}

			void setLocation(float x, float y) {
				if ((x > -INFINITY && x < INFINITY) &&
					(y > -INFINITY && y < INFINITY)) {
					geom_properties.location[0] = x;
					geom_properties.location[1] = y;
				}
				else
					throw "Coordinates must be real numbers";
			}
			float *getLocation() {
				return geom_properties.location;
			}

			/**
			 *	This method gets the name of the shape
			 *
			 *  @return name   shape name
			 */
			string getName()  const {
				return name;
			}

			/**
			 * This method sets the shape size
			 *
			 * @param size
			 */
			void setSize(int sz) {
					if (sz <= 0 || sz > 300) {
							throw "Illegal Size Value! Please enter a size in the range(0-300)";
					}
					else {
							geom_properties.size = sz;
							if (shape_type == "circle") {
									geom_properties.radius = sz/2;
							} else if (shape_type == "rect") {
									geom_properties.width = geom_properties.height = sz;
							} else if (shape_type == "text") {
									attributes.textWidth = attributes.textHeight = sz;
							}
					}
			}

			void setSize(int width, int height) {
					if (width <= 0 || width > 300 || height <= 0 || height > 300) {
							throw "Illegal Size Value! Please enter a size in the range(0-300)";
					} else if (shape_type == "circle") {
						throw "Circle symbol types only have on size dimension, radius";
					} else {
							geom_properties.size = width * height;
							if	(shape_type == "rect"){
									geom_properties.width = width;
									geom_properties.height = height;
							}
							else if (shape_type == "text") {
									attributes.textWidth = width;
									attributes.textHeight = height;
							}
					}

			}

			int getSize() {
				return geom_properties.size;
			}

			int getRadius() {
				if (shape_type == "circle") {
						return geom_properties.radius;
				} else {
						throw "You may only get radius on circle symbol types";
				}
			}

			int getHeight() {
					if (shape_type == "rect") {
							return geom_properties.height;
					} else {
							throw "You may only get height on rect symbol types";
					}
			}

			int getWidth() {
				if (shape_type == "rect") {
						return geom_properties.width;
				} else {
						throw "You may only get width on rect symbol types";
				}
			}

			/**
			 * This method returns the dimensions of the shape: min and max
			 *	values in X and Y
			 *
			 * @param none
			 * @return array of 4 values
			 */
			vector<float> getDimensions() {
				vector<float> dims(4);
				if (shape_type == "circle") {
					dims[0] = geom_properties.location[0] - geom_properties.radius;
					dims[1] = geom_properties.location[0] + geom_properties.radius;
					dims[2] = geom_properties.location[1] - geom_properties.radius;
					dims[3] = geom_properties.location[1] + geom_properties.radius;
				}
				else if ( (shape_type == "rect") || (shape_type == "label") ){
					dims[0] = geom_properties.location[0] - geom_properties.width/2;
					dims[1] = geom_properties.location[0] + geom_properties.width/2,
					dims[2] = geom_properties.location[1] - geom_properties.height/2;
					dims[3] = geom_properties.location[1] + geom_properties.height/2;
				}
				else if (shape_type == "polygon") {
					dims[0] = dims[1] = INFINITY;
					dims[2] = dims[3] = -INFINITY;
					float x, y;
					for (std::size_t i = 0, size = geom_properties.points->size(); i < size; i += 2) {
						x = geom_properties.points->at(i);
						y = geom_properties.points->at(i + 1);
						if (x < dims[0])
							dims[0] = x;
						if (x > dims[2])
							dims[2] = x;
						if (y < dims[1])
							dims[1] = y;
						if (y > dims[3])
							dims[3] = y;
					}
				}
				else {
					dims[0] = dims[1] = dims[2] = dims[3] = 0.0f;
				}
				return dims;
			}
			void addPoint(int x, int y) {

				float fx = float(x);
				float fy = float(y);
				if (shape_type == "polygon") {
					if 	((fx > -INFINITY) && (fx < INFINITY) &&
						(fy > -INFINITY) && (fy < INFINITY)) {

						geom_properties.points->push_back(x);
						geom_properties.points->push_back(y);
					}
				}
				else {
					throw "points are valid only for polygons!";
				}
			}
			vector<float> *getPoints() {
				if (shape_type == "polygon")
					return geom_properties.points;
				else
					throw "You may only get points from a polygon shape";
			}
			void setFontSize(int font) {
				attributes.fontSize = font;
			}

			int getFontSize() {
				return attributes.fontSize;
			}

			void setTextWidth(int w) {
				attributes.textWidth = w;
			}

			int getTextWidth() {
				return attributes.textWidth;
			}

			void setTextHeight(int h) {
				attributes.textHeight = h;
			}

			int getTextHeight() {
				return attributes.textHeight;
			}


			/**
			 * Getting the JSON reprasentation  of the Symbol object.
			 * It produces both the attributes and geometric properties of the
			 * symbol.
			 *
			 * @returns the encoded JSON string
			 */
			const string getSymbolRepresentation() const {

									// first get all the non-geometric attributes

				string symbol_json = OPEN_CURLY;

				if (attributes.fillColor.getRepresentation() !=
					getDefaultFillColor().getRepresentation()) {
					symbol_json += QUOTE + "fill" + QUOTE + COLON +
						attributes.fillColor.getRepresentation() + COMMA;
				}

				if (attributes.opacity != getDefaultOpacity()) {
					symbol_json + QUOTE + "opacity" + QUOTE + COLON +
					to_string(attributes.opacity) + COMMA;
				}

				if (attributes.strokeColor.getRepresentation() !=
					getDefaultStrokeColor().getRepresentation()) {
					symbol_json += QUOTE + "stroke" + QUOTE + COLON +
						attributes.strokeColor.getRepresentation() + COMMA;
				}

				if (attributes.strokeWidth != getDefaultStrokeWidth()) {
					symbol_json += QUOTE + "stroke-width" + QUOTE + COLON +
						to_string(attributes.strokeWidth) + COMMA;
				}

				if (attributes.strokeDash != getDefaultStrokeDash()) {
					symbol_json += QUOTE + "stroke-dasharray" + QUOTE + COLON +
						to_string(attributes.strokeDash) + COMMA;
				}

				float *def_loc = getDefaultLocation();
				if (geom_properties.location[0] != def_loc[0] ||
					geom_properties.location[1] != def_loc[1]) {
					symbol_json += QUOTE + "location" + QUOTE + COLON +
						OPEN_CURLY +
							QUOTE + "x" + QUOTE + COLON  +
									to_string(geom_properties.location[0]) + COMMA +
							QUOTE + "y" + QUOTE + COLON +
									to_string(geom_properties.location[1]) +
						CLOSE_CURLY   + COMMA;
				}
									// next get the geometric properties

				if (shape_type != "text") {
					symbol_json +=
						QUOTE + "name" + QUOTE + COLON +  QUOTE + name + QUOTE + COMMA +
						QUOTE + "shape" + QUOTE + COLON + QUOTE + shape_type + QUOTE + COMMA;
				}
									// circle has radius
				if (shape_type == "circle")
					symbol_json += QUOTE + "r" + QUOTE + COLON +
								to_string(geom_properties.radius);

									// set up width and height of rectangles
				if (shape_type == "rect") {
					symbol_json +=
						QUOTE + "width" + QUOTE + COLON + to_string(geom_properties.width) + COMMA +
						QUOTE + "height" + QUOTE + COLON + to_string(geom_properties.height);
				}

				if (shape_type == "text") {
					symbol_json +=
						QUOTE + "name" + QUOTE + COLON + QUOTE + attributes.label
														+ QUOTE + COMMA +
						QUOTE + "shape" + QUOTE + COLON + QUOTE + "text" + QUOTE;
					if (attributes.fontSize != getDefaultFontSize())
						symbol_json += COMMA + QUOTE + "fontSize" + QUOTE + COLON +
									to_string(attributes.fontSize);
				}

									// add point list to polygons
				if (shape_type == "polygon") {
					symbol_json += QUOTE + "points" + QUOTE + COLON + OPEN_BOX;
					vector<float>::iterator it;
					string s;
					for (it = geom_properties.points->begin();
						it != geom_properties.points->end(); it++) {
									// remove trailing zeros
						s = removeTrailingZeros2(*it);
						symbol_json += s + COMMA;
					}
					symbol_json.erase(symbol_json.size() - 1);
					symbol_json += CLOSE_BOX;
				}
				symbol_json += CLOSE_CURLY;


				return symbol_json;
			}

			const string removeTrailingZeros2(const double& num) const {
                if (static_cast<int>(num) == num) {
                    return to_string(static_cast<int>(num));
                }  				 //if integer return as int
                string numRep = to_string(num);
                				//removes trailing 0s
                numRep.erase(numRep.find_last_not_of("0") + 1);
                return numRep;
            }

	};

} // namespace bridges

#endif
