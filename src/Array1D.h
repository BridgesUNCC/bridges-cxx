#ifndef ARRAY_1D_H
#define ARRAY_1D_H

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


#include "Array.h"
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
		class Array1D : public Array<E> {

			private:
				int size;

			public:
				Array1D() {}

				~Array1D() {}

				/// builds an array given the dimensions
				///@param num_dims number of dimension
				///@param dims size of each dimension

				Array1D(int sz) {
					int dim[] = {sz, 1, 1};
					this->setSize(1, dim);
				}

				Element<E>& operator[](int indx) {
					return  Array<E>::getElement(indx);
				}
		  Element<E> const & operator[](int indx) const {
		    return  Array<E>::getElement(indx);
		  }

		}; // Array1D
	}
}// end namespace bridges

#endif
