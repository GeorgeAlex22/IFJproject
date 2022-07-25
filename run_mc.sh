#!/usr/bin/env bash

for file in cmc/*
do
    fileName=`echo "$file" | awk '{split($0,a,"/"); print a[2]}'`
    # echo $fileName
    ./events_filtered.exe accepted.$fileName $file -mc
    ./mTTD_cut.exe mTTD_cut.$fileName accepted.$fileName
done