.PHONY: all clean
#~ .SECONDARY: # use to suppress deletion of intermediate files

EXTINC      := -Ikit-dedx-fitter/src
ROOTCONFIG := root-config
CPPFLAGS    := $(shell $(ROOTCONFIG) --cflags) -MMD -MP -Isrc/include -I$(BOOSTROOT)/include $(EXTINC)
CXXFLAGS    := $(shell $(ROOTCONFIG) --auxcflags) -g -O3 -fPIC -Wall -Wextra
# --std=c++11 -Wall -Wextra
LDFLAGS     := $(shell $(ROOTCONFIG) --ldflags)
ROOTLIBS    := $(shell $(ROOTCONFIG) --libs) -lGenVector
BOOSTLIBS    := -L$(BOOSTROOT)/lib -lboost_program_options


USER_SRCS := $(filter-out  $(wildcard src/*Main.cc), $(wildcard src/*.cc))
OBJ := $(patsubst src/%.cc, %.o, $(USER_SRCS))
OBJ_DICT := $(patsubst src/include/%LinkDef.h, %.o, $(wildcard src/include/*LinkDef.h))
OBJ_OTHER := $(filter-out $(OBJ_DICT), $(OBJ)) # no dict
LIBNODICT := $(patsubst %.o, %.noDict.so, $(OBJ_OTHER))
LIB := $(patsubst src/include/%LinkDef.h, %.so, $(wildcard src/include/*LinkDef.h))

.INTERMEDIATE: $(OBJ)


all: $(LIB) $(LIBNODICT)

%.o: src/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%Dict.o: src/include/%.h src/include/%LinkDef.h | src/%.cc
	rootcling -f $(patsubst %.o, %.cc, $@) -c -p $(filter -I%, $(CPPFLAGS)) $^
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $(patsubst %.o, %.cc, $@) -o $@
	rm $(patsubst %.o, %.cc, $@)

%.noDict.so: %.o
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) -o $@ $^

%.so: %Dict.o %.o
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean:
	- rm -f *.o *.d *.pcm $(LIB) $(LIBNODICT) src/*~ Make-depend core 

# Include dependencies for CPP files
ifneq ($(MAKECMDGOALS),clean)
-include $(OBJ:.o=.d)
endif
