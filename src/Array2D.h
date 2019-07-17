#ifndef ARRAY_2D_H
#define ARRAY_2D_H

/**
 *
 *
 * @brief This class can be used to create 2 dimensional arrays of type Element<E> where E
 *  is a generic type representation that is application specific.
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
	 * @brief A BRIDGES array type
	 *
	 * This class can be used to create 2D arrays of any type.
	 *
	 * Generic Parameters: E the application data type
	 *
	 * @author Kalpathi Subramanian
	 * @date 7/16/19
	 */


	template <typename E>
	class Array2D : public DataStructure {

		friend class Element<E>;

		private:
			Element<E> *array_data;
			int num_rows;
			int num_cols;

		public:
			Array2D()
				: array_data(nullptr), num_rows(0), num_cols(0) {
			}

			virtual ~Array2D() {
				if (array_data != nullptr)
					delete [] array_data;
			}

			/// builds an array given the dimensions
			/// @param rows number of rows
			/// @param cols number of cols

			Array2D(int rows, int cols) {
				setSize (rows, cols);
			}
			/** 
			 *	Gets the number of rows of the 2D array
			 *  @return number of rows
			 */
			int getNumRows () {
				return num_rows;
			}
			/** 
			 *	Gets the number of columns of the 2D array
			 *  @return number of rows
			 */
			int getNumColumns () {
				return num_cols;
			}
			/** 
			 *	Set the dimensions of the array
			 *  @param cols number of columns
	 		 *	@param rows number of rows
			 */
			void setSize(rows, cols) {
				if (rows < 0 || cols < 0) {
					cout << "Dimensions of array must be positive!" << endl
						<< "\tProvided dimensions: " << rows << "," << cols << endl;
					throw;
				}
				num_rows = rows; num_cols = cols;

				// allocate space for the array
				if (array_data != nullptr)
					delete[] array_data;
				array_data = new Element<E>[num_rows*num_cols];
			}

			/**
			 *
			 *  Get the object at (x, y) 
			 *
			 *  @param x  - column index
			 *  @param y  - row index
			 *
			 *  @return Element<E>  at x, y
			 */
			Element<E>& getElement(int x, int y) {
				return array_data[y * num_cols + x];
			}

			/**
			 *
			 *  Set the object at index x, y  - 2D array
			 *
			 *  @param x - col index into the array
			 *  @param y - row index into the array
			 *  @param el - Element object
			 *
			 *  @return none
			 */
			void setElement(int x, int y, Element<E> el) {
				array_data[y * num_cols + x] = el;
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

				int size = num_rows*num_cols;
				for (int k = 0; k < size; k++) {
					nodes.push_back(&array_data[k]);
				}
				//  first write out dimensions
				string array_json =
					QUOTE + "dims" + QUOTE + COLON +
					OPEN_BOX +
					JSONencode(num_cols) + COMMA +
					JSONencode(num_rows) + COMMA +
					JSONencode(1) +
					CLOSE_BOX + COMMA +

					QUOTE + "nodes"  + QUOTE + COLON +
					OPEN_BOX +
					generateJSON(nodes) +
					CLOSE_BOX + CLOSE_CURLY;

				return array_json;
			}

			Array2D(const Array2D&) = delete; //would be incorrect, so disabled.
			Array2D& operator=(const Array2D&) = delete; //would be incorrect, so disabled.


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


	}; // Array2D
    }
}// end namespace bridges

#endif
