#ifndef SCENEOBJECT_H

#define SCENEOBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <variant>

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

		float position[4] = {0.0, 0.0, 0.0, 1.0};

		float transform[4][4] = {
			{1.0, 0.0, 0.0, 0.0},
			{0.0, 1.0, 0.0, 0.0},
			{0.0, 0.0, 1.0, 0.0},
			{0.0, 0.0, 0.0, 1.0}
			} ;

		std::string jsonHeader = "";


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

		// matrix methods used for affine transformations on symbols
		void matMult (float m1[][4], float m2[][4], float result[][4])
		const {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					result[i][j] = 0.;
					for (int k = 0; k < 4; ++k) {
						result[i][j] += m1[i][k] * m2[k][j];
					}
				}
			}
		}

		void identity(float m[][4]) {
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					m[i][j] = (i == j) ? 1. : 0.;
		}

		void copyMat(float m[][4], float copy[][4]) {
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					copy[i][j] = m[i][j];
		}

		void printMat(float m[][4]) {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j)
					cout <<  m[i][j] << ", ";
				cout << "\n";
			}
		}

		void printMat() {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j)
					cout <<  transform[i][j] << ", ";
				cout << "\n";
			}
		}

		void translate (float tx, float ty, float tz) {
			float result[4][4];
			float transl[4][4] = {
				{1., 0., 0., tx}, {0., 1., 0., ty}, {0., 0., 1., tz}, {0., 0., 0., 1.}
			};

			// update current transform matrix
			matMult (transform, transl, result);
			copyMat (result, transform);

			updatedThisFrame = true;

		}

		void scale(float sx, float sy, float sz) {
			float result[4][4];
			float scale[4][4] = {
				{sx, 0., 0., 0.}, {0., sy, 0., 0.}, {0., 0., sz, 0.}, {0., 0., 0., 1.}
			};

			// update current transform matrix
			matMult (transform, scale, result);
			copyMat (result, transform);

			updatedThisFrame = true;

		}

		void rotateZ(float angle) {
			// compute sin, cos
			float angle_r = angle * M_PI / 180.;
			float c = cos(angle_r);
			float s = sin(angle_r);

			// form the rotation matrix
			float result[4][4];
			float rotation[4][4] = {
				{c, -s, 0., 0.}, {s, c, 0., 0.}, {0., 0., 1., 0.}, {0., 0., 0., 1.}
			};

			// update current transform matrix
			matMult (transform, rotation, result);
			copyMat (result, transform);

			updatedThisFrame = true;
		}

		void rotateY(float angle){
			// compute sin, cos
			float angle_r = angle * M_PI / 180.;
			float c = cos(angle_r);
			float s = sin(angle_r);

			// form the rotation matrix
			float result[4][4];
			float rotation[4][4] = {
				{c, 0., s, 0.}, {0., 1., 0., 0.}, {-s, 0., c, 0.}, {0., 0., 0., 1.}
			};

			// update current transform matrix
			matMult (transform, rotation, result);
			copyMat (result, transform);

			updatedThisFrame = true;
		}

		void rotateX(float angle){
			// compute sin, cos
			float angle_r = angle * M_PI / 180.;
			float c = cos(angle_r);
			float s = sin(angle_r);

			// form the rotation matrix
			float result[4][4];
			float rotation[4][4] = {
				{1., 0., 0., 0.}, {0., c, -s, 0.}, {0., s, c, 0.}, {0., 0., 0., 1.}
			};

			// update current transform matrix
			matMult (transform, rotation, result);
			copyMat (result, transform);

			updatedThisFrame = true;
		}


		float dot(float u[3], float v[3]){
			float sum = 0.0;
			for(int i = 0; i < 3; i++){
				sum += u[i] * v[i];
			}
			return sum;
		}

		float length(float u[3]){
			return sqrt(dot(u,u));
		}

		void normalize(float u[3]){
			float len = length(u);

			for ( int i = 0; i < 3; ++i ) {
			    u[i] /= len;
			}
		}


		void rotate(float angle, float axis[3]){
			normalize(axis);

			float angle_r = angle * M_PI / 180.;

			float x = axis[0];
			float y = axis[1];
			float z = axis[2];

			float c = cos(angle_r);
			float omc = 1.0 - c;
			float s = sin(angle_r);

			// form the rotation matrix
			float result[4][4];
			float rotation[4][4] = {
				{x*x*omc + c,   x*y*omc - z*s, x*z*omc + y*s, 0.0}, 
				{x*y*omc + z*s, y*y*omc + c,   y*z*omc - x*s, 0.0}, 
				{x*z*omc - y*s, y*z*omc + x*s, z*z*omc + c,   0.0}, 
				{0., 0., 0., 1.}
			};

			// update current transform matrix
			matMult (transform, rotation, result);
			copyMat (result, transform);

			updatedThisFrame = true;
		}

		

		/*
		This creates the beginning JSON for all scene objects constructed with all shared
		common attributes related to scene objects. If adding new attributes to scene objects needed
		by the server rendering should be included here.
		*/
		std::string getJSONHeader(){
			jsonHeader = QUOTE + "name" + QUOTE + COLON + 
				QUOTE + name + QUOTE  + COMMA +
				QUOTE + "type" + QUOTE + COLON + QUOTE + type + QUOTE + COMMA +
				QUOTE + "transform" + QUOTE + COLON + OPEN_BOX;
				for (int i = 0; i < 4; i++) {
					jsonHeader += OPEN_BOX;	// row start
					for (int j = 0; j < 4; j++) {
						jsonHeader += std::to_string(transform[i][j])+COMMA;
					}
					// remove the last comma
					jsonHeader.erase(jsonHeader.size()-1);
					jsonHeader += CLOSE_BOX + COMMA; // row end
				}
				// remove the last comma
				jsonHeader.erase(jsonHeader.size()-1);
				jsonHeader += CLOSE_BOX + COMMA;	//end of tranform

			return jsonHeader;
		}

		// void scaleObject(float amount){
		// 	transform[0][0] *= amount;
		// 	transform[1][1] *= amount;
		// 	transform[2][2] *= amount;
		// }

		// void translateObject(float translate[3]){
		// 	transform[0][3] += translate[0];
		// 	transform[1][3] += translate[2];
		// 	transform[2][3] += translate[2];
		// }

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


