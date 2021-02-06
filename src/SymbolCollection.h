#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#include "DataStructure.h"
#include "Symbol.h"

/**
 * @brief The SymbolCollection object is a container object to hold a collection of symbols
 *	(rectangles, polygons, circles, labels).
 *
 * This enables make 2D vector graphics
 *
 * @sa There is a tutorial about Symbol Collections :
 * http://bridgesuncc.github.io/tutorials/Symbol_Collection.html

 * @author David Burlinson, Kalpathi Subramanian
 *
 *
 */

#ifndef SYMBOL_COLLECTION_H

#define SYMBOL_COLLECTION_H

namespace bridges {
	namespace datastructure {
		/**
		 * 	@brief the ShapeCollection represents a collection of symbols (shapes,
		 *		polygons, and text) to visualize in Bridges
		 * 	@author Kalpathi Subramanian
		 *	@date 10/9/18, 7/12/19, 12/28/20
		 *
		 */
		class SymbolCollection : public  DataStructure {
				// keep track of the shape elements; useful
				// to maintain their properties
			private:

				unordered_map<int, Symbol*> symbols;

				// 	default domain (assuming square coordinate space)
				// 	domain emanates in x and y directions, both positive
				//  and negative,
				//	from 0,0

			protected:
				mutable float domainxmin = 0.0;
				mutable float domainxmax = 100.0;
				mutable float domainymin = 0.0;
				mutable float domainymax = 100.0;
				bool autoscaledomain = false;

			public:

				/**
				 * @brief set the dimensions of the view
				 *
				 * If this is not specified, then it will be computed
				 * from the symbols in the domain
				 @param  xmin  minimum X coord of view
				 @param  xmax  maximum X coord of view
				 @param  ymin  minimum Y coord of view
				 @param  ymax  maximum Y coord of view
				 */
				void setViewport(float xmin, float xmax, float ymin, float
					ymax) {
					autoscaledomain = false;
					domainxmin = xmin;
					domainxmax = xmax;
					domainymin = ymin;
					domainymax = ymax;
				}
				/**
				 *	Constructor
				 */
				SymbolCollection() {
				}

				/**
				  *	@brief This method gets the data structure type
				  *
				  *	@return  The date structure type as a string
				  */
				virtual const string getDStype() const {
					return "SymbolCollection";
				}

				/**
				 *   @brief This method adds a symbol to the collection
				 *
				 *   @param s  symbol being added
				 */
				void addSymbol(Symbol *s) {
					//  note: it is the user's responsibility to handle
					//  duplicates where desired
					symbols[s->getIdentifier()] = s;
				}

			private:
				/*
				 *  This method examines whether the axes should be expanded
				 *	to ensure all shapes are shown
				 *
				 *  @param s  Symbol
				 */

				void updateAxisDomains(const Symbol* s) const {
					vector<float> dims = s->getDimensions();

					// check x axis
					if (dims[0] < domainxmin) {
						domainxmin = dims[0];
					}
					if (dims[1] > domainxmax) {
						domainxmax = dims[1];
					}

					// check y axis
					if (dims[2] < domainymin) {
						domainymin = dims[2];
					}
					if (dims[3] > domainymax) {
						domainymax = dims[3];
					}

					// TEMP  (KRS)
					//					domainxmin = 0;
					//					domainxmax = 100;
					//					domainymin = 0;
					//					domainymax = 100;
					// TEMP  (KRS)
				}

				/*
				 *	@brief Get the JSON representation of the the data structure
				 *  @return JSON string of the symbol representation
				 */
				virtual const string getDataStructureRepresentation() const {

					if (autoscaledomain)
						for (auto& entry : symbols)
							updateAxisDomains(entry.second);


					string symbol_json = string();
					for (auto& entry : symbols) {
						symbol_json +=
							entry.second->getSymbolRepresentation() + COMMA;
					}
					// remove last comma
					if (symbols.size()) {
						symbol_json.erase(symbol_json.size() - 1);

						symbol_json = QUOTE + "domainX" + QUOTE + COLON +
							OPEN_BOX +
							to_string(domainxmin) + COMMA + to_string(domainxmax) +
							CLOSE_BOX + COMMA +
							QUOTE + "domainY" + QUOTE + COLON +
							OPEN_BOX +
							to_string(domainymin) + COMMA + to_string(domainymax) +
							CLOSE_BOX + COMMA +
							QUOTE + "symbols" + QUOTE + COLON +
							OPEN_BOX + symbol_json + CLOSE_BOX + CLOSE_CURLY;
					}
					return symbol_json;
				}
		};
	}
} // namespace bridges

#endif
