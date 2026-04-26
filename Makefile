CXX = g++
CXXFLAGS = -Iinclude
LIBS = -lcurl

SRC = $(shell find src -name "*.cpp")
OUT = main

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LIBS) -o $(OUT)