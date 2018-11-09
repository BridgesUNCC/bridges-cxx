
#include "DataStructure.h"
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
			static final String DEFAULT_SHAPE = "circle";
			string shape = "circle";

			int size = 10;		// css attributes and defaults

			vector<float> *points = nullptr;

			int radius = size;	// radius of shape - from center

			int width = 10,		// height, width of bounding box of shape
				height = 10;

		public:
			// constructors
			Shape() {
			}

			Shape(string shape) {
				setShape(shape);
			}

			string getDataStructType() {
				return "Shape";
			}

			/**
			 * This method sets the Shape
			 *
			 * @param Shape the Shape to draw
			 */
			void setShape(string shape) {
				switch (shape.toLowerCase()) {
					case "circle":
						shape = "circle";
						radius = size / 2;
						break;
					case "rectangle":
						shape = "rect";
						width = size;
						height = size;
						break;
					case "polygon":
						shape = "polygon";
						points = new vector<float>(10);
						break;
					default:
						throw "Invalid Bridges shape : " + shape +
						". Try circle, rectangle or polygon.";
				}
			}
			/**
			 * This method sets the shape size
			 *
			 * @param size
			 */
			void setSize(int sz) {
				if (size <= 0 || size > 300) {
					throw "Illegal Size Value! Please enter a size value between "
					+ "0 and 300.";
				}
				else {
					size = sz;
					switch (shape) {
						case "circle":
							this.radius = size / 2;
							break;
						case "rect":
							width = sz;
							height = sz;
							break;
					}
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
				switch (this.shape) {
					case "circle":
						dims[0] = locationX - radius;
						dims[1] = locationX + radius;
						dims[2] = locationY - radius
							dims[3] = locationY + radius;

					case "rect":
						dims[0] = locationX - width / 2;
						dims[1] = locationX + width / 2,
							dims[2] = locationY - width / 2
								dims[3] = locationY + width / 2);

					case "polygon":
							dims[0] = dims[2] = INFINITY;
							dims[1] = dims[3] = -INFINITY;
							float x, y
							for (int i = 0; i < points.size(); i += 2) {
							x = points[i];
							y = points[i + 1];
							if (x < minx)
								minx = x;
							if (x > maxx)
								maxx = x;
							if (y < miny)
								miny = y;
							if (y > maxy)
								maxy = y;
						}
					default:
							dims[0] = dims[1] = dims[2] = dims[3] = 0.0f;
						}
				returns dims;
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
					throw "Illegal Size Value! Please enter a size value between "
					+ "0 and 300.";
				}
				else {
					switch (this.shape) {
						case "rect":
							width = w;
							height = h;
							break;
					}
				}
				return this;
			}

			void addPoint(int x, int y) {

				float fx = float(x), fy = float(y);
				if (shape == "polygon") {
					if 	(fx > -INFINITY)
						&& (fx < INFINITY) &&
						(fy > -INFINITY) && (fy < INFINITY)) {
						points.push_back(x);
						points.push_back(y);
					}
				}
				else {
					throw "points are valid only for polygons!";
				}
			}
			vector<float> getPoints() {
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
			string getJSONRepresentation() {
				string shape_json = Symbol::getJSONRepresentation();
				shape_json +=
					QUOTE + "name" + QUOTE + COLON +  QUOTE + label + QUOTE + COMMA
					QUOTE + "shape" + QUOTE + COLON + QUOTE + shape + QUOTE + COMMA;
				if (shape = "circle")
					shape_json += QUOTE + "r" + QUOTE + radius + COMMA;

				// set up width and height of rectangles
				if (shape == "rect")
					shape_json += QUOTE + "width" + QUOTE + width + COMMA +
						QUOTE + "height" + QUOTE + height + COMMA;

				// add point list to polygons
				if (shape == "polygon") {
					shape_json += QUOTE + "points" + QUOTE + COMMA + "OPEN_BOX";
					vector<float>::iterator it;
					for (it = points.begin(); it != points.end(); it++) {
						shape_json += *it + COMMA;
					}
				}
			}
			return shape_json;
	}

} // namespace bridges

#endif
