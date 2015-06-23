
#ifndef SLELEMENT_H

#define SLELEMENT_H

#include "Element.h"
/**
 * This class can be used to instantiate Singly List Elements
 * with identifiers (automatically generated), 
 * labels (derived from the values of E or manually set)
 * next pointers
 * an object of E data type: integer, string, Tweet, Actor, Movie, 
 * EarthquakeTweet, etc.
 * element visualizer objects containing all the CSS atributes 
 * (color, shape, opacity, size) necessary for displaying them in a web browser
 * @author Kalpathi Subramanian, 6/11/15.
 *
 * @param <E>
 */
template <typename E> class SLelement : public Element<E> {

	private:

		SLelement<E> *next; //the link to the next element 

		SLelement<E>(const SLelement<E> &);  	// protect copy constructor
		SLelement<E>& operator=(const SLelement<E> &);  // protect assignment
	
	public:
		/**
	 	* This constructor creates an SLelement object with no parameters
		* Both label and the application data need to be set separately.
		**/

		SLelement() : Element<E>() {
			next = NULL;
		}
		/**
	 	* This constructor creates an SLelement object of value "e" and 
		* label "label" and sets the next pointer to null
	 	* @param label the label of SLelement that shows up on the Bridges 
		* visualization
	 	* @param e the generic object that this SLelement will hold
	 	*/

		SLelement (string label, E e) : Element<E>(label, e) {
			next = NULL;
		}
	
		/**
	 	* Creates a new element with value "e" and sets the next pointer
	 	* to the SLelement referenced by the "next" argument 
	 	* @param e the generic object that this SLelement will hold
	 	* @param next the SLelement that should be assigned to the next pointer
	 	*/
		SLelement (E e, SLelement<E> *next) : Element<E>(e) {
			this->next = next;
		}

		/**
	 	* Creates a new element and sets the next pointer
	 	* to the SLelement "next"
	 	* @param next the SLelement that should be assigned to the next pointer
	 	*/
		SLelement (SLelement<E> *next) : Element<E>() {
			this->next = next;
		}
	
		/**
	 	* Retrieves the next SLelement
	 	* @return SLelement<E> assigned to next
	 	*/
		SLelement<E> *getNext() {
			return next;
		}
	
		/**
	 	* Sets the pointer to the next SLelement
	 	* @param next SLelement<E> that should be assigned to the next pointer
	 	*/
		void setNext(SLelement<E> *next) {
			this->next = next;
		}
	
};
#endif
