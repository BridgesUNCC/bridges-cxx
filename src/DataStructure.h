#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <string> //string
using namespace std;

namespace bridges{
					// string constants  for use in constructing JSON representation of
					// the data structure
const string
    QUOTE = "\"",
    COMMA = ",",
    COLON = ":",
    OPEN_CURLY = "{",
    CLOSE_CURLY = "}",
	OPEN_BOX = "[",
	CLOSE_BOX = "]",
	OPEN_PARENS = "(",
	CLOSE_PARENS = ")";

					// Maximum number of elements that can be visualized 
constexpr int MAX_ELEMENTS_ALLOWED = 5000;

					//Forward Declaration for Befriendment
namespace Bridges{
	class POD;
}
template<typename E> class Element;

/**
 * @brief This is the superclass of all data structure types in BRIDGES
 *
 * This is the superclass of all data structure types in BRIDGES.
 * Both Elements and Graphs inherit from this.
 *
 * @date 6/11/15, Dakota Carmer, Kalpathi Subramanian, 7/10/16
 */
class DataStructure {
	friend class Bridges::POD; //Used for access to getDataStructureRepresentation()

	public:

		/**
		 *	 Virtual Destructor 
		 **/
		virtual ~DataStructure()=default;

		/** 
		 *	@return The string representation of this data structure type 
		 **/
		virtual const string getDStype() const=0;

		/**
		 * Ease of use function for the deletion of an entire datastructure.
		 * Overrides should call delete on itself and each linked data structure
		 *
		 * @warning Only call if all these data structures were all dynamicaly 
		 *	allocated(aka: using new)
		 **/
		virtual void cleanup() {delete this;}

	private:

		/**
		 * Gets the JSON representation of this DataStructure's nodes and links
		 *
		 * @param arr_size The size of the array determined by this
		 * @return A pair holding the nodes and links JSON strings respectively
		 */
		virtual const pair<string,string> getDataStructureRepresentation(const 
								unsigned int& arr_size) const=0;
	protected:

		/** 
		 *	@return to_string of "num" without unnessasary trailing 0s 
		 **/
		static string removeTrailingZeros(const double& num) {
			if (static_cast<int>(num) == num){
				return to_string(static_cast<int>(num));//if integer return as int
			}
            string numRep = to_string(num);
            numRep.erase(numRep.find_last_not_of("0")+1);//removes trailing 0s
            return numRep;
		}
};	//end of DataStructure class

}	//end of bridges namespace

#endif
