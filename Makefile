tracks_tree.exe: tracks_tree.C tracks_tree.h
	g++ tracks_tree.C -o tracks_tree.exe `root-config --cflags --glibs`

run: tracks_tree.exe ArSc150_charged_tree.root histograms.root
	./tracks_tree.exe histograms.root ArSc150_charged_tree.root

plot: histograms.root
	root -l -b -q plot.C
