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
				// label origin
				int origin[2]  = {0, 0};

				// label attributes
				int fontSize = 12;

				int textWidth = 100;
				int textHeight = 50;
				float rotation_angle = 0.;

				string label_text = string();

				string anchorType = string();

				/**
				 *  @brief Rotate a 2D point (about Z)
				 *
				 *	@param pt  2D point (x, y)
				 *  @param angle rotation angle in degrees (positive is
				 *		counter clockwise, negative is clockwise)
				 */
				void rotatePoint (float *pt, float angle) const {
					// compute sin, cos
					float angle_r = angle * M_PI / 180.;
					float c = cos(angle_r);
					float s = sin(angle_r);

					// rotate the point
					float tmp[] = { pt[0]*c - pt[1]*s, pt[0] * s + pt[1] * c };

					// assign to point
					pt[0] = tmp[0];
					pt[1] = tmp[1];
				}

			public:

				/**
				 * 	constructors
				 */
				Label() {
					origin[0] = origin[1] = 0;
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
					Label();
					label_text = l;
				}

				/*
				 * @brief Get Data Structure name
				 * @return name of data type
				 */
				string getDataStructType() {
					return "label";
				}
				/**
				 * @brief Set the label text
				 *
				 * @param lbl the label to set
				 */
				void setLabel(string lbl) {
					label_text = lbl;
				}

				/**
				 * @brief Get the symbol label
				 *
				 * @return  the label
				 */
				string getLabel() const {
					return label_text;
				}

				/**
				 * @brief This method sets the label origin; 
				 *
				 * @param  x  x coordinate of label location
				 * @param  y  y coordinate of label location
				 *
				 */
				void setLocation(int *loc) {
					origin[0] = loc[0];
					origin[1] = loc[1];
				}

				int *getLocation() {
					return origin;
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
					string str = label_text;
					float length = 0.;
					bool upper_case_exists = false;
					for (auto ch : str) {
						if (std::islower(ch)) {
							if (ch == 'm' || ch == 'w')
								length +=  0.6;
							else if (ch == 'i' || ch == 'l' || ch == 'j')
								length +=  0.4;
							else
								length += 0.5;
						}
						else if (std::isupper (ch)) {
							upper_case_exists = true;
							if (ch == 'M' || ch == 'W')
								length +=  0.72;
							else if (ch == 'I')
								length +=  0.52;
							else
								length += 0.62;
						}
						else // support only spaces
							length += 0.55;
					}
					length *= fontSize;

					float width = length;
					float height = 0.;
					if (upper_case_exists) {
						height = fontSize + 0.3f * fontSize;
					}
					else
						height = fontSize + 0.1f * fontSize;

					// account for text orientation to compute an
					// axis aligned bounding box

					float bbox_width = length;
					float bbox_height = height;

					float pt[2];
					bbox[0] = bbox[1] = std::numeric_limits<float>::max();
					bbox[2] = bbox[3] = -std::numeric_limits<float>::max();
					// rotate  the four corners of the bounding box
					// only need to rotate the 3 points of the box
					for (int k = 0; k < 4; k++) {
						switch (k) {
							case 0: 	// lower left at (0,0)
								pt[0] = pt[1] = 0.;
								break;
							case 1:		// upper left
								pt[0] = 0.;
								pt[1] = bbox_height;
								break;
							case 2:		// lower right
								pt[0] = bbox_width;
								pt[1] = 0.;
								break;
							case 3:		// upper right
								pt[0] = bbox_width;
								pt[1] = bbox_height;
								break;
						}
						rotatePoint (pt, rotation_angle);

						// update bounding box
						if (pt[0] < bbox[0])
							bbox[0] = pt[0];
						if (pt[1] < bbox[1])
							bbox[1] = pt[1];
						if (pt[0] > bbox[2])
							bbox[2] = pt[0];
						if (pt[1] > bbox[3])
							bbox[3] = pt[1];
					}
					// translate center of box to center of label
					float tx = origin[0] - (bbox[0] + (bbox[2] - bbox[0]) / 2.);
					float ty = origin[1] - (bbox[1] + (bbox[3] - bbox[1]) / 2.);
					bbox[0] += tx;
					bbox[2] += tx;
					bbox[1] += ty;
					bbox[3] += ty;

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
						QUOTE + "text" + QUOTE + COLON +  QUOTE + label_text + QUOTE + COMMA +
						QUOTE + "anchor-location" + QUOTE + COLON +  QUOTE + 
							OPEN_BOX + 
								to_string(origin[0]) + COMMA + to_string(origin[0]) +
							CLOSE_BOX + COMMA +
						QUOTE + "anchorType" + QUOTE + COLON + QUOTE + anchorType + QUOTE + COMMA +
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
