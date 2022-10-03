#ifdef SCENE_H

#define SCENE_H

#include <string> 
#include <unordered_list>

#include "Camera.h"

namespace bridges {
    class Scene {

    	private:
    		std::unordered_list<> scene_list;
    		Camera  camera;

    	public:
    		Scene(std::string type, int fov, float position[3]) {
    			scene_list.clear();
                camera.setType(type);
                camera.setFov(fov);
                camera.setPosition(position);
    		}

    		void add (??? scene_object) {
    			scene_list[scene_object.getName()] = scene_object;
    		}

    		?? get (std::string scene_object_name) {
    			return scene_list[scene_object.scene_object_name];
    		}

    		Camera getCamera() {
    			return camera;
    		}

    		void setCamera(Camera& cam) {
    			camera = cam;
    		}

            void remove(??? scene_object) {
                std::remove(std::begin(scene_list), std::end(scene_list), scene_object);
            }

    		std::string getDataStructureRepresentation() {
    			std::string scene_json;
    			for (auto i: scene_list) {
    				scene_json
    			}
    		}
    };
}


#endif
