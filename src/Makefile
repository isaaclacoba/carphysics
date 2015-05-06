HEADERDIR=. managers util model state controllers network /usr/include/Ice
HEADERFLAGS=$(foreach directory, $(HEADERDIR), -I$(directory))

vpath %.cpp $(HEADERDIR)

OBJECTS=$(patsubst %.cpp, %.o, $(shell find -type f -name '*.cpp' ! -name "main.cpp"))

CXX=g++ -std=c++14

CXXFLAGS = -Wall -ggdb -Og $(HEADERFLAGS) -DBOOST_LOG_DYN_LINK \
 $(shell pkg-config --cflags OGRE OIS CEGUI-0 bullet)

BOOST_LOG=-DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lboost_log_setup
LDLIBS = $(shell pkg-config --libs-only-l OGRE OIS CEGUI-0 bullet) \
-lSDL -lSDL_mixer -lCEGUIOgreRenderer-0 \
$(BOOST_LOG) -lIce -lIceUtil -lpthread

all: main

main: ${@:%.o} $(OBJECTS)

clean:
	$(RM) *# *~ main
	find . -type f \( -name "*.o" -o -name "*#" -o -name "*~" -o -name "*.log" \) -delete
