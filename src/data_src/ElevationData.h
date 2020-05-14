
#ifndef ELEVATION_DATA

#define ELEVATION_DATA

namespace bridges {

	namespace dataset {

		/**
		 * @brief  Class that hold elevation data
		 *
		 * Class that holds Elevation data, from  ??
		 *
		 * @author Kalpathi Subramanian
		 *
		 * @date 3/28/20
		 */


		class ElevationData {
			private:

				// elevation data - sequence of integers
				int *data;

				// data dimensions
				int rows, cols;

				// origin
				int xll, yll;
				int cellSize;

				// maximum value in the data set
				int maxVal;

			public:

				/**
				 *
				 * constructors
				 *
				 */
				ElevationData() {
					data = nullptr;
					cols = rows = 0;
					xll = yll = 0.;
					cellSize = 0;
					maxVal = 0;
				}

				ElevationData(int r, int c) {
					rows = r;
					cols = c;
					data = new int[cols * rows];
					xll = yll = 0.;
					cellSize = 0;
					maxVal = 0;
				}


				ElevationData (int cols, int rows, int xll,
					int yll, int cellsize, int maxVal) {
					data = new int[cols * rows];
					setCols(cols);
					setRows(rows);
					setxll(xll);
					setyll(yll);
					setCellSize (cellsize);
					setMaxVal(maxVal);
				}

				/**
				 * destructor
				 */
				~ElevationData() {
					delete [] data;
				}

				/**
				 *
				 * setters, getters
				 *
				 */

				int getCols() {
					return cols;
				}

				void setCols(int c) {
					cols = c;
				}

				/**
				 *
				 *	get elevation value
				 *
				 */
				int getVal (int r, int c) {
					return data[r * cols + c];
				}

				/**
				 *
				 *	set elevation value
				 *
				 */
				void setVal (int r, int c, int val) {
					data[r * cols + c] = val;
				}


				/**
				 *
				 *	get num rows of data
				 *
				 */
				int getRows() {
					return rows;
				}

				/**
				 *
				 *	set num rows of data
				 *
				 */
				void setRows(int r) {
					rows = r;
				}

				/**
				 *
				 *	get lower left corner of data (X)
				 *
				 */
				int getxll() {
					return xll;
				}

				/**
				 *
				 *	set lower left corner of data (X)
				 *
				 */
				void setxll(int x_ll) {
					xll = x_ll;
				}

				/**
				 *
				 *	get lower left corner of data (Y)
				 *
				 */
				int getyll() {
					return yll;
				}

				/**
				 *
				 *	set lower left corner of data (Y)
				 *
				 */
				void setyll(int y_ll) {
					yll = y_ll;
				}

				/**
				 *
				 *	get  data resolution
				 *
				 */
				int getCellSize() {
					return cellSize;
				}

				/**
				 *
				 *	set  data resolution
				 *
				 */
				void setCellSize(int cell_size) {
					cellSize = cell_size;
				}

				/**
				 *
				 *	get max elevation of data
				 *
				 */
				int getMaxVal() {
					return maxVal;
				}

				/**
				 *
				 *	set max elevation of data
				 *
				 */
				void setMaxVal(int max_val) {
					maxVal = max_val;
				}
		};
	}
}

#endif
