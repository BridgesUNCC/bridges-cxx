
#ifndef ELEVATION_DATA

#define ELEVATION_DATA

namespace bridges {

	namespace dataset {

		using namespace bridges::datastructure;
		/**
		 * @brief  Class that hold Open Street Map vertices
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

				ElevationData() {
        			data = nullptr;
					cols = rows = 0;
					xll = yll = 0.;
					cellSize = 0;
					maxVal = 0;
				}
				~ElevationData() {
					delete [] data;
				}

				ElevationData(int c, int r) {
					cols = c; rows = r;
					data = new int[cols*rows];	
					cols = rows = 0;
					xll = yll = 0.;
					cellSize = 0;
					maxVal = 0;
				}

				ElevationData (int cols, int rows, int xll, 
							int yll, int cellsize, int maxVal){
					data = new int[cols*rows];
					setData(data);
					setCols(cols);
					setRows(rows);
					setxll(xll);
					setyll(yll);
					setCellSize (cellsize);
					setMaxVal(maxVal);
    			}

				int *getData(){
					return data;
				}

				void setData(int *data){
					data = data;
				}

				int getCols(){
					return cols;
				}

				int getVal (int r, int c) {
					return data[r*cols+c];
				}

				void setVal (int r, int c, int val) {
					data[r*cols + c] = val;	
				}

				void setCols(int cols){
					cols = cols;
				}

				int getRows(){
					return rows;
				}

				void setRows(int rows){
					rows = rows;
				}

				int getxll(){
					return xll;
				}

				void setxll(int x_ll){
					xll = x_ll;
				}

				int getyll(){
					return yll;
				}
    
				void setyll(int y_ll){
					yll = y_ll;
				}

				int getCellSize(){
					return cellSize;
				}

				void setCellSize(int cell_size){
					cellSize = cell_size;
				}

				int getMaxVal(){
					return maxVal;
				}

				void setMaxVal(int max_val){
					maxVal = max_val;
				}
		};
	}
}

#endif
