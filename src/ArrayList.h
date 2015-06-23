#include  <vector>

/**
 *
 * The ArrayList class can be used to represent arrays of type Element<E> in
 * in BRIDGES. The class is simply a wrapper  around the C++ STL  vector class
 * and, thus, derives all its operations from the super class.
 * BRIDGES provides methods to visualize arrays and its contents. The 
 * contents of the array element can be held in the generic parameter E.
 *
 * Author: Kalpathi Subramanian, 6/22/15
 *
 * @param Element<E>
 *
 */

using namespace std;

#include "Element.h"


///
/// The declaration below is a convenient means to alias the STL vector
/// and conform to BRIDGES type hierarchy
///
/// To use this class you can declare an integer array list as follows:
///
///  ArrayList<Element<int>> int_array
///
template<typename E> using ArrayList = vector<Element<E>>;

