#include <string>
using namespace std;

namespace bridges {
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
  			objectJson obJ1;

  		camera(string type, int fov, float position[3]) : setType(type), setFov(fov), setPosition(position) {
			obJ1.type = type;
			obJ1.fov = for;
			obJ1.position = position;    
  		}

  		def getType(){
			return type;
  		}
  
  		def setType(string t) {
			type = t;
  		}
  
  		def getFov(){
			return fov;
  		}

  		def setFov(int f){
			fov = f;
  		}

  		def setPosition(float p[3]){
			position = p;
  		}

  		def pushRepresentation(){
			return obJ1;
  		}
	};
} //namespace bridges
