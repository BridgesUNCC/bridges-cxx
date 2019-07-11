#ifndef NONBLOCKING_GAME_H
#define NONBLOCKING_GAME_H

#include <GameBase.h>

namespace bridges {

  ///this is meant to be an internal class, not something that the library user will use
  class InputHelper: public KeypressListener {
    bool debug = false;
  
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
    bool q = false;
    bool space = false;

    
  private:
    void handleKey(std::string JSONmessage) {
      using namespace rapidjson;
      // ...
      rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> alloc;
      Document msg(&alloc);
      msg.Parse(JSONmessage.c_str());
    
      std::string type = msg["type"].GetString();

      bool setto = (type.compare("keydown") == 0);
    
      std::string key = msg["key"].GetString();
    
      if (key.compare("ArrowUp") == 0)
	up = setto;
      else if (key.compare("ArrowDown") == 0)
	down = setto;
      else if (key.compare("ArrowLeft") == 0)
	left = setto;
      else if (key.compare("ArrowRight") == 0)
	right = setto;
      else if (key.compare("w") == 0)
	w = setto;
      else if (key.compare("a") == 0)
	a = setto;
      else if (key.compare("s") == 0)
	s = setto;
      else if (key.compare("d") == 0)
	d = setto;
      else if (key.compare("q") == 0)
	q = setto;
      else if (key.compare(" ") == 0)
	space = setto;
    }

    
  protected:
    virtual void keyup(std::string JSONmessage) override {
      if (debug)
	std::cerr<<"InputHelper::keyup(\""<<JSONmessage<<"\")\n";
      handleKey(JSONmessage);
    }

    virtual void keydown(std::string JSONmessage) override {
      if (debug)
	std::cerr<<"InputHelper::keydown(\""<<JSONmessage<<"\")\n";
      handleKey(JSONmessage);
    }

  
  public:

    bool keyUp() const {
      return up;
    }

    bool keyDown() const {
      return down;
    }

    bool keyLeft() const {
      return left;
    }

    bool keyRight() const {
      return right;
    }

    bool keyW() const {
      return w;
    }
    bool keyA() const {
      return a;
    }
    bool keyS() const {
      return s;
    }
    bool keyD() const {
      return d;
    }
    bool keyQ() const {
      return q;
    }
    bool keySpace() const {
      return space;
    }
    
  };

  class NonBlockingGame : public GameBase {
  private:
    using GameBase::render;
    using GameBase::registerKeyListener; 

    typedef std::chrono::steady_clock localclock;

    InputHelper ih;

    int fps = 30;

    localclock::time_point timeOfLastFrame;

    void handleFrameRate() {
      using std::chrono::seconds;
      using std::chrono::microseconds;
      using std::chrono::duration_cast;
    
      microseconds frametime = duration_cast<microseconds>(seconds(1l)) / fps;

      localclock::time_point theoretical_next_frame = timeOfLastFrame + frametime;

      auto wait_time = theoretical_next_frame - localclock::now();
    
      if (wait_time.count() > 0) {
	microseconds wait_time_in_us = duration_cast<microseconds>(wait_time);
	usleep(wait_time_in_us.count());
      }

      timeOfLastFrame = localclock::now();
    }

    
  public:
    NonBlockingGame(int assignmentID, std::string username, std::string apikey, int nbRow=10, int nbCol=10)
      :GameBase(assignmentID, username, apikey, nbRow, nbCol) {
      if(debug)
	std::cerr<<"nbRow: "<<nbRow<<" nbCol: "<<nbCol<<std::endl;
      
      if (nbRow*nbCol > 32*32) {
	throw "NonBlockingGame can not have a grid of more than 32x32 (or a combination(so 16x64 is ok; 16x128 is not)";
      }

      registerKeyListener(&ih);
      
    }

    virtual void initialize () = 0;
    virtual void GameLoop () = 0;

  
  
    void start() {
      timeOfLastFrame = localclock::now();
      initialize();
    
      while(true) {
	GameLoop();
	render();
	handleFrameRate();
      }
    }


  protected:
    ///@return true if Left is currently pressed
    bool keyLeft() {
      return ih.keyLeft();
    }

    ///@return true if Right is currently pressed
    bool keyRight() {
      return ih.keyRight();
    }

    ///@return true if Up is currently pressed
    bool keyUp() {
      return ih.keyUp();
    }

    ///@return true if Down is currently pressed
    bool keyDown() {
      return ih.keyDown();
    }

    ///@return true if W is currently pressed
    bool keyW() {
      return ih.keyW();
    }

    ///@return true if A is currently pressed
    bool keyA() {
      return ih.keyA();
    }

    ///@return true if S is currently pressed
    bool keyS() {
      return ih.keyS();
    }

    ///@return true if D is currently pressed
    bool keyD() {
      return ih.keyD();
    }

    ///@return true if S is currently pressed
    bool keyQ() {
      return ih.keyQ();
    }

    ///@return true if Space is currently pressed
    bool keySpace() {
      return ih.keySpace();
    }

  };
}

#endif
