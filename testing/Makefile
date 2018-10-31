CC = c++

TARGET = bstt

SRCS = bstTest.cpp
OBJS = $(SRCS:.cpp=.o)

INCLUDES = Element.h SLelement.h DLelement.h BSTElement.h TreeElement.h\
			ADTVisualizer.h ElementVisualizer.h	LinkVisualizer.h \
			GraphList.h Edge.h	BTElement.h\
			Bridges.h Connector.h Validation.h

BRIDGES_INCL = /Users/krs/gr/bridges/cxx/git-cxx/src
IFLAGS = -I.  -I/usr/local/curl742/include/curl -I$(BRIDGES_INCL)

CPPFLAGS = -c -g $(IFLAGS) -std=c++11 -stdlib=libc++

LDFLAGS =  -L/usr/local/curl742/lib
LIBS =  -lcurl

.SUFFIXES: .cpp

.cpp.h: $(INCLUDES)
	$(CC) $(CPPFLAGS)  $< -o $@

.cpp.o:  
	$(CC) $(CPPFLAGS)  $< -o $@

TARGET: $(OBJS) 
	$(CC) -g -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	rm bstTest.o bstt

sllist: sllist.o
	$(CC) -g -o sllist sllist.o $(LDFLAGS) $(LIBS)

dllist: dllist.o
	$(CC) -g -o dllist dllist.o $(LDFLAGS) $(LIBS)

tmp: tmp.o
	$(CC) -g -o tmp tmp.o  $(LDFLAGS) $(LIBS)
tmp2: tmp2.o
	$(CC) -g -o tmp2 tmp2.o  $(LDFLAGS) $(LIBS)

bst.o: bst.o
	$(CC) -g -o bst bst.o $(LDFLAGS) $(LIBS)

graph.o: graph.o
	$(CC) -g -o graph graph.o $(LDFLAGS) $(LIBS)

bak:
	tar cvfz bridges_cxx.tgz  src docs Makefile 
	cp bridges_cxx.tgz ~/Dropbox/.

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ -MF  ./.depend;


# DO NOT DELETE

