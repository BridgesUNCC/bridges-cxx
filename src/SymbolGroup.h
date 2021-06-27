#include <string>
#include <unordered_map>

using namespace std;

#include <JSONutil.h>
#include "DataStructure.h"
#include "Symbol.h"

/**
 * @brief The SymbolGroup object is a container object to hold a collection
 *	of primitive symbol objects  such as rectangles, polygons, circles, labels.
 *
 *	In this version, all symbols are individual primitives; future versions
 *	 will support groups within groups, thereby facilitating a hierarchical
 * 	 model of symbols
 *
 * @sa

 * @author Kalpathi Subramanian
 *
 */

#ifndef SYMBOL_GROUP_H

#define SYMBOL_GROUP_H

namespace bridges {
	namespace datastructure {
		/**
		 * 	@brief the SymbolGroup represents a collection of symbols (shapes,
		 *		polygons, and text) to visualize in Bridges
		 *
		 * 	@author Kalpathi Subramanian
		 *	@date 3/31/21
		 *
		 */
		class SymbolGroup : public  Symbol {
			private:

				// symbols in this group
				unordered_map<int, Symbol*> symbols;

			public:
				/**
				 *	Constructors
				 */
				SymbolGroup() {
					setShapeType("group");
					symbols.clear();
				}

				/**
				 *   @brief This method adds a symbol to the collection
				 *
				 *   @param s  symbol being added
				 */
				void addSymbol(Symbol *s) {
cout << "adding symbol " << s->getIdentifier() << endl;
					symbols[s->getIdentifier()] = s;
cout << "num symbols " << symbols.size() << endl;
				}
				/**
				 * This method returns the bounding box of all symbols making
				 *  up the symbol group
				 *
				 * @return array of 4 values
				 */
				vector<float> getDimensions() const {

					vector<float> dims = {INFINITY, -INFINITY, INFINITY, -INFINITY};
					vector<float> tdims;
					for (auto& entry : symbols) {
						tdims = entry.second->getDimensions();
						if (tdims[0] <  dims[0])
							dims[0] = tdims[0];
						if (tdims[1] >  dims[1])
							dims[1] = tdims[1];
						if (tdims[2] <  dims[2])
							dims[2] = tdims[2];
						if (tdims[3] >  dims[3])
							dims[3] = tdims[3];
					}
					return dims;
				}

				/**
				 * @brief This method returns the JSON representation of the
				 *		symbol group
				 *
				 * @return string  JSON string
				 */
				virtual const string getSymbolRepresentation() const {

					using bridges::JSONUtil::JSONencode;

					string symbol_json = OPEN_CURLY;  

					if (this->xform_flag) {
						symbol_json +=
							QUOTE + "transform" + QUOTE + COLON +
							OPEN_BOX +
								JSONencode(this->xform[0][0]) + COMMA +
								JSONencode(this->xform[1][0]) + COMMA +
								JSONencode(this->xform[0][1]) + COMMA +
								JSONencode(this->xform[1][1]) + COMMA +
								JSONencode(this->xform[0][2]) + COMMA +
								JSONencode(this->xform[1][2]) +
								CLOSE_BOX + COMMA;
					}
					symbol_json += 
                    		QUOTE + "type" + QUOTE + COLON +
                            QUOTE + getShapeType() + QUOTE + COMMA + 
                            QUOTE + "ID" + QUOTE + COLON +
                            QUOTE + to_string(getIdentifier()) + QUOTE +
						CLOSE_CURLY + COMMA;

					// process the symbols in the group
					for (auto& entry : symbols) {
						symbol_json +=
							entry.second->getSymbolRepresentation();

						// remove the close curly brace 
						if (symbol_json.size())
							symbol_json.erase(symbol_json.size() - 1);

						// add parent id
						symbol_json += COMMA + QUOTE + "parentID" + QUOTE + COLON +
								to_string(getIdentifier()) + CLOSE_CURLY + COMMA;
					}
					// remove last comma
					if (symbols.size()) {
						symbol_json.erase(symbol_json.size() - 1);
					}

					return symbol_json;
				}
		};
	}
} // namespace bridges

#endif
