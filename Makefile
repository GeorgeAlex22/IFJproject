.PHONY: all clean bethebloch runE runE_debug runF runF_debug runF1 runF1_debug runF2 runF2_debug plot efficiency_purity factorial_moment

# ROOT libraries + Boost
BOOSTHEADERS := /usr/include/boost
BOOSTLIBDIR := /lib/x86_64-linux-gnu
ROOTCONFIG := root-config
CPPFLAGS    := $(shell $(ROOTCONFIG) --cflags) -MMD -MP -Isrc/include -I$(BOOSTHEADERS)
CXXFLAGS    := $(shell $(ROOTCONFIG) --auxcflags) -g -O3 -fPIC -Wall -Wextra
LDFLAGS     := $(shell $(ROOTCONFIG) --ldflags) -Wl,--no-as-needed
ROOTLIBS    := $(shell $(ROOTCONFIG) --glibs) -lGenVector
BOOSTLIBS    := -L$(BOOSTLIBDIR) -lboost_program_options -lboost_context

MYINCS := -I./Tools/src/include -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src
MYLIBS := ./BetheBloch/BetheBlochWrapper.so ./Tools/Event.so  ./Tools/EventMixer.noDict.so ./Tools/CutsMap.noDict.so

# Inputs
EVROOTS := $(wildcard ./EventTrees/ArScCharged150T2_r*.root)

# Targets
PROGALL := $(patsubst %.cc, %.exe, $(wildcard *.cc))

all: $(PROGALL)

clean:
	- rm -f *.o *.d $(PROGALL)

%.exe: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(MYINCS) $(LDFLAGS) -o $@ $^ $(ROOTLIBS) $(BOOSTLIBS) $(MYLIBS)


bethebloch: bethebloch.exe
	./bethebloch.exe

run: tracks_tree.exe ArSc150_charged_tree.root histograms.root
	./tracks_tree.exe histograms.root ArSc150_charged_tree.root

run_debug: tracks_tree.exe ArSc150_charged_tree.root histograms.root
	./tracks_tree.exe histograms.root ArSc150_charged_tree.root 1

runE: events_tree.exe $(EVROOTS)
	./events_tree.exe filtered.root `dir ./EventTrees/ArScCharged150T2_r20*.root`

runE_debug: events_tree.exe $(EVROOTS)
	./events_tree.exe filtered.root `dir ./EventTrees/ArScCharged150T2_r20*.root` -d

runF: events_filtered.exe filtered.root
	./events_filtered.exe accepted.root filtered.root

runF1: events_filtered.exe filtered.root
	./events_filtered.exe accepted1.root filtered.root -1

runF2: events_filtered.exe filtered.root
	./events_filtered.exe accepted2.root filtered.root -2

runF_debug: events_filtered.exe filtered.root
	./events_filtered.exe accepted.root filtered.root -d

runF1_debug: events_filtered.exe filtered.root
	./events_filtered.exe accepted1.root filtered.root -d -1

runF2_debug: events_filtered.exe filtered.root
	./events_filtered.exe accepted2.root filtered.root -d -2

mTTD_cut: mTTD_cut.exe accepted.root
	./mTTD_cut.exe mTTD_cut.root accepted.root

mTTD_cut_debug: mTTD_cut.exe accepted.root
	./mTTD_cut.exe mTTD_cut.root accepted.root -d

factorial_moment: factorial_moment.exe mTTD_cut.root
	./factorial_moment.exe factorial_moment.root mTTD_cut.root 

plot: filtered.root
	root -l -b -q plot.C

efficiency_purity: calculateEffPure.exe
	./calculateEffPure.exe

# Include dependencies for CPP files
ifneq ($(MAKECMDGOALS),clean)
-include $(OBJ:.o=.d)
endif
