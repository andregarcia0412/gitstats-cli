CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
LIBS = -lcurl

SRC = $(shell find src -name "*.cpp")
OUT = bin/gitstats

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LIBS) -o $(OUT)