#!/usr/bin/make -f
# -*- mode: makefile -*-
COMMON_DIR=../src
TARGET=tests/car-physics

BOOST_LOG=-DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lboost_log_setup
HEADERDIR=../bandit $(COMMON_DIR)
LOCALHEADER=$(foreach directory, $(HEADERDIR), -I$(directory))
STANDARFLAGS=-std=c++11 -fPIC -ggdb

CXX=g++
CXXFLAGS=$(STANDARFLAGS) -DBOOST_LOG_DYN_LINK \
	$(shell pkg-config --cflags OGRE bullet) $(LOCALHEADER)
LDLIBS=$(shell pkg-config --libs-only-l OGRE bullet) $(BOOST_LOG)

all: $(TARGET)

$(TARGET): $(COMMON_DIR)/log.o $(COMMON_DIR)/car-physics.o


$(COMMON_DIR)/log.o:
	$(CXX) $(STANDARFLAGS) $(BOOST_LOG) -c -o $(COMMON_DIR)/log.o $(COMMON_DIR)/log.cpp

clean:
	$(RM) *# *~ main *.o ogre.cfg config/*.log $(TARGET)
	find . -name "*.o" -delete
