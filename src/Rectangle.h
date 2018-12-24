#include "DataStructure.h"
#include "Symbol.h"
#include <vector>

using namespace std;

#ifndef  RECTANGLE_H

#define RECTANGLE_H

namespace bridges {

	/*
	 * @brief This class defines a rectangle and is part of the symbol collection. 
	 *		A rectangle has height and width
	 *
	 * @author Kalpathi Subramanian
	 * @date 12/23/18
	 *
	*/
	class Rectangle : public Symbol {
		private:
			string shape = "rect";
								// height, width of rectangle
			int width = 10,		
				height = 10;

		public:

			/**
             *  constructors
             */
			Rectangle() {
				width = height = 10;
			}

			Rectangle (int w, int h) {
				if (w < 0 || h < 0) 
					throw "Illegal height or width! Height and Width values need to be positive";
				width = w; height = h;
			}

			Rectangle (int locx, int locy, int w, int h) {
				setLocation (float(locx), float(locy));
				if (w < 0 || h < 0) 
					throw "Illegal height or width! Height and Width values need to be positive";
				width = w; height = h;
			}

			string getDataStructType() {
				return "rect";
			}

			/**
			 *	This method gets the name of the shape
			 *
			 *  @return name   shape name
			 */
			string getName()  const {
				return "rect";
			}

			/**
			 * This method sets the shape width
			 *
			 * @param w  width
			 */
			void setWidth(int w) {
				if (w <= 0 || w > 300) {
					throw "Illegal Size Value! Please enter a value in the range(0-300)";
				}
				width = w;
			}

			/**
			 * This method sets the shape height
			 *
			 * @param h  height
			 */
			void setHeight(int h) {
				if (h <= 0 || h > 300) {
					throw "Illegal Size Value! Please enter a value in the range(0-300)";
				}
				height = h;
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

				dims[0] = location[0] - width / 2;
				dims[1] = location[0] + width / 2,
				dims[2] = location[1] - height / 2;
				dims[3] = location[1] + height / 2;

				return dims;
			}

			/*
			 * This method sets the location and size of the rectangle
			 *
			 * @pram locx  x coordinate of location
			 * @pram locy  y coordinate of location
			 * @param w  width of rectangle
			 * @param h  height of rectangle
			 *
			 * @return none
			 */
			void setRectangle(int locx, int locy, int w, int h) 	{

				setLocation (float(locx), float(locy));
				if (w <= 0 || w > 300 || h <=0 ||  w > 300) {
					throw "Illegal Size Value! Please enter values in the range 0-300";
				}
				width = w;
				height = h;
			}

			/**
             * This method returns the JSON representation of the shape
             *
             * @return string  JSON string
             */
			virtual const string getSymbolRepresentation() const {

				string shape_json = getSymbolAttributeRepresentation();

				shape_json +=
					QUOTE + "name" + QUOTE + COLON +  QUOTE + getLabel() + QUOTE + COMMA +
					QUOTE + "shape" + QUOTE + COLON + QUOTE + shape + QUOTE + COMMA;

				// set up width and height of rectangles
				if (shape == "rect")
					shape_json += QUOTE + "width" + QUOTE + COLON + to_string(width) + COMMA +
						QUOTE + "height" + QUOTE + COLON + to_string(height) + 
					CLOSE_CURLY;

				return shape_json;

			}
	};

} // namespace bridges

#endif
