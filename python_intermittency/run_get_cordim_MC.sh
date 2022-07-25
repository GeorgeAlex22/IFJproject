#/usr/bin/env bash

for file in ../mTTD_cut.cmc.mul.3.704.bkg_pc.*.root
do
    fileName=`echo "$file" | awk '{split($0,a,"/"); print a[2]}' | awk '{split($0,a,".root"); print a[1]}'`
    # echo $fileName
    ./get_cordim.sh $fileName
done