#include "DataStructure.h"
#include "Symbol.h"
#include <vector>


using namespace std;

#ifndef  RECTANGLE_H

#define RECTANGLE_H

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class defines a rectangle and is part of the symbol collection.
		 *		A rectangle has height and width
		 *
		 * @author Kalpathi Subramanian
		 * @date 12/23/18, 7/12/19
		 *
		 */
		class Rectangle : public Symbol {
			private:
				// height, width of rectangle
				float width = 1.0, height = 1.0;

			public:
				/**
				 *  constructors
				 */
				Rectangle() {
					setRectangle(0., 0., 1., 1.);
				}

				/**
				 * create rectangle with width w and height h
				 * @param w  width
				 * @param h  height
				 */
				Rectangle (int w, int h) {
					setRectangle (0., 0., w, h);
				}

				/**
				 * create rectangle with width w and height h
				 * @param locx  rect lower left - x coord
				 * @param locy  rect lower left - y coord
				 * @param w  width
				 * @param h  height
				 */
				Rectangle (float locx, float locy, float w, float h) {
					setRectangle (locx, locy, w, h);
				}

				/**
				 *	This method gets the data type name
				 *
				 *  @return name   data type name
				 */
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
				void setWidth(float w) {
					if (w <= 0.) {
						throw "Illegal Size Value! Please enter a value in the range(0-300)";
					}
					width = w;
				}

				/**
				 * This method sets the shape height
				 *
				 * @param h  height
				 */
				void setHeight(float h) {
					if (h <= 0.) {
						throw "Illegal Size Value! Please enter a value in the range(0-300)";
					}
					height = h;
				}

				/**
				 *	Translate the rectangle
				 *
				 *	@param tx translation factor along x axis
				 *	@param ty translation factor along y axis
				 */
				void translate(float tx, float ty) {
					const float *loc = getLocation();
					float myloc[] = {loc[0], loc[1]};
					translatePoint (myloc, tx, ty);
					setLocation(myloc[0], myloc[1]);
				}
				/**
				 *	Scale the rectangle about its center
				 *
				 *	@param sx scale factor along x axis
				 *	@param sy scale factor along y axis
				 */
				void scale(float sx, float sy) {
					// scale the height, width
					// center remains the same
					float pt[2] = {(float) width, (float) height};
					scalePoint (pt, sx, sy);
					width = pt[0];
					height = pt[1];
				}

				/**
				 * This method returns the dimensions of the shape: min and max
				 *	values in X and Y
				 *
				 * @return array of 4 values
				 */
				vector<float> getDimensions() const {

					vector<float> dims(4);
					const float *location = getLocation();

					dims[0] = location[0];
					dims[1] = location[0] + width;
					dims[2] = location[1];
					dims[3] = location[1] + height;

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
				void setRectangle(float locx, float locy, float w, float h) {
					if (w <= 0 || h <= 0)
						throw  "Width, Height must be positive";
					setLocation (float(locx), float(locy));
					width = w;
					height = h;
					setShapeType("rect");
				}

				/**
				 * This method returns the JSON representation of the shape
				 *
				 * @return string  JSON string
				 */
				virtual const string getSymbolRepresentation() const {

					string shape_json = getSymbolAttributeRepresentation();

					string shape = getShapeType();
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
	}
} // namespace bridges

#endif
