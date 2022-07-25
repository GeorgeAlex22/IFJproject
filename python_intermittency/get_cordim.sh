#!/usr/bin/env bash

./proton_reader_ROOT_mulsort.py ../$1.root
./bootstrap_weights_mulsort.py ../$1.hdf5 --nsamples 2 --nrepeat 500
./cordim_boot.py ../$1.hdf5
./fmom_parser_cordim.py ../$1.cordim.npz
head -n 155 ../F2_cordim_$1.cordim.dat | tail -n 150 | awk -v OFS='\t' '{print $1,$2,$5}' > ../$1.dat
rm -f ../F2_cordim_$1.cordim.dat