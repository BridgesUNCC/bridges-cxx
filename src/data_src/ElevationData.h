
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
				int cellsize;

				// maximum value in the data set
				int maxVal;

			public:

				ElevationData() {
        			data = null;
					cols = rows = 0;
					xll = yll = 0;
					cellsize = 0;
					maxVal = 0;
				}
				~ElevationData() {
					delete [] data;
				}

				ElevationData (int *data, int cols, int rows, int xll, 
							int yll, int cellsize, int maxVal){
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

				setData(int *data){
					data = data;
				}

				int getCols(){
					return cols;
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

				int setxll(int xll){
					xll = xll;
				}

				int getyll(){
					return yll;
				}
    
				void setyll(int yll){
					yll = yll;
				}

				int getCellSize(){
					return cellsize;
				}

				void setCellSize(int cellsize){
					cellsize = cellsize;
				}

				int getMaxVal(){
					return maxVal;
				}

				void setMaxVal(int maxVal){
					maxVal = maxVal;
				}
		};
	}
}

#endif
