
#include <string>
using namespace std;

#ifndef COLOR_GRID_H
#define COLOR_GRID_H 1

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
			int debug() const {
				return 0;
			}
			Color baseColor = Color("black");

			/**
			 * initializes the grid with the passed color
			 *
			 * @param color - Color object
			 *
			 **/
			void initializeGrid (Color col) {
				// fill elements with base color
				for (int i = 0; i < gridSize[0]; i++)
					for (int j = 0; j < gridSize[1]; j++)
						grid[i][j] = col;
			}

		public:
			virtual const string getDStype() const override {
				return "ColorGrid";
			}

			/**
			 * ColorGrid constructors
			 *
			 **/
			ColorGrid () : Grid<Color> () {
				initializeGrid(baseColor);
			}

			/**
			 * Grid constructor with size arguments
			 *
			 * @param rows - int representing the number of rows of the grid
			 * @param cols - int representing the number of columns of the grid
			 *
			 **/
			ColorGrid (int rows, int cols) : Grid<Color> (rows, cols) {
				initializeGrid(baseColor);
			}

			/**
			 * Grid constructor with size and color string argument
			 *
			 * @param rows - int representing the number of rows of the grid
			 * @param cols - int representing the number of columns of the grid
			 * @param color - Color object
			 *
			 **/
			ColorGrid (int rows, int cols, Color color) : Grid<Color> (rows, cols) {
				baseColor = color;
				initializeGrid(color);
			}


			/**
			 * Copy Constructor
			 **/
			ColorGrid (const ColorGrid& cg)
				: Grid<Color> (cg.gridSize[0], cg.gridSize[1]),
				  baseColor(cg.baseColor) {
				for (int i = 0; i < gridSize[0]; i++) {
					for (int j = 0; j < gridSize[1]; j++) {
						set (i, j, cg.get(i, j));
					}
				}
			}
		private:

			/**
			 * returns a vector of BYTEs that is a RAW encoding of the ColorGrid
			 */
			std::vector<BYTE> getRAWencoding() const {
				std::vector<BYTE> byte_buf(4 * gridSize[0] * gridSize[1]);

				int k = 0;
				for (int i = 0; i < gridSize[0]; i++) {
					for (int j = 0; j < gridSize[1]; j++) {
						byte_buf[k++] = grid[i][j].getRed();
						byte_buf[k++] = grid[i][j].getGreen();
						byte_buf[k++] = grid[i][j].getBlue();
						byte_buf[k++] = grid[i][j].getAlpha();
					}
				}
				return byte_buf;

			}

			/**
			 * returns a vector of BYTEs that is an RLE encoding of the ColorGrid
			 */
			std::vector<BYTE> getRLEencoding() const {
				std::vector<BYTE> vec;

				int count = 0;
				BYTE r, g, b, a;

				auto commit = [&]() {
					if (count == 0)
						return;

					if (debug())
						std::cerr << "RLEencodingstream: " << (int)count << " " << (int)r << " " << (int)g << " " << (int)b << " " << (int)a << std::endl;

					BYTE repeat = (BYTE) (count - 1);

					vec.push_back(repeat);
					vec.push_back(r);
					vec.push_back(g);
					vec.push_back(b);
					vec.push_back(a);

					count = 0;
				};

				int pos = 0;
				while (pos < gridSize[0]*gridSize[1]) {

					int posX = pos / gridSize[0];
					int posY = pos % gridSize[1];
					BYTE lr = grid[posX][posY].getRed();
					BYTE lg = grid[posX][posY].getGreen();
					BYTE lb = grid[posX][posY].getBlue();
					BYTE la = grid[posX][posY].getAlpha();

					if (count == 0) {
						count = 1;
						r = lr;
						g = lg;
						b = lb;
						a = la;
					}
					else {
						if (r == lr &&
							g == lg &&
							b == lb &&
							a == la) { //same color than previous pixel
							count++;
						}
						else { //different color than previous pixel
							commit();
							count = 1;
							r = lr;
							g = lg;
							b = lb;
							a = la;
						}
					}

					if (count == 255) {
						commit();
					}

					pos++;
				}
				//there could be something uncommitted at this point.
				commit();

				if (debug())
					std::cerr << "RLE length: " << vec.size()
						<< " raw length: " << gridSize[0]*gridSize[1] * 4
						<< " Compression rate:" << (float)(vec.size()) / (gridSize[0]*gridSize[1] * 4)
						<< std::endl;
				return vec;
			}

			//public:
			/**
			 * get the JSON representation of the color grid
			 *
			 * @return the JSON representation of the color grid
			 **/
			virtual const string getDataStructureRepresentation () const override {

				// Maintain a bytebuffer for the byte representations of each grid color
				std::vector<BYTE> byte_buf = getRLEencoding();
				std::string encoding = "RLE";
				if (1 || (int)(byte_buf.size()) > gridSize[0]*gridSize[1] * 4) {
					encoding = "RAW";
					byte_buf = getRAWencoding();
					if (debug())
						std::cerr << "encoding ColorGrid as RAW" << std::endl;
				}
				else {
					if (debug())
						std::cerr << "encoding ColorGrid as RLE" << std::endl;
				}

				// set the grid dimensions for the visualizer
				// get the base64 representation of the color array
				string grid_json  =
					QUOTE + "encoding" + QUOTE + COLON + QUOTE + encoding + QUOTE + COMMA +
					QUOTE + "dimensions" + QUOTE + COLON +
					OPEN_BOX +
					to_string(gridSize[0]) + COMMA + to_string(gridSize[1]) +
					CLOSE_BOX + COMMA +

					QUOTE + "nodes" + QUOTE + COLON +
					OPEN_BOX + QUOTE +
					base64::encode (&(byte_buf[0]), byte_buf.size()) +
					QUOTE + CLOSE_BOX +
					CLOSE_CURLY;


				return grid_json;
			}


	};
} // end namespace bridges

#endif
