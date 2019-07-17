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
		 * @param E the application data type
		 *
		 * @author Kalpathi Subramanian
		 * @date 7/16/19
		 */
		template <typename E>
		class Array2D : public Array<E> {

			private:
				int num_rows;
				int num_cols;

				Array2D()
					: num_rows(0), num_cols(0) {
				}
			public:

				virtual ~Array2D() {
				}

				/// builds an array given the dimensions
				/// @param rows number of rows
				/// @param cols number of cols

		  Array2D(int rows, int cols)
		    :num_rows(rows), num_cols(cols) {
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
				 *  @brief Gets the number of columns of the 2D array
				 *
				 *  @return number of rows
				 */
				int getNumColumns () {
					return num_cols;
				}

				/**
				 *
				 *  Get the object at (x, y) 
				 *
				 *  @param row - row index
				 *  @param col - column index
				 *
				 *  @return Element<E>  at (row, col)
				 */
				Element<E>& getElement(int row, int col) {
					return Array<E>::getElement(row * num_cols + col);
				}

				/**
				 *
				 *  Set the object at index x, y  - 2D array
				 *
				 *  @param row - row index into the array
				 *  @param col - column index into the array
				 *  @param el - Element object
				 *
				 *  @return none
				 */
				void setElement(int row, int col, Element<E> el) {
					setElement(row*num_cols + col, el);
				}

		  struct Bracket_helper {
		    Array2D<E>& arr;
		    int row;
		    Bracket_helper(Array2D<E>& a, int r) :arr(a), row(r) {}

		    E& operator[] (int col) {
		      return arr.getElement(row, col).getValue();
		    }
		  };

		  Bracket_helper operator[] (int index) {
		    return Bracket_helper(*this, index);
		  }

		  struct Bracket_helper_const {
		    Array2D<E> const& arr;
		    int row;
		    Bracket_helper_const(Array2D<E>& a, int r) :arr(a), row(r) {}

		    E const & operator[] (int col) const {
		      return arr.getElement(row, col).getValue();
		    }
		  };

		  Bracket_helper_const operator[] (int index) const {
		    return Bracket_helper_const(*this, index);
		  }		  
		  
		}; // Array2D
    }
}// end namespace bridges

#endif
