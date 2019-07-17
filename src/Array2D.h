#ifndef ARRAY_2D_H
#define ARRAY_2D_H


#include "Element.h"
#include "Array.h"

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
		class Array2D : public Array<E> {

			private:
				int num_rows;
				int num_cols;

			public:
				Array2D()
					: num_rows(0), num_cols(0) {
				}

				virtual ~Array2D() {
				}

				/// builds an array given the dimensions
				/// @param rows number of rows
				/// @param cols number of cols

				Array2D(int rows, int cols) {
					int dims[] = {cols, rows, 1};
					this->setSize (2, dims);
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
				 *
				 *  Get the object at (x, y) 
				 *
				 *  @param x  - column index
				 *  @param y  - row index
				 *
				 *  @return Element<E>  at x, y
				 */
				Element<E>& getElement(int x, int y) {
					return Array<E>::getElement(y * num_cols + x);
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
					setElement(y*num_cols + x, el);
				}
		}; // Array2D
    }
}// end namespace bridges

#endif
