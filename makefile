CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC = 	src/dijkstra.cpp \
	src/functions.cpp \
	src/graphAssem.cpp \
	src/map.cpp \
	bin/main.cpp

TARGET = final

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

clean:
	rm -f $(TARGET)
