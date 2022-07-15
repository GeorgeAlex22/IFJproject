tracks_tree.exe: tracks_tree.cc tracks_tree.h
	g++ tracks_tree.cc -o tracks_tree.exe `root-config --cflags --glibs` -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src ./BetheBloch/BetheBlochWrapper.so

tracks_filtered.exe: tracks_filtered.cc tracks_filtered.h
	g++ tracks_filtered.cc -o tracks_filtered.exe `root-config --cflags --glibs` -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src ./BetheBloch/BetheBlochWrapper.so

bethebloch.exe: makeBetheBloch.cc 
	g++ makeBetheBloch.cc -o bethebloch.exe `root-config --cflags --glibs` -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src ./BetheBloch/BetheBlochWrapper.so

calculateEffPure.exe: calculateEffPure.cc 
	g++ calculateEffPure.cc -o calculateEffPure.exe `root-config --cflags --glibs` -I./BetheBloch/src/include -I./BetheBloch/kit-dedx-fitter/src ./BetheBloch/BetheBlochWrapper.so

bethebloch: bethebloch.exe
	./bethebloch.exe

run: tracks_tree.exe ArSc150_charged_tree.root histograms.root
	./tracks_tree.exe histograms.root ArSc150_charged_tree.root

run_debug: tracks_tree.exe ArSc150_charged_tree.root histograms.root
	./tracks_tree.exe histograms.root ArSc150_charged_tree.root 1

runFiltered: tracks_filtered.exe tracks_filtered.root histogramsFiltered.root
	./tracks_filtered.exe histogramsFiltered.root tracks_filtered.root

plot: histograms.root
	root -l -b -q plot.cc

efficiency_purity: calculateEffPure.exe
	./calculateEffPure.exe
