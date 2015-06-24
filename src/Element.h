
#ifndef ELEMENT_H

#define ELEMENT_H

#include "ElementVisualizer.h"
#include "LinkVisualizer.h"

#include <iostream>
#include <new>
#include <string>
#include <unordered_map>

using namespace std;

///
///		This is the Superclass Element with SLelement, DLelement,
///		ArrayListElement, TreeElement, BSTElement subclasses.
///		Generic parameter E  is provided and all application specific data 
///     can be stored here).
///		An object of E data type can be integer, string, Tweet, Actor, Movie, 
///		EarthquakeTweet, etc.
///     The label field(string type)  is used to label the visualization of 
///		the element node.
///		Element has two visualizer objects. ElementVisualizer holds properties
///     of the element itself, and LinkVisualizer, which holds properties
///     of the link between this element and the element it is linked to
///     -- useful in linked structures and graphs that contain edges.
///		Identifier field automatically generated
///
///		@author  Kalpathi Subramanian, 6/11/15
///

template <typename E> class Element{
	private:

		static int ids;
		int MAX_ELEMENTS_SIZE;
		string label;
    	string identifier;
		ElementVisualizer *el_visualizer;
		unordered_map<string, LinkVisualizer*>  *link_visualizer;
    	E value;
	
	public:
	
		///
		/// Element constructor
		///	creates an ElementVisualizer object
		///	sets a unique identifier for the current Element
		///	normally used from subclasses
	 	///
		Element() {
			identifier = to_string(ids);
			MAX_ELEMENTS_SIZE = 5000;
			label = "";
			ids++;
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
		}; 

		Element& operator=(const Element& el) {/// define  assignment
			Element();
			value = el.value;
			label = el.label;
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
	 	* @param label the string that is visible on the Bridges Visualization
	 	* @param val will be used to construct Element's data component
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
		 * @param visualizer the visualizer to set
		 */
		void setVisualizer(ElementVisualizer el_vis) {
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
	 	* @parm Element el -- the element terminating the link 
	 	* @return the link visualizer
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

					return NULL;
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
	 	* @param label the label to set
	 	*/
		void setLabel(string label) {
			this->label = label;
		}
	
		/**
	 	* this method returns the value E for the current Element
	 	* @return the value
	 	*/
		E getValue() {
			return value;
		}

		/**
	 	* This method sets the value field to the E argument value
	 	* @param value the value to set
	 	*/
		void setValue(E value) {
			this->value = value;
		}
};
							// declare the static Element::ids variable
template <typename E> int Element<E>::ids = 0;
#endif
