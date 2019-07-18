#ifndef ELVIS_H
#define ELVIS_H

#include "Color.h"
#include <cmath>

namespace bridges {
  namespace datastructure {  
	/** Enumeration of valid shapes for visualization */
	enum Shape {CIRCLE, SQUARE, DIAMOND, CROSS, TRIANGLE, STAR, WYE};
	/**
	 * @brief This class maintains the visual properties of the  a Bridges element
	 *
	 * This class is used to store the visualization elements for Bridges
	 * Visualiztions, including the color, shape, and size of the node.
	 * Defaults of green, circle, and 10.0 respectively.
	 *
	 * Size values must range from [1.0,50.0].
	 * BRIDGES supports the following shapes: "circle", "square", "diamond",
	 *  "cross", "triangle-down", "triangle-up"
	 *
	 * Objects of this class are stored as properties of all Element subclasses.
	 *
	 * @author Kalpathi Subramanian
	 * @date 6/11/15, 7/12/19
	 */
	class ElementVisualizer {
		public:
			static const Color DEFAULT_COLOR() {
				return Color("steelblue");
			}
			static constexpr Shape DEFAULT_SHAPE () {
				return CIRCLE;
			}
			static constexpr double DEFAULT_SIZE () {
				return 10.;
			}
		private:
			Color color = DEFAULT_COLOR();
			double size = DEFAULT_SIZE();
			Shape shape = DEFAULT_SHAPE();
			double locationX = INFINITY, locationY = INFINITY; // location of element
		public:
			/**
			 * Constructs an element with the provided Color, Size, and Shape.
			 * The defaults will be used if not provided.
			 *
			 * @param hue The Color for display
			 * @param sz The Size for display
			 * @param shp The Shape for display
			 */
			ElementVisualizer(const Color& hue = DEFAULT_COLOR(),
				const double& sz = DEFAULT_SIZE(),
				const Shape& shp = DEFAULT_SHAPE())
				: color(hue), size(sz), shape(shp) {}
			/**
			 * Sets size to "sz"
			 * Valid Range:[1,50]
			 *
			 * @param sz The size in pixel weight of the element
			 * @throw string If size is invalid
			 */
			void setSize(const double& sz) {
				(sz < 1 || 50 < sz)
					? throw "Invalid Size Value.. " + to_string(sz) +
						" Must be in the [1.0,50.0] range"
					: size = sz;
			}
			/** @return The size in pixel weight of the element*/
			double getSize() const {
				return size;
			}
			/**
			 *  Set the color to "col"
			 *  @param color The color of the element
			 */
			void setColor(const Color& col) {
				color = col;
			}
			/**
             *  Set the color to a named color "col"
             *  @param color The color name
             */
            void setColor(const string col) {
                color = Color(col);
            }

			/**
			 *  Return the element color
			 *	@return The color of the element
			 */
			Color getColor() const {
				return color;
			}

			/**
			 *	Set opacity of element - use the 4th color component
			 *
			 *  @param opacity
			 */
			void setOpacity(double opacity) {
				if (opacity >= 0.0 && opacity <= 1.0)
					color.setAlpha( (int) (opacity * 255.));
			}

			/**
			 *	Get opacity of element
			 *
			 *	@return opacity
			 */
			double getOpacity() {
				return color.getAlpha() / 255.;
			}
			/**
			 * Set the shape  of the element
			 *
			 * @param Shape is one of CIRCLE,SQUARE,DIAMOND,CROSS,TRI_DOWN,TRI_UP
			 */
			void setShape(const Shape& shp) {
				shape = shp;
			}
			/**
			 *  Return the shape of the element
			 *	@return The shape of the element(one of CIRCLE,SQUARE,
			 *		DIAMOND,CROSS,TRI_DOWN,TRI_UP
			 */
			Shape getShape() const {
				return shape;
			}
			/**
			 * Set the location attributes of an element. Set location to INFINITY for 
			 *	bridges to chose the location.
			 *
			 * @param locX X coordinate of the element location
			 * @param locY Y coordinate of the element location
			 */
			void setLocation(const double& locX, const double& locY) {
				locationX  = locX;
				locationY  = locY;
			}

			/**
			 *	@return the X coordinate of the  element's location attribute
			 */
			double getLocationX() const {
				return locationX;
			}
			/**
			 *	@return the Y coordinate of the  element's location attribute
			 */
			double getLocationY() const {
				return locationY;
			}
	};//end of ElementVisualizer class
  }
}//end of bridges namespace
#endif
