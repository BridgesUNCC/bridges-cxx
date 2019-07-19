#include "DataStructure.h"
#include "Symbol.h"
#include <vector>

using namespace std;


#ifndef  POLYGON_H

#define POLYGON_H

namespace bridges {
  namespace datastructure {
	/**
	 * @brief This class defines a polygon and is part of the symbol collection.
	 *      A polygon has a set of vertices, with vertices connected by line
	 *		segments. It differs from the polyline in the sense that the last
	 *		and first vertex are connect to close the shape.
	 *
	 * @author David Burlinson, Kalpathi Subramanian
	 * @date 12/23/18, 7/12/19
	 *
	 */
	class Polygon : public Symbol {
		private:
			string shape = "polygon";

			// points of the polygon
			vector<float> points;

		public:

			// constructors
			Polygon () {
				points.clear();
			}

			Polygon (vector<float> pts) {
				points = pts;
			}

			/**
			 *	This method gets the name of the data type
			 *
			 *  @return name   data type
			 */
			string getDataStructType() {
				return "polygon";
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
			 * This method adds a point to the polygon
			 *
			 * @param x, y:  X, Y coordinates of the point
			 */
			void addPoint(float x, float y) {
				if 	((x > -INFINITY) && (x < INFINITY) &&
						(y > -INFINITY) && (y < INFINITY)) {
					points.push_back(x);
					points.push_back(y);
				}
				else {
					throw "points are valid only for polygons!";
				}
			}
			/**
			 * This method returns the point list of the polygon
			 *
			 * @return points  point list of the polygon - sequence of x, y values
			 */
			vector<float> getPoints() {
				return points;
			}

			/**
			 * This method sets the points for the polygon
			 *
			 * @param pts  point list of the polygon - sequence of x, y values
			 */
			void setPolygon (vector<float> pts) {
				points = pts;
			}

			/** 
			 *	Translate the polyline
			 *
			 *	@param translation factor (tx, ty)
			 */
		 	void translate(float tx, float ty) {
				// translate the points
				for (int k = 0; k < points.size(); k += 2) {
					points[k]   += tx;
					points[k+1] += ty;
				}
			}

			/** 
			 *	rotate the polyline about its center
			 *
			 *	@param rotation angle 
			 */
		 	void rotate(float angle) {
				// get center of polyline
				float center[2];
				getCenter(center);
				// translate the center to the origin
				float transl[] = {-center[0], -center[1]};
				translate (transl[0], transl[1]);
				// rotate the points
				for (int k = 0; k < points.size(); k += 2) {
					float tmp[] = { points[k], points[k+1] };
					rotatePoint (tmp,  angle);
					points[k] = tmp[0]; points[k+1] = tmp[1];
				}
				// translate back
				transl[0] = center[0]; transl[1] = center[1];
				translate (transl[0], transl[1]);
			}

			/** 
			 *	Scale the polyline about its center
			 *
			 *	@param scale factor (sx, sy)
			 */
		 	void scale(float sx, float sy) {
				// get center of polyline
				float center[2];
				getCenter(center);
				// translate the center to the origin
				float transl[] = {-center[0], -center[1]};
				translate (transl[0], transl[1]);
				// scale the points
				for (int k = 0; k < points.size(); k += 2) {
					points[k]   *=  sx;
					points[k+1] *=  sy;
				}
				// translate back
				transl[0] = center[0]; transl[1] = center[1];
				translate(transl[0], transl[1]);
			}

			/** 
			 *	Get center of polyline - use its bounding box
			 */
			void getCenter(float *center) {
				float bbox[4];
				bbox[0] = bbox[1] = INFINITY;
				bbox[2] = bbox[3] = -INFINITY;
				for (int k = 0; k < points.size(); k += 2) {
					if (points[k] < bbox[0]) bbox[0] = points[k];
					if (points[k] > bbox[2]) bbox[2] = points[k];
					if (points[k+1] < bbox[1]) bbox[1] = points[k+1];
					if (points[k+1] > bbox[3]) bbox[3] = points[k+1];
				}
				center[0] = bbox[0] + (bbox[2]-bbox[0])/2.;	
				center[1] = bbox[1] + (bbox[3]-bbox[1])/2.;	
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
				dims[0] = dims[1] = INFINITY;
				dims[2] = dims[3] = -INFINITY;
				float x, y;
				for (std::size_t i = 0, size = points.size();
					i < size; i += 2) {
					x = points.at(i);
					y = points.at(i + 1);
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
				for (int k = 0; k < points.size(); k++) {
					shape_json += to_string(points[k]) + COMMA;
				}

				// remove last comma
				if (points.size())
					shape_json.erase(shape_json.size() - 1);
				shape_json += CLOSE_BOX + CLOSE_CURLY;

				return shape_json;
			}
	};
  }
} // namespace bridges

#endif
