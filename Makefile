## This is a simple Makefile 

# Define what compiler to use and the flags.
CC=cc
CXX=g++
CCFLAGS= -g -std=c++11 -Wall -Werror
LDLIBS= -lm
SRC=$(wildcard *.cpp)

all: proj2



###################################
# BEGIN SOLUTION
proj2: $(SRC)
	$(CXX) -o proj2 $^ $(CCFLAGS) $(LDLIBS)


clean:
	rm -f *.o proj2