#!/bin/sh

reinit() {
    git clean -ffdx ## This restore the directory to a clean build setting by removing all untracked files even if they are part of git ignore
}

##first reset all submodules to 
reset_installation() {

    git submodule deinit -f .
    git submodule update --init
    git submodule foreach 'git clean -ffdx'
}

## Getting boost properly setup
install_boost() {
    ( cd ../dependencies/boost ;
      git submodule init ;
      git submodule update ;
      ./bootstrap.sh --with-libraries=system,date_time,random ; # only need a few libraries; #no need for prefix becasue we won't install in the end
      ./b2 headers ;
      ./b2 ;
      #./b2 install ## ./b2 install is not necessary because socketio will copy what it needs
    )
}

## get rapidjson properly set up. Disabling docs, examples, and tests
install_rapidjson() {
    ( cd ../dependencies/rapidjson;
      cmake -D CMAKE_INSTALL_PREFIX=../../unix/build/rapidjson \
	    -D RAPIDJSON_BUILD_TESTS=OFF \
	    -D RAPIDJSON_BUILD_EXAMPLES=OFF \
	    -D RAPIDJSON_BUILD_DOC=OFF \
      . ;
      make -j 4 install ;
    )
}

##get websocket properly set up in unix/build/
install_websocketpp() {
    (
	cd ../dependencies/websocketpp;
	cmake -D CMAKE_INSTALL_PREFIX=../../unix/build/websocketpp . ;
	make -j 4 install
    )
}


##get SocketIO properly setup in unix/build
install_socketIO() {
    #socket IO package does not seem to make install correctly, so coppying data manually
    #the cp of internal is due to bridges using a hack for the moment.
    ( cd ../dependencies/socket.io-client-cpp
      cmake -D CMAKE_BUILD_TYPE=Release \
	    -D Boost_USE_STATIC_LIBS=ON \
            -D CMAKE_INSTALL_PREFIX=../../unix/build/socket.io-client-cpp  \
            -D CMAKE_CXX_FLAGS="-I ../../unix/build/websocketpp/include -I ../../unix/build/rapidjson/include" \
	    -D Boost_DEBUG=OFF -D CMAKE_VERBOSE_MAKEFILE=OFF \
	    -D Boost_USE_DEBUG_LIBS=OFF \
	    -D BOOST_INCLUDEDIR=../boost/ -D BOOST_LIBRARYDIR=../boost/stage/lib -D BOOST_VER=1.64.0 \
	    .
      make -j 8 ;
      make -j 4 install ;
      mv build ../../unix/build/socket.io-client-cpp;
      cp -r src/internal ../../unix/build/socket.io-client-cpp/include ;
    )
}

build_distribute() {
    TARGETDIR="bridges-cxx-$(git describe --tags)-$(gcc -dumpmachine)" #if gcc isn't there we have bigger problems
    rm -rf ${TARGETDIR}
    mkdir ${TARGETDIR}
    
    INCLUDEDIR=${TARGETDIR}/include
    LIBDIR=${TARGETDIR}/lib
    
    mkdir ${INCLUDEDIR}
    mkdir ${LIBDIR}
    
    #copy bridges headers
    cp ../../src/*.h ${INCLUDEDIR}
    cp -r ../../src/data_src ${INCLUDEDIR}  #no / after data_src to copy the directory and not its content
    
    #copy rapidjson
    cp -r build/rapidjson/include/rapidjson ${INCLUDEDIR}
    
    #copy socketio
    cp -r build/socket.io-client-cpp/include/* ${INCLUDEDIR}
    
    cp -r build/socket.io-client-cpp/lib/Release/* ${LIBDIR}


    #
    (
	cd ${TARGETDIR}/lib ;
	ar x libboost_system.a ;
	ar x libsioclient.a ;
	if [ "$(uname)" = "Linux" ] ; #on linux, need to include libstdc++. macos does not have that problem
	then
	   ar x $(gcc -print-file-name=libstdc++.a) ;
	fi
	rm *.a ;
	ar qc libbridges.a *.o ;
	rm *.o ;
    )

    tar zcvf ${TARGETDIR}.tgz ${TARGETDIR}
}


reinit
reset_installation
install_boost
install_rapidjson
install_websocketpp
install_socketIO
build_distribute
reset_installation
