#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#include "DataStructure.h"
#include "Symbol.h"

#ifndef SYMBOL_COLLECTION_H

#define SYMBOL_COLLECTION_H

namespace bridges {

	/*
	 * 	@brief the ShapeCollection represents a collection of symbols (shapes,
	 *		polygons, and text) to visualize in Bridges
	 * 	@author Kalpathi Subramanian
	 *	@date 10/9/18
	 *
	*/
	class SymbolCollection : public  DataStructure {
			// keep track of the shape elements; useful
			// to maintain their properties
		private:

			unordered_map<int, Symbol> symbols;

			// 	default domain (assuming square coordinate space)
			// 	domian emanates in x and y directions, both positive and negative,
			//	from 0,0

		protected:
			float domain = 100.0f;

		public:
			/**
			 *
			 *	Constructor
			 */
			SymbolCollection() {
			}

			/**
			  *	This method gets the data structure type
			  *
			  *	@return  The date structure type as a string
			  *
			  */
			virtual const string getDStype() const {
				return "SymbolCollection";
			}

			/**
			 *   This method adds a symbol to the collection
			 *
			 *   @param s  symbol being added
			 */
			void addSymbol(Symbol *s) {
				// note: it is the user's responsibility to handle
				//  duplicates where desired
				symbols[s->getIdentifier()] = *s;

				// update the axes limits for the visualization
				updateAxisDomains(s);
			}

		private:
			/*
			 *  This method examines whether the axes should be expanded
			 *	to ensure all shapes are shown
			 */
			void updateAxisDomains(Symbol *s) {
				vector<float> dims = s->getDimensions();

				// check x axis
				if (fabs(dims[0]) > domain) {
					domain = fabs(dims[0]);
				}
				if (fabs(dims[1]) > domain) {
					domain = fabs(dims[1]);
				}

				// check y axis
				if (fabs(dims[2]) > domain) {
					domain = fabs(dims[2]);
				}
				if (fabs(dims[3]) > domain) {
					domain = fabs(dims[3]);
				}
			}

			/*
			 *	Get the JSON representation of the the data structure
			 */
			virtual const string getDataStructureRepresentation() const {
				string symbol_json = string();
				for (auto& entry : symbols) {
					symbol_json +=
						entry.second.getSymbolRepresentation() + COMMA;
				}
				// remove last comma
				if (symbols.size()) {
					symbol_json.erase(symbol_json.size() - 1);

					symbol_json = QUOTE + "domainX" + QUOTE + COLON +
						OPEN_BOX +
						to_string(-domain) + COMMA + to_string(domain) +
						CLOSE_BOX + COMMA +
						QUOTE + "domainY" + QUOTE + COLON +
						OPEN_BOX +
						to_string(-domain) + COMMA + to_string(domain) +
						CLOSE_BOX + COMMA +
						QUOTE + "symbols" + QUOTE + COLON + 
							OPEN_BOX + symbol_json + CLOSE_BOX + CLOSE_CURLY;
				}
				return symbol_json;
			}
	};

} // namespace bridges

#endif
