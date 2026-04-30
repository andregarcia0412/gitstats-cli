CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -MMD -MP
LIBS = -lcurl

SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))
DEP= $(OBJ:.o=.d)
OUT = bin/gitstats

all: $(OUT)

$(OUT): $(OBJ)
	@mkdir -p $(dir $(OUT))
	$(CXX) $(OBJ) $(LIBS) -o $(OUT)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


-include $(DEP)

clean:
	rm -rf build bin