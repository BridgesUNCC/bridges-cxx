#ifndef SLELEMENT_H
#define SLELEMENT_H

#include "Element.h" //string, using std

namespace bridges{
/**
 * @brief The singly linked list element, derived from Element
 *
 * This class can be used to create singly linked elements, with a next SLelement pointer
 *
 * Generic Parameters: E the application data type
 *
 * @author Kalpathi Subramanian
 * @date 6/11/15
 */
template <typename E>
class SLelement : public Element<E>
{
	protected:
	    /** The pointer to the next SLelement */
		SLelement* next = nullptr;
	public:
	    /**
		 * Constructs an slelement with the provided value, label, and next slelement.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
		 * @param n The next SLelement
	 	 */
		SLelement(SLelement* n,const E& val = E(),const string& lab = string()) : Element<E>(val,lab) {setNext(n);}
		/**
		 * Constructs an slelement with the provided value and label, setting the next slelement to NULL.
		 * The defaults will be used if not provided.
		 *
		 * @param val The data to hold
		 * @param lab The label to show
	 	 */
		SLelement(const E& val = E(),const string& lab = string()) : SLelement(nullptr, val, lab) {}
		/** @return The next SLelement */
		virtual SLelement* getNext() {return next;}
		/** Constant version */
		virtual const SLelement* getNext() const {return next;}
        /** Sets next to "n" @param n The next SLelement */
		void setNext(SLelement* n)
		{
		    if(next!=n){this->links.erase(next);}//if different, remove old link data
		    if((next=n)){this->links[next];} //set next to n and if not null, create default link data if none already present
        }
        /**
	 	 * Calls delete on itself and each next linked SLelement*
		 *
		 * @warning Only call if these SLelements were all dynamicaly allocated(aka: using new)
		 * @warning If linked list contains redundant links, delete will be called multiple times on it, leading to undefined behavior
		 */
		virtual void cleanup() override {if(next){next->cleanup();}Element<E>::cleanup();}
    private:
		/**
         * Gets the JSON representation of this slelement and its links
         *
         * @param arr_size The size of the array determined by this
         * @return A pair holding the nodes and links JSON strings respectively
         */
        virtual const pair<string,string> getDataStructureRepresentation(const unsigned int& arr_size) const override final
        {
			unordered_set<const Element<E>*> nodes;
			for(unsigned int i=0;i<arr_size;i++){this[i].orderHelper(nodes);}
			return this->generateJSON(nodes); // generate the JSON string
		}
		/**
		 * Modifys "nodes" by adding this node and its next recursively
		 *
		 * @param nodes The set to be added to
		 */
		void orderHelper(unordered_set<const Element<E>*>& nodes) const {if(nodes.emplace(this).second && next){next->orderHelper(nodes);} }//prevents potential infinite loop
}; //end of SLelement class
}//end of bridges namespace
#endif
