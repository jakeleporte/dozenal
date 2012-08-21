#!/bin/bash

./dozdate -d"10 Apr 1187"
echo "Should be Sat 11 Apr 1187:"
./dozdate -sd"10 Apr 1187"

./dozdate -d"25 Dec 1191"
echo "Should be Tue 2 Irv 1191:"
./dozdate -sd"25 Dec 1191"
./dozdate -sd"25 Dec 1191" "%b"
./dozdate -d"25 Jan 1191"
./dozdate -sd"25 Jan 1191"
./dozdate -d"25 Jan 1190"
./dozdate -sd"25 Jan 1190"
