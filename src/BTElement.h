#ifndef BT_ELEMENT_H
#define BT_ELEMENT_H

#include "TreeElement.h" //string, using std

namespace bridges{
/**
 * @brief This class can be used to create binary tree elements, derived from TreeElement
 *
 * This class can be used to create binary tree elements, with left and right subtrees
 *
 * Generic Parameters: E the application data type
 *
 * @author Kalpathi Subramanian
 * @date 6/12/15
 */
template <typename E>
class BTElement : public TreeElement<E>
{
	public:
		/**
		 * Constructs a BTElement with the provided value, label, left and right BTElements.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
		 * @param l The left TreeElement
		 * @param r The right TreeElement
	 	 */
		BTElement(BTElement* l,BTElement* r,const E& e = E(),const string& lab = string()) : TreeElement<E>(e, lab) {setLeft(l); setRight(r);}
		/**
		 * Constructs a BTElement with the provided value and label, setting the left and right BTElement to NULL.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
	 	 */
		BTElement(const E& e = E(),const string& lab = string()) : BTElement(nullptr,nullptr,e,lab) {}
		/** @return The left BTElement */
		virtual BTElement* getLeft() {return static_cast<BTElement*>(this->getChild(-1));}
		/** Constant version */
		virtual const BTElement* getLeft() const {return static_cast<BTElement*>(this->getChild(-1));}
		/** Sets left to "l" @param l The left BTElement */
		void setLeft(BTElement* l){setChild(-1,l);}

		/** @return The right BTElement */
		virtual BTElement* getRight() {return static_cast<BTElement*>(this->getChild(1));}
		/** Constant version */
		virtual const BTElement* getRight() const {return static_cast<BTElement*>(this->getChild(1));}
        /** Sets right to "r" @param r The right BTElement */
		void setRight(BTElement* r){setChild(1,r);}
}; //end of BTElement class
}//end of bridges namespace
#endif
