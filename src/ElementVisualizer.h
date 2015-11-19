#ifndef ELEMENT_VISUALIZER_H

#define ELEMENT_VISUALIZER_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

#include "Validation.h"


namespace bridges {

/**
 *@brief This class maintains the visual properties of the  a Bridges element

 * This class is used to store the visualization elements for Bridges
 * Visualiztions, including the color, shape, opacity, and size of the node.
 * Binary search trees will also store the element's search key value.
 * <p>
 * Objects of this class are stored as properties of all Element subclasses.
 * Generally, you will manipulating the ElementVisualizer returned from the
 * Element getVisualizer() method, and then call the setVisualizer() method on
 * the Element after changes have been made.
 *
 *
 * BRIDGES supports the following named colors(passed into either via
 * the constructor or as a parameter to setColor():
 *
 *
 *	"aliceblue", "antiquewhite", "aqua", "aquamarine", "azure", "beige",
 *	"bisque", "black", "blanchedalmond", "blue", "blueviolet", "brown",
 *	"burlywood", "cadetblue", "chartreuse", "chocolate", "coral",
 *	"cornflowerblue", "cornsilk", "crimson", "cyan", "darkblue", "darkcyan",
 *	"darkgoldenrod", "darkgray", "darkgreen", "darkgrey", "darkkhaki",
 *	"darkmagenta", "darkolivegreen", "darkorange", "darkorchid", "darkred",
 *	"darksalmon", "darkseagreen", "darkslateblue", "darkslategray", 
 *	"darkslategrey", "darkturquoise", "darkviolet", "deeppink", "deepskyblue",
 *	"dimgray", "dimgrey", "dodgerblue", "firebrick", "floralwhite",
 *	"forestgreen", "fuchsia", "gainsboro", "ghostwhite", "gold", "goldenrod",
 *	"gray", "green", "greenyellow", "grey", "honeydew", "hotpink", "indianred",
 *	"indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen",
 *	"lemonchiffon", "lightblue", "lightcoral", "lightcyan", 
 *	"lightgoldenrodyellow", "lightgray", "lightgreen", "lightgrey", "lightpink",
 *	"lightsalmon", "lightseagreen", "lightskyblue", "lightslategray",
 *	"lightslategrey", "lightsteelblue", "lightyellow", "lime", "limegreen",
 *	"linen", "magenta", "maroon", "mediumaquamarine", "mediumblue", 
 *	"mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue",
 *	"mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue",
 *	"mintcream", "mistyrose", "moccasin", "navajowhite", "navy", "oldlace",
 *	"olive", "olivedrab", "orange", "orangered", "orchid", "palegoldenrod",
 *	"palegreen", "paleturquoise", "palevioletred", "papayawhip", "peachpuff",
 *	"peru", "pink", "plum", "powderblue", "purple", "red", "rosybrown",
 *	"royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen", "seashell",
 *	"sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey", "snow",
 *	"springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise",
 *	"violet", "wheat", "white", "whitesmoke", "yellow", "yellowgreen"
 *
 *	BRIDGES supports the following shapes:
 *
 *	"circle", "square", "diamond", "cross", "triangle-down", "triangle-up"
 *	Default : "circle"
 *
 *  Opacity: Links can be transparent, specified by the opacity value. 
 *  Must be within  0.0(fully transparent) - 1.0(fully opaque), Default: 1.0
 *
 *  Size: Element size. Size values must be positive and range from 10.0-50.0. 
 * 	Default: 10.0
 *
 *
 * @author Kalpathi Subramanian(C++ port)
 * @date 6/27/15
 *
 **/



class ElementVisualizer {
							// Visualization properties for this Node.
	private:
		unordered_map<string, string> properties;
	
		string  toLowerCase(string s) {
//			for (string::size_type i = 0; i < s.length(); i++)
//				s[i] = tolower(s[i]);
			transform(s.begin(), s.end(), s.begin(), 
				static_cast<int(*)(int)>(std::tolower));

			return s;
		}
		/**
		 * 	Construct an ElementVisualizer with the default visualization 
		 *	settings. Default settings are color = green, opacity = 1.0, 
		 *	size = 10.0, shape = circle.
		 **/
	public: 
		ElementVisualizer() {
			properties.clear();
			properties.emplace("color", "green");
			properties.emplace("opacity", "1.0");
			properties.emplace("size", "10.0");
			properties.emplace("shape", "circle");
		}

		~ElementVisualizer() {
			properties.clear();
		}
	
		/**
		 * Construct an ElementVisualizer with its color set to "aColor".
		 * 
		 * @param aColor the string that represents one of the Bridges colors.
		 *
		 *
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
		 * 	@param aColor : the string that represents one of the Bridges colors.
		 * 	@param aShape : the string that represents one of the Bridges shapes
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
		 * 	@param size : represents the size in pixels of 
		 *	the Element on the Bridges Visualization
		 */
		ElementVisualizer(int size) : ElementVisualizer() {
			setSize(size);
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
		 * @param ev
		 *            the ElementVisualizer whose settings you want to copy.
		 */
		ElementVisualizer(ElementVisualizer& ev) :
			ElementVisualizer(ev.getColor(), ev.getShape(), ev.getOpacity(), 
								ev.getSize()) {
		}
	
		/**
		 * Set the size of the Element in the Bridge Visualization in pixels
		 * 
		 * @param size - the pixel size of the Element in the 
		 * Bridges Visualization. Must be (0.0-50), Default 10.0
		 */
		void setSize(double size) {
			try{
				Validation::getCurrent()->validateSize(size);
				properties["size"] = to_string(size);
			}
			catch (string msg) {
				cerr << msg << endl;
				cerr << "Using default size (10).." << endl;
				properties["size"]  = "10.0";
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
		 *  @param aColor - the string reprsenting the color of the Element 
		 *	in the Bridges Visualization
		 *
		 *  See the top of the page for the supported colors
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
				cerr << "Using default color (`black').." << endl;
				properties["color"]  = "black";
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
		 * 	@param aShape - the string representing the shape of the Element 
		 *	in the Bridges Visualization
		 *
		 *  See the top of the page for the supported shapes (Default: "circle")
		 *
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
				cerr << "Using default shape (`circle').." << endl;
				properties["shape"]  = "circle";
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
		 * @param opacity - a double value  between 0.0(fully transparent) 
		 *		and 1 (fully opaque)
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
				cerr << "Using default opacity (1.0).." << endl;
				properties["opacity"]  = "1.0";
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
		 * 
		 *  Sets the key value attribute  of the Element  as a string;
		 *  used by search structures - binary tree, binary search tree, etc. 
		 * 
		 * @param key - is a string (key value, which is orderable converted 
		 *		 into a string, used for creating the JSON representation
		 * 
		 **/
		void setKey(string key) {
			try{
								// validate key
//				Validation::getCurrent()->validateKey(key);
				properties["key"]  = key;
			}
			catch (string msg) {
				cerr << msg << endl;
			}
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


}
#endif
