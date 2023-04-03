#ifndef TERRAIN_MESH

#define TERRAIN_MESH

#include <string>
#include <vector>
#include "Mesh.h"
using namespace std;

namespace bridges {
	class TerrainMesh : public Mesh{

		private:
			string name;
  			string type;
  			//vector<vector<float>> vertices;
  			//vector<float> colors;
  			float** heights = nullptr;
  			float*** colors = nullptr;
  			int rows;
  			int cols;

  			//TODO:: allocation and dealocation for the color arrays
  			void allocateHeightArray(vector<float> elevation_data){
  				heights = new float*[rows];
  				for(int i = 0; i < rows; i++){
  					heights[i] = new float[cols];
  				}
  				for(int j = 0; j < rows; j++){
  					for(int k = 0; k < cols; k++){
  						heights[j][k] = elevation_data[k+(j*cols)];
  					}
  				}
  			}

  			//3D array to hold the color information for a specific height position.
  			//row, col, then 3 positions for r,g,b values
  			void allocateColorArray(){
  				colors = new float**[rows];
  				for(int i = 0; i < rows; i++){
  					colors[i] = new float*[cols];
  					for(int j = 0; j < cols; j++){
  						colors[i][j] = new float[3];
  						for(int k = 0; k < 3; k++){
  							colors[i][j][k] = 0.5;
  						}
  					}
  				}
  			}

  			

		public:
			TerrainMesh() : Mesh(){}
  			TerrainMesh(string id, int r, int c, vector<float> elevation_data) : Mesh("terrain", id) {
            	name = id;
            	type = "terrain";
				rows = r; cols = c; 
				allocateHeightArray(elevation_data);
				allocateColorArray();
				// for(int i = 0; i < rows; i++){
				// 	vector<float> temp;
				// 	for(int j = 0; j < cols; j++){
				// 		temp.push_back(elevation_data[j+(i*cols)]);
				// 	}
				// 	vertices.push_back(temp);
				// }

				// set color for each vertex
				// for (int i = 0; i < rows; i++)
				// for (int j = 0; j < cols; j++) 
				// for (int k = 0; k < 4; k++) 
				// 	colors.push_back(1.);
  			}

		
			void setName (string n) {
				name = n;
			}
	
			string getName () {
				return name;
			}
	
			void setType (string t) {
				type = t;
			}
	
			string getType () {
				return type;
			}
	
	  		int getRows() {
	    		return rows;
	  		}
	
	  		void setRows(int r) {
	    		rows = r;
	  		}

	  		int getCols(){
	  			return cols;
	  		}
			
	  		float*** getColors() override{
	    		return colors;
	  		}


	  		float** getVertices() override{
	    		return heights;
	  		}
	
	  		void setHeights(float** v) {
	    		heights = v;

	  		}

	  		void setVertices(int x, int y, float value) override{
	  			heights[x][y] = value;
	  			updatedThisFrame = true;
	  		}

	  		void deallocateHeightArray(){
  				if (heights) {
					for (int i = 0; i < rows; i++)  {
						delete[] heights[i];
					}
					delete[] heights;
				}
				heights = nullptr;
  			}

  			void deallocateColorArray(){
  				if(colors){
  					for (int i = 0; i < rows; i++){
  						for(int j = 0; j < cols; j++){
  							delete[] colors[i][j];
  						}
  						delete[] colors[i];
  					}
  				}	delete[] colors;
  				colors = nullptr;
  			}

  			// ~TerrainMesh(){
  			// 	deallocateColorArray();
  			// 	deallocateHeightArray();
  			// }

  			const std::string getDataStructureRepresentation() const override{
  				std::string terrain_json = 
  				// 		QUOTE + "name" + QUOTE + COLON + 
						// QUOTE + name + QUOTE  + COMMA +
						// QUOTE + "type" + QUOTE + COLON + QUOTE + meshType + QUOTE + COMMA +
  						QUOTE + "rows" + QUOTE + COLON + QUOTE + std::to_string(rows) + QUOTE + COMMA +
						QUOTE + "cols" + QUOTE + COLON + QUOTE + std::to_string(cols)+ QUOTE + COMMA +
						// terrain vertices
						QUOTE + "vertices" + QUOTE + COLON; 

						terrain_json += OPEN_BOX;			//vertices start
						// list vertices one row at a time
						int k = 0;
						for (int i = 0; i < rows; i++) {
							terrain_json += OPEN_BOX;	// row start
							for (int j = 0; j < cols; j++) {
								terrain_json += std::to_string(heights[i][j])+COMMA;
							}
							// remove the last comma
							terrain_json.erase(terrain_json.size()-1);
							terrain_json += CLOSE_BOX + COMMA; // row end
						}
						// remove the last comma
						terrain_json.erase(terrain_json.size()-1);
						terrain_json += CLOSE_BOX + COMMA;	//end of vertices

						terrain_json += QUOTE + "colors" + QUOTE + COLON; 
						terrain_json += OPEN_BOX;				//colors start

						// list colors one row at a time
						k = 0;
						for (int i = 0; i < rows; i++) {
							terrain_json += OPEN_BOX;	// row start
							for (int j = 0; j < cols; j++) {
								string col_str = std::to_string(colors[i][j][k])
									+ COMMA + std::to_string(colors[i][j][k+1])
									+ COMMA + std::to_string(colors[i][j][k+2])
									+ COMMA + std::to_string(colors[i][j][k+3]);
								terrain_json += OPEN_BOX + col_str + CLOSE_BOX +
										COMMA;
								k += 4;
							}
							// remove the last comma
							terrain_json.erase(terrain_json.size()-1);
							terrain_json += CLOSE_BOX + COMMA; // row (colors) end
							 
						}
						terrain_json.erase(terrain_json.size()-1);
						terrain_json += CLOSE_BOX + CLOSE_CURLY + COMMA;
						return terrain_json;
	
  			}

		};
} //namespace bridges

#endif
