
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
	class Symbol: public DataStructure {

		private:

			int identifier;
			string name = string();

										// geoemtric properties of symbol
			struct geometry {
				int size = 10;			// size of shape
				int	width = 10, 
					height = 10;		// height, width of bound box of symbol
				int radius = size; 		// radius of shape - from center
				float *location;		// symbol location
				vector<float> *points = nullptr;// points list for polylines
			} geom_properties;

			float *getDefaultLocation() const {
				static float default_location[2] = {0.0f, 0.0f};

				return default_location;
			}
								// non-geometric properties of symbol
			struct attributes { 
				string label = string();
				Color fillColor, strokeColor;
				float opacity;
				float strokeWidth;
				int strokeDash;

				
			} attributes;

			/**
			 *
			 *	these functions maintain default attributes for symbols
			 *
			 */
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

		public:
			const string getDStype() const override {
				return "Symbol";
			}

			Symbol() {
				identifier = getIdentifier();
				setSymbol(getDefaultSymbol());
			}

			Symbol(string symb) {
				identifier = getIdentifier();
				setSymbol(symb);	
			}
			/**
			 * This method sets the Shape
			 *
			 * @param Shape the Shape to draw
			 */
			void setSymbol(string shape_name) {
				name = shape_name;
				geom_properties.location = getDefaultLocation();
				attributes.fillColor = getDefaultFillColor();
				attributes.opacity = getDefaultOpacity();
				attributes.strokeColor = getDefaultStrokeColor();
				attributes.strokeWidth = getDefaultStrokeWidth();
				attributes.strokeDash = getDefaultStrokeDash();
				attributes.label = string();

				transform(shape.begin(), shape.end(),
					shape.begin(), ::tolower);
				cout << "setShape(): shape:" << shape << endl;
				if (shape == "circle") {
					radius = size / 2;
				}
				else if (shape == "rectangle") {
					width = height = size;
				}
				else if (shape == "polygon") {
					points = new vector<float>(50, 0.0);
				}
				else {
					throw "Invalid Bridges shape : ` + shape + '. Try circle, rectangle or polygon.";
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

			vector<float> getDimensions() {
				vector<float> dims(4, 0.0f);

				return dims;
			}
			Shape(string shp) {
				setShape(shp);
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
				if (size <= 0 || size > 300) {
					throw "Illegal Size Value! Please enter a size in the range(0-300)";
				}
				else {
					size = sz;
					if (shape == "circle")
						radius = sz / 2;
					else if	(shape == "rect")
						width = height = sz;
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
				if (shape == "circle") {
					dims[0] = location[0] - radius;
					dims[1] = location[0] + radius;
					dims[2] = location[1] - radius;
					dims[3] = location[1] + radius;
				}
				else if (shape == "rect") {
					dims[0] = location[0] - width / 2;
					dims[1] = location[0] + width / 2,
						dims[2] = location[1] - width / 2;
					dims[3] = location[1] + width / 2;
				}
				else if (shape == "polygon") {
					dims[0] = dims[2] = INFINITY;
					dims[1] = dims[3] = -INFINITY;
					float x, y;
					for (int i = 0; i < points->size(); i += 2) {
						x = points->at(i);
						y = points->at(i + 1);
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
				if (shape == "polygon") {
					if 	((fx > -INFINITY) && (fx < INFINITY) &&
						(fy > -INFINITY) && (fy < INFINITY)) {

						points->push_back(x);
						points->push_back(y);
					}
				}
				else {
					throw "points are valid only for polygons!";
				}
			}
			vector<float> *getPoints() {
				if (shape == "polygon")
					return points;
				else
					throw "You may only get points from a polygon shape";
			}

			/**
			 * Internal code for getting the properties of the Symbol object.
			 * It produces (without the spaces or newlines):
			 * {
			 *  "name": "Some label",
			 *  "other CSS properties like color": any_JSON_value
			 * }
			 * @returns the encoded JSON string
			 */
			virtual const string getSymbolRepresentation() const override {
cout << "calling Symbol::getDSR().." << endl;
				string symbol_json = OPEN_CURLY;

				if (fillColor.getRepresentation() !=
					getDefaultFillColor().getRepresentation()) {
					symbol_json += QUOTE + "fill" + QUOTE + COLON +
						attributes.getRepresentation() + COMMA;
				}

				if (opacity != getDefaultOpacity()) {
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
						QUOTE + "x" + QUOTE + to_string(geom_properties.location[0]) + COMMA +
						QUOTE + "y" + QUOTE + to_string(geom_properties.location[1]) +
						CLOSE_CURLY;
				}
				symbol_json += CLOSE_CURLY;

				return symbol_json;
			}

			/**
			 * Internal code for getting the properties of the Shape object.
			 * It produces (without the spaces or newlines):
			 * {
			 *  "name": "Some label",
			 *  "other CSS properties like color": any_JSON_value
			 * }
			 * @returns the encoded JSON string
			 */
			virtual const string getDataStructureRepresentation() const override{
cout << "calling Shape::getDSR().." << endl;
				string shape_json = Symbol::getDataStructureRepresentation();
				shape_json +=
					QUOTE + "name" + QUOTE + COLON +  QUOTE + label + QUOTE + COMMA +
					QUOTE + "shape" + QUOTE + COLON + QUOTE + shape + QUOTE + COMMA;
				if (shape == "circle")
					shape_json += QUOTE + "r" + QUOTE + to_string(radius) + COMMA;

				// set up width and height of rectangles
				if (shape == "rect")
					shape_json += QUOTE + "width" + QUOTE + to_string(width) + COMMA +
						QUOTE + "height" + QUOTE + to_string(height) + COMMA;

				// add point list to polygons
				if (shape == "polygon") {
					shape_json += QUOTE + "points" + QUOTE + COMMA + "OPEN_BOX";
					vector<float>::iterator it;
					for (it = points->begin(); it != points->end(); it++) {
						shape_json += to_string(*it) + COMMA;
					}
				}
				cout << "JSON (Shape.h)" << shape_json << endl;
				return shape_json;
			}
	};

} // namespace bridges

#endif

#endif
