#ifndef TREE_ELEMENT_H
#define TREE_ELEMENT_H

#include "Element.h" //string, using std

namespace bridges{
/**
 * @brief This class can be used to create tree elements, derived from Element
 *
 * This class can be used to create tree elements, with subtrees
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
	    /** A list of pointers to this Elements subtrees */
	    vector<TreeElement*> children;
	public:
		/**
		 * Constructs a TreeElement with the provided value and label, setting the left and right TreeElements to NULL.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
	 	 */
		TreeElement(const E& e = E(),const string& lab = string()) : Element<E>(e,lab) {}
		/** @return The string representation of this data structure type */
		virtual const string getDStype() const {return "tree";}
		/** @return The children TreeElements */
		vector<TreeElement*>& getChildren() {return children;}
		/** Constant version */
		const vector<TreeElement*>& getChildren() const {return children;}

        /**
         * Gets the nth child of this TreeElement, returns null if non-existent
         *
         * @param n The index of the child
         * @return The child TreeElement*
         */
		TreeElement* getChild(const int& n) {return (n>=children.length || n<0)? nullptr:children.at(n);}
		/** Constant version */
		const TreeElement* getChild(const int& n) const {return (n>=children.length || n<0)? nullptr:children.at(n);}
		/** Adds "kid" to children and returns its position @param kid The child TreeElement @return index of child */
		size_type addChild(TreeElement* kid)
		{
            children.push_back(kid);
            if(kid){this->links[kid];}
            return children.length;
        }
        /** Sets child at index to "kid". Will do nothing given invalid index. @param index of child to replace @param kid The child TreeElement */
        void setChild(const size_type& index,TreeElement* kid)
        {
            /* For any element being replaced, if not a duplicate, remove its linkage. For new elements, if not null, create linkage */
            if(index < children.length && index >= 0)
            {
                bool duplicate = false;
                for(size_type i=0;i<children.length;i++)
                {
                    if(i != index && children[i] == children[index]){duplicate=true;break;}
                }
                if(!duplicate){this->links.erase(children[index]);}
                children[index] = kid;
                if(kid){this->links[kid];}
            }
        }
		/**
	 	 * Calls delete on itself and each next linked TreeElement*
		 *
		 * @warning Only call if these TreeElements were all dynamicaly allocated(aka: using new)
		 * @warning If tree contains redundant links, delete will be called multiple times on it, leading to undefined behavior
		 */
		virtual void cleanup() override
		{
		    TreeElement* child = nullptr;
		    for(int i=children.size(); i-->0;)
            {
                child = children.at(i);
                if(child){child->cleanup();}
            }
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
			for(unsigned int i=0;i<arr_size;i++){this[i].preOrder(nodes);}
			return this->generateJSON(nodes); // generate the JSON string
		}
        /**
		 * Modifys "nodes" by adding its nodes via a preorder traversal
		 *
		 * @param nodes The set to be added to
		 */
		void preOrder(unordered_set<const Element<E>*>& nodes) const
		{
            if(nodes.emplace(this).second)//prevents potential infinite loop
            {
                for(const auto& child: children)
                {
                    if(child){child->preOrder(nodes);}
                }
            }
		}
}; //end of TreeElement class
}//end of bridges namespace
#endif
