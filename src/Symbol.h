
#include <string>
#include <vector>

using namespace std;

#include "DataStructure.h"
#include "Color.h"

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
	class Symbol: public DataStructure {

		private:

			int identifier;

			/**
			 *	these functions maintain default attributes for symbols
			 */
			Color getDefaultFillColor() const {
				static Color default_fill_color("blue");

				return default_fill_color;
			}
			Color getDefaultStrokeColor() const {
				static Color default_stroke_color("white");

				return default_stroke_color;
			}
			float getDefaultOpacity() const {
				static float default_opacity = 1.0f;

				return default_opacity;
			}

			float getDefaultStrokeWidth() const {
				static float default_stroke_width = 1.0f;

				return default_stroke_width;
			}

			int getDefaultStrokeDash() const {
				static int default_stroke_dash = 1;

				return default_stroke_dash;
			}

			float *getDefaultLocation() const {
				static float default_location[2] = {0.0f, 0.0f};

				return default_location;
			}

		protected:
			string label = string();
			// default css attributes for Symbols
			Color fillColor = getDefaultFillColor();
			float opacity = getDefaultOpacity();
			Color strokeColor = getDefaultStrokeColor();
			float strokeWidth = getDefaultStrokeWidth();
			int strokeDash = getDefaultStrokeDash();

			// default location attributes for Symbols
			float *location = getDefaultLocation();



		public:
			const string getDStype() const {
				return "Symbol";
			}

			Symbol() {
				identifier = getIdentifier();
				label = string();
			}

			/**
			 * 	Maintains unique identifiers of symbols
			 * 	and returns the Symbol's unique identifier
			 *
			 * 	@return the string identifier
			 */
			int getIdentifier() {
				static int ids = 0;
				ids++;

				return ids - 1;
			}

			/**
			 * This method sets the label
			 *
			 * @param lbl the label to set
			 */
			void setLabel(string lbl) {
				label = lbl;
			}

			string getLabel() {
				return label;
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
				if (strokeWidth <= 0.0f || strokeWidth > 10.0f)
					throw "Stroke width must be between 0 and 10";
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
					throw "Dash must be between 0 and 10 (inclusive)";
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
					location[0] = x;
					location[1] = y;
				}
				else
					throw "Coordinates must be real numbers";
			}
			float *getLocation() {
				return location;
			}
			vector<float> getDimensions() {
				vector<float> dims(4, 0.0f);

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
			virtual const string getDataStructureRepresentation() const override {
				string symbol_json = OPEN_CURLY;

				if (fillColor.getRepresentation() !=
					getDefaultFillColor().getRepresentation()) {
					symbol_json += QUOTE + "fill" + QUOTE + COLON +
						fillColor.getRepresentation() + COMMA;
				}

				if (opacity != getDefaultOpacity()) {
					symbol_json + QUOTE + "opacity" + QUOTE + COLON +
					to_string(opacity) + COMMA;
				}

				if (strokeColor.getRepresentation() !=
					getDefaultStrokeColor().getRepresentation()) {
					symbol_json += QUOTE + "stroke" + QUOTE + COLON +
						strokeColor.getRepresentation() + COMMA;
				}

				if (strokeWidth != getDefaultStrokeWidth()) {
					symbol_json += QUOTE + "stroke-width" + QUOTE + COLON +
						to_string(strokeWidth) + COMMA;
				}

				if (strokeDash != getDefaultStrokeDash()) {
					symbol_json += QUOTE + "stroke-dasharray" + QUOTE + COLON +
						to_string(strokeDash) + COMMA;
				}

				float *def_loc = getDefaultLocation();
				if (location[0] != def_loc[0] ||
					location[1] != def_loc[1]) {
					symbol_json += QUOTE + "location" + QUOTE + COLON +
						OPEN_CURLY +
						QUOTE + "x" + QUOTE + to_string(location[0]) + COMMA +
						QUOTE + "y" + QUOTE + to_string(location[1]) +
						CLOSE_CURLY;
				}
				symbol_json += CLOSE_CURLY;

				return symbol_json;
			}
	};

} // namespace bridges

#endif
