#!/usr/bin/env bash

root -l -b -q 'plotF2.C("graphF2_data.root", "graphF2_mix.root", "F2")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data1.root", "graphF2_mix1.root", "F2_1")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data2.root", "graphF2_mix2.root", "F2_2")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data_pr80.root", "graphF2_mix_pr80.root", "F2_pr80")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data1_pr80.root", "graphF2_mix1_pr80.root", "F2_1_pr80")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data2_pr80.root", "graphF2_mix2_pr80.root", "F2_2_pr80")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data_pr90.root", "graphF2_mix_pr90.root", "F2_pr90")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data1_pr90.root", "graphF2_mix1_pr90.root", "F2_1_pr90")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data2_pr90.root", "graphF2_mix2_pr90.root", "F2_2_pr90")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data_pr95.root", "graphF2_mix_pr95.root", "F2_pr95")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data1_pr95.root", "graphF2_mix1_pr95.root", "F2_1_pr95")'
sleep 2

root -l -b -q 'plotF2.C("graphF2_data2_pr95.root", "graphF2_mix2_pr95.root", "F2_2_pr95")'
sleep 2


