CXX = clang++
CXXFLAGS = -g -O2 -Wall -std=c++11
INC=-I. -I.. -I/usr/include/catch
LIBS= -pthread -lbenchmark 

bin/% : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $< -o $@ $(LIBS)

all: $(patsubst %.cpp, bin/%, $(wildcard *.cpp))

clean:
	rm -f bin/*
