#ifndef TREE_ELEMENT_H
#define TREE_ELEMENT_H

#include "Element.h" //string, list, using std

namespace bridges{
/**
 * @brief  This class can be used to create binary tree element objects,
 *   derived from Element
 *
 * The BSTElement<E> is derived from Element<E>  to represent binary tree
 * elements, with accessors to left and right subtrees
 *
 * Param <E> : Can be of any legal C++ type: integer, string, float,
 *  	double, or any user defined object(class, struct, array), and
 *  	represents application dependent data.
 *
 * @author Kalpathi Subramanian
 * @date 6/12/15
 */
template <typename E>
class TreeElement : public Element<E>
{
	private:
		TreeElement* left = nullptr; 	//the left child link
		TreeElement* right = nullptr; 	//the right child link
	public:
		/**
		 * This constructor sets left to "l", right to "r", value to "e" and label to "lab"
		 * If an argument is not provided its default constructor will be used.
		 *
		 * @param l The left TreeElement
		 * @param r The right TreeElement
		 * @param e The data to hold
		 * @param lab The label to show
		 */
		TreeElement(TreeElement* l,TreeElement* r,E e = E(),string lab = string()) : Element<E>(e, lab), left(l), right(r) {}
		/**
		 * This constructor sets left and right to NULL, value to "e" and label to "lab"
		 * If an argument is not provided its default constructor will be used.
		 *
		 * @param e The data to hold
		 * @param lab The label to show
		 */
		TreeElement(E e = E(),string lab = string()) : TreeElement(nullptr,nullptr,e,lab) {}
		/** Copy Constructor */
		TreeElement(const TreeElement& te) : TreeElement(te.left,te.right,te.value,te.label) {}
		/** Assignment Operator */
		TreeElement& operator=(const TreeElement& that)
		{
		    Element<E>::operator=(that);
		    left = that.left;
		    right = that.right;
		    return *this;
		}
		/**
		 * Returns the left TreeElement
		 *
		 * @return The left TreeElement
		 */
		TreeElement* getLeft() {return left;}
		/**
		 * Sets left to "l"
		 *
		 * @param l The left TreeElement
		 */
		void setLeft(TreeElement* l){left = l;}
		/**
		 * Returns the right TreeElement
		 *
		 * @return The right TreeElement
		 */
		TreeElement* getRight() {return right;}
        /**
		 * Sets right to "r"
		 *
		 * @param r The right TreeElement
		 */
		void setRight(TreeElement* r){right = r;}
		/**
	 	 * Calls delete on "root" and each linked TreeElement*
		 *
		 * @param root Root of a binary tree
		 * @warning Only call if these TreeElements were all dynamicaly allocated(aka: using new)
		 */
		static void cleanup(TreeElement* root)
		{
			if(root)
            {
				cleanup(root->getLeft()); // cleanup left subtree
				cleanup(root->getRight()); // cleanup right subtree
				delete root; // remove root
			}
		}
        /**
		 * Returns a pair of JSON strings of the nodes and links of the tree
		 * made by using preorder traversal
		 *
		 * @return A pair of node and link JSON
		 */
		pair<string,string> getDataStructureRepresentation()
		{
			list<const Element<E>*> nodes;
			preOrderBT(nodes);
			return Element<E>::generateJSON_Of_Nodes_And_Links(nodes); // generate the JSON string
		}
		/**
		 * Use a preorder traversal to collect the nodes and links in the
		 * binary tree
		 *
		 * @param nodes Modified list of nodes
		 * @param links Modified list of links
		 */
		void preOrderBT(list<const Element<E>*>& nodes)
		{
            nodes.push_front(this);
            if(left)
            {
                this->getLinkVisualizer(left); //link to left
                left->preOrderBT(nodes);
            }
            if(right)
            {
                this->getLinkVisualizer(right); //link to right
                right->preOrderBT(nodes);
            }
		}
}; //end of TreeElement class
}//end of bridges namespace
#endif
