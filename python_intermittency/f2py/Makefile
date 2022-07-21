.PHONY: all clean veryclean

F2PYC=python -m numpy.f2py
F2PYFLAGS= --f90flags="-fPIC -fopenmp"
F2PYLDFLAGS= -lgomp

EXT_SUFFIX := $(shell python3-config --extension-suffix)
SRCS := $(wildcard *.f90)
LIBS := $(patsubst %.f90, %$(EXT_SUFFIX), $(SRCS))

all: $(LIBS)

# Implicit rules

%$(EXT_SUFFIX): %.f90
	$(F2PYC) $< -m $* -h Temp.pyf
	$(F2PYC) $(F2PYFLAGS) $(F2PYLDFLAGS) -c Temp.pyf $<
	rm Temp.pyf

#############################################################

clean:
	- rm -f $(LIBS)
veryclean:
	- rm -f $(LIBS)


