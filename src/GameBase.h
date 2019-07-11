#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <SocketConnection.h>



namespace bridges {
  class GameBase {
  private:
    Bridges bridges;

    GameGrid gg;

    bool firsttime = true;


    std::unique_ptr<SocketConnection> sockcon;

  protected:
    bool debug = true;
    
  
    ///Having a protected constructor prevent the object from being
    ///directly created. Since GameBase is meant to be a purely internal
    ///class, that seems appropriate.
    GameBase(int assignmentID, std::string username, std::string apikey, int nbRow=10, int nbColumn=10)
      :bridges(assignmentID, username, apikey), gg(nbRow, nbColumn) {
      bridges.setServer("games");

      sockcon = std::make_unique<SocketConnection>(bridges);

      if (debug)
	std::cerr<<"nbRow: "<<nbRow<<" nbCol: "<<nbColumn<<std::endl;
    }


    virtual void initialize () = 0;
    virtual void GameLoop () = 0;

    
  protected:
    void registerKeyListener(KeypressListener* p) {
      sockcon->registerKeyListener(p);
    }

    void render() {
      if (firsttime) {
	bridges.setVisualizeJSONFlag(true);
    
	bridges.setDataStructure(&gg);

	bridges.visualize();

	firsttime = false;
      
      }

      sockcon->sendGameGrid(gg);
    }

  protected:
    void setBGColor(int row, int col, NamedColor nc) {
      gg.setBGColor(row, col, nc);
    }

    void drawObject(int row, int col, NamedSymbol symb, NamedColor nc) {
      gg.drawObject(row, col, symb, nc);
    }


  };
}

#endif
