#ifndef BST_ELEMENT_H
#define BST_ELEMENT_H

#include <sstream> //stringstream

#include "TreeElement.h" //string, using std

namespace bridges{
/**
 * @brief This class defines a binary search tree element
 *
 * This class extends the TreeElement class by adding a key property
 * to allow for easier use in a binary search tree implementation.
 *
 * Has two generic parameters: K that is teh search key type -- must be
 *  orderable -- and E the application data type
 *
 * @author Kalpathi Subramanian,
 * @date 6/18/15
 */
template <typename K, typename E>
class BSTElement : public TreeElement<E>
{
	private:
		K key = K(); //this is the BSTElement key
	public:
        /**
		 * This constructor sets left to "l", right to "r", value to "e", key to "k" and label to "lab".
		 * If an argument is not provided its default constructor is used.
		 *
		 * @param l The left BSTElement
		 * @param r The right BSTElement
		 * @param e The value to hold
		 * @param k The key for ordering
		 * @param lab The label to show
		 */
        BSTElement(BSTElement* l,BSTElement* r,E e = E(),K k = K(),string lab = string()) : TreeElement<E>(l,r,e,lab), key(k) {}
		/**
		 * This constructor sets left and right to NULL, value to "e", key to "k" and label to "lab".
		 * If an argument is not provided its default constructor is used.
		 *
		 * @param e The value to hold
		 * @param k The key for ordering
		 * @param lab The label to show
		 */
		BSTElement(E e = E(),K k = K(),string lab = string()) : BSTElement(nullptr,nullptr,e,k,lab){}
		/** Copy Constructor */
		BSTElement(const BSTElement& bst) : BSTElement(bst.left,bst.right,bst.value,bst.key,bst.label){}
		/** Assignment Operator */
		BSTElement& operator=(const BSTElement& that)
		{
		    TreeElement<E>::operator=(that);
		    key = that.key;
		    return *this;
		}
		/**
		 * Return the key
		 *
		 * @return The key
		 */
		K getKey() const {return key;}
		/**
		 * Set key to "k"
		 *
		 * @param k Input key
		 */
		void setKey(const K& k){key = k;}
		/**
		 * Return the left BSTElement
		 *
		 * @return Left BSTElement
		 */
		BSTElement* getLeft() {return static_cast<BSTElement*>(TreeElement<E>::getLeft());}
        /**
		 * Return the right BSTElement
		 *
		 * @return Right BSTElement
		 */
		BSTElement* getRight() {return static_cast<BSTElement*>(TreeElement<E>::getRight());}
		/**
	 	 * Calls delete on "root" and each linked BSTElement*
		 *
		 * @param root Root of a binary search tree
		 * @warning Only call if these BSTElements were all dynamicaly allocated(aka: using new)
		 */
		static void cleanup(BSTElement* root){TreeElement<E>::cleanup(root);}
		/**
	 	 * Internal code for getting the properties of the BSTElement object.
	 	 * It produces (without the spaces or newlines):
	 	 * {
	 	 *  "element tag" : value here,
         *  "key" : "Some key"
	 	 * }
	 	 *
	 	 * @return The JSON string
	 	 */
		string getRepresentation() const override
		{
			string json = Element<E>::getRepresentation();
            stringstream conv; conv<<key; // convert the key to a string, for the JSON representation, use a stream that can handle any type conversion elegantly
            return json.insert(json.size()-1, COMMA + QUOTE + "key" + QUOTE + COLON + QUOTE + conv.str() + QUOTE);
		}
}; //end of BSTElement class
}//end of bridges namespace
#endif
