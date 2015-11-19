
#ifndef TREE_ELEMENT_H

#define TREE_ELEMENT_H

using namespace std;

#include "Element.h"

namespace bridges{

/**
 *
 * @brief  This class can be used to create binary tree element objects,
 *   derived from Element

 * The BSTElement<E> is derived from Element<E>  to represent binary tree 
 * elements, with accessors to left and right subtrees
 *
 * Param <E> : Can be of any legal C++ type: integer, string, float,
 *  	double, or any user defined object(class, struct, array), and
 *  	represents application dependent data.
 *
 * @author Kalpathi Subramanian 
 * @date 6/12/15
 *
 */

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
		 *
		 *	@param l : the TreeElement to be assigned to the left pointer of 
		 *		this TreeElement
		 * 	@param r : the TreeElement to be assigned to the right 
		 *		pointer of this TreeElement
		 *
		 **/
		TreeElement(TreeElement<E> *l, TreeElement<E> *r):Element<E>(){
			this->left = l;
			this->right = r;
		}
		
		/** 
		 *	Constructs a TreeElement holding the object "e", left pointer 
		 *	pointing to "left" and right pointer pointing to "right".
		 *
		 * @param e : the generic object that TreeElement will hold 
		 * @param l : the TreeElement to be assigned to the left pointer of 
		 *		this TreeElement
		 * @param r :  the TreeElement to be assigned to the right pointer of 
		 *		this TreeElement
		 *
		 **/
		TreeElement(E e, TreeElement<E> *l, TreeElement<E> *r)
								: Element<E> (e) {
			this->left = l;
			this->right = r;
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
		 *
		 * @param l : the TreeElement that should be assigned to the left child
		 *
		 **/
		void setLeft(TreeElement<E> *l) {
			this->left = l;
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
		 *
		 * @param r : the TreeElement that should be assigned to the 
				right child
		 *
		 */
		void setRight(TreeElement<E> *r) {
			this->right = r;
		}

		/**
		 *
	 	 * Cleans up the tree, starting at the root
		 *
		 * @param root - root of the binary tree
		 *
		 **/
		static void cleanup(TreeElement<E> *root) {
			if (root) {
								// cleanup left subtree
				cleanup(root->getLeft());
								// cleanup right subtree
				cleanup(root->getRight());
								// remove root
				delete root;
			}
		}
};

}
#endif
