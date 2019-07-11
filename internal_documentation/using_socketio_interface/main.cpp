//
//  sio_test_sample.cpp
//
//  Created by Melo Yao on 3/24/15.
//

#include "sio_client.h"


#include "Bridges.h"
#include "GameGrid.h"
#include "Array.h"

using namespace bridges;



#include <unistd.h>

#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>



using namespace sio;
using namespace std;
std::mutex _lock;

std::condition_variable_any _cond;
bool connect_finish = false;

socket::ptr current_socket;


class connection_listener
{
    sio::client &handler;

public:
    
    connection_listener(sio::client& h):
    handler(h)
    {
    }
    

    void on_connected()
    {
      std::cout<<"connected!!"<<std::endl;
        _lock.lock();
        _cond.notify_all();
        connect_finish = true;


	_lock.unlock();
    }
    void on_close(client::close_reason const& reason)
    {
      std::cout<<"sio closed "<<std::endl;
        exit(0);
    }
    
    void on_fail()
    {
        std::cout<<"sio failed "<<std::endl;
        exit(0);
    }

  void on_keyup (string const& name, message::ptr const& data, bool isAck,message::list &ack_resp) {
    _lock.lock();
    string type = data->get_map()["type"]->get_string();
    string key = data->get_map()["key"]->get_string();
    
    std::cerr<<"type: "<<type<<" key: "<<key<<"\n";
    _lock.unlock();
    
  }

  void on_keydown (string const& name, message::ptr const& data, bool isAck,message::list &ack_resp) {
    _lock.lock();
    string type = data->get_map()["type"]->get_string();
    string key = data->get_map()["key"]->get_string();
    
    std::cerr<<"type: "<<type<<" key: "<<key<<"\n";
    _lock.unlock();
    
  }

  void on_announcement (string const& name, message::ptr const& data, bool isAck,message::list &ack_resp) {
    _lock.lock();
    std::cout<<"announcement something\n";
    _lock.unlock();
    
  }

  
};



int main (int argc, char*argv[])
{


    Bridges bridges(99, "esaulesomething", "880684136078");
    bridges.setServer("games");
     
    GameGrid gg;


    bridges.setVisualizeJSONFlag(true);
    
    bridges.setDataStructure(&gg);

    std::cerr<<static_cast<int>(gg.getBGColor(0,0))<<"\n";

    gg.setBGColor (0, 0, NamedColor::blue);

    std::cerr<<static_cast<int>(gg.getBGColor(0,0))<<"\n";

    gg.drawObject (3, 3, NamedSymbol::bear, NamedColor::yellow);


    bridges.setDataStructure(&gg);
	
    bridges.visualize();

  
    sio::client h;
    connection_listener l(h);
    
    h.set_open_listener(std::bind(&connection_listener::on_connected, &l));
    h.set_close_listener(std::bind(&connection_listener::on_close, &l,std::placeholders::_1));
    h.set_fail_listener(std::bind(&connection_listener::on_fail, &l));

    
    
    h.connect("ws://bridges-games.herokuapp.com/");
    
    _lock.lock();
    if(!connect_finish)
    {
        _cond.wait(_lock);
    }
    _lock.unlock();
    current_socket = h.socket();

    current_socket->on("keyup", std::bind(&connection_listener::on_keyup, &l,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    current_socket->on("keydown", std::bind(&connection_listener::on_keydown, &l,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    current_socket->on("announcement", std::bind(&connection_listener::on_announcement, &l,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    
    
    std::string user = "esaulesomething";
    
    std::string assID = "99";
    
    current_socket->emit("credentials",
			 "{\"user\":\"" + user
			 + "\",\"assignment\":\"" + assID
			 + "\"}");


    
    for (int i=1; i< 200; ++i) {

      std::cout<<"step "<<i<<"\n";
      
      gg.drawObject (i/10, i%10, NamedSymbol::bear, NamedColor::yellow);


      std::string gridjson = "{" + gg.getDataStructureRepresentation();

      current_socket->emit("gamegrid:recv", gridjson);
      
      sleep(1);
    }

    
    h.sync_close();
    h.clear_con_listeners();
    return 0;
}

