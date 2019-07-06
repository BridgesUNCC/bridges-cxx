SOCKETIODIR=~/prgs/socket.io-client-cpp/
RAPIDJSONDIR=~/prgs/rapidjson
BRIDGESCXXDIR=~/prgs/bridges-cxx

CXXFLAGS=-I $(BRIDGESCXXDIR)/src -I $(RAPIDJSONDIR)/include/ -I $(SOCKETIODIR)/src

LDFLAGS=-L $(SOCKETIODIR)

LDLIBS=-l curl -lsioclient -lpthread -l boost_system

main:

clean:
	-rm main

