CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -MMD -MP
LIBS = -lcurl

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)
DEP= $(OBJ:.o=.d)
OUT = bin/gitstats

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $(OUT)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(OUT)