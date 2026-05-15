APP = gitstats
VERSION = 1.0.1
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -MMD -MP
LIBS = -lcurl
ARCH = amd64
DEB_NAME = $(APP)_$(VERSION)_$(ARCH)

SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))
DEP= $(OBJ:.o=.d)

ifeq ($(OS),Windows_NT)
	EXE = .exe
	INSTALL_DIR = $(USERPROFILE)/AppData/Local/Programs/$(APP)
	PREFIX ?= $(USERPROFILE)/AppData/Local/Programs/$(APP)
	BINDIR = $(PREFIX)
else
	EXE = 
	PREFIX ?= $(HOME)/.local
	BINDIR = $(PREFIX)/bin
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
	install -Dm755 "$(OUT)" "$(DESTDIR)$(BINDIR)/$(APP)$(EXE)"
	@echo "$(APP) successfully installed in $(DESTDIR)$(BINDIR)"

uninstall:
	rm -f "$(DESTDIR)$(BINDIR)/$(APP)$(EXE)"

clean:
	rm -rf build bin

deb: all
	mkdir -p build_deb/DEBIAN
	cp debian/control build_deb/DEBIAN/
	$(MAKE) PREFIX=/usr DESTDIR=./build_deb install	
	dpkg-deb --build build_deb $(DEB_NAME).deb	
	rm -rf build_deb

.PHONY: all install uninstall clean deb

-include $(DEP)
