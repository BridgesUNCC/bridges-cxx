#ifndef ELEMENT_VISUALIZER_H

#define ELEMENT_VISUALIZER_H

#include <string>
#include <unordered_map>

using namespace std;

#include "Validation.h"



/**
 * This class is used to store the visualization elements on the for the Bridges
 * Visualiztion, including the color, shape, opacity, and size of the node.
 * <p>
 * Objects of this class are stored as properties of all Element subclasses.
 * Generally, you will manipulating the ElementVisualizer returned from the
 * Element getVisualizer() method, and then call the setVisualizer() method on
 * the Element after changes have been made.
 **/

class ElementVisualizer {
							// Visualization properties for this Node.
	private:
		unordered_map<string, string> properties;
	
		string  toLowerCase(string s) {
			for (string::size_type i = 0; i < s.length(); i++)
				s[i] = tolower(s[i]);

			return s;
		}
		/**
		 * 	Construct an ElementVisualizer with the default visualization 
		 *	settings. Default settings are color = green, opacity = 1.0, 
		 *	size = 10.0, shape = circle.
		 **/
	public: 
		ElementVisualizer() {
			properties.emplace("color", "green");
			properties.emplace("opacity", "1.0");
			properties.emplace("size", "10.0");
			properties.emplace("shape", "circle");
		}
	
		/**
		 * Construct an ElementVisualizer with its color set to "aColor".
		 * 
		 * @param aColor the string that represents one of the Bridges colors.
		 **/
		ElementVisualizer(string aColor) : ElementVisualizer()  {
							// need to validate color 
			setColor(aColor);
		}
	
		/**
		 * 	Construct an ElementVisualizer with its color set to "aColor" 
		 *	and shape
		 * 	set to "aShape".
		 * 
		 * 	@param aColor: the string that represents one of the Bridges colors.
		 * 	@param aShape: the string that represents one of the Bridges shapes
		 **/
		ElementVisualizer(string aColor, string aShape) 
						: ElementVisualizer() {
							// need to validate color 
			setColor(aColor);
			setShape(aShape);
		}
	
		/**
		 * 	Construct an ElementVisualizer with its size set to "size".
		 * 
		 * 	@param size : the double that represents the size in pixels of 
		 *	the Element on the Bridges Visualization
		 */
		ElementVisualizer(double size) : ElementVisualizer() {
			Validation::getCurrent()->validateSize(size);
			properties["size"] = to_string(size);
		}
	
		/**
		 * 	Construct an ElementVisualizer with its color set to "aColor", 
		 *	its shape set to "aShape", its opacity set to "opacity" and 
		 *	size set to "size".
		 * 	@param aColor
		 *     the string that represents one of the Bridges colors.
		 * @param aShape
		 *     the string that represents one of the Bridges shapes
		 * @param opacity
		 *     a double between 0 and 1 representing how transparent the node
		 *	should be on the Bridges Visualization. 0 for invisible, 1 for
		 *  fully visible, a decimal between 0 and 1 for varying transparency.
		 * @param size
		 *     the double that represents the size of the Element on the
		 *     Bridges Visualization
		 */
		ElementVisualizer(string aColor, string aShape, double opacity,
				double size) {
			setColor(aColor);
			setShape(aShape);
			setOpacity(opacity);
			setSize(size);
		}
	
		/**
		 * Construct a new ElementVisualizer with the same color, shape, opacity,
		 * and size as "v"
		 * 
		 * @param v
		 *            the ElementVisualizer whose settings you want to copy.
		 */
		ElementVisualizer(ElementVisualizer& ev) :
			ElementVisualizer(ev.getColor(), ev.getShape(), ev.getOpacity(), 
								ev.getSize()) {
		}
	
		/**
		 * Set the size of the Element in the Bridge Visualization in pixels
		 * 
		 * @param size
		 *            the pixel size of the Element in the Bridges Visualization
		 */
		void setSize(double size) {
			try{
				Validation::getCurrent()->validateSize(size);
				properties["size"] = to_string(size);
			}
			catch (string msg) {
				cerr << msg << endl;
			}
		}
	
		/**
		 * Get the size of the Element in the Bridges Visualiation
		 * 
		 * @return the size in pixels of the Element in the Bridges 
		 *     Visualization
		 */
		double getSize() {
			return stod(properties["size"]);
		}
	
		/** 
		  *	Set the color of the Element in the Bridges Visualization 
		  *	to "aColor".
		  * @param aColor the string reprsenting the color of the Element 
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
	
		/**
		 *	Get the color of the Element in the Bridges Visualization
		 * 	@return the string reprsenting the color of the Element in the 
		 *	Bridges Visualization
		**/
		string getColor() {
			return properties["color"];
		}
	
		/**
		 * 	Sets the shape of the Element in the Bridges Visualization
		 * 
		 * 	@param aShape the string representing the shape of the Element 
		 *	in the Bridges Visualization
		 **/
		void setShape(string aShape) {
			aShape = toLowerCase(aShape);
			try{
								// validate shape
				Validation::getCurrent()->validateShape(aShape);
				properties["shape"]  = aShape;
			}
			catch (string msg) {
				cerr << msg << endl;
			}
		}

		/**
		 * Get the shape of the Element in the Bridges Visualization.
		 * @return the string that represents the Element's shape in the 
		 *		Bridges Visualization.
		 */
		string getShape() {
			return properties["shape"];
		}
	
		/**
		 * 
		 * Sets the opacity of the Element in the Bridges Visualization
		 * 
		 * @param opacity a double value  between 0.0(fully opaque) 
		 *		and 1 (fully transparent representing how 
		 * 
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
		 * Get the opacity of the Element in the Bridges Visualization
		 * @return the opacity value
		 */
		double getOpacity() {
			return stod(properties["opacity"]);
		}
		/** 
	     *  This method returns the properties map
		 *
		 *  @return the properties map
		 **/
		unordered_map<string, string> getProperties() {
			return properties;
		}
};

#endif
