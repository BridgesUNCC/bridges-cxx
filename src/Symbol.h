#include "DataStructure.h"

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
				locationX = x; locationY = y;
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
			JSONObject json_builder = new JSONObject();
			JSONObject location = new JSONObject();
			JSONArray myColor;

			if (fillColor.getRepresentation().compareTo(DEFAULT_FILLCOLOR.getRepresentation()) != 0) {
				myColor = new JSONArray();
				myColor.add(fillColor.getRed());
				myColor.add(fillColor.getGreen());
				myColor.add(fillColor.getBlue());
				myColor.add(fillColor.getAlpha());
				json_builder.put("fill", myColor);
			}

			if (opacity != DEFAULT_OPACITY) {
				json_builder.put("opacity", opacity);
			}

			if (strokeColor.getRepresentation().compareTo(DEFAULT_STROKECOLOR.getRepresentation()) != 0) {
				myColor = new JSONArray();
				myColor.add(strokeColor.getRed());
				myColor.add(strokeColor.getGreen());
				myColor.add(strokeColor.getBlue());
				myColor.add(strokeColor.getAlpha());
				json_builder.put("stroke", myColor);
			}

			if (strokeWidth != DEFAULT_STROKEWIDTH) {
				json_builder.put("stroke-width", strokeWidth);
			}

			if (strokeDash != DEFAULT_STROKEDASH) {
				json_builder.put("stroke-dasharray", strokeDash);
			}

			if (locationX != DEFAULT_LOCATIONX && locationY != DEFAULT_LOCATIONY) {
				location.put("x", locationX);
				location.put("y", locationY);
				json_builder.put("location", location);
			}

			// System.out.println(json_builder.toString());
			return json_builder;
		}
		public String getElementRepresentation() {
			return getJSONRepresentation().toString();
		}
}
