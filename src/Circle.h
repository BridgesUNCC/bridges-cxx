#include "DataStructure.h"
#include "Symbol.h"
#include <vector>

using namespace std;


#ifndef  CIRCLE_H

#define CIRCLE_H

namespace bridges {

	/**
	 * @brief This class defines a circle and is part of the symbol collection.
	 *      A circle  has a radius
	 *
	 * @author Kalpathi Subramanian
	 * @date 12/24/18
	 *
	 */
	class Circle : public Symbol {
		private:

			string shape = "circle";
			// height, width of rectangle
			int radius = 10;

		public:

			/**
			 *  constructors
			 */
			Circle () {
				radius = 10;
			}

			Circle (int r) {
				if (r < 0)
					throw "Illegal value for radius. Must be positive";
				radius = r;
			}

			// provides both location and radius

			Circle (int locx, int locy, int r) {
				setLocation (locx, locy);
				if (r < 0)
					throw "Illegal value for radius. Must be positive";
				radius = r;
			}

			string getDataStructType() {
				return "circle";
			}

			/**
			 *	This method gets the name of the shape
			 *
			 *  @return name   shape name
			 */
			string getName()  const {
				return "circle";
			}

			/**
			 * This method sets the radius of the circle
			 *
			 * @param r  radius
			 */
			void setRadius(int r) {
				if (r < 0)
					throw "Illegal value for radius. Must be positive";
				radius = r;
			}

			/**
			 * This method sets the circle dimensions
			 *
			 * @param locx  x coordinat of location
			 * @param locy  y coordinat of location
			 * @param r  radius
			 * @return none
			 */
			void setCircle (int locx, int locy, int r) {
				setLocation (locx, locy);
				if (r < 0)
					throw "Illegal value for radius. Must be positive";
				radius = r;
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
				float *location = getLocation();

				dims[0] = location[0] - radius;
				dims[1] = location[0] + radius;
				dims[2] = location[1] - radius;
				dims[3] = location[1] + radius;

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

				if (shape == "circle")
					shape_json += QUOTE + "r" + QUOTE + COLON + to_string(radius)
						+ CLOSE_CURLY;

				return shape_json;

			}
	};

} // namespace bridges

#endif
