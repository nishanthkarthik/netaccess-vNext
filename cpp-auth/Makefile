appname := auth

CXX := g++
CXXFLAGS := -Wall -g -std=c++11
ADDFLAGS := -lcurl
SRC := netaccess.cpp main.cpp

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(SRC) $(ADDFLAGS)

clean:
	rm -f $(objects)
	rm $(appname)
