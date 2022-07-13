tracks_tree.exe: tracks_tree.cc tracks_tree.h
	g++ tracks_tree.cc -o tracks_tree.exe `root-config --cflags --glibs` -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src

bethebloch.exe: makeBetheBloch.cc 
	g++ makeBetheBloch.cc -o bethebloch.exe `root-config --cflags --glibs` -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src

bethebloch: bethebloch.exe
	./bethebloch.exe

run: tracks_tree.exe ArSc150_charged_tree.root histograms.root
	./tracks_tree.exe histograms.root ArSc150_charged_tree.root

run_debug: tracks_tree.exe ArSc150_charged_tree.root histograms.root
	./tracks_tree.exe histograms.root ArSc150_charged_tree.root 1

plot: histograms.root
	root -l -b -q plot.cc
