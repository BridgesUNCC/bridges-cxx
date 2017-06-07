/**
 * 	@brief This class can be used to instantiate Multi-list Elements.

 * 	This class extends SLelement (singly linked list element) to build multi-lists;
 *	Multilist elements contain a tag that indicates if the element is a sublist or not;
 *	If the element points to a sublist, then the sublist field is the beginning of
 *	this sublist. If not, the data field contains the user specified data item and
 *	list continues (getNext()/setNex()). As in singly linked elements, the next pointer
 *	points to the following list element of the list or sublist.
 *
 * 	Multi-list elements contain a visualizer (ElementVisualizer) object for setting
 *	visual attributes (color, shape, opacity, size), necessary for displaying
 *	them in a web browser.
 *
 *	Elements also have a LinkVisualizer object, that is used when they are linked to
 *	another element, appropriate for setting link attributes, for instance, between
 *	the current element and its next element. In this case, the link in question is that
 *  which connects the element to the following elements; a similar logic follows for
 *	sublists.
 *
 * @author , Kalpathi Subramanian
 *
 * @date 5/24/17
 *
 * @param <E> The generic parameter object that is part of this element, representing
 *			either application specific data, or a pointer to a sublist.
 *
 *	\sa Example Tutorial at <br> ??
 */

#include "SLelement.h"

namespace bridges {

	template <typename E>
	class MLelement : public SLelement<E> {

		protected:
			MLelement<E> *sub_list = nullptr; // link to a sublist
			bool tag = false;

		public:

			/**
			 *
			 * This constructor creates an MLelement object
			 * and sets the next pointer to null
			 *
			 */

			MLelement(const E& val = E(), const string& lab = string())
				: SLelement<E> (nullptr, val, lab) {
				sub_list = nullptr;
				tag = false;
			}

			/**
			 *
			 * This constructor creates an SLelement object of generic parameter object E,
			 *	and label "label" and sets the next pointer to null
			 *
			 * @param label the label of SLelement that shows up on the Bridges visualization
			 * @param e the generic object that this SLelement will hold
			 *
			 */
			MLelement (string label) : SLelement<E> (nullptr, E(), label) {
				sub_list = nullptr;
				tag = false;
			}

			/**
			 *
			 * Creates a new element with value "e" and sets the next pointer
			 * to the SLelement referenced by the "next" argument
			 *
			 * @param e the generic object that this element will hold
			 * @param next the element that should be assigned to the next pointer
			 *
			 */
			MLelement (E e, MLelement<E> *next) : SLelement<E> (next, e, string()) {
				sub_list = nullptr;
				tag = false;
			}

			/**
			 * Sets the start of a new sublist.
			 * to the SLelement "next"
			 *
			 * @param sl the MLelement that is the beginning of a sublist
			 */
			void setSubList(MLelement<E> *sl) {
				// Hmmm, need to think about removing link data from
				// an existing sublist
				this->sub_list = sl;
				tag = true;

				// create link data from node to head of sublist
				if (sl)
					this->links[sl];

				// by default, color and shape sublist nodes to distinguish them
				this->getVisualizer()->setColor(Color("red"));
				this->getVisualizer()->setShape(SQUARE);
			}

			/**
			 * Gets the sublist at this node, if it exists
			 *
			 * @return  the sublist head element, if it exists
			 */
			MLelement *getSubList() {
				return sub_list;
			}

			/**
			 *	This method gets the data structure type
			 *
			 *	@return  The date structure type as a string
			 *
			 */
			string getDataStructType() {
				return "MultiList";
			}

			/**
			 * Retrieves the element following this element
			 *
			 * @return MLelement<E> assigned to next
			 *
			 */
			MLelement<E> *getNext() override {
				return (MLelement<E>*) this->next;
			}

			/**
			 * Sets the element to point to the next MLelement
			 *
			 * @param next SLelement<E> that should be assigned to the next pointer
			 */
			void setNext(MLelement<E> *n) {
				if (n) {
					if (this->next != n)	// remove old link data, possibly
						this->links.erase(this->next);

					this->next = n;
					this->links[this->next];
				}
			}

			/**
			 *
			 *	Sets the tag of the element.
			 *
			 *	@param boolean t
			 *
			 */
			void setTag(bool t) {
				tag = t;
			}

			/**
			 *
			 *	Gets the tag of the element.
			 *
			 *  @return tag of the element
			 */
			bool getTag() {
				return tag;
			}
		private:
			/**
			 * Gets the JSON representation of this multilist and its links
			 *
			 * @return A pair holding the nodes and links JSON strings respectively
			 */
			virtual const pair<string, string> getDataStructureRepresentation()
									const override final {
				vector<const Element<E>*> nodes;

				// get the list of nodes
				this->getListElements(this, nodes);

				// generate the JSON string
				return Element<E>::generateOrderedJSON(nodes);
			}
			/**
			 *  Get the list of nodes
			 *
			 *  @param nodes The list of nodes
			 */
			void getListElements(const MLelement<E> *list,
				vector<const Element<E>*>& nodes) const {

				auto it = list;
				while (it != nullptr) {
					nodes.push_back(it);
					// if this node has a sublist, recurse
					if (it->tag) {
						getListElements(it->sub_list, nodes);
					}
					// iterate
					it = (MLelement<E>*) it->next;
				}
			}
	};

} // end namespace bridges
