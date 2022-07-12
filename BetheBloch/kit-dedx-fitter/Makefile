.PHONY: all clean
#~ .SECONDARY: # use to suppress deletion of intermediate files

ROOTCONFIG := root-config
CPPFLAGS    := $(shell $(ROOTCONFIG) --cflags) -Isrc -I$(BOOSTROOT)/include
#CXXFLAGS    := $(shell $(ROOTCONFIG) --auxcflags) -g -O3 -fPIC -Wall -Wextra
CXXFLAGS    := $(shell $(ROOTCONFIG) --auxcflags) -ggdb3 -O0 -fPIC -Wall -Wextra
LDFLAGS     := $(shell $(ROOTCONFIG) --ldflags)
ROOTLIBS    := $(shell $(ROOTCONFIG) --libs)
BOOSTLIBS    := -L$(BOOSTROOT)/lib -lboost_program_options

LIB := $(patsubst src/%LinkDef.h, %.so, $(wildcard src/*LinkDef.h))
PROGALL := $(patsubst src/%Main.cc, %, $(wildcard src/*Main.cc))
PROG :=  $(filter-out ReadData, $(PROGALL))
OBJ := $(patsubst src/%.cc, %.o, $(wildcard src/*.cc))
OBJ_MAIN := $(patsubst src/%.cc, %.o, $(wildcard src/*Main.cc))
OBJ_DICT := $(patsubst src/%LinkDef.h, %.o, $(wildcard src/*LinkDef.h))
OBJ_OTHER := $(filter-out $(OBJ_MAIN) $(OBJ_DICT), $(OBJ)) # no main, no dict

all: $(PROG) $(LIB)

clean:
	- rm -f *.o *.pcm $(PROG) $(LIB) $(XML)

%: %Main.o $(OBJ_OTHER) $(LIB)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(ROOTLIBS) $(BOOSTLIBS)

%.o: src/%.cc
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

%Dict.o: src/%.h src/%LinkDef.h | src/%.cc
	rootcling -f $(patsubst %.o, %.cc, $@) -c -p $(filter -I%, $(CPPFLAGS)) $^
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $(patsubst %.o, %.cc, $@) -o $@
	rm $(patsubst %.o, %.cc, $@)

%.so: %Dict.o %.o
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(ROOTLIBS)
