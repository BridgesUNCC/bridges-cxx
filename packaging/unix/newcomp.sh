
reinit() {
    git clean -ffdx ## This restore the directory to a clean build setting by removing all untracked files even if they are part of git ignore
}

##first reset all submodules to 
reset_installation() {

    git submodule deinit -f .
    git submodule update --init
    git submodule foreach 'git clean -ffdx'
    git submodule foreach --recursive git submodule update --init

}



compilesio() {
    (
    cd ../dependencies/socket.io-client-cpp/src
    cat > Makefile <<EOF
SOCKETIOFLAGS=-D BOOST_DATE_TIME_NO_LIB -D BOOST_REGEX_NO_LIB -D ASIO_STANDALONE -D _WEBSOCKETPP_CPP11_STL_ -D _WEBSOCKETPP_CPP11_FUNCTIONAL_
SOCKETIOINCLUDES=-I ../lib/asio/asio/include -I ../lib/websocketpp -I ../../rapidjson/include

CXXFLAGS=\$(SOCKETIOINCLUDES) \$(SOCKETIOFLAGS)


all: libsioclient.a

libsioclient.a: sio_client.o sio_socket.o internal/sio_client_impl.o internal/sio_packet.o
	ar qc libsioclient.a sio_client.o sio_socket.o internal/sio_client_impl.o internal/sio_packet.o

EOF

    make -j 4
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

    #get libs
    mv ../dependencies/socket.io-client-cpp/src/libsioclient.a ${LIBDIR}/libbridges.a
    
    #copy bridges headers
    cp ../../src/*.h ${INCLUDEDIR}
    cp -r ../../src/data_src ${INCLUDEDIR}  #no / after data_src to copy the directory and not its content

    #copy socket.io headers
    cp -r ../dependencies/socket.io-client-cpp/src/* ${INCLUDEDIR}

    #copy socket.io dependencies headers
    cp -r ../dependencies/socket.io-client-cpp/lib/asio/asio/include/* ${INCLUDEDIR}
    cp -r ../dependencies/socket.io-client-cpp/lib/websocketpp/websocketpp ${INCLUDEDIR} #no / after the last websocketpp to copy the directory and not its content
    cp -r ../dependencies/rapidjson/include/* ${INCLUDEDIR} #copying a more recent rapidjson packaged by socketio
    #there is a lib/catch that does not seem to be necessary

    tar zcvf ${TARGETDIR}.tgz ${TARGETDIR}

}

reinit
reset_installation
compilesio
build_distribute

