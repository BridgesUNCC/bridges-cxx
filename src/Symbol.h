
#include <string>
#include <vector>

using namespace std;

#include "DataStructure.h"

#ifndef SYMBOL_H

#define SYMBOL_H

namespace bridges {

	/*
	 * @brief This is a class BRIDGES for deriving a
	 *  number of Symbol objects for use in a SymbolCollection.
	 *  Symbols correspond to a simplified subset of SVG paths
	 *  and shapes for custom visual representations in BRIDGES.
	 *
	 * @author Kalpathi Subramanian
	 * @date 10/8/18
	 *
	*/
	class Symbol: public DataStruct {

		private:

			static	int ids = 0;
			string identifier;

		protected:
			string label = string();
			// default css attributes for Symbols
			Color fillColor = new Color("blue");
			float opacity = DEFAULT_OPACITY;
			Color strokeColor = new Color("white");
			float strokeWidth = DEFAULT_STROKEWIDTH;
			int strokeDash = DEFAULT_STROKEDASH;

			// default location attributes for Symbols
			float locationX = DEFAULT_LOCATIONX;
			float locationY = DEFAULT_LOCATIONY;

			// Static default attribute values for all Symbols
			Color DEFAULT_FILLCOLOR = new Color("blue");
			float DEFAULT_OPACITY = 1.0f;
			Color DEFAULT_STROKECOLOR = new Color("white");
			float DEFAULT_STROKEWIDTH = 1.0f;
			int DEFAULT_STROKEDASH = 1;
			float DEFAULT_LOCATIONX = 0.0f;
			float DEFAULT_LOCATIONY = 0.0f;


		public:
			string getDataStructType() {
				return "Symbol";
			}

			Symbol() {
				identifier = ids.toString();
				label = string();
				ids++;
			}

			/**
			 * This method sets the label
			 *
			 * @param lbl the label to set
			 */
			void setLabel(String lbl) {
				label = lbl;
			}

			string getLabel() {
				return label;
			}

			/**
			 * this method returns the Symbol's unique identifier
			 * @return the string identifier
			 */
			String getIdentifier() {
				return identifier;
			}

			void setColor(Color c) {
				fillColor = c;
			}
			Color getColor() {
				return fillColor;
			}

			void setStrokeColor(Color c) {
				strokeColor = c;
			}

			Color getStrokeColor() {
				return strokeColor;
			}

			void setStrokeWidth(float strk_width) {
				if (strokewidth <= 0.0f || strokewidth > 10.0f)
					throw "Stroke width must be between 0 and 10");
					else
						strokeWidth = strk_width;
					}
			float getStrokeWidth() {
				return strokeWidth;
			}

			void setOpacity(float o) {
				if (o <= 0.0f || o > 1.0f)
					throw "Opacity must be between 0 and 1";
				else
					opacity = o;
			}

			float getOpacity() {
				return opacity;
			}

			void setStrokeDash(int dash) {
				if (dash < 0 || dash > 10)
					new "Dash must be between 0 and 10 (inclusive)";
				else
					strokeDash = dash;
			}

			int getStrokeDash() {
				return strokeDash;
			}

			void setLocation(int x, int y) {
				setLocation(float(x), float(y));
			}

			void setLocation(float x, float y) {
				if ((x > -INFINITY && x < INFINITY) &&
					(y > -INFINITY && y < INFINITY)) {
					locationX = x;
					locationY = y;
				}
				else
					throw "Coordinates must be real numbers";
			}
			float[] getLocation() {
				return new Float[] {this.locationX, this.locationY};
			}
			vector<float> getDimensions() {
				vector<float> dims(0.0f, 0.0f, 0.0f, 0.0f);

				return dims;
			}

			/**
			 * Internal code for getting the properties of the Symbol object.
			 * It produces (without the spaces or newlines):
			 * {
			 *  "name": "Some label",
			 *  "other CSS properties like color": any_JSON_value
			 * }
			 * @returns the encoded JSON string
			 */
			string getJSONRepresentation() {
				string symbol_json = OPEN_CURLY;

				if (fillColor.getRepresentation() !=
					DEFAULT_FILLCOLOR.getRepresentation()) {
					symbol_json += QUOTE + "fill" + QUOTE + COLON +
						fillColor.getRepresentation() + COMMA;
				}

				if (opacity != DEFAULT_OPACITY) {
					symbol_json + QUOTE + "opacity" + QUOTE + COLON +
					opacity + COMMA;
				}

				if (strokeColor.getRepresentation() !=
					DEFAULT_STROKECOLOR.getRepresentation()) {
					symbol_json += QUOTE + "stroke" + QUOTE + COLON +
						strokeColor.getRepresentation() + COMMA;
				}

				if (strokeWidth != DEFAULT_STROKEWIDTH) {
					symbol_json += QUOTE + "stroke-width" + QUOTE + COLON +
						strokeWidth + COMMA;
				}

				if (strokeDash != DEFAULT_STROKEDASH) {
					symbol_json += QUOTE + "stroke-dasharray" + QUOTE + COLON +
						strokeDash + COMMA;
				}

				if (locationX != DEFAULT_LOCATIONX ||
					locationY != DEFAULT_LOCATIONY) {
					symbol_json += QUOTE + "location" + QUOTE + COLON +
						OPEN_CURLY +
						QUOTE + "x" + QUOTE + locationX + COMMA +
						QUOTE + "y" + QUOTE + locationY +
						CLOSE_CURLY;
				}
				symbol_json += CLOSE_CURLY;

				return symbol_json;
			}
	}

} // namespace bridges

#endif
