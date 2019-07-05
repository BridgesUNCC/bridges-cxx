
#include <string>
using namespace std;

#ifndef GAME_GRID_H
#define GAME_GRID_H 1

#include "Grid.h"
#include "Color.h"
#include "base64.h"

/**
 * @brief This is a class in BRIDGES for representing an (n x n) game grid.
 *
 * @author Erik Saule
 * @param
 **/
namespace bridges {

   enum class NamedColor {
  aliceblue,
  antiquewhite,
  aqua,
  aquamarine,
  azure,
  beige,
  bisque,
  black,
  blanchedalmond,
  blue,
  blueviolet,
  brown,
  burlywood,
  cadetblue,
  chartreuse,
  chocolate,
  coral,
  cornflowerblue,
  cornsilk,
  crimson,
  cyan,
  darkblue,
  darkcyan,
  darkgoldenrod,
  darkgray,
  darkgreen,
  darkgrey,
  darkkhaki,
  darkmagenta,
  darkolivegreen,
  darkorange,
  darkorchid,
  darkred,
  darksalmon,
  darkseagreen,
  darkslateblue,
  darkslategray,
  darkslategrey,
  darkturquoise,
  darkviolet,
  deeppink,
  deepskyblue,
  dimgray,
  dimgrey,
  dodgerblue,
  firebrick,
  floralwhite,
  forestgreen,
  fuchsia,
  gainsboro,
  ghostwhite,
  gold,
  goldenrod,
  gray,
  grey,
  green,
  greenyellow,
  honeydew,
  hotpink,
  indianred,
  indigo,
  ivory,
  khaki,
  lavender,
  lavenderblush,
  lawngreen,
  lemonchiffon,
  lightblue,
  lightcoral,
  lightcyan,
  lightgoldenrodyellow,
  lightgray,
  lightgreen,
  lightgrey,
  lightpink,
  lightsalmon,
  lightseagreen,
  lightskyblue,
  lightslategray,
  lightslategrey,
  lightsteelblue,
  lightyellow,
  lime,
  limegreen,
  linen,
  magenta,
  maroon,
  mediumaquamarine,
  mediumblue,
  mediumorchid,
  mediumpurple,
  mediumseagreen,
  mediumslateblue,
  mediumspringgreen,
  mediumturquoise,
  mediumvioletred,
  midnightblue,
  mintcream,
  mistyrose,
  moccasin,
  navajowhite,
  navy,
  oldlace,
  olive,
  olivedrab,
  orange,
  orangered,
  orchid,
  palegoldenrod,
  palegreen,
  paleturquoise,
  palevioletred,
  papayawhip,
  peachpuff,
  peru,
  pink,
  plum,
  powderblue,
  purple,
  red,
  rosybrown,
  royalblue,
  saddlebrown,
  salmon,
  sandybrown,
  seagreen,
  seashell,
  sienna,
  silver,
  skyblue,
  slateblue,
  slategray,
  slategrey,
  snow,
  springgreen,
  steelblue,
  tan,
  teal,
  thistle,
  tomato,
  turquoise,
  violet,
  wheat,
  white,
  whitesmoke,
  yellow,
  yellowgreen
   };

   enum class NamedSymbol {
     none,
     A,
     B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  a,
  b,
  c,
  d,
  e,
  f,
  g,
  h,
  i,
  j,
  k,
  l,
  m,
  n,
  o,
  p,
  q,
  r,
  s,
  t,
  u,
  v,
  w,
  x,
  y,
  z,
  zero,
  one,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  empty0,
  circle,
  square,
  diamond,
  triangle_down,
  triangle_up,
  triangle_left,
  triangle_right,
  man,
  woman,
  cat,
  pawn,
  knight,
  bishop,
  rook,
  queen,
  king,
  arrow_right,
  arrow_left,
  arrow_up,
  arrow_down,
  star,
  droplet,
  heart,
  lightning,
  thoughtbubble,
  speechbubble,
  flower,
  square_thatch,
  circle_x,
  circle_x2,
  circle_segment,
  empty1,
  sword,
  horn_helmet,
  astro_helmet,
  target,
  empty2,
  waves,
  rain,
  drink,
  paperclip,
  elephant,
  cowboyhat,
  ballcap,
  flag,
  bomb,
  bear,
  giraffe,
  bug1,
  bug2,
  bug3,
  magnifying_glass,
  fishes,
  duck,
  sloth,
  bird,
  apple,
  carrot,
  lemon,
  pepper,
  onion,
  potion1,
  potion2,
  bow_and_arrow,
  campfire,
  donut,
  monitor
};

   
   class GameCell {
     NamedColor bg;
     NamedColor fg;
     NamedSymbol symbol;
     
   public:
     GameCell() {
       bg = NamedColor::black;
       fg = NamedColor::white;
       symbol = NamedSymbol::none;
     }

     GameCell(NamedColor bg, NamedColor fg, NamedSymbol symbol) {
       this->bg = bg;
       this->fg = fg;
       this->symbol = symbol;
     }
     
     /**
      *  Set background color using NamedColor Enum argument
      *  @param bg - Named Color from the NamedColor enum
      */
     void setBGColor(NamedColor bg) {
       this->bg = bg;
     }
     
     /**
      *  Set foreground color using NamedColor Enum argument
      *  @param fg - Named Color from the NamedColor enum
      */
     void setFGColor(NamedColor fg) {
       this->fg = fg;
     }

     /**
      *  Set symbol using int argument
      *  @param s - Named symbol
      */
      void setSymbol(NamedSymbol s) {
       this->symbol = s;
     }

      NamedColor getBGColor() const {
	return bg;
      }

      NamedColor getFGColor() const {
	return fg;
      }
      
      NamedSymbol getSymbol() const {
	return symbol;
      }     

   };
   
  
	class GameGrid : public Grid<GameCell> {
		private:

		public:


	  /**
	   *  Set background color of a cell using an enum argument
	   *
	   *  @param row, col - integer indices specifying the position to modify
	   *  @param color - Named Color enum argument to set the background at the chosen position
	   */
	  void setBGColor(int row, int col, NamedColor color) {
	    (*this)[row][col].setBGColor(color);
	  }

	  
	  /**
	   *  Set foreground color of a cell using an enum argument
	   *
	   *  @param row, col - integer indices specifying the position to modify
	   *  @param color - Named Color enum argument to set the foreground at the chosen position
	   */
	  void setFGColor(int row, int col, NamedColor color) {
	    (*this)[row][col].setFGColor(color);
	  }

	  /**
	   *  Set the symbol of a cell using an enum argument
	   *
	   *  @param row, col - integer indices specifying the position to modify
	   *  @param symbol - the symbol to set
	   */
	  void setSymbol(int row, int col, NamedSymbol symbol) {
	    (*this)[row][col].setSymbol(symbol);
	  }

	  
	  /**
	   *  Draw a symbol at the specified location
	   *  @param row, col - integer indices specifying the position to modify
	   *  @param symbol - Integer symbol argument to set the symbol at the chosen position
	   *  @param
	   */
	  void drawObject(int row, int col,
				 NamedSymbol symbol, NamedColor color) {
	    setFGColor(row, col, color);

	  }

	  
	  virtual const string getDStype() const override {
	    return "GameGrid";
	  }
	  
	  /**
	   * GameGrid constructors
	   *
	   **/
	  GameGrid () : Grid<GameCell> () {
	    //initializeGrid(baseColor);
	  }
	  
	  
	private:
	  
	  //public:
	  /**
	   * get the JSON representation of the game grid
	   *
	   * @return the JSON representation of the game grid
	   **/
	  virtual const string getDataStructureRepresentation () const override {
	    
	    return "";
	  }
	  

	};
} // end namespace bridges

#endif
