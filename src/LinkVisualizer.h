#ifndef LINK_VISUALIZER_H
#define LINK_VISUALIZER_H

#include "Color.h" //validation, cerr, unordered_map, string, using std

namespace bridges {
/**
 * @brief This class maintains the visual properties of links that
 *  part of linked data structures.
 *
 * This class is used to keep the visual properties of links that are part of
 * data structures such as linked lists, pointer based trees, link based
 * graph representations, etc.  Relevant attributes include
 * color, thickness, opacity, line end point attributes.
 *
 * Objects of this class are stored as properties of all Element subclasses.
 * Generally, a user will manipulate the LinkVisualizer returned from the
 * Element's getLinkVisualizer() method, and then call the setLinkVisualizer()
 * method on the Element after changes have been made.
 *
 * BRIDGES supports color of any legal named CSS or #hexadecimal value. Defalt: black
 * Thickness values must range from [0.0,10.0]. Default: 1.0
 * Opacity must be between 0.0(fully transparent) and 1.0(fully opaque). Default: 1.0
 * Weight must be positive. Default: 1.0
 *
 * @author Kalpathi Subramanian, 6/29/15
 * @date 6/29/15
 */
class LinkVisualizer
{
    public:
        static constexpr double
            DEFAULT_THICKNESS = 1.0,
            DEFAULT_WEIGHT = 1.0;
        static const Color
            DEFAULT_COLOR;//black
	private:
		//Initialized here, for safty
		Color color=DEFAULT_COLOR;
		double thickness=DEFAULT_THICKNESS,
               weight=DEFAULT_WEIGHT;
	public:
		/**
		 * Constructor
		 *
		 * @param col Link color
		 * @param opac Link opacity
		 * @param thick Link thickness
		 * @param wt Link weight
		 */
		LinkVisualizer(Color col = DEFAULT_COLOR,double thick = DEFAULT_THICKNESS,double wt = DEFAULT_WEIGHT){setColor(col); setThickness(thick); setWeight(wt);}
		/**
		 * Set the thickness to "thick"
		 * Valid Range:[0,10] Default: 1
		 *
		 * @param thickness The size in pixels of the Link
		 */
		void setThickness(const double& thick)
		{
			try
			{
				Validation::validateThickness(thick);
				thickness = thick;
            }
            catch (const string& msg)
            {
                cerr << msg << endl << "Thickness left unchanged.." << endl;
            }
		}
        /**
		 * Get the thickness of the link in the Bridges Visualiation
		 *
		 * @return Size in pixels of the Link
		 */
		double getThickness() const {return thickness;}
		/**
		 * Set the color to "col"
		 * Default: black
		 *
		 * @param col The Color of the Link
		 */
		void setColor(const Color& col){color = col;}
		/**
		 * Get the color of the link in the Bridges Visualization
		 *
		 * @return The color of the Link
		 */
		Color getColor() const {return color;}
		/**
		 * Sets the edge weight to "wt"
		 * Valid Range:[0,inf) Default: 1
		 *
		 * @param weight The weight of the Link
		 **/
		void setWeight(const double& wt)
		{
			try
			{
				Validation::validateWeight(wt); // validate weight
				weight = wt;
			}
			catch (const string& msg)
			{
				cerr << msg << endl << "Weight left unchanged.." << endl;
			}
		}
		/**
		 * Get the weight of the link
		 *
		 * @return The weight of the Link
		 */
		double getWeight() const {return weight;}
}; //end of LinkVisualizer class
constexpr double LinkVisualizer::DEFAULT_THICKNESS,
                 LinkVisualizer::DEFAULT_WEIGHT;
const Color LinkVisualizer::DEFAULT_COLOR("black");

}//end of bridges namespace
#endif
