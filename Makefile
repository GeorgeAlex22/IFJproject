

tracks_tree.exe: tracks_tree.C tracks_tree.h
	g++ tracks_tree.C -o tracks_tree.exe `root-config --cflags --glibs` -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src BetheBloch/BetheBlochWrapper.so

bethebloch.exe: makeBetheBloch.C 
	g++ makeBetheBloch.C -o bethebloch.exe `root-config --cflags --glibs` -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src BetheBloch/BetheBlochWrapper.so

runBloch: bethebloch.exe
	./bethebloch.exe
	
run: tracks_tree.exe ArSc150_charged_tree.root histograms.root
	./tracks_tree.exe histograms.root ArSc150_charged_tree.root

plot: histograms.root
	root -l -b -q plot.C
