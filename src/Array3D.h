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
#include "Array.h"


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
		class Array3D : public Array<E> {
			private:
				int num_slices, num_rows, num_cols;

			public:
				Array3D() {
					num_slices = num_rows = num_cols = 0;
				}

				virtual ~Array3D() {
				}

				///builds a 3D array.
				///@param cols number of columns
				///@param rows number of rows
				///@param slices number of slices 
				Array3D(int cols, int rows, int slices) {
					int dim[] = {cols, rows, slices};
					this->setSize(3, dim);
				}
				/** 
				 *	Gets the number of rows of the 3D array
				 *  @return number of rows
				 */
				int getNumRows () {
					return num_rows;
				}
				/** 
				 *	Gets the number of columns of the 3D array
				 *  @return number of columns
				 */
				int getNumColumns () {
					return num_cols;
				}
				/** 
				 *	Gets the number of slices of the 3D array
				 *  @return number of slices
				 */
				int getNumSlices () {
					return num_slices;
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
					return Array<E>::getElement(z * num_cols * num_rows * y * num_cols + x);
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
					setElement(x_indx + y_indx * num_cols+ z_indx * num_rows*num_cols, el);
				}
			}; // Array3D
    }
}// end namespace bridges

#endif
