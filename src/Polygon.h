#include "DataStructure.h"
#include "Polyline.h"
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
		class Polygon : public Polyline {

			public:
				// constructors
				Polygon () : Polyline() {
					setShapeType("polygon");
				}

				Polygon (vector<float> pts) : Polyline (pts) {
					setShapeType("polygon");
				}

				/**
				 *	This method gets the name of the data type
				 *
				 *  @return name   data type
				 */
				virtual string getDataStructType() {
					return "polygon";
				}

				/**
				 *	This method gets the name of the shape
				 *
				 *  @return name   shape name
				 */
				virtual string getName()  const {
					return "polygon";
				}

				void setPolygon (vector<float> pts) {
					this->setPolyline(pts);
					setShapeType("polygon");
				}
		};
	}
} // namespace bridges

#endif
