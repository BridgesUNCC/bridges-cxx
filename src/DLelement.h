#ifndef DLelement_H


#define DLelement_H

#include "Element.h"

namespace bridges {
/**
 * @brief The basic doubly linked list element, derived from Element

 * This class can be used to create doubly linked element objects
 * with next and previous (prev) pointers
 *
 * <E> Can be any legal C++ type: integer, string, float, double, 
 *	or any user defined object(class, struct, array) , and represents 
 *	application dependent data.
 *
 * @author Kalpathi Subramanian 
 *
 * @date 6/11/15
 *
 **/


template<typename E>  class DLelement: public Element<E>{
	private:
		DLelement<E> *prev; 	// link to previous element
		DLelement<E> *next;		// link to next element


		DLelement<E>& operator=(const DLelement<E>&); // protect assignment
	public:
		/** 
	 	 *  Constructs an empty DLelement with next and prev 
	 	 *  pointers set to NULL.
	 	 **/
		DLelement() : Element<E>() {
			prev = next = NULL;
		}
										// copy constructor
		DLelement<E>(const DLelement<E>& dle): Element<E>(dle){
			prev = next = NULL;
		}
	
		/** Constructs a DLelement labeled "label", holding an 
	 	 * object "e", with next and prev pointers set to null. 
	 	 * @param label the label for this DLelement that shows up on the 
	 	 * Bridges visualization
	 	 * @param e the genereic object that this DLelement is holding
	 	 * 
	 	 **/
		DLelement (string label, E e) : Element<E>(label, e) {
			prev = next = NULL;
		}

		/** Constructs an empty DLelement with the next pointer 
		* set to the DLelement "next" and the prev pointer set to 
		* DLelement "prev". 
 		*
	 	* @param n  : the DLelement that should be assigned to the next pointer
	 	* @param p  : the DLelement that should be assigned to the prev pointer
 		*
	 	* */
		DLelement(DLelement<E> *n, DLelement<E> *p) : Element<E>()  {
			this->next = n;
			this->prev = p;
		}

		/** Constructs a DLelement holding an object "e", with the 
		* next pointer set to the DLelement "next" and the prev pointer 
		* set to DLelement "prev". 
	 	* @param e : the genereic object that this DLelement is holding
	 	* @param nxt : the DLelement that should be assigned to the next pointer
	 	* @param prv : the DLelement that should be assigned to the prev pointer
	 	*/

		DLelement(E e, DLelement<E> *nxt, DLelement<E> *prv): Element<E>(e) {
			this->prev = prv;
			this->next = nxt;
		}
	
		/**
	 	* This method returns the pointer to the next DLelement
	 	* @return the DLelement assigned to the next pointer
	 	*/

		DLelement<E> *getNext() {
			return next;
		}
	

		/**
	 	* This method sets the pointer to the next DLelement
	 	* @param nxt  : the DLelement that should be assigned to the next pointer
	 	*/
		void setNext(DLelement<E> *nxt) {
			this->next = nxt;
		}
	

		/**
	 	* This method returns the pointer to the previous DLelement
	 	* @return the DLelement assigned to the prev pointer
	 	*/
		DLelement<E> *getPrev() {
			return prev;
		}

		/**
	 	* This method sets the pointer to the previous DLelement
	 	* @param prv : the DLelement that should be assigned to the prev pointer
	 	*/
		void setPrev(DLelement<E> *prv) {
			this->prev = prv;
		}

		/**
		 *
	 	 * Cleans up the doubly linked list starting at head
		 *
		 * @param head - head of the doubly linked list
		 *
		 **/
		static void cleanup(DLelement<E> *head) {
			DLelement<E> *next = NULL;
			for (DLelement<E> *l = head; l != NULL; ){	
				next = l->getNext();
				delete l;
				l = next;
			}
		}
};

}

#endif
