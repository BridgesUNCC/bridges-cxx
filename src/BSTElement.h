/**
 *
 * This class extends the TreeElement class by adding a key property 
 * to allow for easier use in a binary search tree implementation. 
 *
 * @author Kalpathi Subramanian, 6/18/15
 **/

#ifndef BST_ELEMENT_H

#define BST_ELEMENT_H

#include <sstream>
#include <string>

using namespace std;

#include "TreeElement.h"

namespace bridges{

template <typename K, typename E> class BSTElement : public TreeElement<E> {
	private:

		K key; //this is the BSTElement key

		BSTElement& operator=(const BSTElement&); // protect assignment
	
	public:

		/**
		 * Construct an empty BSTElement with no key assigned and left 
		 * and right pointers set to null.
		 **/
		BSTElement() : TreeElement<E>() {
		}

								// copy constructor
		BSTElement(const BSTElement& bel): TreeElement<E>(bel){
			setKey(bel.key);
		}
	
		/**
		 * 	Construct a BSTElement holding an object "e" with a left 
		 *	pointer assigned to "left" and a right pointer assigned to "right".
		 *
		 *	@param e the object that BSTElement is holding
		 *	@param left the BSTElement that should be assigned to the 
		 *		left pointer
		 * @param right the BSTElemetn taht should be assigned to the 
		 *	right pointer
		 **/
		BSTElement(E e, BSTElement<K, E> *left, BSTElement<K, E> *right) 
				: TreeElement<E>(e, left, right) {
		}
		
		/**	Construct a BSTElement with a key "key", holding an object "e" 
		 *	with a left pointer assigned to "left" and a right pointer 
		 *	assigned to "right".
		 * 	@param key the key to be used in a binary search tree implementation
		 * 	@param e the object this BSTElement is holding
		 * 	@param left the BSTElement that should be assigned to the 
		 *		left pointer
		 * 	@param right the BSTElement that should be assigned to the 
		 *	right pointer
		 **/
		BSTElement(K key, E e, BSTElement<K,E> *left, BSTElement<K, E> *right) 
				: TreeElement<E>(e, left, right) {
			setKey(key);
		}
	
		/**
		 *
		 *	Construct a BSTElement holding the object "e", with no key 
		 *	assigned and left and right pointers set to null.
		 * @param e the object this BSTElement is holding
		 *
		 **/
		BSTElement(E e) : TreeElement<E>(e) {
		}
	
		/**
		 *	Construct a BSTElement holding the object "e", with key "key" 
		 *	assigned and left and right pointers set to null.
		 * 	@param key the key to be used in a binary search tree 
		 *		implementation
		 * 	@param e the object this BSTElement is holding
		 */
		BSTElement(K key, E e) : TreeElement<E>(e) {
			setKey(key);
		}
	
		/**
		 *	Construct a BSTElement holding the object "e", with label 
		 *	set to "label", with "key" assigned to key, and left and right 
		 *	pointers set to null.
		 * @param label the label of BSTElement that shows up on the Bridges 
		 *	visualization
		 * @param key the key to be used in a binary search tree implementation
		 * @param e the object this BSTElement is holding
		 **/
		BSTElement(string label, K key, E e) : TreeElement<E>(label, e) {
			setKey(key);
		}
		
		/**	Construct an empty BSTElement, with no key assigned, and 
		 *	left and right pointers set to null.
		 * 	@param left the BSTElement that should be assigned to the 
		 *		left pointer
		 * 	@param right the BSTElement that should be assigned to the 
		 *		right pointer
		 **/
		BSTElement(BSTElement<K, E> *left, BSTElement<K, E> *right) 
					: TreeElement<E>(left, right) {
		}
	
		/**Return the key of the BSTElement
		 * @return the key of this BSTElement
		 */
		K getKey() {
			return key;
		}
	
		/**
		 *	Set the key of the BSTElement to key
		 * 	@param key the key to set
		 **/
		void setKey(K key) {
			this->key = (K) key;
							// convert the key to a string, for the
							// JSON representation, use a string stream
							// that can handly any type conversion elegantly
			stringstream conv;
			conv << key;
							// add the element representation
			this->getVisualizer()->setKey(conv.str());
		}
	
		/** 
		 *	
		 * 	get Left child
		 *	
		 *  @return left child pointer (from parent)
		 **/
		BSTElement<K,E> *getLeft() {
			return (BSTElement<K,E>*)TreeElement<E>::getLeft();
		}
	
		/* 
		 * 	get right child
		 *	
		 *  @return right child pointer (from parent)
		 *
		 */
		BSTElement<K,E> *getRight() {
			return (BSTElement<K,E>*)TreeElement<E>::getRight();
		}
	
		/** 
		 * @Override, must include key 
		 * get JSON of node representation 
		 *
		 * @return JSON of the node representation
		 **/
		string getRepresentation(){
			string json = "{";
			for (auto& entry: this->getVisualizer()->getProperties()) 
				json += "\"" + entry.first + "\":\"" + entry.second + "\", ";

			json += "\"name\":\"" + this->getLabel() + "\"" + "}";
			json += "\"key\":\"" + tostring(key) + "\"" + "}";

			return json;
		}
};

}
#endif
