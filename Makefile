# Makefile for C++ programs
# Usage: make target1 target2 ...

# Author: John M. Weiss, Ph.D.
# Class:  CSC 315 Data Structures & Algorithms (PA#1)
# Date:   Spring 2018

CC = gcc
CXX = g++
LINK = g++

# compilation flags
CFLAGS += -O -Wall -fmax-errors=5
CXXFLAGS += $(CFLAGS) -std=c++11

# targets:
all:	pa1
debug:	CXXFLAGS+= -g
debug:	all
pa1:	pa1.o largeint.h cgfunc.o DRfuncs.o asl.o
	g++ $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o
