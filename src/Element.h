
#ifndef ELEMENT_H

#define ELEMENT_H

#include <iostream>
#include <new>
#include <string>
#include <unordered_map>

using namespace std;

#include "ElementVisualizer.h"
#include "LinkVisualizer.h"

namespace bridges {

/**
 *	@brief This is the fundamental building block used in building all
 *		data structures in BRIDGES

 *	This is the Superclass Element with SLelement, DLelement,
 *	TreeElement, BSTElement subclasses. Arrays are also built of this type.
 *	Template type  parameter E  is provided to store any application 
 *	specific data. E  can be of any legal C++ type: integer, string, float,
 *	double, or any user defined object(class, struct, array).
 *  The label field(string type) is used to label the visualization of 
 *	the element node. Element has two visualizer objects. ElementVisualizer 
 *	holds properties of the element itself, and LinkVisualizer, which holds 
 *	properties of the link between this element and the element it is linked 
 *	to -- useful in linked structures and graphs that contain edges.
 *	The identifier field automatically generated to keep track of the 
 *	generated objects and is transparent to the user.
 *
 *  E : Application specific data type - can be any legal C++ type.
 *
 *	@author  Kalpathi Subramanian, 
 *	@date 6/11/15
 *
 **/

template <typename E> class Element{
	private:

		static int ids;
		string label;
    	string identifier;
		ElementVisualizer *el_visualizer;
		unordered_map<string, LinkVisualizer*>  *link_visualizer;
    	E value;
	
	public:
	
		/**
		 *
		 * Element constructor creates an ElementVisualizer object
		 * a unique identifier for the current Element normally used 
		 * from subclasses
		 *
		 **/
		Element() {
			identifier = to_string(ids);
			label = "";
			ids++;
			value = E();
			try {
				el_visualizer = new ElementVisualizer;
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (ElementVisualizer) caught: " << ba.what()
								<< endl;
			}
			try {
				link_visualizer = new unordered_map<string, LinkVisualizer*>;
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (LinkVisualizer) caught: " << ba.what()
								<< endl;
			}
		}
		Element(const Element& el) : Element() { /// copy constructor
			value = el.value;
			label = el.label;
		} 

		Element& operator=(const Element& el) {	/// define  assignment
			value = el.value;
			label = el.label;

			return *this;
		}

		/**
	 	* the constructor of Element
	 	* @param val will be used to construct Element
	 	*/
		Element (E val) : Element() {
			value = val;
		}
	
		/**
	 	* the constructor of Element
		*
	 	* @param labl : the string that is visible on the Bridges Visualization
	 	* @param val : will be used to construct Element's data component
		*
	 	*/
		Element (string labl, E val) :Element() {
			value = val;
			label = labl;
		}

		~Element() { 						/// destructor
			delete el_visualizer;
			delete link_visualizer;
		}
	

		/**
		 * This method sets the visualizer object for the current 
		 * element object
		 *
		 * @param el_vis : the visualizer to set
		 */
		void setVisualizer(ElementVisualizer *el_vis) {
			if (el_vis)
				delete el_vis;

			el_visualizer = el_vis;
		}

		/**
	 	* this method returns the element's unique identifier
	 	* @return the string identifier
	 	*/
		string getIdentifier(){
			return identifier;
		}
	
		/**
	 	* Returns the Element's visualizer object
	 	* @return the visualizer
	 	*/
		ElementVisualizer *getVisualizer(){
			return el_visualizer;
		}

		/**
	 	* Returns the Element's link visualizer object 
     	* that is linked to element el
		*
	 	* @param el : the element terminating the link 
		*
	 	* @return the link visualizer
		*
	 	*/
		LinkVisualizer *getLinkVisualizer(Element<E> *el){
						// note: if the key-value pair does not exist
						// a new value is created (C++ only) and returned
			if (link_visualizer->find(el->getIdentifier())
							== link_visualizer->end()){  // non-existent key
														// create entry
				try {
					(*link_visualizer)[el->getIdentifier()] =  
										new LinkVisualizer;
				} 
				catch (bad_alloc& ba) {
					cerr << "bad_alloc (LinkVisualizer) in "
						<< "getLinkVisualizer()  caught: " << ba.what() << endl;

					exit(EXIT_FAILURE);
				}
			}
			return (*link_visualizer)[el->getIdentifier()];
		}
	
		/**
	 	* Internal code for getting the properties of the Element object.
	 	* It produces (without the spaces or newlines):
	 	* {
	 	*  "name": "Some label",
	 	*  "other CSS properties like color": any_JSON_value
	 	* }
	 	* @returns the encoded JSON string
	 	*/
		string getRepresentation(){
			string json = "{";
			for (auto& entry: el_visualizer->getProperties()) 
				json += "\"" + entry.first + "\":\"" + entry.second + "\", ";

			json += "\"name\":\"" + label + "\"" + "}";

			return json;
		}

		/**
	 	* This method returns the existing value of the label fields
	 	* @return the label of the Element that shows up on the Bridges 
		* Visualization
	 	*/
		string getLabel() {
			return label;
		}

		/**
	 	* This method sets the label
		*
	 	* @param labl : the label to set
		*
	 	*/
		void setLabel(string labl) {
			this->label = labl;
		}
	
		/**
	 	* this method returns the value E for the current Element
		*
	 	* @return the value
	 	*/
		E getValue() {
			return value;
		}

		/**
	 	* This method sets the value field to the E argument value
		*
	 	* @param val : the value to set
		*
	 	*/
		void setValue(E val) {
			this->value = val;
		}
};
							// declare the static Element::ids variable
template <typename E> int Element<E>::ids = 0;

}

#endif

