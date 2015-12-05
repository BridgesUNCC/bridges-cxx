#ifndef COLOR_H
#define COLOR_H

#include <iostream> //cerr
#include <array> //array
#include <regex> //regex
#include <unordered_map> //unordered_map

#include "Validation.h" //string, using std

namespace bridges{
/**
 * @brief This class represents Color, and supports rgba, hexadecimal and named color values
 *
 * This class contains functions for the manipulation of a Color representation.
 *
 * Supported rgba colors are integer representations of each color channel,
 * in the range of [0,255].
 * rgb input is also supported, and given a default alpha value of 255(opaque)
 *
 * Supported Hexadecimal colors are in the form #RRGGBBAA, #RRGGBB, #RGBA, or #RGB.
 * With R,G,B and A, representing the Red, Green, Blue, and Alpha color channels respectivly,
 * in hexadecimal digits(0-9a-f, base 16) prefixed by '#'.
 * #RGBA and #RGB are shorthand versions of #RRGGBBAA and #RRGGBB, where each channel pair is the same.
 * If no alpha channel is provided, a default of 'ff'(opaque) will be used
 *
 * Supported named colors are:
 * "red", "yellow", "blue", "orange", "green", "purple", "brown", "black", "grey", and "white"
 * All named colors have are fully opaque by default.
 *
 * Default Color is white
 *
 * @date  12/5/15
 */
class Color
{
    private:
        static const regex HEX_RANGE; //regex for #hex value validation
        static const unordered_map<string,array<int,4>>ColorNames; //map of named colors to rgba values
        array<int,4> channels{{255,255,255,255}};//red,green,blue,alpha
    public:
        /** Constructor with rgba values, if no alpha is provided 255 is used */
        Color(const int& r,const int& g,const int& b,const int& a=255){setValue(r,g,b,a);}
        /** Constructor with named or hexadecimal values */
        Color(const string& name){setValue(name);}
        /** Copy Constructor */
        Color(const Color& col){channels = col.channels;}
        /** Assignment Operator */
        Color& operator=(const Color& that){channels = that.channels; return *this;}
        /** Equality Operator */
        bool operator==(const Color& that) const {return channels == that.channels;}
        /** @return True if opaque red, false if not */
        bool isRed()    const {return ColorNames.at("red")   ==channels;}
        /** @return True if opaque yellow, false if not */
        bool isYellow() const {return ColorNames.at("yellow")==channels;}
        /** @return True if opaque blue, false if not */
        bool isBlue()   const {return ColorNames.at("blue")  ==channels;}
        /** @return True if opaque orange, false if not */
        bool isOrange() const {return ColorNames.at("orange")==channels;}
        /** @return True if opaque green, false if not */
        bool isGreen()  const {return ColorNames.at("green") ==channels;}
        /** @return True if opaque purple, false if not */
        bool isPurple() const {return ColorNames.at("purple")==channels;}
        /** @return True if opaque brown, false if not */
        bool isBrown()  const {return ColorNames.at("brown") ==channels;}
        /** @return True if opaque black, false if not */
        bool isBlack()  const {return ColorNames.at("black") ==channels;}
        /** @return True if opaque grey, false if not */
        bool isGrey()   const {return ColorNames.at("grey")  ==channels;}
        /** @return True if opaque white, false if not */
        bool isWhite()  const {return ColorNames.at("white") ==channels;}
        /** @return True if fully opaque, false if not */
        bool isOpaque()      const {return getAlpha()==255;}
        /** @return True if fully transparent, false if not */
        bool isTransparent() const {return getAlpha()==0;}
        /** @return rgba value of the red channel [0,255] */
        int getRed()   const {return channels.at(0);}
        /** @return rgba value of the green channel [0,255] */
        int getGreen() const {return channels.at(1);}
        /** @return rgba value of the blue channel [0,255] */
        int getBlue()  const {return channels.at(2);}
        /** @return rgba value of the alpha channel [0,255] */
        int getAlpha() const {return channels.at(3);}
        /** @return The hexadecimal string representation (#RRGGBBAA) */
        string getHexValue() const {return "#"+to_hex(getRed())+to_hex(getGreen())+to_hex(getBlue())+to_hex(getAlpha());}
        /**
         * Sets red channel to "r"
         *
         * @param r red channel's rgba value representation
         */
        void setRed(const int& r)
        {
            try
            {
                Validation::validateRGBAchannel(r);
                channels.at(0)=r;
            }
            catch(const string& msg)
            {
                cerr << msg << endl << "Red channel left unchanged.." << endl;
            }
        }
        /**
         * Sets green channel to "g"
         *
         * @param g green channel's rgba value representation
         */
        void setGreen(const int& g)
        {
            try
            {
                Validation::validateRGBAchannel(g);
                channels.at(0)=g;
            }
            catch(const string& msg)
            {
                cerr << msg << endl << "Green channel left unchanged.." << endl;
            }
        }
        /**
         * Sets blue channel to "b"
         *
         * @param b blue channel's rgba value representation
         */
        void setBlue(const int& b)
        {
            try
            {
                Validation::validateRGBAchannel(b);
                channels.at(0)=b;
            }
            catch(const string& msg)
            {
                cerr << msg << endl << "Blue channel left unchanged.." << endl;
            }
        }
        /**
         * Sets alpha channel to "a"
         *
         * @param a alpha channel's rgba value representation
         */
        void setAlpha(const int& a)
        {
            try
            {
                Validation::validateRGBAchannel(a);
                channels.at(0)=a;
            }
            catch(const string& msg)
            {
                cerr << msg << endl << "Alpha channel left unchanged.." << endl;
            }
        }
        /**
         * Sets red, green, blue, and alpha channels to "r","g","b", and "a" respectively.
         * If no alpha value is provided, the default value of 255(opaque) is used.
         *
         * @param r red channel's rgba value representation
         * @param g green channel's rgba value representation
         * @param b blue channel's rgba value representation
         * @param a alpha channel's rgba value representation
         */
        void setValue(const int& r,const int& g,const int& b,const int& a=255){setRed(r); setGreen(g); setBlue(b); setAlpha(a);}
        /**
         * Sets value to "name"'s color representation
         *
         * @param name Color representation in #hex or by name
         */
        void setValue(string name)
        {
            for (char& c: name){c=tolower(c);} //gets lowercase version
            if(ColorNames.find(name) != ColorNames.end()) //Named value
            {
                channels = ColorNames.at(name);
            }
            else if(regex_match(name,HEX_RANGE))//#Hex value
            {
                name.erase(0,1); //removes "#"
                channels.at(3) = 255; //alpha value, overwritten if present by loop
                int chanChars = (name.size()==3||name.size()==4)? 1: 2; //number of chars representing a channel
                int chanMultiplier = (chanChars==1)? 17: 1; //unit place scale factor, handles channel size variance
                for(size_t i=0;i<name.size();i++)
                {
                    channels.at(i) = strtol(name.substr(i*chanChars,chanChars).c_str(),nullptr,16)*chanMultiplier; //convers and save hex val to rgba val
                }
            }
            else //invalid color
            {
                string errStr = "Invalid Color: " + name + "\n";
                errStr += "Must be a hexadecimal(#RRGGBBAA, #RRGGBB, #RGBA, or #RGB) color representation;\n";
                errStr += "Or one of these supported named colors: ";
                for(const auto& p: ColorNames)
                {
                    errStr += " \"" + p.first + "\"";
                }
                errStr+="\n";
                throw errStr;
            }
        }
        /** @return Legal CSS color value */
        string getCSSrep() const
        {
            string strCSS = to_string(getRed())+","+to_string(getGreen())+","+to_string(getBlue());
            if(isOpaque())//leaves off alpha if unnessesary
            {
                strCSS = "rgb("+strCSS+")";
            }
            else
            {
                strCSS = "rgba("+strCSS+","+removeTrailingZeros(static_cast<double>(getAlpha())/255.0)+")";
            }
            return strCSS;
        }
    private:
        /** Removes unnessasary trailing 0s to lower size of JSON string */
		static string removeTrailingZeros(const double& num)
        {
            if(static_cast<int>(num) == num){return to_string(static_cast<int>(num));}//if integer return as int
            string numRep = to_string(num);
            numRep.erase(numRep.find_last_not_of("0")+1);//removes trailing 0s
            return numRep;
        }
        /** Converts int to appropriate hex value */
        static string to_hex(const int& val)
        {
            string hex;
            if(val>=16) //get greater 16 powers recursively
            {
                hex = to_hex(val/16);
            }
            switch(val%16) //tack on this 16 place
            {
            case 10: hex += "a"; break;
            case 11: hex += "b"; break;
            case 12: hex += "c"; break;
            case 13: hex += "d"; break;
            case 14: hex += "e"; break;
            case 15: hex += "f"; break;
            default: hex += to_string(val%16);
            }
            return hex;
        }
};//end of color class
const regex Color::HEX_RANGE("^#([[:xdigit:]]{8}|[[:xdigit:]]{6}|[[:xdigit:]]{3,4})$");//greedy, so checks for 8(RRGGBBAA), then 6(RRGGBB) then 4(RGBA) then 3(RGB)
const unordered_map<string,array<int,4>>
    Color::ColorNames
    {
        {"red",   {{255,  0,  0,255}}}, //Primary
        {"yellow",{{255,255,  0,255}}}, //Primary
        {"blue",  {{  0,  0,255,255}}}, //Primary
        {"orange",{{255,165,  0,255}}}, //Secondary
        {"green", {{  0,128,  0,255}}}, //Secondary(full 255 is considered lime by CSS)
        {"purple",{{128,  0,128,255}}}, //Secondary
        {"brown", {{165, 42, 42,255}}}, //Neutral
        {"black", {{  0,  0,  0,255}}}, //Monochrome
        {"grey",  {{192,192,192,255}}}, //Monochrome
        {"white", {{255,255,255,255}}}  //Monochrome
    };
}//end of bridge namespace
#endif
