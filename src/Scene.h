#ifdef SCENE_H

#define SCENE_H

#include <string> 
#include <list>

#include "Camera.h"
#include "TerrainMesh.h"
#include "DataStructure.h"

namespace bridges : public DataStructure {
    class Scene {

    	private:
    		std::list<Camera> cameraSceneList;
            std::list<TerrainMesh> terrainSceneList;
    		Camera  camera;

    	public:
    		Scene(std::string type, int fov, float position[3]) {
    			scene_list.clear();
                camera.setType(type);
                camera.setFov(fov);
                camera.setPosition(position);
    		}

			/** 
			 * @brief Get data structure type
			 */
			virtual const string getDStype() const override {
				return "Scene";
			}

            /**
             * @brief add function for Camera objects
             */
    		void add (Camera scene_object) {
    			cameraSceneList.push_back(scene_object);
    		}

            /**
             * @brief add function for TerrainMesh objects
             */
            void add(TerrainMesh scene_object){
                terrainSceneList.push_back(scene_object);
            }

    		Camera getCamera() {
    			return camera;
    		}

    		void setCamera(Camera& cam) {
    			camera = cam;
    		}

            /**
             * @brief remove function for Camera objects
             */
            void remove(Camera scene_object) {
                cameraSceneList.remove(scene_object);
            }

            /**
             * @brief remove function for TerrainMesh objects
             */
            void remove(TerrainMesh scene_object) {
                terrainSceneList.remove(scene_object);
            }

    		std::string getDataStructureRepresentation() {
    			std::string scene_json;
    			for (auto i: cameraSceneList) {
    				scene_json += i;
    			}

                for(auto i: terrainSceneList) {
                    scene_json += i;
                }
    		}
    };
}


#endif
