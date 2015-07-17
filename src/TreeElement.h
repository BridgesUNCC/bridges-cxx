
#ifndef TREE_ELEMENT_H

#define TREE_ELEMENT_H

#include <string>

using namespace std;

/**
 * @author Kalpathi Subramanian, 6/12/15
 * This class can be used to create tree element objects
 * with left and right pointers
 *
 */

#include "Element.h"

namespace bridges{

template <typename E>  class TreeElement : public Element<E> {

	private: 

		TreeElement<E> *left; 	//the left child link
		TreeElement<E> *right; 	//the right child link

        TreeElement<E>& operator=(const TreeElement<E>&);// protect assignment

	public:
		/** 
	 	*	Constructs an empty TreeElement with right and left 
 	 	*	pointers set to null. 
	 	**/
		TreeElement() : Element<E>() {
			left = right = NULL;
		}
							// copy constructor 
		TreeElement(const TreeElement<E>& te ): Element<E> (te) {
			left = te.left; right = te.right;
		}
		
		/** 
		  *	Constructs a TreeElement holding an object "e" with 
		  *	right and left pointers set to null. 
		  * @param e the generic object that TreeElement will hold 
		  **/
		TreeElement (E e) : Element<E>(e) {
			left = right = NULL;
		}
		
		/** 
		 *	Constructs a TreeElement with label set to "label", holding an 
		 *	object "e". 
		 * 	@param label the label of TreeElement that shows up on the Bridges 
		 * 	visualization
		 * 	@param e the generic object that TreeElement will hold 
		 **/
		TreeElement (string label, E e) : Element<E> (label, e) {
			left = right = NULL;
		}
		
		/** 
		 * 	Construct a TreeElement with 
		 *	@param left the TreeElement to be assigned to the left pointer of 
		 *	this TreeElement
		 * 	@param right the TreeElement to be assigned to the right pointer of 
		 *	this TreeElement
		 **/
		TreeElement(TreeElement<E> *left, TreeElement<E> *right):Element<E>(){
			this->left = left;
			this->right = right;
		}
		
		/** 
		 *	Constructs a TreeElement holding the object "e", left pointer 
		 *	pointing to "left" and right pointer pointing to "right".
		 * @param e the generic object that TreeElement will hold 
		 * @param left the TreeElement to be assigned to the left pointer of 
		 *	this TreeElement
		 * @param right the TreeElement to be assigned to the right pointer of 
		 *	this TreeElement
		 **/
		TreeElement(E e, TreeElement<E> *left, TreeElement<E> *right)
								: Element<E> (e) {
			this->right = right;
			this->left = left;
		}
		
		/**
		 * This method returns the left tree element pointer
		 * @return the left child of this TreeElement
		 **/
		TreeElement<E> *getLeft() {
			return left;
		}
		
	
		/**
		 * This method sets the left tree element pointer
		 * @param left the TreeElement that should be assigned to the left child
		 **/
		void setLeft(TreeElement<E> *left) {
			this->left = left;
		}
		
	
		/**
		 * This method returns the right tree element pointer
		 * @return the right child of this TreeElement
		 **/
		TreeElement<E> *getRight() {
			return right;
		}
		
	
		/**
		 * This method sets the right tree element pointer
		 * @param right the TreeElement that should be assigned to the right child
		 */
		void setRight(TreeElement<E> *right) {
			this->right = right;
		}
	
		/**
		 * Comparing 2 tree elements
		 * @param e1
		 * @return
		 */
/*
		public int compareTo(TreeElement<E> e1) {
			return super.compareTo(e1);
		}
*/
};

}
#endif
