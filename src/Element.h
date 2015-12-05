#ifndef ELEMENT_H
#define ELEMENT_H

#include <list> //list

#include "LinkVisualizer.h" //Color, cerr, string, unordered_map, using std

namespace bridges {
    const string// Some constants used to generate JSON strings
        QUOTE = "\"",
        COMMA = ",",
        COLON = ":",
        OPEN_CURLY = "{",
        CLOSE_CURLY = "}",
        OPEN_PAREN = "[",
        CLOSE_PAREN = "]";
/**
 * @brief This is the fundamental building block used in building all
 *		data structures in BRIDGES
 *
 * This is the Superclass Element with SLelement, DLelement,
 * TreeElement, BSTElement subclasses. Arrays are also built of this type.
 *
 * Template type  parameter E  is provided to store any application
 * specific data. E  can be of any legal C++ type: integer, string, float,
 * double, or any user defined object(class, struct, array).
 *
 * The label field(string type) is used to label the visualization of
 * the element node.
 *
 * Element holds a LinkVisualizer for each of its links. LinkVisualizer holds
 * visualization properties of the link between this element and the element it is linked
 * to -- useful in linked structures and graphs that contain edges.
 *
 * Element also hold visualization properties for itself,
 * including the color, shape, opacity, and size of the node.
 *
 * BRIDGES supports color of any legal named CSS or #hexadecimal value. Defalt: green
 * Size values must range from [10.0,50.0]. Default: 10.0
 * Opacity must be between 0.0(fully transparent) and 1.0(fully opaque). Default: 1.0
 * BRIDGES supports the following shapes:
 * "circle", "square", "diamond", "cross", "triangle-down", "triangle-up"
 * Default: "circle"
 *
 * E : Application specific data type - can be any legal C++ type.
 *
 * @author  Kalpathi Subramanian,
 * @date 6/11/15
 */
template <typename E> class Element
{
    public:
	    static const Color DEFAULT_COLOR; //green
        static const string DEFAULT_SHAPE; //circle
		static constexpr double DEFAULT_SIZE = 10;
	private:
        //Element Visualizer Properties
        Color color=DEFAULT_COLOR;
        string shape=DEFAULT_SHAPE;
		double size=DEFAULT_SIZE;
        //Element Properties
		string label;
		unordered_map<Element*, LinkVisualizer> links;
    	E value = E();
	public:
        /**
		 * Element constructor creates an ElementVisualizer,
		 * a map of LinkVisualizers, sets value to "val", and
		 * sets label to "lab". If an argument isn't provided
		 * it's default constructor will be used.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
		 */
		Element(E val = E(),string lab = string()) : label(lab), value(val) {links.clear();}
        /** Copy constructor */
		Element(const Element& el) : Element(el.value, el.label){}
        /** Assignment operator */
		Element& operator=(const Element& el){value = el.value; label = el.label; return *this;}
        /** Destructor */
		virtual ~Element(){links.clear();}
		/**
		 * Sets size to "sz"
		 * Valid Range:[0,50] Default: 10
		 *
		 * @param size Input size in pixels of Element.
		 */
		void setSize(const double& sz)
		{
			try
			{
				Validation::validateSize(sz);
				size = sz;
			}
			catch (const string& msg)
			{
				cerr << msg << endl << "Size left unchanged.." << endl;
			}
		}
		/**
		 * Get the size of the Element in the Bridges Visualiation
		 *
		 * @return Size in pixels of Element
		 */
		double getSize() const {return size;}
		/**
		 * Set the color to "col"
		 * Default: green
		 *
		 * @param color Input Bridges color of Element
		 */
		void setColor(const Color& col){color = col;}
		/**
		 * Get the color of the Element in the Bridges Visualization
		 *
		 * @return Bridges color of Element
		 */
		Color getColor() const {return color;}
		/**
		 * Sets the shape to "shp"
		 * Default: circle, See the top of the page for the supported shapes.
		 *
		 * @param shape Input Bridges shape of Element
		 */
		void setShape(const string& shp)
		{
			try
			{
				Validation::validateShape(shp);
				shape = shp;
			}
			catch (const string& msg)
			{
				cerr << msg << endl << "Shape left unchanged.." << endl;
			}
		}
		/**
		 * Get the shape of the Element in the Bridges Visualization.
		 *
		 * @return Bridges shape of Element
		 */
		string getShape() const {return shape;}
        /**
	 	 * Returns the LinkVisualizer to element "el"
	 	 * (Creates Default LinkVisualizer if none set)
		 *
	 	 * @param el The terminating element
	 	 * @return The LinkVisualizer
	 	 */
		LinkVisualizer& getLinkVisualizer(Element* el){return links[el];}
        /**
	 	 * This returns the label
	 	 *
	 	 * @return The label
	 	 */
		string getLabel() const {return label;}
		/**
	 	 * Sets label to "lab"
		 *
	 	 * @param lab Input label
		 *
	 	 */
		void setLabel(const string& lab){label = lab;}
		/**
	 	 * Returns the Element's data
		 *
	 	 * @return The value
         */
		E getValue() const {return value;}
		/**
	 	 * Sets value to "val"
		 *
	 	 * @param val Input data
	 	 */
		void setValue(const E& val){value = val;}
		/** Removes unnessasary trailing 0s to lower size of JSON string */
		static string removeTrailingZeros(const double& num)
        {
            if(static_cast<int>(num) == num){return to_string(static_cast<int>(num));}//if integer return as int
            string numRep = to_string(num);
            numRep.erase(numRep.find_last_not_of("0")+1);//removes trailing 0s
            return numRep;
        }
		/**
	 	 * Internal code for getting the properties of the Element object.
	 	 * It produces (without the spaces or newlines):
	 	 * {
	 	 *  "other CSS properties like color": any_JSON_value
         *  "name": "Some label"
	 	 * }
	 	 *
	 	 * @return The JSON string
	 	 */
		virtual string getRepresentation() const
		{
			return
            OPEN_CURLY +
                //write out element visualizer properties
                QUOTE + "color"   + QUOTE + COLON + QUOTE + color.getCSSrep()         + QUOTE + COMMA +
                QUOTE + "opacity" + QUOTE + COLON + QUOTE + to_string(1)              + QUOTE + COMMA + //color's alpha will take care of, left here untill server code updated
                QUOTE + "shape"   + QUOTE + COLON + QUOTE + shape                     + QUOTE + COMMA +
                QUOTE + "size"    + QUOTE + COLON + QUOTE + removeTrailingZeros(size) + QUOTE + COMMA +
                //write out this node
                QUOTE + "name" + QUOTE + COLON + QUOTE + label + QUOTE +
            CLOSE_CURLY;
		}
		/**
		 * Returns a pair of JSON strings of the nodes and links of the Bridges array
		 * It is the user's responsibility to supply a correct size, as bound validation doesn't occur.
		 * The object this function is called with will function as the first element of the array.
		 *
		 * @param arr_size This' array length
		 * @return A pair of node and link JSON
		 */
		virtual pair<string,string> getDataStructureRepresentation(const int& arr_size)
		{
			list<const Element*> nodes;
			this->links.clear();
			for(int i = 0; i < arr_size; i++) //get nodes
            {
                nodes.push_front(&this[i]);
            }
			return Element<E>::generateJSON_Of_Nodes_And_Links(nodes);
		}
		/**
		 * Generates the Pair of JSON of the given the nodes and links
		 *
		 * @param nodes List of nodes
		 * @param links List of Links
		 * @return A pair of node and link JSON
		 */
		static pair<string,string> generateJSON_Of_Nodes_And_Links(const list<const Element*>& nodes)
		{

		    Validation::validate_ADT_size(nodes.size()); // cant exceed max number of elements
			// map the nodes to a sequence of ids, 0...N-1 then get the JSON string for nodes
			unordered_map<const Element*,int> map;
			string nodes_JSON, links_JSON;

            int i=0;
			for(const auto* e: nodes) // get the JSON string for nodes
            {
                map.emplace(e,i++);
                nodes_JSON += e->getRepresentation() + COMMA;
			}
			if(nodes_JSON.size()){nodes_JSON = nodes_JSON.erase(nodes_JSON.size()-1);} //Remove trailing comma

			for(const auto* e: nodes) //each Element* in nodes
            {
                for(const auto& p: e->links) //each pair<Element*,LinkVisualizer> in Element*->links
                {
                    const LinkVisualizer& lv = p.second;
                    if(lv.getWeight()) //Only add data if weight isn't 0
                    {
                        links_JSON +=
                            OPEN_CURLY +
                                //write out LinkVisualizer properties
                                QUOTE + "color"     + QUOTE + COLON + QUOTE + lv.getColor().getCSSrep()              + QUOTE + COMMA +
                                QUOTE + "opacity"   + QUOTE + COLON + QUOTE + to_string(1)                           + QUOTE + COMMA + //color's alpha will take care of, left here untill server code updated
                                QUOTE + "thickness" + QUOTE + COLON + QUOTE + removeTrailingZeros(lv.getThickness()) + QUOTE + COMMA +
                                QUOTE + "weight"    + QUOTE + COLON + QUOTE + removeTrailingZeros(lv.getWeight())    + QUOTE + COMMA +
                                //write out the source and targets of the link
                                QUOTE + "source" + QUOTE + COLON + to_string(map.at(e))       + COMMA +
                                QUOTE + "target" + QUOTE + COLON + to_string(map.at(p.first)) +
                            CLOSE_CURLY + COMMA;
                    }
                }
            }
			if (links_JSON.size()){links_JSON = links_JSON.erase(links_JSON.size()-1);}//Remove trailing comma

            return pair<string,string>(nodes_JSON, links_JSON);
		}
};//end of Element class
template <typename E> const Color Element<E>::DEFAULT_COLOR("green");
template <typename E> const string Element<E>::DEFAULT_SHAPE = "circle";
template <typename E> constexpr double Element<E>::DEFAULT_SIZE;
}//end of bridges namespace
#endif
