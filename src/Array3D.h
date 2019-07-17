#ifndef ARRAY_3D_H
#define ARRAY_3D_H

/**
 *
 *
 * @brief This class can be used to create 3D arrays of type Element<E> where E
 *  is a generic type representation application specific data.
 *  Arrays are internally represented as 1D arrays. 
 *  3D arrays are supported.
 *
 * @param <E>

 * @author  Kalpathi Subramanian
 * @date    10/8/16, 7/12/19
 *
 */


#include "Element.h"

#include "Bridges.h"

namespace bridges {
    namespace datastructure {
	/**
	 * @brief A BRIDGES array type
	 *
	 * This class can be used to create 3D arrays of any type.
	 *
	 * Generic Parameters: E the application data type
	 *
	 * @author Kalpathi Subramanian
	 * @date 7/16/19
	 */


	template <typename E>
	class Array3D : public DataStructure {

		friend class Element<E>;

		private:
			Element<E> *array_data;
			int num_slices, num_rows, num_cols;

		public:
			Array3D() : array_data(nullptr) {
				num_slices = num_rows = num_cols = 0;
			}

			virtual ~Array3D() {
				if (array_data != nullptr)
					delete [] array_data;
			}

			///builds a 3D array.
			///@param cols number of columns
			///@param rows number of rows
			///@param slices number of slices 
			Array3D(int cols, int rows, int slices) {
				setSize(cols, rows, slices);
			}

			/// Set array size and allocate storage
			///@param cols number of columns
			///@param rows number of rows
			///@param slices number of slices 
			void setSize(int cols, int rows, int slices) {
				if (cols < 0 || rows < 0 || slices < 0) {
					cout << "Dimensions of array must be positive!" << endl
							<< "\tProvided dimension: " << cols << "," << rows << "," <<
									slices << endl; 
				}
				num_cols = cols; num_rows = rows; num_slices = slices;
				// allocate space for the array
				if (array_data != nullptr)
					delete[] array_data;
				array_data = new Element<E>[cols*rows*slices];
			}

			/**
			 *
			 *  Get the object at (x, y, z) for 3D arrays
			 *
			 *  @param x  - column index
			 *  @param y  - row index
			 *  @param z  - slice index
			 *
			 *  @return Element<E>  object at x, y, z
			 */
			Element<E>& getElement(int x, int y, int z) {
				return array_data[z * num_cols * num_rows * y * num_cols + x];
			}

			/**
			 *
			 *  Set the object at index x, y, z  - 3D array
			 *
			 *  @param x - col index into the array
			 *  @param y - row index into the array
			 *  @param z - slice index into the array
			 *  @param el - Element object
			 *
			 *  @return none
			 */

			void setElement(int x_indx, int y_indx, int z_indx, Element<E> el) {
				array_data[x_indx + y_indx * num_cols+ z_indx * num_rows*num_cols] = el;
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

				int size = num_cols*num_rows*num_slices;
cout << "Array size:" << size << endl;
				for (int k = 0; k < size; k++) {
					nodes.push_back(&array_data[k]);
				}
				//  first write out dimensions
				string array_json =
					QUOTE + "dims" + QUOTE + COLON +
					OPEN_BOX +
					JSONencode(num_cols) + COMMA +
					JSONencode(num_rows) + COMMA +
					JSONencode(num_slices) +
					CLOSE_BOX + COMMA +

					QUOTE + "nodes"  + QUOTE + COLON +
					OPEN_BOX +
					generateJSON(nodes) +
					CLOSE_BOX + CLOSE_CURLY;

				return array_json;
			}

			Array3D(const Array3D&) = delete; //would be incorrect, so disabled.
			Array3D& operator=(const Array3D&) = delete; //would be incorrect, so disabled.


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


	}; // Array3D
    }
}// end namespace bridges

#endif
