#include <string>
using namespace std;

class camera {

struct objectJson {
  string type;
  int fov;
  float position[3];
};

public:
  string type;
  int fov;
  float position[3];

  camera(string type, int fov, float position[3]) : type(type), fov(fov) {
    //TODO
  }
};
