#ifndef LINK_VISUALIZER_H
#define LINK_VISUALIZER_H

#include "Color.h" //string, using std

namespace bridges {
  namespace datastructure {
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
	 * BRIDGES supports color of any legal named CSS or #hexadecimal value. Default:
	 *  opaque black
	 * Thickness values must range from [1.0,10.0]. Default: 1.0
	 *
	 * @author Kalpathi Subramanian, Dakota Carmer
	 * @date 6/29/15, 6/10/16, 7/12/19
	 */
	class LinkVisualizer {
		public:

			static constexpr double DEFAULT_THICKNESS() {
				return 1.0;
			}
			static Color DEFAULT_COLOR() {
				return Color("steelblue");
			}; //SteelBlue

		private:

			Color color = DEFAULT_COLOR();
			string label = "";
			double thickness = DEFAULT_THICKNESS();

		public:
			/**
			 * Constructs a LinkVisualizer with the specified color and thickness.
			 * The defaults will be used if not provided (black,1)
			 *
			 * @param col Link color
			 * @param thick Link thickness
			 *
			 */
			LinkVisualizer(Color col = DEFAULT_COLOR(),
				double th = DEFAULT_THICKNESS()):
				color(col) {
				setThickness(th);
			}

			/**
			 *  Return the element label
			 *  @return The label of the element
			 */
			string getLabel() const {
				return label;
			}

			/**
			 * Sets label to "lab"
			 *
			 * @param lab The label of the element
			 */
			void setLabel(const string& lab) {
				label = lab;
			}

			/**
			 * Set the link thickness
			 * Valid Range:[1,10] Default: 1
			 *
			 * @param thick The size in pixels of the link's line weight
			 * @throw string If invalid thickness
			 */
			void setThickness(const double& th) {
				if (th < 1 || 10 < th)
					throw "Invalid Thickness Value.. " + to_string(th) +
					" Must be in the [1.0,10.0] range";
				else
					thickness = th;
			}
			/**
			 *  Get the link thickness
			 *	@return Size in pixels of the link's line thickness
			 */
			double getThickness() const {
				return thickness;
			}

			/**
			 * Set the link color to "col", default black
			 *
			 * @param color The color of the element
			 */
			void setColor(const Color& col) {
				color = col;
			}
			/**
             *  Set the color to a named color "col"
			 *  Check the Color class for supported color names
             *  @param color The color name
             */
            void setColor(const string col) {
                color = Color(col);
            }

			/**
			 *  Return the link color
			 *	@return The color of the link
			 */
			Color getColor() const {
				return color;
			}
	}; //end of LinkVisualizer class
  }
}//end of bridges namespace
#endif
