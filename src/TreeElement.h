#ifndef TREE_ELEMENT_H
#define TREE_ELEMENT_H

#include "Element.h" //string, using std

#include <vector>

using namespace std;
namespace bridges{
static int k = 0;
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
class TreeElement : public Element<E> {
	private:
	    /** A list of pointers to this Elements subtrees */
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
		TreeElement(const E& e = E(),const string& lab = string())
									: Element<E>(e,lab) {
			children.reserve(10);
		}

		/** @return The string representation of this data structure type */

		virtual const string getDStype() const override {
			return "Tree";
		}

		/** @return The children TreeElements */

		vector<TreeElement*>& getChildren() {
			return children;
		}

		/** Constant version */
		const vector<TreeElement*>& getChildren() const {
			return children;
		}

        /**
         * Gets the nth child of this TreeElement, returns null if non-existent
         *
         * @param n The index of the child
         * @return The child TreeElement*
         */
		TreeElement* getChild(const int& n) {
			return (n >= children.size() || n < 0 )? nullptr : children.at(n);
		}

		/** Constant version */
		const TreeElement* getChild(const int& n) const {
			return (n >= children.size() || n < 0)? nullptr : children.at(n);
		}

		/** 
		 *	Adds "kid" to children and returns its position 
		 *  @param kid The child TreeElement @return index of child 
		 */
		void addChild(TreeElement* kid) {
            children.push_back(kid);
            if(kid){
				this->links[kid];
			}
        }
        /** 
		 * Sets child at index to "kid". Will do nothing given invalid index. 
		 * @param index of child to replace @param kid The child TreeElement 
		 */
        void setChild(const size_t& index,TreeElement* kid) {
		/** 
		 *	This simply replaces the element at position index and the old element 
		 *  is lost(actually can create memory leak if it came from dynamic memory
		 *  Since we cannot distinguish from allocated or static memory from pointers,
		 *  it is the user's responsibility to keep track of allocated memory
		 * 	its linkage. For new elements, if not null, create linkage 
		 */
/*
		if (index < children.size() && index >= 0) {
				bool duplicate = false;
				for(size_t i=0;i <children.size(); i++) {
					if(i != index && children[i] == children[index]){
						duplicate=true;break;
					}
				}
				if(!duplicate){
					this->links.erase(children[index]);
				}
				children[index] = kid;
            	if(kid) {
					this->links[kid];
				}
			}
*/
			if ((index < children.size()) && index >= 0) {
				children[index] = kid;
				this->links.erase(children[index]);	// remove any existing links
				this->links[kid];					// initialize this element in the map
			}
        }
		/**
	 	 * Calls delete on itself and each next linked TreeElement*
		 *
		 * @warning Only call if these TreeElements were all dynamicaly allocated(
		 * 	aka: using new)
		 * @warning If tree contains redundant links, delete will be called multiple 
		 *	times on it, leading to undefined behavior
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
         *
         * @param arr_size The size of the array determined by this
         * @return A pair holding the nodes and links JSON strings respectively
         */
		virtual const pair<string,string> getDataStructureRepresentation(
					const unsigned int& arr_size) const override final {

				// The JSON creation for a tree structure is different from other
				// data structures; we will use a preorder traversal to build a hierarch.
				// JSON; it is assumed that children are in order from left to right.
				// Also each child that is NULL is explicitly specified as NULL for 
				// visualization convenience

			unordered_set<const Element<E>*> nodes;

//			for (unsigned int i=0;i<arr_size;i++) {
//				this[i].preOrder(nodes);
//			}
//TEST
//string test_str = this[0].preOrder2(this);
//cout << "JSON String(HIER): \n" << OPEN_CURLY + test_str + CLOSE_CURLY << endl << endl;
//TEST
										// To Do. Must check the max nodes is not 
										// exceeded.
				
										// return the JSON
			return pair<string, string> 
					(OPEN_CURLY + this[0].preOrder2(this) + CLOSE_CURLY,"");
//			return this->generateJSON(nodes); // generate the JSON string
		}
        /**
		 * Modifies "nodes" by adding its nodes via a preorder traversal
		 *
		 * @param nodes The set to be added to
		 */
		void preOrder(unordered_set<const Element<E>*>& nodes) const {
            if (nodes.emplace(this).second) {	//prevents potential infinite loop
                for(const auto& child: children) {
                    if(child){
						child->preOrder(nodes);
					}
                }
            }
		}


		/** 
		 *	Does a preorder traversal to build a hierarchical JSON of the tree
		 *
		 *	@param root - the tree root
		 *
		 *	@return the JSON string
		 **/

		string  preOrder2(const TreeElement<E>* root) const {
			string json_str = "", children = "", link_props = "", elem_rep = "";
			string t_str;
			if (root != NULL) {
									// first get the node representation
				elem_rep = root->getRepresentation();
									// remove surrounding curly braces
				t_str = elem_rep.substr(1, elem_rep.size()-2);
				json_str += t_str + COMMA;
									// now get the children
				json_str += QUOTE + "children" + QUOTE + COLON + OPEN_BOX ;
				for (int k = 0; k < root->children.size(); k++) {
					if (root->children[k] == NULL) {
						json_str += OPEN_CURLY + QUOTE + "name" + QUOTE + COLON + 
							QUOTE + "NULL" + QUOTE + CLOSE_CURLY + COMMA;
					}
					else {
						const LinkVisualizer *lv = 
							root->getLinkVisualizer(root->children[k]);
						json_str += OPEN_CURLY;
						if (lv) {
							Color c = lv->getColor();
							json_str += QUOTE +"linkProperties"+QUOTE+COLON+OPEN_CURLY +
								QUOTE +"color" + QUOTE+ COLON + 
									this->getCSSrep(c) + COMMA +
/*
									to_string(c.getRed()) + COMMA +
									to_string(c.getGreen()) + COMMA +
									to_string(c.getBlue()) + COMMA +
									to_string(c.getAlpha()) + 
*/
								QUOTE + "thickness" + QUOTE + COLON + 
								this->removeTrailingZeros(lv->getThickness()) + COMMA +
								QUOTE + "weight" + QUOTE + COLON + 
								this->removeTrailingZeros(lv->getWeight()) + 
								CLOSE_CURLY + COMMA;
						}
						else json_str += "linkProperties" + COLON + "{}" + COMMA;
									// process its children
						json_str +=	preOrder2(root->children[k]);
						json_str += CLOSE_CURLY + COMMA;
					}
				}
							// remove last comma
				json_str = json_str.substr(0, json_str.size()-1);
							// end of children
				json_str += CLOSE_BOX;
			}

			return json_str;
		}


}; //end of TreeElement class

}//end of bridges namespace
#endif
