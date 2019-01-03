#ifndef ELEMENT_H

#define ELEMENT_H

#include <unordered_set>
#include <unordered_map>
#include <cmath>

using namespace std;

#include "DataStructure.h"
#include "ElementVisualizer.h"
#include "LinkVisualizer.h"
#include <JSONutil.h>

namespace bridges {
	// forward Declarations
	template <typename K, typename E1, typename E2> class GraphAdjList;
	template <typename K, typename E1, typename E2> class GraphAdjMatrix;

	/**
	 *	@brief This is the fundamental building block for all data structures
	 *	in BRIDGES.
	 *
	 *	This is the Superclass Element with SLelement, DLelement, MLElement,
	 *	CircSlElement, CircDlElement, TreeElement, AVLTreeElement, BSTElement
	 *	subclasses.
	 *
	 * 	Generic Parameters: E the application data type
	 *
	 * 	The label field(string type) is used to label the visualization of the
	 * 	element.
	 *
	 * 	Element holds a LinkVisualizer for each of its links and
	 * 	an ElementVisualizer for itself
	 *
	 * 	@author Kalpathi Subramanian
	 *
	 * 	@date 6/11/15, 11/27/16
	 */


	template <typename E> class Element {
			//Used for access to generateJSON() and for links manipulation
			template <typename K, typename E1, typename E2> friend class GraphAdjList;
			template <typename K, typename E1, typename E2> friend class GraphAdjMatrix;
			template <typename K> friend class Array;

		private:
			static const unordered_map<const Shape, const string, hash<int>>& ShapeNames() {

			  static std::unordered_map<const Shape, const string, hash<int>> sn = 
			    {
			      {CIRCLE, "circle"},
			      {SQUARE, "square"},
			      {DIAMOND, "diamond"},
			      {CROSS, "cross"},
			      {TRIANGLE, "triangle"},
			      {WYE, "wye"},
			      {STAR, "star"}
			    };
			  return sn;
			}


			
			//this element's label
			string label;
			// appl. specific data stored with element
			E value = E();
			// this element's visualizer
			ElementVisualizer* elvis;

		protected:

			// this element's collection of links
			unordered_map<Element*, LinkVisualizer> links;

		public:
			/**
			 * Constructs an element with the provided value and label.
			 * The defaults will be used if not provided.
			 *
			 * @param val The data to hold
			 * @param lab The label to show
			 */
			Element(const E& val = E(), const string& lab = string()) :
				label(lab), value(val) {
				elvis = new ElementVisualizer;
			}

			Element(const Element& e)
				: label(e.label), value(e.value), elvis(new ElementVisualizer(*(e.elvis))), links(e.links) {
			}

			Element& operator= (const Element& e) {
				this->label = e.label;
				this->value = e.value;
				*(this->elvis) = *(e.elvis);
				this->links = e.links;
				return *this;
			}

			virtual ~Element() {
				delete elvis;
			}

			/**
			 *	@return The ElementVisualizer of this element
			 */
			ElementVisualizer* getVisualizer() {
				return elvis;
			}
			/**
			 * Constant version
			 *
			 * @return The ElementVisualizer of this element
			 */
			const ElementVisualizer* getVisualizer() const {
				return elvis;
			}
			/**
			 * Returns the LinkVisualizer to element "el" or NULL if no link exists
			 *
			 * @param el The terminating element of the link
			 *
			 * @return The LinkVisualizer
			 */
			LinkVisualizer* getLinkVisualizer(const Element* el) {
				if (links.find(const_cast<Element*>(el)) != links.end()) {
					return &(links.at(const_cast<Element*>(el)));
				}
				cerr << "Element " << label << " not linked to Element "
					<< el->getLabel() << ", returning NULL" << endl;
				return nullptr;
			}

			/**
			 * Constant version
			 *
			 * @param el The terminating element of the link
			 * @return The LinkVisualizer
			 */
			LinkVisualizer* getLinkVisualizer(const Element* el) const {
				return const_cast<Element*> (this)->getLinkVisualizer(el);
			}

			/**
			 *	@return The label of the element
			 */
			string getLabel() const {
				return label;
			}

			/**
			 * Sets label to "lab"
			 *
			 * @param lab The label of the element
			 */
			void setLabel(const string& lab) {
				label = lab;
			}

			/**
			 *	@return The value of the element
			 */
			E getValue() const {
				return value;
			}

			/**
			 * Sets value to "val"
			 *
			 * @param val The value of the element
			 */
			void setValue(const E& val) {
				value = val;
			}

		protected:
			/**
			 *	@return The JSON string of this element's properties
			 */
			virtual const string getElementRepresentation() const {
				using bridges::JSONUtil::JSONencode;
				//write out ElementVisualizer properties

				// first check if location is set and needs to be included
				string loc_str = "";
				if ( (elvis->getLocationX() != INFINITY) &&
					(elvis->getLocationY() != INFINITY) ) {
					loc_str =  QUOTE + "location" + QUOTE + COLON +
						OPEN_BOX +
						JSONencode(elvis->getLocationX())  + COMMA +
						JSONencode(elvis->getLocationY()) +
						CLOSE_BOX + COMMA;
				}
				return  OPEN_CURLY +
					QUOTE + "color" + QUOTE + COLON + getCSSRepresentation(elvis->getColor())
					+ COMMA +
					loc_str +
					QUOTE + "shape" + QUOTE + COLON + QUOTE +
					ShapeNames().at(elvis->getShape()) + QUOTE + COMMA +
					QUOTE + "size" + QUOTE + COLON +
					JSONencode(elvis->getSize()) + COMMA +
					QUOTE + "name" + QUOTE + COLON + JSONencode( label) +
					CLOSE_CURLY;
			}
			/**
			 * Gets the JSON representation of this link visualizer using
			 * the supplied source and destination strings
			 *
			 * @param lv The LinkVisualizer
			 * @param src The source vertex
			 * @param dest The destination vertex
			 * @return The JSON of this link visualizer
			 *
			 */
			static const string getLinkRepresentation(const LinkVisualizer& lv,
				const string& src, const string& dest) {
				using bridges::JSONUtil::JSONencode;


				//write out LinkVisualizer properties
				return OPEN_CURLY +
					QUOTE + "color"     + QUOTE + COLON + getCSSRepresentation(lv.getColor())
					+ COMMA +
					(!lv.getLabel().empty() ?
						(QUOTE + "label" + QUOTE + COLON +
							JSONencode( lv.getLabel()) + COMMA) : "") +
					QUOTE + "thickness" + QUOTE + COLON +
					JSONencode(lv.getThickness()) + COMMA +
					QUOTE + "weight"    + QUOTE + COLON +
					JSONencode(lv.getWeight()) + COMMA +
				  QUOTE + "source"    + QUOTE + COLON + JSONencode(src)  + COMMA +
				  QUOTE + "target"    + QUOTE + COLON + JSONencode(dest) +
					CLOSE_CURLY;
			}
			/**
			 * Gets the JSON representation of this color
			 *
			 * @param col The Color
			 * @return Equivilant Legal CSS color representation
			 */
			static const string getCSSRepresentation(const Color& col) {
				using bridges::JSONUtil::JSONencode;
				if (col.isTransparent()) {
					//leaves off other channels if transparent
					return "[0, 0, 0, 0.0f]";
				}
				const string strCSS =
					JSONencode(col.getRed()) + "," +
					JSONencode(col.getGreen()) + "," +
					JSONencode(col.getBlue()) + "," +
					JSONencode( ((float) (col.getAlpha()) / 255.0f));

				return OPEN_BOX + strCSS + CLOSE_BOX;
			}
		public:
			void printLinks() {
				cout << "[printLinks]Source vert: " << label << ", " << this << endl;

				for (auto& it : links) {
					cout << "\t Dest Elements : " << (it.first)->getLabel() << ","
						<< it.first << endl;
				}
			}

			// temp
	};	//end of Element class


}//end of bridges namespace

#endif
