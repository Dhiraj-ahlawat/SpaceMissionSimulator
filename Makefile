CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

SRCDIR = src
INCDIR = include

SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

TARGET = SpaceMissionSimulator

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
