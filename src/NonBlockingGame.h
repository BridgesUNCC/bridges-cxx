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
  };

  class NonBlockingGame : public GameBase {
    typedef std::chrono::steady_clock localclock;

    InputHelper ih;

    int fps = 30;

    localclock::time_point timeOfLastFrame;
  
  public:
  NonBlockingGame(int assignmentID, std::string username, std::string apikey)
    :GameBase(assignmentID, username, apikey) {
      sockcon->registerKeyListener(&ih);
    }

    virtual void initialize () = 0;
    virtual void GameLoop () = 0;

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
  
  
    void start() {
      timeOfLastFrame = localclock::now();
      initialize();
    
      while(true) {
	GameLoop();
	render();
	handleFrameRate();
      }
    }

    ///@return true if Left is currently pressed
    bool KeyLeft() {
      return ih.keyLeft();
    }

    ///@return true if Right is currently pressed
    bool KeyRight() {
      return ih.keyRight();
    }

    ///@return true if Up is currently pressed
    bool KeyUp() {
      return ih.keyUp();
    }

    ///@return true if Down is currently pressed
    bool KeyDown() {
      return ih.keyDown();
    }
  };
}

#endif
