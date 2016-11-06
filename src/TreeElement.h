#ifndef TREE_ELEMENT_H
#define TREE_ELEMENT_H

#include <vector>

#include "Element.h" //string, using std

namespace bridges{
/**
 * @brief This class can be used to create tree elements, derived from Element
 *
 * This class can be used to create tree elements, with subtrees
 *
 * Generic Parameters: E the application data type
 *
 * @author Kalpathi Subramanian, Dakota Carmer
 * @date 6/12/15
 */
template <typename E>
class TreeElement : public Element<E>, public DataStructure
{
    private:
        vector<TreeElement*> children;
    public:
        /**
         * Constructs a TreeElement with the provided value and label, setting the
         * left and right TreeElements to NULL.
         * The defaults will be used if not provided.
         *
         * @param val The data to hold
         * @param lab The label to show
         */
        TreeElement(const E& e = E(),const string& lab = string()): Element<E>(e,lab) {}
        /** @return The string representation of this data structure type */
        virtual const string getDStype() const override {return "Tree";}
        /** @return The children TreeElements */
        vector<TreeElement*>& getChildren() {return children;}
        /**
         * Constant version
         *
         * @return The children TreeElements
         */
        const vector<TreeElement*>& getChildren() const {return children;}
        /**
         * Gets the nth child of this TreeElement, returns null if non-existent
         *
         * @param n The index of the child
         * @return The child TreeElement
         */
        TreeElement* getChild(const int& n) {return (n >= children.size() || n < 0 ) ? nullptr : children.at(n);}
        /**
         * Constant version
         *
         * Gets the nth child of this TreeElement, returns null if non-existent
         *
         * @param n The index of the child
         * @return The child TreeElement
         */
        const TreeElement* getChild(const int& n) const {return (n >= children.size() || n < 0)? nullptr : children.at(n);}
        /**
         * Adds a child to children
         *
         * @param kid The child TreeElement
         * @return index of child
         */
        void addChild(TreeElement* child)
        {
            children.push_back(child);
            if(child) {this->links[child];}
        }
        /**
         * Sets child at index to "kid". Will do nothing given invalid index.
         *
         * @param index of child to replace
         * @param kid The child TreeElement
         */
        void setChild(const size_t& index,TreeElement* kid)
        {
            /**
             *  This simply replaces the element at position index and the old element
             *  is lost(actually can create memory leak if it came from dynamic memory
             *  Since we cannot distinguish from allocated or static memory from pointers,
             *  it is the user's responsibility to keep track of allocated memory
             *  its linkage. For new elements, if not null, create linkage
             */
            if ((index < children.size()) && index >= 0)
            {
                children[index] = kid;
                this->links.erase(children[index]); // remove any existing links
                this->links[kid];                   // initialize this element in the map
            }
        }
        /**
         * Calls delete on itself and each next linked TreeElement*
         *
         * @warning Only call if these TreeElements were all dynamicaly allocated(
         *  aka: using new)
         * @warning If tree contains redundant links, delete will be called multiple
         *  times on it, leading to undefined behavior
         */
        virtual void cleanup() override
        {
            TreeElement* child = nullptr;
            for(int i=children.size(); i-->0;)
            {
                child = children.at(i);
                if(child){child->cleanup();}
            }
            DataStructure::cleanup();
        }
    private:
        /**
         * Gets the JSON representation of this TreeElement and its links
         *
         * @return A pair holding the nodes and links JSON strings respectively
         */
        virtual const pair<string,string> getDataStructureRepresentation() const override final
        {
            /**
             * The JSON creation for a tree structure is different from other
             * data structures; we will use a preorder traversal to build a hierarch.
             * JSON; it is assumed that children are in order from left to right.
             * Also each child that is NULL is explicitly specified as NULL for
             * visualization convenience
             */
            return pair<string, string> (generateHierarchicalJSON(),""); ///TODO Check for exceeding max node
        }
        /**
         * Does a preorder traversal to build a hierarchical JSON of the tree
         * rooted at this node
         *
         * @return the JSON string
         */
        string generateHierarchicalJSON()
        {
            string json = this->getRepresentation(); //This nodes rep
            if(children.size()>0)
            {
                json = json.substr(0, json.size()-1);// remove end curly brace
                json+= COMMA + QUOTE + "children" + QUOTE + COLON + OPEN_BOX;
                for(const auto& ele : children) // each TreeElement* in children
                {
                    if(!ele){json+= OPEN_CURLY+QUOTE+"name"+QUOTE+COLON+"null"+CLOSE_CURLY;}
                    else
                    {
                        json+=ele->preOrder3();
                        json = json.substr(0, json.size()-1);// remove end curly brace

                        json+=COMMA+QUOTE+"linkProperties"+QUOTE+COLON+OPEN_CURLY;
                        if(LinkVisualizer* lv = getLinkVisualizer(ele))
                        {
                            json += QUOTE+"color"    +QUOTE+COLON+this->getCSSrep(lv->getColor())+COMMA+
                                    QUOTE+"thickness"+QUOTE+COLON+this->removeTrailingZeros(lv->getThickness())+COMMA+
                                    QUOTE+"weight"   +QUOTE+COLON+this->removeTrailingZeros(lv->getWeight());
                        }
                        json+=CLOSE_CURLY;
                    }
                    json+=COMMA;
                }
                json = json.substr(0, json.size()-1)+CLOSE_BOX+CLOSE_CURLY;// remove last comma, end of children
            }
            return json;
        }
}; //end of TreeElement class
}//end of bridges namespace
#endif
