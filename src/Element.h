#ifndef ELEMENT_H
#define ELEMENT_H

#include <unordered_set> //unordered set

#include "DataStructure.h"
#include "LinkVisualizer.h" //Color, cerr, string, unordered_map, using std

namespace bridges{

template <typename K, typename T> class GraphAdjList; template <typename K, typename T> class GraphAdjMatrix; //Forward Declaration for Befriendment

/** Enumeration of valid shapes for visualization */
enum Shape{CIRCLE,SQUARE,DIAMOND,CROSS,TRI_DOWN,TRI_UP};

/**
 * @brief This is the fundamental building block used in building all data structures in BRIDGES
 *
 * This is the Superclass Element with SLelement, DLelement, TreeElement, BSTElement subclasses.
 *
 * Generic Parameters: E the application data type
 *
 * The label field(string type) is used to label the visualization of the element.
 *
 * Element holds a LinkVisualizer for each of its links.
 * Element also hold visualization properties for itself, including the color, shape, and size.
 * Defaults of green, circle, and 10.0 respectively.
 *
 * Size values must range from [10.0,50.0].
 * BRIDGES supports the following shapes: "circle", "square", "diamond", "cross", "triangle-down", "triangle-up"
 *
 * @author Kalpathi Subramanian
 * @date 6/11/15
 */
template <typename E> class Element : public DataStructure
{
    //Used for access to generateJSON() and for links manipulation
    template <typename K, typename T> friend class GraphAdjList;
    template <typename K, typename T> friend class GraphAdjMatrix;

    public:
        /** The default color of an element */
	    static const Color DEFAULT_COLOR; //green
	    /** The default shape of an element */
        static constexpr Shape DEFAULT_SHAPE = CIRCLE; //circle
        /** The default size of an element */
		static constexpr double DEFAULT_SIZE = 10;
	private:
	    static const unordered_map<const Shape,const string, hash<int>> ShapeNames;
        /** This element's color */
        Color color=DEFAULT_COLOR;
        /** This element's shape */
        Shape shape=DEFAULT_SHAPE;
        /** This element's size */
		double size=DEFAULT_SIZE;
        /** This element's label */
		string label;
		/** This element's value */
		E value = E();
    protected:
        /** This element's collection of links */
    	unordered_map<Element*, LinkVisualizer> links;
	public:
        /**
		 * Constructs an element with the provided value and label.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
		 */
		Element(const E& val = E(),const string& lab = string()) : label(lab), value(val) {}
		/** @return The string representation of this data structure type */
		virtual const string getDStype() const override {return "llist";}
		/**
		 * Sets size to "sz"
		 * Valid Range:[10,50]
		 *
		 * @param size The size in pixel weight of the element
		 * @throw string If size is invalid
		 */
		void setSize(const double& sz){(sz<10||50<sz)?throw "Invalid Size Value.. "+to_string(sz)+" Must be in the [10.0,50.0] range" : size = sz;}
		/** @return The size in pixel weight of the element */
		double getSize() const {return size;}
		/** Set the color to "col" @param color The color of the element */
		void setColor(const Color& col){color = col;}
		/** @return The color of the element */
		Color getColor() const {return color;}
		/**
		 * Sets the shape to "shp"
		 * See the top of the page for the supported shapes.
		 *
		 * @param shape The shape of the element
		 * @throw string If the shape is invalid
		 */
		void setShape(const Shape& shp){shape = shp;}
		/** @return The shape of the element */
		Shape getShape() const {return shape;}
        /**
	 	 * Returns the LinkVisualizer to element "el" or NULL if no link exists
		 *
	 	 * @param el The terminating element
	 	 * @return The LinkVisualizer
	 	 */
		LinkVisualizer* getLinkVisualizer(const Element* el)
		{
		    if(links.find(const_cast<Element*>(el)) != links.end())
            {
                return &(links.at(const_cast<Element*>(el)));
            }
            cerr<<"Not linked to given Element... returned NULL"<<endl;
            return nullptr;
        }
        /** Constant version */
        const LinkVisualizer* getLinkVisualizer(const Element* el) const {return const_cast<Element*>(this)->getLinkVisualizer(el);}
        /** @return The label of the element */
		string getLabel() const {return label;}
		/** Sets label to "lab" @param lab The label of the element */
		void setLabel(const string& lab){label = lab;}
		/** @return The value of the element */
		E getValue() const {return value;}
		/** Sets value to "val"  @param val The value of the element */
		void setValue(const E& val){value = val;}
    private:
		/**
         * Gets the JSON representation of this element
         *
         * @param arr_size The size of the array determined by this
         * @return A pair holding the nodes and links JSON strings respectively
         */
		virtual const pair<string,string> getDataStructureRepresentation(const unsigned int& arr_size) const override
		{
		    unordered_set<const Element*> nodes;
		    for(unsigned int i=0;i<arr_size;i++){nodes.emplace(this+i);}
			return generateJSON(nodes);
		}
    protected:
		/** @return The JSON string of this element's properties */
		virtual const string getRepresentation() const
		{
			return
            OPEN_CURLY +
                //write out visualizer properties
                QUOTE + "color"   + QUOTE + COLON + QUOTE + getCSSrep(color)          + QUOTE + COMMA +
                QUOTE + "shape"   + QUOTE + COLON + QUOTE + ShapeNames.at(shape)      + QUOTE + COMMA +
                QUOTE + "size"    + QUOTE + COLON + QUOTE + removeTrailingZeros(size) + QUOTE + COMMA +
                //write out this node
                QUOTE + "name" + QUOTE + COLON + QUOTE + label + QUOTE +
            CLOSE_CURLY;
		}
		/**
		 * Gets the JSON representation of this link visualizer using the supplied source and destination strings
		 *
		 * @param lv The LinkVisualizer
		 * @param src The source vertex
		 * @param dest The destination vertex
		 * @return The JSON of this link visualizer
		 */
        static const string getJSONrepresentation(const LinkVisualizer& lv,const string& src,const string& dest)
        {
            return
            OPEN_CURLY +
                //write out LinkVisualizer properties
                QUOTE + "color"     + QUOTE + COLON + QUOTE + getCSSrep(lv.getColor())               + QUOTE + COMMA +
                QUOTE + "thickness" + QUOTE + COLON + QUOTE + removeTrailingZeros(lv.getThickness()) + QUOTE + COMMA +
                //write out the source and targets of the link
                QUOTE + "source" + QUOTE + COLON + src  + COMMA +
                QUOTE + "target" + QUOTE + COLON + dest +
            CLOSE_CURLY;
        }
        /**
         * Gets the JSON representation of this color
         *
         * @param col The Color
         * @return Equivilant Legal CSS color representation
         */
        static const string getCSSrep(const Color& col)
        {
            if(col.isTransparent()){return "rgba(0,0,0,0)";} //leaves off other channels if transparent
            const string strCSS = to_string(col.getRed())+","+to_string(col.getGreen())+","+to_string(col.getBlue()); //leaves off alpha if unnessesary
            return col.isOpaque()?
                "rgb("+strCSS+")":
                "rgba("+strCSS+","+removeTrailingZeros(static_cast<double>(col.getAlpha())/255.0)+")";
        }
		/**
		 * Generates the JSON of the given the nodes and associated links
		 *
		 * @param nodes List of nodes
		 * @throw string If maximum elements exceeded
		 * @return A pair holding the nodes and links JSON strings respectively
		 */
		static const pair<string,string> generateJSON(const unordered_set<const Element*>& nodes)
		{
		    if(MAX_ELEMENTS_ALLOWED<=nodes.size()){throw "Max allowed elements(for visualization) exceeded.. "+to_string(nodes.size())+" Must be less than "+to_string(MAX_ELEMENTS_ALLOWED);} // cant exceed max number of elements
			// map the nodes to a sequence of ids, 0...N-1 then get the JSON string for nodes
			unordered_map<const Element*,int> map{{nullptr,-1}}; //placeholder nullptr prevents insertion of other nullptrs
			string nodes_JSON, links_JSON;

            int i=0; // get the JSON string for nodes
			for(const auto* e: nodes){if(map.emplace(e,i).second && ++i){nodes_JSON += e->getRepresentation() + COMMA;}}//short circut only incriments i and gets rep upon sucessful emplacement
			map.erase(nullptr); if(nodes_JSON.size()){nodes_JSON = nodes_JSON.erase(nodes_JSON.size()-1);} //Remove trailing comma and nullptr entry

			for(const auto& ele_int: map) //each pair<Element*,int> in map
            {
                for(const auto& ele_lv: ele_int.first->links) //each pair<Element*,LinkVisualizer> in Element*->links
                {
                    auto it = map.find(ele_lv.first); //mapping of destination node
                    if(it!=map.end()){links_JSON += getJSONrepresentation(ele_lv.second,to_string(ele_int.second),to_string(it->second)) + COMMA;} //only add link if dest node exists
                }
            }
			if (links_JSON.size()){links_JSON = links_JSON.erase(links_JSON.size()-1);}//Remove trailing comma
            return pair<string,string>(nodes_JSON, links_JSON);
		}
};//end of Element class
template <typename E> const Color Element<E>::DEFAULT_COLOR("green");
template <typename E> const unordered_map<const Shape,const string, hash<int>>
    Element<E>::ShapeNames
    {
        {CIRCLE,"circle"},
        {SQUARE,"square"},
        {DIAMOND,"diamond"},
        {CROSS,"cross"},
        {TRI_DOWN,"triangle-down"},
        {TRI_UP,"triangle-up"}
    };
}//end of bridges namespace
#endif
