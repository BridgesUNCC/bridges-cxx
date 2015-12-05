#ifndef SLELEMENT_H
#define SLELEMENT_H

#include "Element.h" //string, list, using std

namespace bridges {
/**
 * @brief The singly linked list element, derived from Element
 *
 * This class can be used to instantiate singly linked list elements. Most
 * of the methods are inherited from Element. The singly linked element provides
 * a next pointer, used to link to the following element in a singly linked
 * list.
 *
 * <E> Can be of any legal C++ type: integer, string, float, double, or
 * any user defined object(class, struct, array) , and represents application
 * dependent data.
 *
 * @author Kalpathi Subramanian,
 * @date 6/11/15.
 */
template <typename E>
class SLelement : public Element<E>
{
	private:
		SLelement* next = nullptr; //the link to the next element
	public:
	    /**
	 	 * This constructor sets the next pointer
	 	 * to the "n", value to "e", and label to "lab".
	 	 * If an argument is not provided, its default constructor is used.
	 	 *
	 	 * @param n The next SLelement
	 	 * @param e The data to hold
	 	 * @param lab The label to show
	 	 */
		SLelement(SLelement* n = nullptr,E e = E(),string lab = string()) : Element<E>(e,lab), next(n) {}
		/**
	 	 * This constructor sets value to "e" and
		 * label to "lab" and sets the next pointer to NULL.
		 * If an argument is not provided, its default constructor is used.
		 *
	 	 * @param lab The label to show
	 	 * @param e The data to hold
	 	 */
		SLelement(E e,string lab = string()) : SLelement(nullptr, e, lab) {}
		/** Copy constructor */
		SLelement(const SLelement& sl) : SLelement(sl.next,sl.value,sl.label){}
		/** Assignment Operator */
		SLelement& operator=(const SLelement& that)
		{
		    Element<E>::operator=(that);
		    next = that.next;
		    return *this;
		}
		/**
	 	 * Returns the next SLelement
		 *
	 	 * @return The next SLelement
	 	 */
		SLelement* getNext() {return next;}
        /**
	 	 * Sets next to "n"
	 	 * (user is reponsible for next's memory management)
		 *
	 	 * @param n The next SLelement
	 	 */
		void setNext(const SLelement* n){next = n;}
        /**
	 	 * Calls delete on "head" and each linked SLelement*
		 *
		 * @param head Head of a singly linked list
		 * @warning Only call if these SLelements were all dynamicaly allocated(aka: using new)
		 */
		static void cleanup(SLelement* head)
		{
		    if(head)
            {
                cleanup(head->getNext()); //cleanup next sublist
                delete head; //remove head
            }
		}
		/**
		 * Returns a pair of JSON strings of the nodes and links of the single linked list
		 *
		 * @return A pair of node and link JSON
		 */
        virtual pair<string,string> getDataStructureRepresentation()
        {
			list<const Element<E>*> nodes;

            SLelement* sl_list = this;
            nodes.push_front(sl_list);
            while(SLelement* sl_next = sl_list->next)
            {
                nodes.push_front(sl_next);
                sl_list->getLinkVisualizer(sl_next); //link to next
                sl_list = sl_next;
            }
			return Element<E>::generateJSON_Of_Nodes_And_Links(nodes); // generate the JSON string
		}
}; //end of SLelement class
}//end of bridges namespace
#endif
