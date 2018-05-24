#include <string>
using namespace std;

#include "Grid.h"
#include "Color.h"
#include "base64.h"



/**
 * @brief This is a class in BRIDGES for representing an (n x n) grid.
 *
 * @author David Burlinson, C++ port: Kalpathi Subramanian
 * @param 
 **/
namespace bridges {

	class ColorGrid : public Grid<Color> {
  		private: 
			Color baseColor = Color("black");

		public:
			virtual const string getDStype() const override{
				return "ColorGrid";
			}

			/**
			 * ColorGrid constructors
		 	 *
		 	 **/
			ColorGrid () : Grid<Color> (){
				initializeGrid(gridSize[0], gridSize[1], baseColor);
  			}

			/**
		 	 * Grid constructor with size arguments
		 	 *
		 	 * @param rows - int representing the number of rows of the grid
		 	 * @param cols - int representing the number of columns of the grid
		 	 *
		 	 **/
			ColorGrid (int rows, int cols) : Grid<Color> (rows, cols) {
				initializeGrid(rows, cols, baseColor);
			}

			/**
		 	 * Grid constructor with size and color string argument
		 	 *
		 	 * @param rows - int representing the number of rows of the grid
		 	 * @param cols - int representing the number of columns of the grid
		 	 * @param color - Color object
		 	 *
		 	 **/
			ColorGrid (int rows, int cols, Color color)  {

				baseColor = color;
				gridSize = new int[2]; 
				gridSize[0] = rows; gridSize[1] = cols;
				initializeGrid (rows, cols, color);
			}

			void initializeGrid (int rows, int cols, Color col) {
							// fill elements with base color
				for (int i = 0; i < gridSize[0]; i++) 
				for (int j = 0; j < gridSize[1]; j++)
					grid[i][j] = col;
			}
	

		/**
		 * get the JSON representation of the color grid
		 *
		 * @return the JSON representation of the color grid
		 **/
		virtual const pair<string, string> getDataStructureRepresentation () 
							const override {
				// Maintain a bytebuffer for the byte representations of each grid color

			BYTE *byte_buf = new BYTE[4 * gridSize[0] * gridSize[1]];

			int k = 0;
			for (int i = 0; i < gridSize[0]; i++) {
				for (int j = 0; j < gridSize[1]; j++) {
					byte_buf[k++] = grid[i][j].getRed();
					byte_buf[k++] = grid[i][j].getGreen();
					byte_buf[k++] = grid[i][j].getBlue();
					byte_buf[k++] = grid[i][j].getAlpha();
          		}
        	}
						// get the base64 representation of the color array
			string base64_grid_str = 
					base64::base64_encode (byte_buf, 4*gridSize[0]*gridSize[1]);

						// Add the byte representation of the grid
			string json_str = QUOTE + "nodes" + QUOTE + COLON +
				OPEN_BOX  + 
						QUOTE + base64_grid_str + QUOTE + 
				CLOSE_BOX + COMMA;

						// Specify the dimensions of the grid
    		json_str += QUOTE + "dimensions" + QUOTE + COLON +
				OPEN_BOX + 
						to_string(gridSize[0]) + "," + to_string(gridSize[1]) + 
				CLOSE_BOX + CLOSE_CURLY;

			return pair<string, string> (json_str, "");
  		}
	};
} // end namespace bridges
