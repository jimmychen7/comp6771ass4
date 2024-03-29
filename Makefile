##
## Makefile for COMP6771 Assignment 4
##

## compiler
CXX = g++-4.9

## compiler flags
CXXFLAGS = -pg -Wall -Werror -O2 -std=c++14
## enable this for debugging
#CXXFLAGS = -Wall -g

SOURCES = $(wildcard *.cpp)
OBJECTS = $(subst .cpp,,$(SOURCES))

default: test04

## using this target will automagically compile all the *.cpp
## files (hopefully tests) found in the current directory into
## individual binaries
all: $(OBJECTS)

%: %.cpp btree.h btree_iterator.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean: 
	rm -f *.o a.out core out? $(OBJECTS)
