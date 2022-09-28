#include <vector>
#include <string>
using namespace std;

class Mesh {

struct objectJson {
  string type;
  vector<float> vertices;
};

public: 
  vector<float> vertices;
  Mesh(vector<float> vertices) : vertices(vertices){
    float color[4] = {1.0, 1.0, 0.5, 1.0};
    float transform[0] = {};
    objectJson obJ1;
    obJ1.type = "custom mesh";
    obJ1.vertices = vertices;
  }

//TODO FIGURE OUT what scene_json equivalent is
int pushRepresentation()
};

