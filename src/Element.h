#ifndef ELEMENT_H
#define ELEMENT_H

#include <unordered_set> //unordered set

#include "DataStructure.h"
#include "ElementVisualizer.h"
#include "LinkVisualizer.h" //Color, cerr, string, unordered_map, using std

namespace bridges{

template <typename K, typename T> class GraphAdjList; template <typename K, typename T> class GraphAdjMatrix; //Forward Declaration for Befriendment
/**
 * @brief This is the fundamental building block used in building all data structures in BRIDGES
 *
 * This is the Superclass Element with SLelement, DLelement, TreeElement, BSTElement subclasses.
 *
 * Generic Parameters: E the application data type
 *
 * The label field(string type) is used to label the visualization of the element.
 *
 * Element holds a LinkVisualizer for each of its links and
 * an ElementVisualizer for itself
 *
 * @author Kalpathi Subramanian
 * @date 6/11/15
 */
template <typename E> class Element : public DataStructure {

				//Used for access to generateJSON() and for links manipulation
	template <typename K, typename T> friend class GraphAdjList;
	template <typename K, typename T> friend class GraphAdjMatrix;

	private:
		static const unordered_map<const Shape,const string, hash<int>> ShapeNames;

        /** 
		 *	This element's label 
		 */
		string label;

		/** 
		 * 	This element's value 
		 */
		E value = E();

		/** 
		 * 	This element's visualizer 
		 */
		ElementVisualizer *elvis;

    protected:

        /** 
		 *	This element's collection of links 
		 */
    	unordered_map<Element*, LinkVisualizer> links;

	public:

        /**
		 * Constructs an element with the provided value and label.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
		 */
		Element(const E& val = E(),const string& lab = string()) : label(lab), value(val) 
		{
			elvis = new ElementVisualizer;
		}

		/** 
		 *  This is really not used but getting compile errors otherwise. Need to fix.
		 *  @return The string representation of this data structure type 
		 */
		virtual const string getDStype() const override {
			return "Element";
		}


		/** 
		 *	@return The ElementVisualizer of this element 
		 */
		ElementVisualizer *getVisualizer(){
			return elvis;
		}

		/** 
		 *	Constant version 
		 *
		 *	@return The ElementVisualizer of this element 
		 */
		const ElementVisualizer *getVisualizer() const {
			return elvis;
		}

        /**
	 	 * Returns the LinkVisualizer to element "el" or NULL if no link exists
		 *
	 	 * @param el The terminating element of the link
		 *
	 	 * @return The LinkVisualizer
	 	 */
		LinkVisualizer* getLinkVisualizer(const Element* el) {
		    if(links.find(const_cast<Element*>(el)) != links.end()) {
                return &(links.at(const_cast<Element*>(el)));
            }
            cerr<<"Not linked to given Element... returned NULL"<<endl;
            return nullptr;
        }

        /** 
		 *	Constant version 
		 *
	 	 * @param el The terminating element of the link
		 *
	 	 * @return The LinkVisualizer
		 */
        const LinkVisualizer* getLinkVisualizer(const Element* el) const {
			return const_cast<Element*>(this)->getLinkVisualizer(el);
		}

        /** 
		 *	@return The label of the element 
		 **/
		string getLabel() const {
			return label;
		}

		/** 
		 *	Sets label to "lab" 
		 *
		 *	@param lab The label of the element 
		 *
		 **/
		void setLabel(const string& lab){
			label = lab;
		}

		/** 
		 *	@return The value of the element 
		 **/
		E getValue() const {
			return value;
		}

		/** 
		 *	Sets value to "val"  
		 *
		 *	@param val The value of the element 
		 */
		void setValue(const E& val){
			value = val;
		}

    private:

		/**
         * Gets the JSON representation of this element
         *
         * @param arr_size The size of the array determined by this
		 *
         * @return A pair holding the nodes and links JSON strings respectively
		 *
         */
		virtual const pair<string,string> getDataStructureRepresentation(const 
						unsigned int& arr_size) const override {
		    unordered_set<const Element*> nodes;
		    for (unsigned int i=0; i < arr_size; i++) {
				nodes.emplace(this+i);
			}
			return generateJSON(nodes);
		}

    protected:

		/** 
		 *	@return The JSON string of this element's properties 
		 */
		virtual const string getRepresentation() const {
										//write out visualizer properties
			return 	OPEN_CURLY +
				QUOTE + "color"   + QUOTE + COLON + 
					getCSSrep(elvis->getColor())  + COMMA +
				QUOTE + "shape"   + QUOTE + COLON + 
					QUOTE + ShapeNames.at(elvis->getShape()) + QUOTE + COMMA +
				QUOTE + "size" + QUOTE + COLON + 
					removeTrailingZeros(elvis->getSize()) + COMMA +
                QUOTE + "name" + QUOTE + COLON + QUOTE + label + QUOTE +
            CLOSE_CURLY;
		}

		/**
		 * Gets the JSON representation of this link visualizer using the supplied 
		 *	source and destination strings
		 *
		 * @param lv The LinkVisualizer
		 * @param src The source vertex
		 * @param dest The destination vertex
		 * @return The JSON of this link visualizer
		 */
        static const string getJSONrepresentation(const LinkVisualizer& lv,const 
								string& src,const string& dest) {
            return
            OPEN_CURLY +
								//write out LinkVisualizer properties
                QUOTE + "color"     + QUOTE + COLON + QUOTE + 
						getCSSrep(lv.getColor())    + QUOTE + COMMA +
                QUOTE + "thickness" + QUOTE + COLON + 
					removeTrailingZeros(lv.getThickness()) + COMMA +
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
        static const string getCSSrep(const Color& col) {
						//leaves off other channels if transparent
            if(col.isTransparent()){	
				return "[0, 0, 0, 0]";
			} 

            const string strCSS = 
					to_string(col.getRed())+","+
					to_string(col.getGreen()) + ","+
					to_string(col.getBlue()) + "," + 
					to_string(col.getAlpha()); 

			return OPEN_BOX + strCSS + CLOSE_BOX;

//					removeTrailingZeros(static_cast<double>(col.getAlpha())/255.0)+")";
//				return col.isOpaque()
//					?  "rgb("+strCSS+")"
//					: "rgba("+strCSS+","+ 
//					removeTrailingZeros(static_cast<double>(col.getAlpha())/255.0)+")";
        }
		/**
		 * Generates the JSON of the given the nodes and associated links
		 *
		 * @param nodes List of nodes
		 * @throw string If maximum elements exceeded
		 * @return A pair holding the nodes and links JSON strings respectively
		 */
		static const pair<string,string> generateJSON(const 
						unordered_set<const Element*>& nodes) {
								// cant exceed max number of elements
		    if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
				throw "Max allowed elements(for visualization) exceeded.. "+
					to_string(nodes.size())+" Must be less than "+
					to_string(MAX_ELEMENTS_ALLOWED);} 
			// map the nodes to a sequence of ids, 0...N-1 then get the JSON string for nodes
							//placeholder nullptr prevents insertion of other nullptrs
			unordered_map<const Element*,int> map{{nullptr,-1}}; 

			string nodes_JSON, links_JSON;

            int i=0; // get the JSON string for nodes
			for(const auto* e: nodes) {
				if (map.emplace(e,i).second && ++i) {
							// short circut only incriments i and gets rep upon 
							// successful emplacement
					nodes_JSON += e->getRepresentation() + COMMA;
				}
			}
								//Remove trailing comma and nullptr entry
			map.erase(nullptr); 
			if (nodes_JSON.size()){
				nodes_JSON = nodes_JSON.erase(nodes_JSON.size()-1);
			} 

			for (const auto& ele_int: map) { //each pair<Element*,int> in map
							//each pair<Element*,LinkVisualizer> in Element*->links
               	for(const auto& ele_lv: ele_int.first->links) { 
                   	auto it = map.find(ele_lv.first); //mapping of destination node
                   	if (it!=map.end()){
										//only add link if dest node exists
						links_JSON += getJSONrepresentation(
							ele_lv.second,to_string(ele_int.second),
								to_string(it->second)) + COMMA;
					} 
               	}
            }
			if (links_JSON.size()) {
									//Remove trailing comma
				links_JSON = links_JSON.erase(links_JSON.size()-1);
			}

            return pair<string,string>(nodes_JSON, links_JSON);
		}
};//end of Element class
template <typename E> const unordered_map<const Shape,const string, hash<int>>
    Element<E>::ShapeNames {
        {CIRCLE,"circle"},
        {SQUARE,"square"},
        {DIAMOND,"diamond"},
        {CROSS,"cross"},
        {TRI_DOWN,"triangle-down"},
        {TRI_UP,"triangle-up"}
    };

}//end of bridges namespace

#endif
