#ifndef ARRAY_ELEMENT_H

#define  ARRAY_ELEMENT_H

/**
 * 
 * @author Kalpathi Subramanian, 6/19/15
 *
 * @param <E>
 *
 * @Description This class can be used to create arrays with generic types
 * as follows: 
 *
 * ArrayElement<E>[] myArray = 
 * 		where E is any generic type
 */
template <typename E> class ArrayOfElements{
	private:
		string label;
		vector<E> v;

	public:
	
		/** Construct an array labeled "label" and holding elements 
		 * of "type E". 	 
	 	 * @param label the label of ArrayElement that shows up on the 
		 * Bridges visualization
	 	 * @param type the type of Element this array should be holding
	 	 **/

		ArrayOfElements(){
			label = "";
			v.reserve(100);

		ArrayOfElements(string l){
			v.reserve(100);
			label = l;
		}
		ArrayOfElements(string labl, int size){
			if (size > 0)
				v.reserve(size);
			label = l;
		}

		E& operator [] (const int indx) {
			return  v[indx];
		}
	
	
};

#endif
