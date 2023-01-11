#ifndef NONBLOCKING_GAME_H
#define NONBLOCKING_GAME_H

#include <GameBase.h>
#include <InputHelper.h>
#include <InputStateMachine.h>

namespace bridges {
	namespace game {

		/**
		 * @brief This class provides the features necessary to implement  simple non blocking games.
		 *
		 * The games that can be created out of NonBlockingGame are
		 * based on a simple board grid of at most 1024 cells (e.g.,
		 * 32x32, or any combinations less than 1024 cells). Each
		 * cell has a background color, and a colored symbol.
		 *
		 * This class is used by having another class derive
		 * from it and implement the two functions: initialize()
		 * and GameLoop(). initialize() is called exactly
		 * once, on the first frame of the game. It is used to
		 * make first time initializations of the game state
		 * (such as setting the board in its initial position,
		 * for instance in chess). However, GameLoop() is called
		 * at every frame of the game. The game starts when the
		 * function start() is called on the object you
		 * created.
		 *
		 * For this reason the simplest game that can run is created
		 * by:
		 *
		 * \code{.cpp}
		 * #include <NonBlockingGame.h>
		 * using namespace bridges::game;
		 * struct my_game : public NonBlockingGame {
		 *   my_game() : NonBlockingGame (1, "myuserid",  "myapikey") {}
		 *   virtual void initialize() override { }
		 *   virtual void GameLoop() override { }
		 * };
		 *
		 * int main () {
		 *   my_game g;
		 *   g.start();
		 * }
		 * \endcode
		 *
		 * This game does not do anything, but it is the
		 * minimal code that will run a game. Note that the
		 * constructor of my_game passes 3 parameters to the
		 * constructor of NonBlockingGame(). These three
		 * parameters are the classic parameters that the
		 * constructor of bridges::Bridges takes (e.g.,
		 * assignmentID, username, apikey).
		 *
		 * To change the board, two functions are
		 * used. setBGColor() change the background color of a
		 * particular cell. It takes three parameters, the
		 * first two identify the cell of the board to change,
		 * and the last one is a color from a color palette
		 * provided by NamedColor. drawSymbol() takes four
		 * parameters, the first two identify the cell of the
		 * board to change, the third is a symbol from a
		 * symbol palette provided by NamedSymbol, the fourth
		 * is the color that symbol shold be drawn in and
		 * provided by NamedColor.
		 *
		 * For instance, a very simple initialize() could look like:
		 * \code{.cpp}
		 * virtual void initialize() override {
		 *   setBGColor(0, 0, NamedColor.lightsalmon);
		 *   drawSymbol(0, 0, NamedSymbol.sword, NamedColor.blue);
		 * }
		 * \endcode
		 *
		 * Note that the size of the board is set by default
		 * at 10x10 and that drawing on a cell that does not
		 * exist will lead to an error. One can specify a
		 * gameboard of a different size by passing additional
		 * parameters to the NonBlockingGame
		 * constructor. However, the game can not be more than
		 * 1024 cells in total, so a 15x15 board is possible,
		 * a 32x32 board is the largest square board possible,
		 * and a rectangular 64x16 rectangular board is also
		 * possible. But a 100x20 board would be 2000 cells
		 * and is not possible. For instance a board of 16
		 * rows and 64 columns can be created defining the
		 * my_game constructor as:
		 *
		 * \code{.cpp}
		 *   my_game() : NonBlockingGame (1, "myuserid",  "myapikey", 16, 64) {}
		 * \endcode
		 *
		 * The bridges game engine will call the GameLoop()
		 * function at each frame of the game. You can write
		 * this function to modify the state of the game board
		 * using setBGColor() and drawSymbol(). For instance,
		 * the following GameLoop() will color the board
		 * randomly one cell at a time.
		 *
		 * \code{.cpp}
		 * virtual void gameLoop() override {
		 *   setBGColor(rand()%10, rand()%10, NamedColor.lightsalmon);
		 * }
		 * \endcode
		 *
		 * The gameLoop can also probe the state of some keys
		 * of the keyboard using functions keyUp(), keyLeft(),
		 * keyDown(), keyRight(), keyW(), keyA(), keyS(),
		 * keyD(), keySpace(), and keyQ(). These functions
		 * return a boolean that indicate whether the key is
		 * pressed at that frame or not. For instance, the
		 * following code will only color the board randomly
		 * when the up arrow is pressed.
		 *
		 * \code{.cpp}
		 * virtual void gameLoop() override {
		 *   if (keyUp())
		 *     setBGColor(rand()%10, rand()%10, NamedColor.lightsalmon);
		 * }
		 * \endcode
		 *
		 * @sa There is a tutorial at: https://bridgesuncc.github.io/tutorials/NonBlockingGame.html
		 *
		 * @author Erik Saule
		 * @date 7/21/19, 12/28/20
		 *
		 **/
		class NonBlockingGame : public GameBase {
			private:
				using GameBase::render;
				using GameBase::registerKeyListener;

				typedef std::chrono::steady_clock localclock;

				InputHelper ih;
				InputStateMachine upSM;
				InputStateMachine downSM;
				InputStateMachine leftSM;
				InputStateMachine rightSM;

				InputStateMachine qSM;
				InputStateMachine spaceSM;

				InputStateMachine wSM;
				InputStateMachine aSM;
				InputStateMachine sSM;
				InputStateMachine dSM;

		  
		  
				double fps = 30.;

				localclock::time_point timeOfLastFrame;

				void handleFrameRate() {
					using std::chrono::seconds;
					using std::chrono::microseconds;
					using std::chrono::duration_cast;

					microseconds frametime = duration_cast<microseconds>(seconds(1l)) / (int)fps;

					localclock::time_point theoretical_next_frame = timeOfLastFrame + frametime;

					auto wait_time = theoretical_next_frame - localclock::now();

					if (wait_time.count() > 0) {
						microseconds wait_time_in_us = duration_cast<microseconds>(wait_time);
						usleep(wait_time_in_us.count());
					}

					timeOfLastFrame = localclock::now();
				}

		  void updateInputState() {
		    upSM.update();
		    downSM.update();
		    leftSM.update();
		    rightSM.update();

		    qSM.update();
		    spaceSM.update();

		    wSM.update();
		    aSM.update();
		    sSM.update();
		    dSM.update();
		  }

			public:
				/// constructor
				/// @param assignmentID  Bridges assignment id
				/// @param username      Bridges user name
				/// @param apikey        Bridges API authentication key
				/// @param nbRow         GameGrid height
				/// @param nbCol         GameGrid width
				NonBlockingGame(int assignmentID, std::string username,
					std::string apikey, int nbRow = 10, int nbCol = 10)
				  : GameBase(assignmentID, username, apikey, nbRow, nbCol),
				    ih(),
				    upSM([this]() ->bool {return this->ih.keyUp();}),
				    downSM([this]() ->bool {return this->ih.keyDown();}),
				    leftSM([this]() ->bool {return this->ih.keyLeft();}),
				    rightSM([this]() ->bool {return this->ih.keyRight();}),

				    qSM([this]() ->bool {return this->ih.keyQ();}),
				    spaceSM([this]() ->bool {return this->ih.keySpace();}),

				    wSM([this]() ->bool {return this->ih.keyW();}),
				    aSM([this]() ->bool {return this->ih.keyA();}),
				    sSM([this]() ->bool {return this->ih.keyS();}),
				    dSM([this]() ->bool {return this->ih.keyD();})
		  {
					if (debug)
						std::cerr << "nbRow: " << nbRow << " nbCol: " <<
							nbCol << std::endl;

					if (nbRow * nbCol > 32 * 32) {
						throw "NonBlockingGame can not have a grid of more than 32x32 (or a combination(so 16x64 is ok; 16x128 is not)";
					}

					registerKeyListener(&ih);

				}

		  virtual ~NonBlockingGame() =default;
		  
				/// @brief Call this function from main to start the game. Runs
				/// exactly once.
				void start() {
					timeOfLastFrame = localclock::now();
					initialize();

					long framelimit = -1; //negative means no limit
					{
						char* str_limit = getenv("FORCE_BRIDGES_FRAMELIMIT");
						if (str_limit != nullptr) {
							std::stringstream ss;
							ss << str_limit;
							ss >> framelimit;
							std::cerr << "Setting framelimit to " << framelimit << std::endl;
						}
					}
					long frame = 0;
					while (!gameover()) {
					  updateInputState();
						gameLoop();
						render();
						handleFrameRate();
						frame++;
						if (framelimit > 0 && frame > framelimit)
							quit();
					}
				}


			protected:
				/// @brief What frame rate is the game running at?
				///
				/// @return the target framerate. The game could be somewhat
				/// slower depending on how computationally expensive the
				/// gameloop is and on the speed of the network.
				double getFrameRate() const {
					return fps;
				}

				///@brief Is Left currently pressed?
				///
				///@return true if Left is currently pressed
				bool keyLeft() {
					return ih.keyLeft();
				}
    bool keyLeftJustPressed() {
        return leftSM.justPressed();
    }
    bool keyLeftStillPressed() {
        return leftSM.stillPressed();
    }
    bool keyLeftJustNotPressed() {
        return leftSM.justNotPressed();
    }
    bool keyLeftStillNotPressed() {
        return leftSM.stillNotPressed();
    }
    bool keyLeftFire() {
        return leftSM.fire();
    }
    void keyLeftSetupFire(int f) {
        leftSM.setFireCooldown(f);
    }
				///@brief Is Right currently pressed?
				///
				///@return true if Right is currently pressed
				bool keyRight() {
					return ih.keyRight();
				}
    bool keyRightJustPressed() {
        return rightSM.justPressed();
    }
    bool keyRightStillPressed() {
        return rightSM.stillPressed();
    }
    bool keyRightJustNotPressed() {
        return rightSM.justNotPressed();
    }
    bool keyRightStillNotPressed() {
        return rightSM.stillNotPressed();
    }
    bool keyRightFire() {
        return rightSM.fire();
    }
    void keyRightSetupFire(int f) {
        rightSM.setFireCooldown(f);
    }
				///@brief Is Up currently pressed?
				///
				///@return true if Up is currently pressed
				bool keyUp() {
					return ih.keyUp();
				}


    bool keyUpJustPressed() {
        return upSM.justPressed();
    }
    bool keyUpStillPressed() {
        return upSM.stillPressed();
    }
    bool keyUpJustNotPressed() {
        return upSM.justNotPressed();
    }
    bool keyUpStillNotPressed() {
        return upSM.stillNotPressed();
    }
    bool keyUpFire() {
        return upSM.fire();
    }
    void keyUpSetupFire(int f) {
        upSM.setFireCooldown(f);
    }






		  
				///@brief Is Down currently pressed?
				///
				///@return true if Down is currently pressed
				bool keyDown() {
					return ih.keyDown();
				}

    bool keyDownJustPressed() {
        return downSM.justPressed();
    }
    bool keyDownStillPressed() {
        return downSM.stillPressed();
    }
    bool keyDownJustNotPressed() {
        return downSM.justNotPressed();
    }
    bool keyDownStillNotPressed() {
        return downSM.stillNotPressed();
    }
    bool keyDownFire() {
        return downSM.fire();
    }
    void keyDownSetupFire(int f) {
        downSM.setFireCooldown(f);
    }

		  
				///@brief Is W currently pressed?
				///
				///@return true if W is currently pressed
				bool keyW() {
					return ih.keyW();
				}

    bool keyWJustPressed() {
        return wSM.justPressed();
    }
    bool keyWStillPressed() {
        return wSM.stillPressed();
    }
    bool keyWJustNotPressed() {
        return wSM.justNotPressed();
    }
    bool keyWStillNotPressed() {
        return wSM.stillNotPressed();
    }
    bool keyWFire() {
        return wSM.fire();
    }
    void keyWSetupFire(int f) {
        wSM.setFireCooldown(f);
    }
		  
				///@brief Is A currently pressed?
				///
				///@return true if A is currently pressed
				bool keyA() {
					return ih.keyA();
				}


    bool keyAJustPressed() {
        return aSM.justPressed();
    }
    bool keyAStillPressed() {
        return aSM.stillPressed();
    }
    bool keyAJustNotPressed() {
        return aSM.justNotPressed();
    }
    bool keyAStillNotPressed() {
        return aSM.stillNotPressed();
    }
    bool keyAFire() {
        return aSM.fire();
    }
    void keyASetupFire(int f) {
        aSM.setFireCooldown(f);
    }
		  
				///@brief Is S currently pressed?
				///
				///@return true if S is currently pressed
				bool keyS() {
					return ih.keyS();
				}


    bool keySJustPressed() {
        return sSM.justPressed();
    }
    bool keySStillPressed() {
        return sSM.stillPressed();
    }
    bool keySJustNotPressed() {
        return sSM.justNotPressed();
    }
    bool keySStillNotPressed() {
        return sSM.stillNotPressed();
    }
    bool keySFire() {
        return sSM.fire();
    }
    void keySSetupFire(int f) {
        sSM.setFireCooldown(f);
    }
		  
				///@brief Is D currently pressed?
				///
				///@return true if D is currently pressed
				bool keyD() {
					return ih.keyD();
				}

    bool keyDJustPressed() {
        return dSM.justPressed();
    }
    bool keyDStillPressed() {
        return dSM.stillPressed();
    }
    bool keyDJustNotPressed() {
        return dSM.justNotPressed();
    }
    bool keyDStillNotPressed() {
        return dSM.stillNotPressed();
    }
    bool keyDFire() {
        return dSM.fire();
    }
    void keyDSetupFire(int f) {
        dSM.setFireCooldown(f);
    }
				///@brief Is Q currently pressed?
				///
				///@return true if S is currently pressed
				bool keyQ() {
					return ih.keyQ();
				}
    bool keyQJustPressed() {
        return qSM.justPressed();
    }
    bool keyQStillPressed() {
        return qSM.stillPressed();
    }
    bool keyQJustNotPressed() {
        return qSM.justNotPressed();
    }
    bool keyQStillNotPressed() {
        return qSM.stillNotPressed();
    }
    bool keyQFire() {
        return qSM.fire();
    }
    void keyQSetupFire(int f) {
        qSM.setFireCooldown(f);
    }
				///@brief Is Space currently pressed?
				///
				///@return true if Space is currently pressed
				bool keySpace() {
					return ih.keySpace();
				}
    bool keySpaceJustPressed() {
        return spaceSM.justPressed();
    }
    bool keySpaceStillPressed() {
        return spaceSM.stillPressed();
    }
    bool keySpaceJustNotPressed() {
        return spaceSM.justNotPressed();
    }
    bool keySpaceStillNotPressed() {
        return spaceSM.stillNotPressed();
    }
    bool keySpaceFire() {
        return spaceSM.fire();
    }
    void keySpaceSetupFire(int f) {
        spaceSM.setFireCooldown(f);
    }
		};
	}
}

#endif
