#ifndef TREE_ELEMENT_H
#define TREE_ELEMENT_H

#include "Element.h" //string, using std

namespace bridges{
/**
 * @brief This class can be used to create binary tree elements, derived from Element
 *
 * This class can be used to create binary tree elements, with left and right subtrees
 *
 * Generic Parameters: E the application data type
 *
 * @author Kalpathi Subramanian
 * @date 6/12/15
 */
template <typename E>
class TreeElement : public Element<E>
{
	private:
	    /** The pointer to the left subtree */
		TreeElement* left = nullptr;
		/** The pointer to the right subtree */
		TreeElement* right = nullptr;
	public:
		/**
		 * Constructs a TreeElement with the provided value, label, left and right TreeElements.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
		 * @param l The left TreeElement
		 * @param r The right TreeElement
	 	 */
		TreeElement(TreeElement* l,TreeElement* r,const E& e = E(),const string& lab = string()) : Element<E>(e, lab) {setLeft(l); setRight(r);}
		/**
		 * Constructs a TreeElement with the provided value and label, setting the left and right TreeElements to NULL.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
	 	 */
		TreeElement(const E& e = E(),const string& lab = string()) : TreeElement(nullptr,nullptr,e,lab) {}
		/** @return The left TreeElement */
		virtual TreeElement* getLeft() {return left;}
		/** Constant version */
		virtual const TreeElement* getLeft() const {return left;}
		/** Sets left to "l" @param l The left TreeElement */
		void setLeft(TreeElement* l)
		{
		    if(left!=right){this->links.erase(left);} //if different, remove old link data
            if((left=l)){this->links[left];} //set left to l and if not null, creates default link data if none already present
        }
		/** @return The right TreeElement */
		virtual TreeElement* getRight() {return right;}
		/** Constant version */
		virtual const TreeElement* getRight() const {return right;}
        /** Sets right to "r" @param r The right TreeElement */
		void setRight(TreeElement* r)
		{
		    if(right!=left){this->links.erase(right);} //if different, remove old link data
            if((right=r)){this->links[right];} //set right to r and if not null, creates default link data if none already present
        }
		/**
	 	 * Calls delete on itself and each next linked TreeElement*
		 *
		 * @warning Only call if these TreeElements were all dynamicaly allocated(aka: using new)
		 * @warning If tree contains redundant links, delete will be called multiple times on it, leading to undefined behavior
		 */
		virtual void cleanup() override
		{
			if(left){left->cleanup();}// cleanup left subtree
            if(right){right->cleanup();} // cleanup right subtree
            Element<E>::cleanup();
		}
    private:
        /**
         * Gets the JSON representation of this TreeElement and its links
         *
         * @param arr_size The size of the array determined by this
         * @return A pair holding the nodes and links JSON strings respectively
         */
		virtual const pair<string,string> getDataStructureRepresentation(const unsigned int& arr_size) const override final
		{
			unordered_set<const Element<E>*> nodes;
			for(unsigned int i=0;i<arr_size;i++){this[i].preOrderBT(nodes);}
			return this->generateJSON(nodes); // generate the JSON string
		}
        /**
		 * Modifys "nodes" by adding its nodes via a preorder traversal
		 *
		 * @param nodes The set to be added to
		 */
		void preOrderBT(unordered_set<const Element<E>*>& nodes) const
		{
            if(nodes.emplace(this).second)//prevents potential infinite loop
            {
                if(left){left->preOrderBT(nodes);}
                if(right){right->preOrderBT(nodes);}
            }
		}
}; //end of TreeElement class
}//end of bridges namespace
#endif
