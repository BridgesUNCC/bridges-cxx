#ifndef ARRAY_3D_H
#define ARRAY_3D_H

#include "Element.h"
#include "Array.h"


namespace bridges {
	namespace datastructure {
		/**
		 * @brief A BRIDGES array type
		 *
		 * This class can be used to create 3D arrays of any type.
		 *
		 * The access to the values stored are done
		 * directly using bracket operators such as
		 *
		 * \code{.cpp}
		 * Array3D<std::string> arr(19, 30, 30);
		 * arr [12][25][12] = "hello!";
		 * \endcode
		 *
		 * Entries in the array can be styled by showing a
		 * label and changing the color of an entry. This is
		 * achieved by styling the underlying element to a
		 * particular entry of the array such as:
		 *
		 * \code{.cpp}
		 * Array3D<std::string> arr(19, 30, 3);
		 * arr.getElement(12, 25, 0).setColor("yellow");
		 * arr.getElement(12, 25, 2).setLabel("Hi there");
		 * \endcode
		 *
		 *

		 * @param E the application data type
		 *
		 * @author Kalpathi Subramanian
		 * @date 7/16/19
		 */
		template <typename E>
		class Array3D : public Array<E> {
			private:
				int num_slices, num_rows, num_cols;

				//preventing the creation of blank array3d
				Array3D() {
					num_slices = num_rows = num_cols = 0;
				}
			public:


				virtual ~Array3D() {
				}

				///builds a 3D array.
				///@param cols number of columns
				///@param rows number of rows
				///@param slices number of slices
				Array3D(int cols, int rows, int slices)
					: num_slices(slices), num_rows(rows), num_cols(cols) {
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
					return Array<E>::getElement(z * num_cols * num_rows + y * num_rows + x);
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
				Element<E> const & getElement(int x, int y, int z) const {
					return Array<E>::getElement(z * num_cols * num_rows + y * num_rows + x);
				}

				/**
				 *
				 *  Set the object at index x, y, z  - 3D array
				 *
				 *  @param x - col index into the array
				 *  @param y - row index into the array
				 *  @param z - slice index into the array
				 *  @param el - Element object
				 */
				void setElement(int x_indx, int y_indx, int z_indx, Element<E> el) {
					setElement(x_indx + y_indx * num_rows + z_indx * num_rows * num_cols, el);
				}


				struct Bracket_helper2 {
					Array3D<E>& arr;
					int x;
					int y;
					Bracket_helper2(Array3D<E>& a, int x, int y) : arr(a), x(x), y(y) {}

					E& operator[] (int z) {
						return arr.getElement(x, y, z).getValue();
					}
				};


				/// @brief helper class to make [][] operators work on array 2d. You should never use it directly
				struct Bracket_helper {
					Array3D<E>& arr;
					int x;
					Bracket_helper(Array3D<E>& a, int x) : arr(a), x(x) {}

					Bracket_helper2 operator[] (int y) {
						return Bracket_helper2(arr, x, y);
					}
				};

				///@brief enables using the bracket [] operator
				Bracket_helper operator[] (int index) {
					return Bracket_helper(*this, index);
				}

				struct Bracket_helper2_const {
					Array3D<E> const & arr;
					int x;
					int y;
					Bracket_helper2_const(Array3D<E>& a, int x, int y) : arr(a), x(x), y(y) {}

					E const & operator[] (int z) const {
						return arr.getElement(x, y, z).getValue();
					}
				};


				/// @brief helper class to make [][] operators work on array 2d. You should never use it directly
				struct Bracket_helper_const {
					Array3D<E> const& arr;
					int x;
					Bracket_helper_const(Array3D<E>& a, int x) : arr(a), x(x) {}

					Bracket_helper2_const operator[] (int y) const {
						return Bracket_helper2(arr, x, y);
					}
				};

				///@brief enables using the bracket [] operator
				Bracket_helper_const operator[] (int index) const {
					return Bracket_helper_const(*this, index);
				}

		}; // Array3D
	}
}// end namespace bridges

#endif
