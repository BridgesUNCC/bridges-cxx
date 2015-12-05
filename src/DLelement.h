#ifndef DLelement_H
#define DLelement_H

#include "SLelement.h" //string, list, using std

namespace bridges {
/**
 * @brief The basic doubly linked list element, derived from Element
 *
 * This class can be used to create doubly linked element objects
 * with next and previous (prev) pointers
 *
 * <E> Can be any legal C++ type: integer, string, float, double,
 * or any user defined object(class, struct, array) , and represents
 * application dependent data.
 *
 * @author Kalpathi Subramanian
 * @date 6/11/15
 */
template<typename E>
class DLelement: public SLelement<E>
{
	private:
		DLelement* prev = nullptr; 	// link to previous element
	public:
		/**
		 * This constructor sets next to "n", prev to "p", value to "e", and label to "lab".
		 * If an argument is not provided, its default constructor will be used.
 		 *
	 	 * @param n The next DLelement
	 	 * @param p The prev DLelement
	 	 * @param e The data to hold
 		 * @param lab The label to show
	 	 */
		DLelement(DLelement* n,DLelement* p,E e = E(),string lab=string()) : SLelement<E>(n,e, lab), prev(p) {}
		/**
		 * This constructor sets left and right to NULL, value to "e" and label to "lab".
		 * If an argument is not provided, its default constructor will be used.
 		 *
	 	 * @param e The data to hold
 		 * @param lab The label to show
	 	 */
		DLelement (E e = E(),string lab = string()) : DLelement(nullptr, nullptr, e, lab) {}
		/** Copy Constructor */
		DLelement(const DLelement& dl) : DLelement(dl.next,dl.prev,dl.value,dl.label) {}
		/** Assignment Operator */
		DLelement& operator=(const DLelement& that)
		{
		    SLelement<E>::operator=(that);
		    prev = that.prev;
		    return *this;
		}
		/**
	 	 * Returns the next DLelement
	 	 *
	 	 * @return The next DLelement
	 	 */
        DLelement* getNext() {return static_cast<DLelement*>(SLelement<E>::getNext());}
        /**
	 	 * Sets next to "n"
	 	 * (user is reponsible for next's memory management)
         *
	 	 * @param n  The next DLelement
	 	 */
		void setNext(const DLelement* n){SLelement<E>::setNext(n);}
		/**
	 	 * Returns the previous DLelement
	 	 *
	 	 * @return The previous DLelement
	 	 */
		DLelement* getPrev() {return prev;}
		/**
	 	 * Sets prev to "p"
	 	 *
	 	 * @param p : The previous DLelement
	 	 */
		void setPrev(const DLelement* p){prev = p;}
		/**
	 	 * Calls delete on "head" and each forwardly linked DLelement*
	 	 *
		 * @param head Head of a doubly linked list
		 * @warning Only cleans "next" links, "prev" links will remain unchanged
		 * @warning Only call if these DLelements were all dynamicaly allocated(aka: using new)
		 */
		static void cleanup(DLelement* head){SLelement<E>::cleanup(head);}
		/**
		 * Returns a pair of JSON strings of the nodes and links of the doubly linked list
		 *
		 * @return A pair of node and link JSON
		 * @warning Only gets links between "next" nodes, links between this' "prev" nodes are not generated
		 */
		pair<string,string> getDataStructureRepresentation() override
		{
			list<const Element<E>*> nodes;

            DLelement* dl_list = this;
            nodes.push_front(dl_list);
            while(DLelement* dl_next = dl_list->getNext())
            {
                nodes.push_front(dl_next);
                dl_list->getLinkVisualizer(dl_next); //link to next
                if(dl_next->prev)
                {
                    dl_next->getLinkVisualizer(dl_next->prev); //link from next
                }
                else
                {
                    cerr << "Warning: Doubly Linked List not properly chained..." << endl;
                }
                dl_list = dl_next;
            }
			return Element<E>::generateJSON_Of_Nodes_And_Links(nodes); // generate the JSON string
		}
}; //end of DLelement class
}//end of bridges namespace
#endif
