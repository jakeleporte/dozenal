#!/bin/bash
# +AMDG

var=`./tgmconv -k 8 -iTm -os 1 | ../dec/dec -k 8`;
echo "0.17361111 --- $var";
var=`./tgmconv -k 8 -oTm -is 1`;
echo "5;915343X1 --- $var";
var=`./tgmconv -k 8 -o3^Tm -imin 5`;
echo "1;00000000 --- $var";
var=`./tgmconv -k 8 -o3_Tm -ims 1`;
echo "9;E53326X4 --- $var";
var=`./tgmconv -k 10 -i3_Tm -oms 1 | ../dec/dec -k 10`;
echo "0.1004693929 --- $var";
var=`./tgmconv -k 10 -iG -om/s2 1 | ../dec/dec -k 10`;
echo "9.8100494007 --- $var";
var=`./tgmconv -k 8 -im/s2 -oG 1`;
echo "0;12819015 --- $var";
var=`./tgmconv -k 8 -ift/s2 -oG 1`;
echo "0;04583309 --- $var";
var=`./tgmconv -k 8 -iG -o ft/s2 1 | ../dec/dec -k 8`;
echo "32.18520142 --- $var";
var=`./tgmconv -k10 -om -iGf 1 | ../dec/dec -k 10`;
echo "0.2956829126 --- $var";
var=`./tgmconv -k 8 -oGf -im 1`;
echo "3;4701219X --- $var";
var=`./tgmconv -k10 -o ft -iGf 1 | ../dec/dec -k 10`;
echo "0.9700882959 --- $var";
var=`./tgmconv -k8 -i ft -oGf 1`;
echo "1;045345X0 --- $var";
var=`./tgmconv -k10 -o in -iGf 1 | ../dec/dec -k 10`;
echo "11.6410595508 --- $var";
var=`./tgmconv -k8 -i in -oGf 1`;
echo "0;1045235X --- $var";
var=`./tgmconv -k10 -o mm -i2_Gf 1 | ../dec/dec -k 10`;
echo "2.0533535596 --- $var";
var=`./tgmconv -k8 -i mm -o2_Gf 1`;
echo "0;5X16727E --- $var";
var=`./tgmconv -k10 -om -i6_Gf 1 | ../dec/dec -ek 10`;
echo "9.902360916e-8 --- $var";
var=`./tgmconv -k8 -o6_Gf -ium 1`;
echo "X;12247357 --- $var";
var=`./tgmconv -k10 -okm -i4^Gf 1 | ../dec/dec -k 10`;
echo "6.1312808754 --- $var";
var=`./tgmconv -k 8 -oGf -ikm 1`;
echo "1E5X;00233X8 --- $var";
var=`./tgmconv -k 10 -omi -i4^Gf 1 | ../dec/dec -k 10`;
echo "3.8098013075 --- $var";
var=`./tgmconv -k8 -o 3^Gf -imi 1`;
echo "3;1969786 --- $var";
var=`./tgmconv -k10 -om/s -iVl 1 | ../dec/dec -k 10`;
echo "1.7031335765 --- $var";
var=`./tgmconv -k8 -oVl -im/s 1`
echo "0;7067255X --- $var";
var=`./tgmconv -k3 -iVl -okm/hr 1 | ../dec/dec -k 3`;
echo "6.131 --- $var";
var=`./tgmconv -k10 -oft/s -iVl 1 | ../dec/dec -k 10`;
echo "5.5877085843 --- $var";
var=`./tgmconv -k8 -o1_Vl -ift/s 1`
echo "2;1930041E --- $var";
