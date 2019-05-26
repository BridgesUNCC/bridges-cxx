#ifndef GRID_H

#define GRID_H

#include "DataStructure.h"
#include <vector>
#include "base64.h"

using namespace std;

namespace bridges {

	/**
	 * @brief This is a class in BRIDGES for representing an (n x n) grid.
	 *
	 * This class will be useful in applications such as image processing, board
	 * games, etc.
	 *
	 * @author David Burlinson, C++ port Kalpathi Subramanian
	 *
	 * @param E
	 **/


	template <typename E>
	class Grid : public  DataStructure {

		private:
			void allocateGrid() {
				int rows = gridSize[0];
				int cols = gridSize[1];
				// to do: must check against maxSize!
				// first allocate pointers for dimension 1
				grid = new E*[rows];
				for (int j = 0; j < rows; j++)  {
					grid[j] = new E[cols];
				}
			}

			void deallocateGrid() {
				if (grid) {
					for (int i = 0; i < gridSize[0]; i++)  {
						delete[] grid[i];
					}
					delete[] grid;
				}
				grid = nullptr;
			}

			void checkRowCol(int row, int col) const {
				if (row < 0 || col < 0 || row >= gridSize[0] || col >= gridSize[1])
					throw "invalid location in Grid";

			}


		protected:
			E  **grid = nullptr;

			int gridSize[2];
			int maxGridSize[2]  = {1080, 1920};

		public:
			virtual const string getDStype() const override {
				return "Grid";
			}

			/**
			 *
			 * Grid constructors
			 *
			 */

			Grid(int rows, int cols) {
				setDimensions(rows, cols);
			}

			Grid()
				: Grid(10, 10) {
			}


			explicit Grid(int *size)
				: Grid(size[0], size[1]) {
			}

			Grid(const Grid& g)
				: Grid(g.gridSize[0], g.gridSize[1]) {
				for (int i = 0; i < gridSize[0]; i++) {
					for (int j = 0; j < gridSize[1]; j++) {
						set (i, j, g.get(i, j));
					}
				}
			}

			virtual ~Grid() {
				deallocateGrid();
			}

			Grid& operator=(const Grid& g) {
				if (this->gridSize[0] != g.gridSize[0] ||
					this->gridSize[1] != g.gridSize[1] ) {
					deallocateGrid();
					setDimensions(g.gridSize[0], g.gridSize[1]);
				}
				for (int i = 0; i < gridSize[0]; i++) {
					for (int j = 0; j < gridSize[1]; j++) {
						set (i, j, g.get(i, j));
					}
				}

				return *this;
			}


			void setDimensions(int rows, int cols) {
				gridSize[0] = rows;
				gridSize[1] = cols;
				if (rows > maxGridSize[0] || cols > maxGridSize[1]) {
					cerr << "Grid Maximum Size (1080 x 1920) exceeded!\n"
						<< "Provided Size: " << rows << " x " << cols
						<< ".  Aborting" << endl << endl;
					exit(-1);
				}
				allocateGrid ();
			}

			int* getDimensions() {
				return gridSize;
			}



			// get the (row, col) element in the grid
			E const& get(int row, int col) const {
				checkRowCol(row, col);

				return grid[row][col];
			}
			// set the (row, col) element in the grid
			void set(int row, int col, E val) {
				checkRowCol(row, col);

				grid[row][col]  = val;
			}

			//This BracketHelperConst is a helper class to get the [] operators to work.
			//It is not intended to be used by bridges users.
			class BracketHelperConst {
					Grid<E> const & gr;
					int row;
				public:
					BracketHelperConst(Grid<E> const & g, int r)
						: gr(g), row(r)
					{}

					E const & operator[] (int col) const {
						return gr.get(row, col);
					}
			};

			///provides the necessary abstraction to do something = grid[x][y];
			BracketHelperConst operator[] (int row) const {
				return BracketHelperConst(*this, row);
			}

			//This BracketHelper is a helper class to get the [] operators to work.
			//It is not intended to be used by bridges users.
			class BracketHelper {
					Grid<E> & gr;
					int row;
				public:
					BracketHelper(Grid<E>  & g, int r)
						: gr(g), row(r)
					{}

					E & operator[] (int col)  {
						gr.checkRowCol(row, col);
						return gr.grid[row][col];
					}
			};

			///provides the necessary abstraction to do grid[x][y] = something;
			BracketHelper operator[] (int row)  {
				return BracketHelper(*this, row);
			}


	}; // end class Grid

} // end - namespace bridges

#endif
