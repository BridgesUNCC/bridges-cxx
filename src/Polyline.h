#include "DataStructure.h"
#include "Symbol.h"
#include <vector>

using namespace std;


#ifndef  POLYLINE_H

#define POLYLINE_H

namespace bridges {

	/**
	 * @brief This class defines a polygon and is part of the symbol collection.
	 *      A polygon has a set of vertices
	 *
	 * @author David Burlinson, Kalpathi Subramanian
	 * @date 12/23/18, 7/12/19
	 *
	 */

	class Polyline : public Symbol {
		private:
			string shape = "polyline";
			// height, width of rectangle
			vector<float> *points = nullptr;
			int radius = 10;

		public:

			// constructors
			Polyline () {
				points = new vector<float>(100);
				points->resize(0);
			}

			/**
			 *  Construct a polyline from sequence of points
		 	 *  @param  pts  point sequence
			 */
			Polyline (vector<float> *pts) {
				points = pts;
			}

			/**
			 * Get the name of the data type
			 * @return name of symbol type
			 */
			string getDataStructType() {
				return "polyline";
			}

			/**
			 *	This method gets the name of the shape
			 *
			 *  @return name   shape name
			 */
			string getName()  const {
				return "polygon";
			}

			/**
			 * This method adds a point to the polyline
			 *
			 * @param x, y : X, Y coordinates of the point
			 */
			void addPoint(int x, int y) {

				float fx = float(x);
				float fy = float(y);

				if 	((fx > -INFINITY) && (fx < INFINITY) &&
					(fy > -INFINITY) && (fy < INFINITY)) {

					points->push_back(fx);
					points->push_back(fy);
				}
				else {
					throw "points are valid only for polygons!";
				}
			}
			/**
			 * This method returns the point list of the polyline
			 *
			 * @return points  point list of the polygon - sequence of x, y values
			 */
			vector<float> *getPoints() {
				return points;
			}

			void setPolyline (vector<float> pts) {
				*points = pts;
			}

			/**
			 * This method returns the dimensions of the shape: min and max
			 *	values in X and Y
			 *
			 * @return array of 4 values
			 */
			vector<float> getDimensions() {

				vector<float> dims(4);
				dims[0] = dims[1] = INFINITY;
				dims[2] = dims[3] = -INFINITY;
				float x, y;
				for (std::size_t i = 0, size = points->size();
					i < size; i += 2) {
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
				return dims;
			}

			/**
			 * This method returns the JSON representation of the shape
			 *
			 * @return string  JSON string
			 */
			const string getSymbolRepresentation() const {

				string shape_json = getSymbolAttributeRepresentation();

				shape_json +=
					QUOTE + "name" + QUOTE + COLON +  QUOTE + getLabel() + QUOTE + COMMA +
					QUOTE + "shape" + QUOTE + COLON + QUOTE + shape + QUOTE + COMMA;

				// add point list to polygons
				shape_json += QUOTE + "points" + QUOTE + COLON + OPEN_BOX;
				vector<float>::iterator it;
				for (it = points->begin(); it != points->end(); it++) {
					shape_json += to_string(*it) + COMMA;
				}

				// remove last comma
				if (points->size())
					shape_json.erase(shape_json.size() - 1);
				shape_json += CLOSE_BOX + CLOSE_CURLY;

				return shape_json;
			}
	};

} // namespace bridges

#endif
