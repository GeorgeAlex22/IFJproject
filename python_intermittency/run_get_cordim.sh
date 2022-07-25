#!/usr/bin/env bash

# ./get_cordim.sh mTTD_cut  &
# sleep 2

# ./get_cordim.sh mTTD_cut1 &
# sleep 2

# ./get_cordim.sh mTTD_cut2 &
# sleep 2

# ./get_cordim.sh mTTD_cut_pr80 &
# sleep 2

# ./get_cordim.sh mTTD_cut1_pr80 &
# sleep 2

# ./get_cordim.sh mTTD_cut2_pr80 &
# sleep 2

# ./get_cordim.sh mTTD_cut_pr90 &
# sleep 2

# ./get_cordim.sh mTTD_cut1_pr90 &
# sleep 2

# ./get_cordim.sh mTTD_cut2_pr90 &
# sleep 2

# ./get_cordim.sh mTTD_cut_pr95 &
# sleep 2

# ./get_cordim.sh mTTD_cut1_pr95 &
# sleep 2

# ./get_cordim.sh mTTD_cut2_pr95 &
# sleep 2

# ./get_cordim.sh mTTD_cut_mix &
# sleep 2

./get_cordim.sh mTTD_cut1_mix --nsamples 5 --nrepeat 200 &
sleep 2

# ./get_cordim.sh mTTD_cut2_mix &
# sleep 2

./get_cordim.sh mTTD_cut_pr80_mix --nsamples 5 --nrepeat 200 &
sleep 2

./get_cordim.sh mTTD_cut1_pr80_mix --nsamples 5 --nrepeat 200 &
sleep 2

# ./get_cordim.sh mTTD_cut2_pr80_mix &
# sleep 2

# ./get_cordim.sh mTTD_cut_pr90_mix &
# sleep 2

# ./get_cordim.sh mTTD_cut1_pr90_mix &
# sleep 2

# ./get_cordim.sh mTTD_cut2_pr90_mix &
# sleep 2

# ./get_cordim.sh mTTD_cut_pr95_mix &
# sleep 2

./get_cordim.sh mTTD_cut1_pr95_mix --nsamples 5 --nrepeat 200 &
sleep 2

./get_cordim.sh mTTD_cut2_pr95_mix --nsamples 5 --nrepeat 200 &
sleep 2

