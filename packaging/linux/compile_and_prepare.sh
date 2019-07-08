#!/bin/sh

##first reset all submodules to 
git submodule deinit -f .
git submodule update --init


## get rapidjson properly set up. Disabling docs, examples, and tests
( cd ../dependencies/rapidjson;
cmake -D CMAKE_INSTALL_PREFIX=../../linux/build/rapidjson \
      -D RAPIDJSON_BUILD_TESTS=OFF \
      -D RAPIDJSON_BUILD_EXAMPLES=OFF \
      -D RAPIDJSON_BUILD_DOC=OFF
      . ;
make install ;
)

##get websocket properly set up in linux/build/
( cd ../dependencies/websocketpp; cmake -D CMAKE_INSTALL_PREFIX=../../linux/build/websocketpp . ; make install )


##get SocketIO properly setup in linux/build
#socket IO package does not seem to make install correctly, so coppying data manually
#the cp of internal is due to bridges using a hack for the moment.
( cd ../dependencies/socket.io-client-cpp
  cmake -D CMAKE_INSTALL_PREFIX=../../linux/build/socket.io-client-cpp  \
        -D CMAKE_CXX_FLAGS="-I ../../linux/build/websocketpp/include -I ../../linux/build/rapidjson/include" \
	.
  make -j 8 ;
  make install ;
  mv build ../../linux/build/socket.io-client-cpp;
  cp -r src/internal ../../linux/build/socket.io-client-cpp/include ;
)


##last reset all submodules to 
git submodule deinit -f .
git submodule update --init
