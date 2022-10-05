#ifndef TERRAIN_MESH

#define TERRAIN_MESH

#include <string>
#include <vector>
using namespace std;

namespace bridges {
	class TerrainMesh {

		private:

			string name;
  			string type;
  			vector<float> vertices;
  			float colors[3];
  			int rows;
  			int cols;

		public:
  			TerrainMesh(int r, int c, vector<float> elevation_data) {
            	name = "terr";
            	colors[0] = colors[1] = colors[2] = 0;
            	type = "terrain";
				rows = r; cols = c; 
				vertices = elevation_data;
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
	
	  		int getCols() {
	    		return cols;
	  		}
	
	  		void setCols(int c) {
	    		cols = c;
	  		}

	  		vector<float> getVertices() {
	    		return vertices;
	  		}
	
	  		void setVertices(vector<float>& v) {
	    		vertices = v;
	  		}
		};
} //namespace bridges

#endif
