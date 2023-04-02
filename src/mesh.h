#ifndef Mesh_H

#define Mesh_H

#include "SceneObject.h"
#include <string>

namespace bridges{

	class Mesh : public SceneObject{
	public:

		std::string meshType;
		std::string name;

		float position[3] = {0.0, 0.0, 0.0};
		float color[3] = {1.0, 0.0, 1.0};

		Mesh(){}

		Mesh(std::string t, std::string n) : SceneObject(t, n){
			meshType = t;
			name = n;
		}

		std::string getName(){
			return name;
		}

		std::string getMeshType(){
			return meshType;
		}

		void moveTo(float pos[3]) override {
			position[0] = pos[0];
			position[1] = pos[1];
			position[2] = pos[2];

			updatedThisFrame = true;
		}

		virtual std::string getObjectType(){
			return "Mesh";
		}


		virtual float** getVertices() override{
			return NULL;
		}
		virtual void setVertices(int x, int y, float value) override {}
		virtual float*** getColors() override{
			return NULL;
		}


		virtual const std::string getDataStructureRepresentation() const override{

				std::string scene_json = "";
				scene_json += QUOTE + "name" + QUOTE + COLON + 
				QUOTE + name + QUOTE  + COMMA +
				QUOTE + "type" + QUOTE + COLON + QUOTE + meshType + QUOTE + COMMA +  
				QUOTE + "position" + QUOTE + COLON + 
								OPEN_BOX + 
									std::to_string(position[0]) + COMMA +
									std::to_string(position[1]) + COMMA +
									std::to_string(position[2])  + 
								CLOSE_BOX + COMMA;
				scene_json += QUOTE + "color" + QUOTE + COLON + OPEN_BOX + 
									std::to_string(color[0]) + COMMA +
									std::to_string(color[1]) + COMMA +
									std::to_string(color[2])  + 
								CLOSE_BOX +
							CLOSE_CURLY + COMMA;
				return scene_json;
		}


		//virtual ~Mesh() =default;


	};
}

#endif

