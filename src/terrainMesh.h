#include <string>
#include <vector>
using namespace std;

namespace bridges {
	class terrainMesh {

		struct objectJson {
  			string name;
  			string type;
  			vector<float> vertices;
  			float colors[0];
  			int rows;
  			int cols;
		};

		public:
  			int rows;
  			int cols;
  			vector<float> vertices;
  			objectJson obJ1;

  		terrainMesh(int rows, int cols, vector<float> elevationData) : setRows(rows), setCols(cols), setVertices(elevationData) {
    			string name = "terr";
    			float colors[0] = {};
    			float color[4] = {1.0, 1.0, 1.0, 1.0};
    			float transform[0];
    			obJ1.name = name;
    			obJ1.type = "terrain";
    			obJ1.vertices = vertices;
    			obJ1.colors = colors;
    			obJ1.rows = rows;
    			obJ1.cols = cols;
  		}

  		int getRows() {
    			return rows;
  		}

  		void setRows(int r) {
    			rows = r;
    			obJ1.rows = rows;
  		}

  		int getCols() {
    			return cols;
  		}

  		void setCols(int c) {
    			cols = c;
    			obJ1.cols = cols;
  		}

  		vector<float> getVertices() {
    			return vertices;
  		}

  		void setVertices(vector<float> v) {
    			vertices = v;
    			obJ1.vertices = vertices;
  		}
	};
} //namespace bridges