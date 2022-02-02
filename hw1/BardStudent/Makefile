CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = linkedlist.o bard.o

bard: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bard linkedlist.o bard.o
	
linkedlist.o: linkedlist.cpp linkedlist.h
	$(CXX) -g $(CXXFLAGS) -c linkedlist.cpp
	
bard.o: linkedlist.cpp linkedlist.h bard.cpp
	$(CXX) -g $(CXXFLAGS) -c bard.cpp
	
clean:
	rm -f *.o
	rm bard