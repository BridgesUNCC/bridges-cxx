#include "DataStructure.h"
#include "Symbol.h"
#include <vector>
#include <cmath>

using namespace std;

/**
 */

#ifndef  LABEL_H

#define LABEL_H


namespace bridges {
	namespace datastructure {
		/**
		 * @brief This is a label object and used for defining text labels
		 *   as part of the symbol collection.
		 *
		 * @author Kalpathi Subramanian
		 * @date 12/23/18, 12/28/20
		 *
		 */
		class Label : public Symbol {
			private:
				// height, width of rectangle
				int fontSize = 12;
				int textWidth = 100;
				int textHeight = 50;
				float rotation_angle = 0.;

			public:

				/**
				 * 	constructors
				 */
				Label() {
					fontSize = 12;
					textWidth = 100;
					textHeight = 50;
				}

				/**
				 * Create a label object with label l
				 *
				 * @param l  label
				 */
				Label (string l) {
					setLabel(l);
				}

				/*
				 * @brief Get Data Structure name
				 * @return name of data type
				 */

				string getDataStructType() {
					return "label";
				}

				/**
				 *	@brief This method gets the name of the shape
				 *
				 *  @return name   shape name
				 */
				string getName()  const {
					return "label";
				}

				/**
				 * @brief This method sets the font size
				 *
				 * @param sz  font size
				 *
				 */
				void setFontSize(float sz) {
					fontSize = sz;
				}

				/**
				 * @brief This method gets the font size
				 *
				 * @return   font size
				 *
				 */
				int getFontSize() {
					return fontSize;
				}

				/**
				 * @brief This method sets the text width
				 *
				 * @param w  text width
				 *
				 */
				void setTextWidth(int w) {
					textWidth = w;
				}

				/**
				 * @brief This method gets the text width
				 *
				 * @return  text width
				 *
				 */
				int getTextWidth() {
					return textWidth;
				}

				/**
				 * This method sets the text height
				 *
				 * @param h  text height
				 *
				 */
				void setTextHeight(int h) {
					textHeight = h;
				}

				/**
				 * @brief This method gets the text height
				 *
				 * @return  text height
				 *
				 */
				int getTextHeight() {
					return textHeight;
				}

				/**
				 * @brief Set the rotation angle for the label
				 *
				 * Permits rotated text labels (only horiz and vertical 
				 *  supported now.
				 *
				 * @param angle  rotation angle in dedgrees
				 *
				 */
				void setRotationAngle (float angle) {
					// right now support for 0, 45, 90 deg.
					rotation_angle = angle;	
				}
				/**
				 * @brief Get the rotation angle for the label
				 *
				 * 
				 * @return angle  rotation angle in degrees
				 *
				 */
				float getRotationAngle () {
					return rotation_angle;
				}

				/**
				 * @brief This method returns the bounding box dimensions of
				 *	the shape
				 *
				 *  A more accurate computation, takes into account 
				 *  the label string content
				 *
				 * @return vector of floats
				 */

				vector<float> getBoundingBox() const {
					vector<float> bbox(4);

					// first get the width of the string by parsing it
					string str = getLabel();
					float length = 0.;
					bool upper_case_exists = false;
					for (auto ch: str) {
						if (std::islower(ch)) {
							cout << ch << " " << endl;					
							if (ch == 'm' || ch == 'w')
								length +=  0.6;
							else if (ch == 'i' || ch == 'l' || ch == 'j')
								length +=  0.4;
							else length += 0.5;
						}
						else if (std::isupper (ch)) {
							upper_case_exists = true;
							if (ch == 'M' || ch == 'W')
								length +=  0.72;
							else if (ch == 'I') 
								length +=  0.52;
							else length += 0.62;
						}
						else // support only spaces
							length += 0.55;
					}
					length *= fontSize;
					cout << "length = " << length << endl;

					float width = length;
					float height = 0.;
					if (upper_case_exists) {
						height = fontSize + 0.3f*fontSize;
					}
					else 
						height = fontSize + 0.1f*fontSize;

					// account for text orientation to compute an 
					// axis aligned bounding box

					float bbox_width = length;
					float bbox_height = height;
					if (rotation_angle == 90.0f || rotation_angle == -90.0f) {
						bbox_width = height;
						bbox_height = length;
					}
					else if (rotation_angle == -45.0f || 
								rotation_angle == 45.0f) {
						bbox_width  = length/sqrt(2.0);
						bbox_height = length/sqrt(2.0);
					}


					// order is xmin, ymin, xmax, ymax
					const float *location = getLocation();
					bbox[0] = location[0] - bbox_width/2.;    
					bbox[1] = location[1] - bbox_height/2.;
					bbox[2] = location[0] + bbox_width/2.;;
					bbox[3] = location[1] + bbox_height/2.;;

					return bbox;
				}

				/**
				 * @brief This method returns the bounding box dimensions of
				 *	the shape
				 *
				 * @return vector of floats
				 */
				vector<float> getDimensions() const {
					vector<float> dims(4);

					return getBoundingBox();
				}

				/**
				 * @brief This method returns the JSON representation of the shape
				 *
				 * @return string  JSON string
				 */
				const string getSymbolRepresentation() const {

					string shape_json = getSymbolAttributeRepresentation();

					shape_json +=
						QUOTE + "name" + QUOTE + COLON +  QUOTE + getLabel() + QUOTE + COMMA +
						QUOTE + "shape" + QUOTE + COLON + QUOTE + "text" + QUOTE + COMMA +
						QUOTE + "font-size" + QUOTE + COLON +  to_string(fontSize)  + COMMA + 
						QUOTE + "angle" + QUOTE + COLON +  to_string(rotation_angle)  +
						CLOSE_CURLY;

					return shape_json;

				}
		};
	}
} // namespace bridges

#endif
