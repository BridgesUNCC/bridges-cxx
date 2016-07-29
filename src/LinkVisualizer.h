#ifndef LINK_VISUALIZER_H
#define LINK_VISUALIZER_H

#include "Color.h" //string, using std

namespace bridges{

/**
 * @brief This class maintains the visual properties of links within data structures.
 *
 * This class is used to keep the visual properties of links that are part of
 * data structures such as linked lists, pointer based trees, link based
 * graph representations, etc.  Relevant attributes include color and thickness
 *
 * Objects of this class are stored as properties of Elements.
 * A user may manipulate the LinkVisualizer returned from the Element's getLinkVisualizer() method.
 *
 * BRIDGES supports color of any legal named CSS or #hexadecimal value. Defalt: 
 *	opaque black
 * Thickness values must range from [0.0,10.0]. Default: 1.0
 *
 * @author Kalpathi Subramanian, Dakota Carmer
 * @date 6/29/15, 6/10/16
 */
class LinkVisualizer {
	public:
	 							// The default thickness of a link 
	static constexpr double DEFAULT_THICKNESS = 1.0;
								//	The default color of a link 
	static const Color DEFAULT_COLOR; //black

	private:
								// This link's color 
		Color color=DEFAULT_COLOR;
								// This link's thickness */
		double thickness=DEFAULT_THICKNESS;
		double weight = 1.0;

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
		 * Constructs a LinkVisualizer with the specified color and thickness.
		 * The defaults will be used if not provided (black,1)
		 *
		 * @param col Link color
		 * @param thick Link thickness
		 */
		LinkVisualizer(Color col = DEFAULT_COLOR,double thick = DEFAULT_THICKNESS)
								: color(col){setThickness(thick);}
		/**
	 	 * Set the thickness to "thick"
		 * Valid Range:[0,10] Default: 1
		 *
		 * @param thick The size in pixels of the link's line weight
		 * @throw string If invalid thickness
		 */
		void setThickness(const double& thick){
			(thick<0||10<thick)
					? throw "Invalid Thickness Value.. "
						+to_string(thick)+" Must be in the [0.0,10.0] range" 
					: thickness=thick;}

        /** 
		 *	@return Size in pixels of the link's line weight 
		 */
		double getThickness() const {
			return thickness;
		}

		/**
	 	 * Set the link weight to "wt"
		 * Valid Range: determined by application, can be negative
		 *
		 * @param wt The size in pixels of the link's line weight
		 * @throw string If invalid thickness
		 */
		void setWeight(const double& wt) {
			weight = wt;
		}

        /** 
		 *	@return link weight 
		 */
		double getWeight() const {
			return weight;
		}
		/** 
		 *	Set the color to "col", default black
		 *
		 *	@param color The color of the element 
		 */
		void setColor(const Color& col){
			color = Color(col.getRed(), col.getGreen(), col.getBlue(), col.getAlpha());
		}
		
		/**
		 * Set color by RGBA specificiation
		 *  @param r, g, b, a  
		 */
		void setColor(const int& r,const int& g,const int& b,const int& a=255) {
			color = Color(r, g, b, a);
		}

		/**
		 * Set color by CSS name
		 */
		void setColor(string name) {
			color.setValue(name);
		}

		/** 
		 * @return The color of the link 
		 */
		Color getColor() const {
			return color;
		}

		/**
		 * @return the opacity  of the link
		 */
		float getOpacity() {
			return float(color.getAlpha())/255.0f;
		}
		
		/**
		 * @set the opacity  of the link (0-255)
		 */
		void  setOpacity (float& opacity) {
			if (opacity < 0.0f || opacity > 1.0f) {
				cerr << "Opacity must be in the range [0.0-1.0]" << endl;
				return;
			}
			color.setAlpha(int(opacity*255.0f));
		}
		
}; //end of LinkVisualizer class

constexpr double LinkVisualizer::DEFAULT_THICKNESS;
const Color LinkVisualizer::DEFAULT_COLOR("SteelBlue");

}//end of bridges namespace
#endif
