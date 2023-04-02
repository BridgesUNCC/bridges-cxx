#ifndef SCENE_H

#define SCENE_H

#include <string> 
#include <list>
#include <unordered_map>

#include "Camera.h"
//#include "TerrainMesh.h"
#include "DataStructure.h"
#include "SceneObject.h"

namespace bridges  {
    class Scene: public DataStructure {

    	private:
            //std::unordered_map<string, TerrainMesh> terrains;
            std::unordered_map<std::string, SceneObject*> entities;
    		Camera  camera;

    	public:
			Scene() {
				float pos[] = {0., 0., 0.};
				Scene("fps", 90, pos);
			}

    		Scene(std::string type, int fov, float position[3]) {
                camera.setType(type);
                camera.setFov(fov);
                camera.setPosition(position);
    		}

			/** 
			 * @brief Get data structure type
			 */
			const string getDStype() const override {
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
            // void add(TerrainMesh &terrain){
            //     terrains[terrain.getName()] = terrain;
            // }


            void add(SceneObject *obj){
            	entities[obj->getName()] = obj;
            }

            SceneObject* get(std::string objName){
            	return entities[objName];
            }

            void printScene(){
            	for(auto obj : entities){
            		cout << obj.second->getColors() << endl;
            	}
            }

            /**
             * @brief add function for TerrainMesh objects
             */
            // TerrainMesh& get(string mesh_name){
            //     return terrains[mesh_name];
            // }

            ~Scene(){
            	// for(auto t : terrains){
            	// 	t.second.deallocateHeightArray();
            	// }
            }

            /**
             * @brief remove function for TerrainMesh objects
             */
//			void remove(TerrainMesh scene_object) {
//				terrains.remove(scene_object);
// 			}

			virtual const string getDataStructureRepresentation() const 
											override {

				bool objectUpdated = false;
				//Have all scene objects construct their own representation and combine here								
    			std::string scene_json = OPEN_CURLY;
    			scene_json += QUOTE + "scene_objects" + QUOTE + COLON + OPEN_BOX;
    			for(auto o : entities){
    				if(o.second->updatedThisFrame){
    					scene_json += OPEN_CURLY;
    					objectUpdated = true;
    					scene_json += o.second->getDataStructureRepresentation();
    					o.second->updatedThisFrame = false;
    				}
    				
    			}
    			//check if an object was updated. if so, delete last comma from JSON
    			if(objectUpdated){scene_json.erase(scene_json.size()-1);}
    			scene_json += CLOSE_BOX; 
				// float pos[3];
				// // add camera
				// camera.getPosition(pos);
    // 			scene_json += 
				// 		QUOTE + "camera" + QUOTE + COLON + 
				// 		OPEN_CURLY + 
				// 			QUOTE + "name" + QUOTE  +  COLON + 
				// 			QUOTE + camera.getType() + QUOTE  + COMMA +
				// 			QUOTE + "fov" + QUOTE + COLON + 
				// 			QUOTE + std::to_string(camera.getFov()) + QUOTE + COMMA +  
				// 			QUOTE + "position" + QUOTE + COLON + 
				// 			OPEN_BOX + 
				// 				std::to_string(pos[0]) + COMMA +
				// 				std::to_string(pos[1]) + COMMA +
				// 				std::to_string(pos[2])  + 
				// 			CLOSE_BOX + 
				// 		CLOSE_CURLY + COMMA; 

				// // add lights
				// scene_json += QUOTE + "lights" + QUOTE + COLON + 
				// 				OPEN_BOX + CLOSE_BOX + COMMA;

				// // add terrain meshes
				// scene_json += 
				// 	QUOTE + "meshes" + QUOTE + COLON + OPEN_BOX;
				// for(auto t : entities) {
				// 	// get vertices of this mesh
				// 	scene_json += OPEN_CURLY + 
				// 		QUOTE + "name" + QUOTE + COLON + QUOTE + t.second->getName() + QUOTE + COMMA +
				// 		QUOTE + "type" + QUOTE + COLON + QUOTE + t.second->getType()+ QUOTE + COMMA;
				// 		scene_json += t.second->getDataStructureRepresentation();
				// 		// remove the last comma
				// 		scene_json.erase(scene_json.size()-1);
				// 		scene_json += CLOSE_BOX + CLOSE_CURLY + CLOSE_BOX + CLOSE_CURLY; 
				// }
				scene_json += CLOSE_CURLY;
				return scene_json;
    		}
    };
}
#endif
