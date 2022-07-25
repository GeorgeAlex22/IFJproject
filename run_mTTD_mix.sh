#!/usr/bin/env bash

./mTTD_cut.exe mTTD_cut_mix.root mixEvents.root &
sleep 5

./mTTD_cut.exe mTTD_cut1_mix.root mixEvents1.root &
sleep 5

./mTTD_cut.exe mTTD_cut2_mix.root mixEvents2.root &
sleep 5

./mTTD_cut.exe mTTD_cut_pr80_mix.root mixEvents_pr80.root &
sleep 5

./mTTD_cut.exe mTTD_cut1_pr80_mix.root mixEvents1_pr80.root &
sleep 5

./mTTD_cut.exe mTTD_cut2_pr80_mix.root mixEvents2_pr80.root &
sleep 5

./mTTD_cut.exe mTTD_cut_pr90_mix.root mixEvents_pr90.root &
sleep 5

./mTTD_cut.exe mTTD_cut1_pr90_mix.root mixEvents1_pr90.root &
sleep 5

./mTTD_cut.exe mTTD_cut2_pr90_mix.root mixEvents2_pr90.root &
sleep 5

./mTTD_cut.exe mTTD_cut_pr95_mix.root mixEvents_pr95.root &
sleep 5

./mTTD_cut.exe mTTD_cut1_pr95_mix.root mixEvents1_pr95.root &
sleep 5

./mTTD_cut.exe mTTD_cut2_pr95_mix.root mixEvents2_pr95.root &
sleep 5

