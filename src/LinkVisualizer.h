#ifndef LINK_VISUALIZER_H
#define LINK_VISUALIZER_H

#include "Color.h" //string, using std

namespace bridges{

template<typename E> class Element; //Forward Declaration for Befriendment

/**
 * @brief This class maintains the visual properties of links within data structures.
 *
 * This class is used to keep the visual properties of links that are part of
 * data structures such as linked lists, pointer based trees, link based
 * graph representations, etc.  Relevant attributes include color and thickness
 *
 * Objects of this class are stored as properties of Elements.
 * A user may manipulate the LinkVisualizer returned from the Element's getLinkVisualizer() method.
 *
 * BRIDGES supports color of any legal named CSS or #hexadecimal value. Defalt: opaque black
 * Thickness values must range from [0.0,10.0]. Default: 1.0
 *
 * @author Kalpathi Subramanian
 * @date 6/29/15
 */
class LinkVisualizer
{
    template<typename E> friend class Element; //Used to access getJSONrepresentation()

    public:
        /** The default thickness of a link */
        static constexpr double DEFAULT_THICKNESS = 1.0;
        /** The default color of a link */
        static const Color DEFAULT_COLOR; //black
	private:
		/** This link's color */
		Color color=DEFAULT_COLOR;
		/** This link's thickness */
		double thickness=DEFAULT_THICKNESS;
	public:
		/**
		 * Constructs a LinkVisualizer with the specified color and thickness.
		 * The defaults will be used if not provided (black,1)
		 *
		 * @param col Link color
		 * @param thick Link thickness
		 */
		LinkVisualizer(Color col = DEFAULT_COLOR,double thick = DEFAULT_THICKNESS) : color(col){setThickness(thick);}
		/**
		 * Set the thickness to "thick"
		 * Valid Range:[0,10] Default: 1
		 *
		 * @param thick The size in pixels of the link's line weight
		 * @throw string If invalid thickness
		 */
		void setThickness(const double& thick){(thick<0||10<thick)?throw "Invalid Thickness Value.. "+to_string(thick)+" Must be in the [0.0,10.0] range" : thickness=thick;}
        /** @return Size in pixels of the link's line weight */
		double getThickness() const {return thickness;}
		/**
		 * Set the color to "col"
		 * Default: black
		 *
		 * @param col The color of the link
		 */
		void setColor(const Color& col){color = col;}
		/** @return The color of the link */
		Color getColor() const {return color;}
    private:
        /** @return to_string of "num" without unnessasary trailing 0s */
		static string removeTrailingZeros(const double& num)
        {
            if(static_cast<int>(num) == num){return to_string(static_cast<int>(num));}//if integer return as int
            string numRep = to_string(num);
            numRep.erase(numRep.find_last_not_of("0")+1);//removes trailing 0s
            return numRep;
        }
		/**
		 * Gets the JSON representation of this link visualizer using the supplied source and destination strings
		 *
		 * @param src The source vertex
		 * @param dest The destination vertex
		 * @return The JSON of this link visualizer
		 */
        string getJSONrepresentation(const string& src,const string& dest) const
        {
            return
            OPEN_CURLY +
                //write out LinkVisualizer properties
                QUOTE + "color"     + QUOTE + COLON + QUOTE + getColor().getCSSrep()              + QUOTE + COMMA +
                QUOTE + "thickness" + QUOTE + COLON + QUOTE + removeTrailingZeros(getThickness()) + QUOTE + COMMA +
                //write out the source and targets of the link
                QUOTE + "source" + QUOTE + COLON + src  + COMMA +
                QUOTE + "target" + QUOTE + COLON + dest +
            CLOSE_CURLY;
        }
}; //end of LinkVisualizer class
constexpr double LinkVisualizer::DEFAULT_THICKNESS;
const Color LinkVisualizer::DEFAULT_COLOR("black");
}//end of bridges namespace
#endif
