#!/usr/bin/env bash

./proton_reader_ROOT_mulsort.py ../$1.root
./bootstrap_weights_mulsort.py ../$1.hdf5
./cordim_boot.py ../$1.hdf5
./fmom_parser_cordim.py ../$1.cordim.npz
