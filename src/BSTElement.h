#ifndef BST_ELEMENT_H
#define BST_ELEMENT_H

#include "TreeElement.h" //string, using std

namespace bridges{
/**
 * @brief This class can be used to create binary search tree elements, derived from TreeElement
 *
 * This class extends the TreeElement class by adding a key property to allow for easier use in a binary search tree implementation.
 *
 * Generic Parameters:
 *      K that is the search key type,
 *      E the application data type
 *
 * @author Kalpathi Subramanian
 * @date 6/18/15
 */
template <typename K, typename E>
class BSTElement : public TreeElement<E>
{
	private:
	    /** The search key value */
		K key = K();
	public:
        /**
		 * Constructs a BSTElement with the provided value, label, key, left and right BSTElements.
		 * The defaults will be used if not provided.
		 *
		 * @param k The key for ordering
		 * @param val The data to hold
		 * @param lab The label to show
		 * @param l The left BSTElement
		 * @param r The right BSTElement
	 	 */
        BSTElement(const K& k,BSTElement* l,BSTElement* r,const E& val = E(),const string& lab = string()) : TreeElement<E>(l,r,val,lab), key(k) {}
		/**
		 * Constructs a BSTElement with the provided value, label, key, setting the left and right BSTElements to NULL.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
		 * @param k The key for ordering
	 	 */
		BSTElement(const K& k,const E& val = E(),const string& lab = string()) : BSTElement(k,nullptr,nullptr,val,lab){}
		/** @return The key of this BSTElement */
		K getKey() const {return key;}
		/** Set key to "k" @param k The key of this BSTElement */
		void setKey(const K& k){key = k;}
		/** @return The left BSTElement */
		virtual BSTElement* getLeft() override {return static_cast<BSTElement*>(TreeElement<E>::getLeft());}
		/** Constant version */
		virtual const BSTElement* getLeft() const override {return static_cast<const BSTElement*>(TreeElement<E>::getLeft());}
		/** Sets left to "l" @param l The left BSTElement */
		void setLeft(BSTElement* l){TreeElement<E>::setLeft(l);}
        /** @return The right BSTElement */
		virtual BSTElement* getRight() override {return static_cast<BSTElement*>(TreeElement<E>::getRight());}
		/** Constant version */
		virtual const BSTElement* getRight() const override {return static_cast<const BSTElement*>(TreeElement<E>::getRight());}
		/** Sets right to "r" @param r The right BSTElement */
		void setRight(BSTElement* r){TreeElement<E>::setRight(r);}
}; //end of BSTElement class
}//end of bridges namespace
#endif
