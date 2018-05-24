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

		private:
			void allocateGrid(int rows = 10, int cols = 10) {
						// to do: must check against maxSize!
						// first allocate pointers for dimension 1
				grid = new E*[rows];
				for (int j = 0; j < rows; j++)  {
					grid[j] = new E[cols];	
				}
			}

		protected:
			E  **grid = nullptr;

  			int *gridSize = nullptr; ;
			int maxGridSize[2]  = {480, 640};

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
				setDimensions(10, 10);
				allocateGrid();
			}

			Grid(int *size) {
				setDimensions(size[0], size[1]);
				allocateGrid (size[0], size[1]);
			}

			Grid(int rows, int cols) {
				setDimensions(rows, cols);
				allocateGrid (rows, cols);
			}

			void setDimensions(int rows, int cols) {
				if (!gridSize)
					gridSize = new int[2];
				gridSize[0] = rows; gridSize[1] = cols;
				Bridges::setDimensions (gridSize);
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
