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
    		std::list<Camera> cameras;
            std::list<TerrainMesh> terrains;
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
                terrains.push_back(scene_object);
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
                terrains.remove(scene_object);
            }

    		std::string getDataStructureRepresentation() {
    			std::string scene_json = "";
				float pos[3];
				// add cameras
    			for (auto c: cameras) {
					c.getPosition(pos);
    				scene_json += 
							QUOTE + "camera" + QUOTE + COLON + 
							OPEN_CURLY + 
								QUOTE + c.getType() + QUOTE  + 
								QUOTE + "fov" + QUOTE + COLON + 
								QUOTE + std::to_string(c.getFov()) + QUOTE  + 
								QUOTE + "position" + QUOTE + COLON + 
								OPEN_BOX + 
										std::to_string(pos[0]) + COMMA +
										std::to_string(pos[1]) + COMMA +
										std::to_string(pos[2])  + 
								CLOSE_BOX + 
							CLOSE_CURLY + COMMA; 
    			}
				// remove the last comma
				scene_json.erase(scene_json.size()-1);

				// add lights
				scene_json += QUOTE + "lights" + QUOTE + COLON + 
								OPEN_BOX + CLOSE_BOX;

				// add terrain meshes
				scene_json += 
					QUOTE + "meshes" + COLON + OPEN_BOX;
                for(auto t : terrains) {
					// get vertices of this mesh
					vector<float> verts = t.getVertices();
					scene_json += OPEN_CURLY + 
						QUOTE + "name" + QUOTE + COLON + QUOTE + t.getName() + QUOTE + COMMA +
						QUOTE + "type" + QUOTE + COLON + QUOTE + t.getType()+ QUOTE + COMMA +
						QUOTE + "rows" + QUOTE + COLON + QUOTE + t.getRows()+ QUOTE + COMMA +
						QUOTE + "cols" + QUOTE + COLON + QUOTE + t.getCols()+ QUOTE + COMMA +
						QUOTE + "vertices" + QUOTE + COLON; 

						scene_json += OPEN_BOX;			//vertices start
						// list vertices one row at a time
						int k = 0;
						for (int i = 0; i < t.getRows(); i++) {
							scene_json += OPEN_BOX;	// row start
							for (int j = 0; j < t.getCols(); j++) {
								scene_json += std::to_string(verts[k++])+COMMA;
							}
							scene_json += CLOSE_BOX + COMMA; // row end
						}
						// remove the last comma
						scene_json.erase(scene_json.size()-1);
						scene_json += CLOSE_BOX + CLOSE_CURLY + COMMA;//vertices end
                }
				// remove the last comma
				scene_json.erase(scene_json.size()-1);

				scene_json += CLOSE_BOX;
    		}
    };
}
#endif
