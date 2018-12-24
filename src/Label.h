#include "DataStructure.h"
#include "Symbol.h"
#include <vector>

using namespace std;

#ifndef  LABEL_H

#define LABEL_H

namespace bridges {

	/*
	 * @brief This class defines a rectangle and is part of the symbol collection. 
	 *		A rectangle has height and width
	 *
	 * @author Kalpathi Subramanian
	 * @date 12/23/18
	 *
	*/
	class Label : public Symbol {
		private:
								// height, width of rectangle
			int fontSize = 12;
			int textWidth = 100;
			int textHeight = 50;
 
		public:

			/** 
			 * 	constructors
			 */
			Label() {
				fontSize = 12;
				textWidth = 100;
				textHeight = 50;
			}

			Label (string l) {
				setLabel(l);
			}


			string getDataStructType() {
				return "label";
			}

			/**
			 *	This method gets the name of the shape
			 *
			 *  @return name   shape name
			 */
			string getName()  const {
				return "label";
			}

			/**
			 * This method sets the font size
			 *
			 * @param f  font size  
 			 *
			 */
			void setFontSize(int font) {
				fontSize = font;
			}

			/**
			 * This method gets the font size
			 *
			 * @return   font size  
 			 *
			 */
			int getFontSize() {
				return fontSize;
			}

			/**
			 * This method sets the text width
			 *
			 * @param w  text width
 			 *
			 */
			void setTextWidth(int w) {
				textWidth = w;
			}

			/**
			 * This method gets the text width
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
			 * This method gets the text height
			 *
			 * @return  text height
 			 *
			 */
			int getTextHeight() {
				return textHeight;
			}

			
            /**
             * This method returns the bounding box dimensions of the shape
             *
             * @return vector of floats  
             */
			vector<float> getDimensions() {
				vector<float> dims(4);

				float length = 0.09*fontSize*getLabel().size();

				float *location = getLocation();
				dims[0] = location[0] - length/2.; 
				dims[1] = location[1] + length/2.; 
				dims[2] = dims[3] = location[1];

                return dims;
            }

            /**
             * This method returns the JSON representation of the shape
             *
             * @return string  JSON string
             */
			const string getSymbolRepresentation() const {

				string shape_json = getSymbolAttributeRepresentation();

				shape_json +=
					QUOTE + "name" + QUOTE + COLON +  QUOTE + getLabel() + QUOTE + COMMA +
					QUOTE + "shape" + QUOTE + COLON + QUOTE + "text" + QUOTE + 
					CLOSE_CURLY;


				return shape_json;

			}
	};

} // namespace bridges

#endif
