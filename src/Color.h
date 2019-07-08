#ifndef COLOR_H
#define COLOR_H

#include <iostream> //cerr
#include <array> //array
#include <regex> //regex
#include <unordered_map> //unordered_map
#include <cmath> //log

#include <sstream>
#include <iomanip>

#include "DataStructure.h" //string, using std

namespace bridges {
	/**
	 * @brief This class represents Color, and supports rgba, hexadecimal and named
	 *color values
	 *
	 * This class contains functions for the manipulation of a Color representation.
	 *
	 * Supported rgba colors are integer representations of each color channel,
	 * in the range of [0,255].
	 * rgb input is also supported, and given a default alpha value of 255(opaque)
	 *
	 * Supported Hexadecimal colors are in the form #RRGGBBAA, #RRGGBB, #RGBA, or #RGB.
	 * With R,G,B and A, representing the Red, Green, Blue, and Alpha color channels
	 * respectivly,
	 * in hexadecimal digits(0-9a-f, base 16) prefixed by '#'.
	 * #RGBA and #RGB are shorthand versions of #RRGGBBAA and #RRGGBB, where each
	 * channel pair is the same.
	 * If no alpha channel is provided, a default of 'ff'(opaque) will be used
	 *
	 * Supported named colors are:
	 * 
	 * <b>"red", "green",
     * "blue",
	 * "yellow",
     * "cyan"
     * "magenta"
     * "white",
     * "black",
     * "orange",
     * "green",
     * "turquoise",
     * "maroon",
     * "aquamarine",
     * "azure",
     * "beige",
     * "brown",
     * "tan",
     * "olive",
     * "chartreuse",
     * "khaki",
     * "bisque",
     * "coral",
     * "pink",
     * "lavender",
     * "purple",
     * "gold",
     * "steelblue" </b>
     *
	 * All named colors have are fully opaque by default.
	 *
	 * Default Color is opaque white
	 *
	 * @date 7/8/19, Kalpathi Subramanian 
	 */
	class Color {
		private:
			// The named colors' rgba channel value mappings
			static const unordered_map<string, const array<int, 4>> & ColorNames() {
				static unordered_map<string, const array<int, 4>> cn {
					{"red",   {{255, 0, 0, 255}}},
					{"green",   {{0, 255, 0, 255}}},
					{"blue",   {{0, 0, 255, 255}}},
					{"yellow",   {{255, 255, 0,  255}}},
					{"cyan",   {{0, 255, 255, 255}}},
					{"magenta",   {{255, 0, 255, 255}}},
					{"white",   {{255, 255, 255, 255}}},
					{"black",   {{0, 0, 0, 255}}},
					{"orange",   {{255, 155, 0, 255}}},
					{"turquoise",   {{64, 224, 208, 255}}},
					{"maroon",   {{176, 48, 96, 255}}},
					{"aquamarine",   {{127, 255, 212, 255}}},
					{"azure",   {{240, 255, 255, 255}}},
					{"beige",   {{245, 245, 220, 255}}},
					{"brown",   {{166, 42, 42,  255}}},
					{"tan",   {{210, 180, 140, 255}}},
					{"olive",   {{128, 128, 0, 255}}},
					{"chartreuse",  {{127, 255, 0, 255}}},
					{"khaki",   {{240, 230, 140, 255}}},
					{"bisque",   {{255, 228, 196, 255}}},
					{"coral",   {{255, 127, 80, 255}}},
					{"pink",   {{255, 192, 203, 255}}},
					{"lavender",   {{230, 230, 250, 255}}},
					{"purple",   {{128, 0, 128, 255}}},
					{"gold",   {{255, 215, 0, 255}}},
					{"steelblue", {{70, 130, 180, 255}}}
				};
				return cn;
			}

			// The rgba channel values of this Color
			array<int, 4> channels{{255, 255, 255, 255}};
		public:
			/**
			 *  Default constructor
			 *  Defaults to black
			 */
			Color() {
				setRed(0);
				setGreen(0);
				setBlue(0);
				setAlpha(255);
			}
			/**
			 * Constructs a color with the specified rgba color channel values [0,255].
			 * If no alpha channel is provided, the default of 255(opaque) is used.
			 *
			 * @param r The red channel
			 * @param g The green channel
			 * @param b The blue channel
			 * @param a The alpha channel(default 255)
			 */
			Color(const int& r, const int& g, const int& b, const int& a = 255) {
				setValue(r, g, b, a);
			}
			/**
			 * Constructs a color from a named color or a #hexadecimal [0-F](base 16)
			 * of the form #RRGGBBAA, #RRGGBBAA, #RGBA, or #RGB.
			 * Named colors and #hexadecimals missing an alpha channel are made opaque.
			 *
			 * @param name The named color or #hexadecimal value
			 */
			Color(const string& name) {
				setValue(name);
			}
			/**
			 * Equality Comparison Operator
			 * @return True if both Colors represent the same Color, false if not
			 */
			bool operator==(const Color& that) const {
				return channels == that.channels;
			}
			/**
			 * Inequality Comparison Operator
			 * @return False if both Colors represent the same Color, true if not
			 */
			bool operator!=(const Color& that) const {
				return channels != that.channels;
			}
			/** @return True if fully opaque, false if not */
			bool isOpaque()  const {
				return getAlpha() == 255;
			}
			/** @return True if fully transparent, false if not */
			bool isTransparent() const {
				return getAlpha() == 0;
			}

			/** @return rgba value of the red channel [0,255] */
			int getRed() const {
				return channels.at(0);
			}
			/** @return rgba value of the green channel [0,255] */
			int getGreen() const {
				return channels.at(1);
			}
			/** @return rgba value of the blue channel [0,255] */
			int getBlue()  const {
				return channels.at(2);
			}
			/** @return rgba value of the alpha channel [0,255] */
			int getAlpha() const {
				return channels.at(3);
			}

			/** @return The #hexadecimal representation (#RRGGBBAA) of this color */
			string getHexValue() const {
				std::stringstream ss;
				ss << "#";
				ss << std::hex << std::setfill('0') << std::setw(2) << getRed();
				ss << std::hex << std::setfill('0') << std::setw(2) << getGreen();
				ss << std::hex << std::setfill('0') << std::setw(2) << getBlue();
				ss << std::hex << std::setfill('0') << std::setw(2) << getAlpha();

				return ss.str();
			}
			/** Sets red channel to "r"
			 *	@param a rgba value to set red channel to
			 */
			void setRed(int r) {
				setChannel(r, 0);
			}
			/** Sets green channel to "g"
			 * 	@param a rgba value to set green channel to
			 */
			void setGreen(int g) {
				setChannel(g, 1);
			}
			/** Sets blue channel to "b"
			 *	@param a rgba value to set blue channel to
			 */
			void setBlue(int b) {
				setChannel(b, 2);
			}
			/** Sets alpha channel to "a"
			 *	@param a rgba value to set alpha channel to
			 */
			void setAlpha(int a) {
				setChannel(a, 3);
			}

			/**
			 * Sets this color's value to the specified rgba color channel values [0,255].
			 * If no alpha channel is provided, the default of 255(opaque) is used.
			 *
			 * @param r rgba value to set the red channel to
			 * @param g rgba value to set the green channel to
			 * @param b rgba value to set the blue channel to
			 * @param a rgba value to set the alpha channel to
			 */
			void setValue(int r, int g, int b, int a = 255) {
				setRed(r);
				setGreen(g);
				setBlue(b);
				setAlpha(a);
			}
			/**
			 * Sets this color's value to the value of a named color or a #hexadecimal
			 *  [0-F](base 16) of the form #RRGGBBAA, #RRGGBBAA, #RGBA, or #RGB.
			 * Named colors and #hexadecimals missing an alpha channel are made opaque.
			 *
			 * @param name The named color or #hexadecimal value
			 * @throw string If name is an invalid color
			 */
			void setValue(string name) {
				//marking static to avoid rebuilding the regexp every time.
				//greedy, so checks for 8(RRGGBBAA), then 6(RRGGBB) then 4(RGBA) then 3(RGB)
				static const regex HEX_RANGE("^#([[:xdigit:]]{8}|[[:xdigit:]]{6}|[[:xdigit:]]{3,4})$");

				for (char& c : name) {
					c = (char) tolower((unsigned char)c);   //convert to lowercase
				}
				auto it = ColorNames().find(name);

				if (it != ColorNames().end()) {
					channels = it->second;   //Named value
				}
				else if (regex_match(name, HEX_RANGE)) { //#Hex value
					name.erase(0, 1); //removes "#"
					// alpha value, overwritten if present by loop number
					// of chars representing a channel
					channels.at(3) = 255;
					const int chanChars = (name.size() == 3 || name.size() == 4) ? 1 : 2;
					//unit place scale factor, handles channel size variance
					const int chanMultiplier = (chanChars == 1) ? 17 : 1;
					for (size_t i = 0; i < name.size() / chanChars; i++) {
						//converts and save hex val to rgba val
						channels.at(i) = (int) strtol(name.substr(i * chanChars,
									chanChars).c_str(), nullptr, 16) * chanMultiplier;
					}
				}
				else { //invalid color
					string errStr = "Invalid Color: " + name + "\nMust be a hexadecimal(#RRGGBBAA, #RRGGBB, #RGBA, or #RGB) color representation\nOr one of these supported named colors: ";
					for (const auto& p : ColorNames()) {
						errStr += " \"" + p.first + "\"";
					}
					errStr += "\n";
					throw errStr;
				}
			}
			const string getRepresentation () const {
				return string(
						"[" + 	to_string(getRed()) + "," +
						to_string(getGreen()) + "," +
						to_string(getBlue()) + "," +
						to_string(getAlpha()) +
						"]");
			}
		private:

			/**
			 * Sets the channel specified by "channel" to "value"
			 *
			 * @param channel The channel to change
			 * @param value The rgba value to set the channel to
			 * @throw string Throw if value is invalid
			 */
			void setChannel(const int& value, const int& channel) {
				(value < 0 || 255 < value)
				? throw "Invalid channel parameter: " + to_string(value) +
				" Must be in the [0,255] range"
				: channels.at(channel) = value;
			}
	};//end of color class
};//end of bridge namespace
#endif
