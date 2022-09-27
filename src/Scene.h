#ifdef SCENE_H

#define SCENE_H

#include <string> 
#include <unordered_list>

#include "Camera.h"

class Scene {

	private:
		std::unordered_list<> scene_list;
		Camera  camera;

	public:
		Scene(Camera& cam) {
			scene_list.clear();
			camera.props['type']  = cam.props['type'];
			camera.props['fov']  = cam.props['fov'];
			camera.props['position']  = cam.props['position'];
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
		Camera setCamera(Camera& cam) {
			camera = cam;
		}

		std::string getDataStructureRepresentation() {
			std::string scene_json;
			for (auto i: scene_list) {
				scene_json 
			}
		}

		
};

#endif
