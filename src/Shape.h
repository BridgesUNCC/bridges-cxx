#include "DataStructure.h"
#include "Symbol.h"
#include <vector>

using namespace std;

#ifndef  SHAPE_H

#define SHAPE_H

namespace bridges {

	/*
	 * @brief This is a class BRIDGES for deriving a
	 *  number of Shape objects for use in a ShapeCollection.
	 *  Shapes correspond to a simplified subset of SVG paths
	 *  and shapes for custom visual representations in BRIDGES.
	 *
	 * @author Kalpathi Subramanian
	 * @date 10/8/18
	 *
	*/
	class Shape : public Symbol {

		private:
			string getDefaultShape() {
				static string default_shape = "circle";

				return default_shape;
			}
			string shape = getDefaultShape();

			int size = 10;		// css attributes and defaults

			vector<float> *points = new vector<float>;

			int radius = size;	// radius of shape - from center

			int width = 10,		// height, width of bounding box of shape
				height = 10;

		public:
			// constructors
			Shape() {
			}

			Shape(string shp) {
				setShape(shp);
			}

			string getDataStructType() {
				return "Shape";
			}

			/**
			 *	This method gets the name of the shape
			 *
			 *  @return name   shape name
			 */
			string getName()  const {
				return shape;
			}

			/**
			 * This method sets the Shape
			 *
			 * @param Shape the Shape to draw
			 */
			void setShape(string shape_name) {
				shape = shape_name;
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
					points = new vector<float>(50);
				}
				else {
					throw "Invalid Bridges shape : ` + shape + '. Try circle, rectangle or polygon.";
				}
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

			/**
			 * This method sets the size given height and width arguments
			 *
			 * @param w  width of object's bounding box
			 * @param h  height of object's bounding box
			 *
			 * @return none
			 */
			void setSize(int w, int h) 	{
				if (size <= 0 || size > 300) {
					throw "Illegal Size Value! Please enter a size in the range 0-300";
				}
				else {
					if (shape == "rect") {
						width = w;
						height = h;
					}
				}
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
			 * Internal code for getting the properties of the Shape object.
			 * It produces (without the spaces or newlines):
			 * {
			 *  "name": "Some label",
			 *  "other CSS properties like color": any_JSON_value
			 * }
			 * @returns the encoded JSON string
			 */
			/*
						virtual const string getDataStructureRepresentation() const override {
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
			*/
	};

} // namespace bridges

#endif
