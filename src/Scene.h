#ifndef SCENE_H

#define SCENE_H

#include <string> 
#include <list>

#include "Camera.h"
#include "TerrainMesh.h"
#include "DataStructure.h"

namespace bridges  {
    class Scene: public DataStructure {

    	private:
            std::list<TerrainMesh> terrains;
    		Camera  camera;

    	public:
			Scene() {}
    		Scene(std::string type, int fov, float position[3]) {
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
    		void setCamera (Camera& c) {
    			camera = c;
    		}

			/** 
			 * 	@brief get the current camera
			 */
			Camera getCamera () {
				return camera;
			}

            /**
             * @brief add function for TerrainMesh objects
             */
            void add(TerrainMesh scene_object){
                terrains.push_back(scene_object);
            }

            /**
             * @brief remove function for TerrainMesh objects
             */
//			void remove(TerrainMesh scene_object) {
//				terrains.remove(scene_object);
// 			}

			virtual const string getDataStructureRepresentation() const 
											override {

    			std::string scene_json = "";
				float pos[3];
				// add camera
				camera.getPosition(pos);
    			scene_json += 
						QUOTE + "camera" + QUOTE + COLON + 
						OPEN_CURLY + 
							QUOTE + "name" + QUOTE  +  COLON + 
							QUOTE + camera.getType() + QUOTE  + COMMA +
							QUOTE + "fov" + QUOTE + COLON + 
							QUOTE + std::to_string(camera.getFov()) + QUOTE + COMMA +  
							QUOTE + "position" + QUOTE + COLON + 
							OPEN_BOX + 
								std::to_string(pos[0]) + COMMA +
								std::to_string(pos[1]) + COMMA +
								std::to_string(pos[2])  + 
							CLOSE_BOX + 
						CLOSE_CURLY + COMMA; 

				// add lights
				scene_json += QUOTE + "lights" + QUOTE + COLON + 
								OPEN_BOX + CLOSE_BOX + COMMA;

				// add terrain meshes
				scene_json += 
					QUOTE + "meshes" + QUOTE + COLON + OPEN_BOX;
                for(auto t : terrains) {
					// get vertices of this mesh
					vector<float> verts = t.getVertices();
					scene_json += OPEN_CURLY + 
						QUOTE + "name" + QUOTE + COLON + QUOTE + t.getName() + QUOTE + COMMA +
						QUOTE + "type" + QUOTE + COLON + QUOTE + t.getType()+ QUOTE + COMMA +
						QUOTE + "rows" + QUOTE + COLON + QUOTE + std::to_string(t.getRows()) + QUOTE + COMMA +
						QUOTE + "cols" + QUOTE + COLON + QUOTE + std::to_string(t.getCols())+ QUOTE + COMMA +
						QUOTE + "vertices" + QUOTE + COLON; 

						scene_json += OPEN_BOX;			//vertices start
						// list vertices one row at a time
						int k = 0;
						for (int i = 0; i < t.getRows(); i++) {
							scene_json += OPEN_BOX;	// row start
							for (int j = 0; j < t.getCols(); j++) {
								scene_json += std::to_string(verts[k++])+COMMA;
							}
							// remove the last comma
							scene_json.erase(scene_json.size()-1);
							scene_json += CLOSE_BOX + COMMA; // row end
						}
						// remove the last comma
						scene_json.erase(scene_json.size()-1);
						scene_json += CLOSE_BOX + CLOSE_CURLY + CLOSE_BOX;//vertices end
                }
				// remove the last comma
				scene_json.erase(scene_json.size()-1);

				scene_json += CLOSE_BOX + CLOSE_CURLY;

				return scene_json;
    		}
    };
}
#endif
