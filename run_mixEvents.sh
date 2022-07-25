#!/usr/bin/env bash

./mixEvents.exe mix_config.inp mixEvents.root mTTD_cut.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents1.root mTTD_cut1.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents2.root mTTD_cut2.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents_pr80.root mTTD_cut_pr80.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents1_pr80.root mTTD_cut1_pr80.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents2_pr80.root mTTD_cut2_pr80.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents_pr90.root mTTD_cut_pr90.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents1_pr90.root mTTD_cut1_pr90.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents2_pr90.root mTTD_cut2_pr90.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents_pr95.root mTTD_cut_pr95.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents1_pr95.root mTTD_cut1_pr95.root &
sleep 5

./mixEvents.exe mix_config.inp mixEvents2_pr95.root mTTD_cut2_pr95.root &
sleep 5

