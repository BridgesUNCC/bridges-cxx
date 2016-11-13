#ifndef ARRAY_H 
#define ARRAY_H 

#include "Element.h"

namespace bridges{

template <typename E>
class Array : public DataStructure {

	private:
		Element<E> *array_data;
		int num_dims;
		int dims[3];
		int size;

	public:
		Array() {
			array_data = NULL;
			num_dims = 1;
			dims[0] = dims[1] = dims[2] = 0;
			size = 0;
		}

		~Array(){
			delete [] array_data;
		}

		Array(int num_dims, int *dims) {
			setNumDimensions(num_dims);
			setDimensions(dims);
		}

		void setNumDimensions(int nd) {
			if (nd > 3) {
				cout << "Only 1D, 2D and 3D arrays supported." << endl;
				exit(-1);
			}
			num_dims = nd;
		}
		void setDimensions(int *dim) {
			int sz = 1;
			for (int k = 0; k < num_dims; k++) {
				dims[k] = dim[k];
				sz *= dim[k];
			}
							// first check the dimensions are all positive
			if (sz < 0) {
				cout << "Negative size in dimension encountered" << endl;
				exit(-1);
			}
			size = sz;
							// allocate space for the array 
			array_data = new Element<E>[size];	
		}

		Element<E>& getValue(int indx) {
			return array_data[indx];
		}

		void setValue(int indx, Element<E> el) {
			array_data[indx] = el;
		}

		Element<E>& getValue(int x_indx, int y_indx) {
				return array_data[x_indx + y_indx*dims[0]];
		}

		void setValue(int x_indx, int y_indx, Element<E> el) {
			array_data[x_indx + y_indx*dims[0]] = el;
		}

		
		Element<E>& getValue(int x_indx, int y_indx, int z_indx) {
				return array_data[x_indx + y_indx*dims[0] + 
								z_indx*dims[1]*dims[0]];
		}

		void setValue(int x_indx, int y_indx, int z_indx, Element<E> el) {
			array_data[x_indx + y_indx*dims[0] + z_indx*dims[0]*dims[1]] = el;
		}

		virtual const string getDStype() const override {
			string s = "1D_Array";
			if (num_dims == 1) 
				return "2D_Array";
			else if (num_dims == 2) 
				return "3D_Array";

			return s;
		}

		virtual const pair<string,string> getDataStructureRepresentation(const 
					unsigned int& arr_size) const override final {
		}
};

}// end namespace bridges


#endif
