#ifndef LINK_VISUALIZER_H

#define LINK_VISUALIZER_H

#include <string>
#include <unordered_map>

using namespace std;

/**
 * 	This class is used to keep the visual properties of links that art of 
 *  data structures such as linked lists, pointer based trees, link based
 *  graph representations, etc.  Relevant attributes include
 *  color, thickness, opacity, line end point attributes.
 * 	<p>
 * 	Objects of this class are stored as properties of all Element subclasses.
 * 	Generally, you will manipulating the LinkVisualizer returned from the
 * 	Element getLinkVisualizer() method, and then call the setLinkVisualizer() 
 * 	method on the Element after changes have been made.
 **/

namespace bridges {

class LinkVisualizer{
					// Link visualization properties for this element.
					// maintains mapping from the terminating vertex to its
					// visual properties
					// implemented as a hashmap mapping into properties, which
					// is als a hashmap, to keep the accesses constant time.
	private:
		unordered_map<string, string> properties; 
		string  toLowerCase(string s) {
			for (string::size_type i = 0; i < s.length(); i++)
				s[i] = tolower(s[i]);

			return s;
		}

	public:
		LinkVisualizer() {
			properties.emplace("color", "black");
			properties.emplace("opacity", "1.0");
			properties.emplace("thickness", "1.0");
//			properties.emplace("weight", "0.0");
		}
	
						// constructor
		/**
		 * 	Constructor 
		 * @param color  - link color
		 * @param opacity  - link opacity
		 * @param thickness  - link thickness
		 *
		 **/
		LinkVisualizer(string color, double opacity, double thickness) {
			setColor(color);
			setOpacity(opacity);
			setThickness(thickness);
		}
		/**
		 * Set the thickness of the link in the Bridge Visualization in pixels
		 * 
		 * @param thickness the pixel size of the Element in the Bridges 
		 *		Visualization
		 */
		void setThickness(double thickness) {
			try{
								// validate thickness
				Validation::getCurrent()->validateThickness(thickness);
				properties["thickness"]  = to_string(thickness);
            }
            catch (string msg) {
                cerr << msg << endl;
            }
		}
	
		/**
		 * Get the thickness of the link in the Bridges Visualiation
		 * 
		 * @return the size in pixels of the Element in the Bridges 
		 *		Visualization
		**/
		double getThickness() {
			return stod (properties["thickness"]);
		}
	
		/** Set the color of the link in the Bridges Visualization to "aColor".
		 * 	@param aColor the string reprsenting the color of the Element 
		 *	in the Bridges Visualization
		**/
		void setColor(string aColor) {
			aColor = toLowerCase(aColor);
			try{
								// validate color
				Validation::getCurrent()->validateColor(aColor);
				properties["color"]  = aColor;

			}
			catch (string msg) {
				cerr << msg << endl;
            }
		}
	
		/**   Get the color of the link in the Bridges Visualization
		 *    @return the string reprsenting the color of the Element in the 
	     *    Bridges Visualization
		 */
		string getColor() {
			return properties["color"];
		}
	
		/**
		 * Sets the opacity of the link in the Bridges Visualization
		 * 
		 * @param opacity a double between 0 and 1 representing how 
		 *		transparent the node should be on the Bridges Visualization. 
		 *		0 for invisible, 1 for fully visible, a decimal between 
		 *		0 and 1 for varying transparency.
		 **/
		void setOpacity(double opacity) {
			try{
								// validate opacity
				Validation::getCurrent()->validateOpacity(opacity);
				properties["opacity"]  = to_string(opacity);
			}
			catch (string msg) {
				cerr << msg << endl;
			}
		}
	
		/** 
		 *	Get the opacity of the link in the Bridges Visualization
		 * 	@return the opacity value
		 **/
		double getOpacity() {
			return stod (properties["opacity"]);
		}
		/**
		 * 
		 * Sets the edge weight  of the link in the Bridges Visualization
		 * 
		 * @param weight an integer value  
		 * 
		 **/
		void setWeight(int w) {
			try{
								// validate opacity
				Validation::getCurrent()->validateWeight(w);
				properties["weight"]  = to_string(w);
			}
			catch (string msg) {
				cerr << msg << endl;
			}
		}
	
		/** 
		 * Get the edge weight of the link 
		 *
		 * @return the weight 
		 */
		double getWeight() {
			return stod(properties["weight"]);
		}
	
		unordered_map<string, string> getProperties() {
			return properties;
		}
};


}
#endif
