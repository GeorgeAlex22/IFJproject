#!/usr/bin/env bash

./mTTD_cut.exe mTTD_cut.root accepted.root &
sleep 5

./mTTD_cut.exe mTTD_cut1.root accepted1.root &
sleep 5

./mTTD_cut.exe mTTD_cut2.root accepted2.root &
sleep 5

./mTTD_cut.exe mTTD_cut_pr80.root accepted_pr80.root &
sleep 5

./mTTD_cut.exe mTTD_cut1_pr80.root accepted1_pr80.root &
sleep 5

./mTTD_cut.exe mTTD_cut2_pr80.root accepted2_pr80.root &
sleep 5

./mTTD_cut.exe mTTD_cut_pr90.root accepted_pr90.root &
sleep 5

./mTTD_cut.exe mTTD_cut1_pr90.root accepted1_pr90.root &
sleep 5

./mTTD_cut.exe mTTD_cut2_pr90.root accepted2_pr90.root &
sleep 5

./mTTD_cut.exe mTTD_cut_pr95.root accepted_pr95.root &
sleep 5

./mTTD_cut.exe mTTD_cut1_pr95.root accepted1_pr95.root &
sleep 5

./mTTD_cut.exe mTTD_cut2_pr95.root accepted2_pr95.root &
sleep 5

