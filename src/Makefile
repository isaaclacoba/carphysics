#!/usr/bin/make -f
# -*- mode: makefile -*-
# Minesweeper author: Isaac Lacoba Molina
# Copyright (C) 2014  ISAAC LACOBA MOLINA

#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.

#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.

#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

HEADERDIR=src src/managers src/util src/model
HEADERFLAGS=$(foreach directory, $(HEADERDIR), -I$(directory))

OBJECTS=src/managers/input.o src/managers/physics.o src/managers/scene.o \
src/util/timer.o src/util/motionstate.o  src/util/bulletimporter.o \
src/util/meshstrider.o src/game.o src/model/car.o

CXX=g++ -std=c++11
CXXFLAGS = -Wall -ggdb $(HEADERFLAGS) \
 $(shell pkg-config --cflags OGRE OIS bullet)
LDLIBS = $(shell pkg-config --libs-only-l OGRE OIS bullet) -lBulletWorldImporter

all: src/main

src/main: $(OBJECTS)

src/util/timer.o: src/util/timer.cpp
	$(CXX) -Wall -ggdb -Isrc/managers	$< -c -o $@


repeat_test:
	for i in seq 1 2 3 4 5 6 7 8 9 10; do ./minesweeper_test ; done

clean:
	$(RM) *# *~ *.o minesweeper_test tests/*.o
	find . -name "*.o" -delete
