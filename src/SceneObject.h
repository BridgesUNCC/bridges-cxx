#ifndef SCENEOBJECT_H

#define SCENEOBJECT_H

#include <iostream>
#include <string>
#include <vector>

namespace bridges{
	class SceneObject{
	public:

		//std::vector<SceneObject> children;
		SceneObject* parent = nullptr;
		std::string type;
		std::string name;

		//determine if this object has been updated and information should be sent to server to update
		//buffers and transforms etc.
		bool updatedThisFrame = true;

		float position[3] = {0.0, 0.0, 0.0};

		SceneObject(){}

		SceneObject(std::string t, std::string n){
			type = t;
			name = n;
		}

		// void addChild(SceneObject& obj){
		// 	children.push_back(obj);
		// 	children[children.size()-1].parent = this;
		// }

		void setName(std::string n){
			name = n;
		}

		std::string getName(){
			return name;
		}

		std::string getType(){
			return type;
		}

		virtual void moveTo(float pos[3])=0;
		virtual const std::string getDataStructureRepresentation()const=0;
		virtual float** getVertices()=0;
		virtual void setVertices(int x, int y, float value) = 0;
		virtual float*** getColors()=0;
		// virtual std::string getColors(){
		// 	return "None";
		// }
		// virtual std::string getVertices(){
		// 	return "None";
		// }

		virtual ~SceneObject() =default;

	};
}

#endif


