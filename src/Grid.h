/**
 * @brief This is a class in BRIDGES for representing an (n x n) grid.
 * @author David Burlinson, C++ port Kalpathi Subramanian
 * @param
**/

#include "DataStructure.h"
#include <vector>
#include "base64.h"

using namespace std;

namespace bridges {

	template <typename E> 
	class Grid : public  DataStructure {
		protected:
			E  **grid = nullptr;

  			int *gridSize = nullptr;
			int *maxGridSize  = nullptr;

		public:
			virtual const string getDStype() const override {
				return "Grid";
			}

			/**
	 		 *
			 * Grid constructors
			 *
			 */
			Grid() {
				gridSize = new int[2];
				gridSize[0] = gridSize[1] = 10;
				maxGridSize = new int[2];	
				maxGridSize[0] = 480; maxGridSize[1] = 640;
				allocateGrid(gridSize[0], gridSize[1]);
			}

			Grid(int rows, int cols) {
				gridSize[0] = rows; gridSize[1] = cols;
				allocateGrid (rows, cols);
			}

			void allocateGrid(int rows, int cols) {
						// to do: must check against maxSize!
						// first allocate pointers for dimension 1
					grid = new E*[rows];
					for (int j = 0; j < cols; j++) 
						grid[j] = new E[cols];	
			}
	
			int* getDimensions() {
				return gridSize;
			}
	
					// get the (row, col) element in the grid
			E get(int row, int col) {
					// to do! Need to check row col against bounds!
				return grid[row][col];
			}
					// set the (row, col) element in the grid
			void set(int row, int col, E val) {
					// to do! Need to check row col against bounds!
				grid[row][col]  = val;
			}

	}; // end class Grid

} // end - namespace bridges
