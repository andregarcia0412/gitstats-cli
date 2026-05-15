APP = gitstats
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -MMD -MP
LIBS = -lcurl

SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))
DEP= $(OBJ:.o=.d)

ifeq ($(OS),Windows_NT)
	EXE = .exe
	INSTALL_DIR = $(USERPROFILE)/AppData/Local/Programs/$(APP)
else
	EXE = 
	INSTALL_DIR = $(HOME)/.local/bin
endif

OUT = bin/$(APP)$(EXE)

all: $(OUT)

$(OUT): $(OBJ)
	@mkdir -p $(dir $(OUT))
	$(CXX) $(OBJ) $(LIBS) -o $(OUT)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


install: $(OUT)
	@mkdir -p "$(INSTALL_DIR)"
	cp "$(OUT)" "$(INSTALL_DIR)/$(APP)$(EXE)"
	chmod +x "$(INSTALL_DIR)/$(APP)$(EXE)" || true
	@echo "$(APP) sucessfully installed in $(INSTALL_DIR)"

uninstall:
	rm -f "$(INSTALL_DIR)/$(APP)$(EXE)"

clean:
	rm -rf build bin

-include $(DEP)