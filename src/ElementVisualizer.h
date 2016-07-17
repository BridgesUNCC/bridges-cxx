#ifndef ELVIS_H
#define ELVIS_H

#include "Color.h"

namespace bridges{

/** 
 * Enumeration of valid shapes for visualization 
 */
enum Shape {
	CIRCLE,SQUARE,DIAMOND,CROSS,TRI_DOWN,TRI_UP
	};
/**
 * @brief This class maintains the visual properties of the  a Bridges element
 *
 * This class is used to store the visualization elements for Bridges
 * Visualiztions, including the color, shape, and size of the node.
 * Defaults of green, circle, and 10.0 respectively.
 *
 * Size values must range from [10.0,50.0].
 * BRIDGES supports the following shapes: "circle", "square", "diamond", 
 *	"cross", "triangle-down", "triangle-up"
 *
 * Objects of this class are stored as properties of all Element subclasses.
 *
 * @author Kalpathi Subramanian
 * @date 6/11/15
 */
class ElementVisualizer {
    public:
								//	The default color of an element 
		static const Color DEFAULT_COLOR; //green

								//	The default shape of an element
        static constexpr Shape DEFAULT_SHAPE = CIRCLE; //circle

								// 	The default size of an element 
        static constexpr double DEFAULT_SIZE = 10;

    private:

								// This element's color 
		Color color=DEFAULT_COLOR;
        						// This element's size 
		double size=DEFAULT_SIZE;
        						// This element's shape */
		Shape shape=DEFAULT_SHAPE;

		/**
		 *  ensure that the color is within  0-255 on all channels
		 */
		bool checkColorBounds() {
			int r = color.getRed();
			int g = color.getGreen();
			int b = color.getBlue();
			int a = color.getAlpha();

			return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255 &&
				a >= 0 && a <= 255);
		}

	public:
        /**
		 * Constructs an element with the provided Color, Size, and Shape.
		 * The defaults will be used if not provided.
		 *
		 * @param hue The Color for display
		 * @param sz The Size for display
		 * @param shp The Shape for display
		 */
		ElementVisualizer(const Color& hue = DEFAULT_COLOR,const double& 
						sz = DEFAULT_SIZE,const Shape& shp = DEFAULT_SHAPE) 
						: color(hue), size(sz), shape(shp) {}

        /**
		 * Sets size to "sz"
		 * Valid Range:[10,50]
		 *
		 * @param size The size in pixel weight of the element
		 * @throw string If size is invalid
		 */
		void setSize(const double& sz){
			(sz<10||50<sz) ?
				throw "Invalid Size Value.. "+to_string(sz) +
					" Must be in the [10.0,50.0] range" 
						: size = sz;
		}

		/** 
		 *@return The size in pixel weight of the element 
		 */
		double getSize() const {
			return size;
		}

		/** 
		 *	Set the color to "col" 
		 *	@param color The color of the element 
		 */
		void setColor(const Color& col){
			if (checkColorBounds()) {
				color = col;
			}
			else cerr << "Color value out of bounds (legal range: 0-255).";
		}
		
		/**
		 * 	Set color by RGBA specificiation
		 *  @param r, g, b, a  (0-255 range)
		 */
		void setColor(const int& r,const int& g,const int& b,const int& a=255) {
			Color c = Color(r, g, b, a);
			if (checkColorBounds()) 
				color = c;
			else cerr << "Color value out of bounds (legal range: 0-255).";
		}

		/**
		 * Set color by CSS name
		 *
		 * @param Color name
		 */
		void setColor(string name) {
			color.setValue(name);
		}


		/** 
		 *	@return The color of the element 
		 */
		Color getColor() const {
			return color;
		}
		/**
		 * Sets the shape to "shp"
		 * See the top of the page for the supported shapes.
		 *
		 * @param shape The shape of the element
		 * @throw string If the shape is invalid
		 */

		/**
         * @return the opacity  of the element,  in the range 0.0-1.0 
         */
        float getOpacity() {
            return float(color.getAlpha())/255.;
		}
        
        /**
         * @set the opacity  of the element (0-255)
         */
        void  setOpacity (float opacity) {
            if (opacity < 0.0f || opacity > 1.0f) {
                cerr << "Opacity must be in the range [0-1.0]" << endl;
                return;
            }
            color.setAlpha(opacity*255.0f);
        }

        /**
         * Set the shape  of the element 
		 *
		 * @param Shape is one of CIRCLE,SQUARE,DIAMOND,CROSS,TRI_DOWN,TRI_UP
         */
		void setShape(const Shape& shp){
			shape = shp;
		}

		/** 
		 *	@return The shape of the element(one of CIRCLE,SQUARE,DIAMOND,CROSS,
		 * 			TRI_DOWN,TRI_UP 
		 *
		 */
		Shape getShape() const {
			return shape;
		}
};//end of ElementVisualizer class

							// define the static variables
const 		Color ElementVisualizer::DEFAULT_COLOR("green");
constexpr 	Shape ElementVisualizer::DEFAULT_SHAPE;
constexpr 	double ElementVisualizer::DEFAULT_SIZE;

}//end of bridges namespace
#endif
