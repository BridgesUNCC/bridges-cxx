#ifndef ARRAY_H
#define ARRAY_H

/**
 *
 *
 * @brief This class can be used to create 1 dimensional arrays of type Element<E> where E
 *  is a generic type representation application specific data.
 *
 * @param <E>

 * @author  Kalpathi Subramanian
 * @date    7/16/19
 *
 */


#include "Element.h"

#include "Bridges.h"

namespace bridges {
    namespace datastructure {
	/**
	 * @brief A BRIDGES 1D array type
	 *
	 * This class can be used to create 1D arrays of any type.
	 *
	 * Generic Parameters: E the application data type
	 *
	 * @author Kalpathi Subramanian
	 * @date 7/16/19
	 */

	template <typename E>
	class Array1D : public DataStructure {

		friend class Element<E>;

		private:
			Element<E> *array_data;
			int size;

		public:
			Array1D()
				: array_data(nullptr), size(0) {
			}

			virtual ~Array1D() {
				if (array_data != nullptr)
					delete [] array_data;
			}

			/// builds an array given the dimensions
			///@param num_dims number of dimension
			///@param dims size of each dimension

			Array1D(int sz) {
				setSize(sz);
			}


			void setSize(int sz) {
				if (sz < 0) {
					cout << "Dimension of array must be positive!" << endl
						<< "\tProvided dimension: " << sz << endl;
					throw;
				}
				size = sz;

				// allocate space for the array
				if (array_data != nullptr)
					delete[] array_data;
				array_data = new Element<E>[sz];
			}

			/**
			 *
			 *  Get the object at index index  - 1D array
			 *
			 *  @param index - index into the array
			 *
			 *  @return Element<E>  at 'index'
			 */
			Element<E>& getElement(int index) {
				return array_data[index];
			}

			/**
			 *
			 *  Set the object at index ind  - 1D array
			 *
			 *  @param ind - index into the array
			 *  @param el - Element object
			 *
			 *  @return none
			 */
			void setElement(int ind, Element<E> el) {
				array_data[ind] = el;
			}

			/**
			 *	Get the data structure type 
			 *	@return data structure name
			 *
			 */
			virtual const string getDStype() const override {
				return "Array";
			}

			virtual const string getDataStructureRepresentation() const override final {
				using bridges::JSONUtil::JSONencode;

				vector<const Element<E>*> nodes;

				for (int k = 0; k < size; k++) {
					nodes.push_back(&array_data[k]);
				}
				//  first write out dimensions
				string array_json =
					QUOTE + "dims" + QUOTE + COLON +
					OPEN_BOX +
					JSONencode(size) + COMMA +
					JSONencode(1) + COMMA +
					JSONencode(1) +
					CLOSE_BOX + COMMA +

					QUOTE + "nodes"  + QUOTE + COLON +
					OPEN_BOX +
					generateJSON(nodes) +
					CLOSE_BOX + CLOSE_CURLY;

				return array_json;
			}

			Array1D(const Array1D&) = delete; //would be incorrect, so disabled.
			Array1D& operator=(const Array1D&) = delete; //would be incorrect, so disabled.


		private:
			const string generateJSON( const vector<const Element<E>*>& nodes) const {
				if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
					// cant exceed max number of elements
					throw "Max allowed elements(for visualization) exceeded.. " +
					to_string(nodes.size()) + " Must be less than " +
					to_string(MAX_ELEMENTS_ALLOWED);
				}
				// map the nodes to a sequence of ids, 0...N-1
				// then get the JSON string for nodes placeholder
				// nullptr prevents insertion of other nullptrs
				unordered_map<const Element<E>*, int> map{{nullptr, -1}};

				string nodes_JSON;

				int i = 0; // get the JSON string for nodes
				for (const auto* e : nodes) {
					if (map.emplace(e, i).second && ++i)  {
						// short circut only incriments i and gets rep
						// upon successful emplacement
						nodes_JSON += e->getElementRepresentation() + COMMA;
					}
				}
				map.erase(nullptr); //Remove trailing comma and nullptr entry
				if (nodes_JSON.size()) {
					nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
				}

				return nodes_JSON;
			};


	}; // Array
    }
}// end namespace bridges

#endif
