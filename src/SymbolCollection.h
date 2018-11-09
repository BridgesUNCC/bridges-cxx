#include <cmath>
#include <string>

using namespace std;

#include "DataStructure.h"

namespace bridges {

	/*
	 * 	@brief the ShapeCollection represents a collection of symbols (shapes,
	 *		polygons, and text) to visualize in Bridges
	 * 	@author Kalpathi Subramanian
	 *	@date 10/9/18
	 *
	*/
	class SymbolCollection : public  DataStruct {
			// keep track of the shape elements; useful
			// to maintain their properties
		private:

			unordered_map<string, Symbol> symbols;

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
			string getDataStructType() {
				return "SymbolCollection";
			}

			/**
			 *   This method adds a symbol to the collection
			 *
			 *   @param s  symbol being added
			 */
			void addSymbol(Symbol s) {
				// note: it is the user's responsibility to handle
				//  duplicates where desired
				symbols[s.getIdentifier()] = s;
			}

		private:
			/*
			 *  This method examines whether the axes should be expanded
			 *	to ensure all shapes are shown
			 */
			void updateAxisDomains(Symbol s) {
				float[] dims = s.getDimensions();

				// check x axis
				if (fabs(dims[0]) > domain) {
					domain = fabs(dims[0]);
				}
				if (fabs(dims[1]) > domain) {
					domain = fabs(dims[1]);
				}

				// check y axis
				if (fabs(dims[2]) > domain) {
					domain = Math.abs(dims[2]);
				}
				if (fabs(dims[3]) > domain) {
					domain = fabs(dims[3]);
				}
			}

			/*
			 *	Get the JSON representation of the the data structure
			 */
			string getDataStructureRepresentation() {
				string symbol_json = string();
				for (auto& entry : symbols) {
					// update axis domains where appropriate for each shape
					updateAxisDomains(entry.second);

					symbol_json += entry.second.getRepresentation() + COMMA;
				}
				// remove last comma
				if (symbols.size()
					symbol_json.erase(symbols_json.size() - 1);

					string symbol_prefix  = QUOTE + "domainX" + QUOTE +
						OPEN_BOX +
						-domain + COMMA + domain +
						CLOSE_BOX + COMMA + QUOTE + "domainY" + QUOTE +
						OPEN_BOX + -domain + COMMA + domain + CLOSE_BOX + COMMA +
						QUOTE + "symbols" + QUOTE + symbol_json + CLOSE_CURLY;

			}
}

} // namespace bridges
