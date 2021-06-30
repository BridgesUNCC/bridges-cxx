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
		class Text : public Symbol {
			private:
				// label anchor location
				float *origin = new float[2];

				// label attributes
				float 	*fontSize = nullptr;
				string 	*anchorType = nullptr,
						*anchorAlignmentLR = nullptr, 
						*anchorAlignmentTB;

				string label_text = string();

				int textWidth = 100;
				int textHeight = 50;
				float rotation_angle = 0.;

			public:

				/**
				 * 	constructors
				 */
				Text() : fontSize(nullptr), 
						anchorType(nullptr),
						anchorAlignmentLR(nullptr),
						anchorAlignmentTB(nullptr) {

					origin[0] = origin[1] = 0.0f;
					setStrokeWidth(0.0f);
				}

				/**
				 * Create a label object with label l
				 *
				 * @param l  label
				 */
				Text (string l): Text() {
					label_text = l;
				}

				~Text() {
					if (fontSize)
						delete fontSize;
					if (anchorType)
						delete anchorType;
					if (anchorAlignmentLR)
						delete anchorAlignmentLR;
					if (anchorAlignmentTB)
						delete anchorAlignmentTB;
				}

				/*
				 * @brief Get Data Structure name
				 * @return name of data type
				 */
				string getShapeType() {
					return "text";
				}
				/**
				 * @brief Set the label text
				 *
				 * @param lbl the text to set
				 */
				void setText(string lbl) {
					label_text = lbl;
				}

				/**
				 * @brief Get the symbol label
				 *
				 * @return  the text label
				 */
				string getText() const {
					return label_text;
				}

				/**
				 * @brief This method sets the label origin; 
				 *
				 * @param  x  x coordinate of label location
				 * @param  y  y coordinate of label location
				 *
				 */
				void setAnchorLocation(float *loc) {
					origin[0] = loc[0];
					origin[1] = loc[1];
				}

				/**
				 * Sets the alignment parameters for the text label
				 *
				 * @param typeLR valid parameters are "left", "middle", and "right"
				 * @param typeTB valid parameters are "top", "bottom", 
				 *	"embottom", "emtop", "middle"
				 *
				 * @return  symbol
				 **/
				Symbol& setAnchorAlignment(string typeLR, string typeTB) {
					if (!anchorAlignmentLR)
						anchorAlignmentLR = new string;
					if (!anchorAlignmentLR)
						anchorAlignmentTB = new string;

					*anchorAlignmentLR = typeLR;
					*anchorAlignmentTB = typeTB;

					return *this;
				}
	
				/**
				 * @brief This method gets the label anchor location; 
				 *
				 * @return anchor location (x, y)
				 *
				 */
				float *getAnchorLocation() {
					return origin;
				}

				/**
				 * @brief This method sets the label's anchor type
				 *
				 * @param  type  string
				 *
				 * @return  symbol
				 */
				Symbol& setAnchorType(string type) {
					if (!anchorType)
						anchorType = new string;

					*anchorType = type;

					return *this;
				}

				/**
				 * @brief This method gets the label's anchor type
				 *
				 * @return  type  
				 *
				 */
				string  getAnchorType() {
					if (!anchorType)
						throw "Anchor type not set!";

					return *anchorType;
				}
				
				/**
				 * @brief This method sets the font size
				 *
				 * @param sz  font size
				 *
				 * @return  symbol
				 */
				Symbol& setFontSize(float sz) {
					if (!fontSize)
						fontSize = new float;

					*fontSize = sz;

					return *this;
				}

				/**
				 * @brief This method gets the font size
				 *
				 * @return   font size
				 *
				 */
				int getFontSize() {
					if (!fontSize) 
						throw "Font size not set!";

					return *fontSize;
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

/*
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
					length *= *fontSize;

					float width = length;
					float height = 0.;
					if (upper_case_exists) {
						height = *fontSize + 0.3f * *fontSize;
					}
					else
						height = *fontSize + 0.1f * *fontSize;

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

*/
				/**
				 * @brief This method returns the JSON representation of the shape
				 *
				 * @return string  JSON string
				 */
				const string getSymbolRepresentation() const {

					string shape_json = getSymbolAttributeRepresentation();

					if (anchorType)  
						shape_json += QUOTE + "anchorType" + QUOTE + COLON + 
								QUOTE + *anchorType + QUOTE + COMMA;

					if (anchorAlignmentLR)
						shape_json += QUOTE + "anchor-alignmentLR" + QUOTE + COLON +
								QUOTE + *anchorAlignmentLR + QUOTE + COMMA;

					if (anchorAlignmentTB)
						shape_json += QUOTE + "anchor-alignmentTB" + QUOTE + COLON +
								QUOTE + *anchorAlignmentTB + QUOTE + COMMA;

					shape_json += QUOTE + "font-size" + QUOTE + COLON +  
								to_string(*fontSize)  + COMMA; 

					shape_json +=
						QUOTE + "anchor-location" + QUOTE + COLON +  
							OPEN_BOX + 
								to_string(origin[0]) + COMMA + to_string(origin[1]) +
							CLOSE_BOX + COMMA + 
						QUOTE + "angle" + QUOTE + COLON +  to_string(rotation_angle) +
								CLOSE_CURLY;


					return shape_json;
				}
		};
	}
} // namespace bridges

#endif
