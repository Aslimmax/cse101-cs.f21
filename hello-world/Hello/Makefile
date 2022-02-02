CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = hello.o utils.o

hello: $(OBJECTS)
	    $(CXX) -g $(CXXFLAGS) -o $@ hello.o utils.o

hello.o: hello.cpp utils.h utils.cpp
		$(CXX) -g $(CXXFLAGS) -c hello.cpp

utils.o: utils.cpp utils.h
		$(CXX) -g $(CXXFLAGS) -c utils.cpp

clean:
	rm *.o
	rm hello
