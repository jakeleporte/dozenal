#!/bin/bash
# +AMDG

echo "Tm to s:"
echo "0.17361111 = `tgmconv -k8 -os -iTm 1 | dec -k8`";
echo "s to Tm:"
echo "5;915343X1 = `tgmconv -k8 -oTm -is 1`";
echo "5 min to 3^Tm:"
echo "1 = `tgmconv -k8 -o3^Tm -imin 5`";
echo "3_Tm to ms:"
echo "0.1004693929 = `tgmconv -k10 -oms -i3_Tm 1 | dec -k10`";
echo "ms to 3_Tm:"
echo "9;E53326X4 = `tgmconv -k8 -ims -o3_Tm 1`";
echo "G to m/s2:"
echo "9.8100494007 = `tgmconv -k10 -iG -o m/s2 1 | dec -k10`";
echo "G to ft/s2:"
echo "32.18520142 = `tgmconv -k8 -iG -oft/s2 1 | dec -k8`";
echo "m/s2 TO G:"
echo "0;12819015 = `tgmconv -k8 -oG -im/s2 1`";
echo "ft/s2 TO G:"
echo "0;04583309 = `tgmconv -k8 -oG -ift/s2 1`";
echo "Gf to m:"
echo "0.2956829126 = `tgmconv -k10 -iGf -om 1 | dec -k10`";
echo "Gf to ft:"
echo "0.9700882959 = `tgmconv -k10 -iGf -oft 1 | dec -k10`";
echo "Gf to in:"
echo "11.6410595508 = `tgmconv -k10 -iGf -oin 1 | dec -k10`";
echo "2_Gf to mm:"
echo "2.0533535596 = `tgmconv -k10 -i2_Gf -omm 1 | dec -k10`";
echo "6_Gf to m:"
echo "0.9902360916e-7 = `tgmconv -k10 -i6_Gf -om -e 1 | dec -k10 -e`"
echo "4^Gf to km:"
echo "6.1312808754 = `tgmconv -k10 -i4^Gf -okm 1 | dec -k10`";
echo "4^Gf to mi:"
echo "3.8098013075 = `tgmconv -k10 -i4^Gf -omi 1 | dec -k10`";
echo "m to Gf:"
echo "3;4701219X = `tgmconv -k8 -im -oGf 1`";
echo "ft to Gf:"
echo "1;045345X0 = `tgmconv -k8 -ift -oGf 1`";
echo "in to Gf:"
echo "0;1045345X = `tgmconv -k8 -iin -oGf 1`";
echo "mm to 2_Gf:"
echo "0;5X16727E = `tgmconv -k8 -imm -o2_Gf 1`";
echo "um to 6_Gf:"
echo "X;12247357 = `tgmconv -k8 -ium -o6_Gf 1`";
echo "km to Gf:"
echo "1E5X;00233X8 = `tgmconv -k7 -ikm -oGf 1`";
echo "mi to 3^Gf:"
echo "3;1969786 = `tgmconv -k7 -imi -o3^Gf 1`";
echo "Vl to m/s:"
echo "1.7031335765 = `tgmconv -k10 -iVl -om/s 1 | dec -k10`";
echo "Vl to ft/s:"
echo "5.5877085843 = `tgmconv -k10 -iVl -oft/s 1 | dec -k10`";
echo "m/s to Vl:"
echo "0;7067255X = `tgmconv -k8 -im/s -oVl 1`";
echo "ft/s to Vl:"
echo "2;1930041E = `tgmconv -k8 -ift/s -o1_Vl 1`";
echo "km/hr to Vl:"
echo "0;1E5X = `tgmconv -k4 -ikm/hr -oVl 1`";
echo "Vl to km/hr:"
echo "6.131 = `tgmconv -k3 -okm/hr -iVl 1 | dec -k3`";
echo "Sf to m2:"
echo "8.7428384796e-2 = `tgmconv -k10 -iSf -om2 1 | dec -ek10`";
echo "Sf to ft2:"
echo "0.9410713018 = `tgmconv -k10 -iSf -oft2 1 | dec -k10`";
echo "4^Sf to acre:"
echo "0.4479810495 = `tgmconv -k10 -i4^Sf -oacre 1 | dec -k10`";
echo "4^Sf to ha:"
echo "0.1812914987 = `tgmconv -k10 -i4^Sf -oha 1 | dec -k10`";
echo "6^Sf to km2:"
echo "0.2610597581 = `tgmconv -k10 -i6^Sf -okm2 1 | dec -k10`";
echo "6^Sf to mi2:"
echo "0.1007957361 = `tgmconv -k10 -i6^Sf -omi2 1 | dec -k10`";
echo "4_Sf to mm2:"
echo "4.2162608409 = `tgmconv -k10 -i4_Sf -omm2 1 | dec -k10`";
echo "m2 to Sf:"
echo "E;5308E881 = `tgmconv -k8 -oSf -im2 1`";
echo "ft2 to Sf:"
echo "1;09025668 = `tgmconv -k8 -oSf -ift2 1`";
echo "acre to 4^Sf:"
echo "2;29538098 = `tgmconv -k8 -o4^Sf -iacre 1`";
echo "ha to 4^Sf:"
echo "5;62373E49 = `tgmconv -k8 -o4^Sf -iha 1`";
echo "km2 to 6^Sf:"
echo "3;9E7210XE = `tgmconv -k8 -o6^Sf -ikm2 1`";
echo "mi2 to 6^Sf:"
echo "9;E076EX30 = `tgmconv -k8 -o6^Sf -imi2 1`";
echo "mm2 to 5^Sf:"
echo "2;X1X127X9 = `tgmconv -k8 -o5_Sf -imm2 1`";
echo "Vm to m3:"
echo "2.5851079459e-2 = `tgmconv -k10 -iVm -om3 1 | dec -ek10`";
echo "Vm to L:"
echo "25.8503556494 = `tgmconv -k10 -iVm -oL 1 | dec -k10`";
echo "Vm to ft3:"
echo "0.9129222555 = `tgmconv -k10 -iVm -oft3 1 | dec -k10`";
echo "Vm to yd3:"
echo "0.033811935389 = `tgmconv -k12 -iVm -oyd3 1 | dec -k12`";
echo "Vm to gali:"
echo "5.6864459111 = `tgmconv -k10 -iVm -ogali 1 | dec -k10`";
echo "Vm to galc:"
echo "6.8290818133 = `tgmconv -k10 -iVm -ogalc 1 | dec -k10`";
echo "2_Vm to pti:"
echo "0.3159136617 = `tgmconv -k10 -i2_Vm -opti 1 | dec -k10`";
echo "2_Vm to ptc:"
echo "0.3793934341 = `tgmconv -k10 -i2_Vm -optc 1 | dec -k10`";
echo "4_Vm to mL:"
echo "1.2466413797 = `tgmconv -k10 -i4_Vm -omL 1 | dec -k10`";
echo "m3 to 1^Vm:"
echo "3;28244X22 = `tgmconv -k8 -im3 -o1^Vm 1`";
echo "L to 2_Vm:"
echo "5;6X1X4457 = `tgmconv -k8 -iL -o2_Vm 1`";
echo "ft3 to Vm:"
echo "1;1189X583 = `tgmconv -k8 -ift3 -oVm 1`";
echo "yd3 to 1^Vm:"
echo "2;56XX2696 = `tgmconv -k8 -iyd3 -o1^Vm 1`";
echo "gali to 1_Vm:"
echo "2;13X69515 = `tgmconv -k8 -igali -o1_Vm 1`";
echo "galc to 1_Vm:"
echo "1;91051389 = `tgmconv -k8 -igalc -o1_Vm 1`";
echo "pti to 2_Vm:"
echo "3;1E9X22E1 = `tgmconv -k8 -ipti -o2_Vm 1`";
echo "ptc to 2_Vm:"
echo "2;77677E72 = `tgmconv -k8 -iptc -o2_Vm 1`";
echo "mL to 5_Vm:"
echo "9;7615XXEX = `tgmconv -k8 -imL -o5_Vm 1`";
echo "Mz to kg:"
echo "25.8503556494 = `tgmconv -k10 -iMz -okg 1 | dec -k10`";
echo "Mz to lb:"
echo "56.9902828681 = `tgmconv -k10 -iMz -olb 1 | dec -k10`";
echo "2^Mz to t:"
echo "3.7224512135 = `tgmconv -k10 -i2^Mz -ot 1 | dec -k10`";
echo "3_Mz to oz:"
echo "0.5276878043 = `tgmconv -k10 -i3_Mz -ooz 1 | dec -k10`";
echo "4_Mz to g:"
echo "1.2466413797 = `tgmconv -k10 -i4_Mz -og 1 | dec -k10`";
echo "kg to 2_Mz:"
echo "5;6X1X4457 = `tgmconv -k8 -ikg -o2_Mz 1`";
echo "lb to 2_Mz:"
echo "2;63X2748X = `tgmconv -k8 -ilb -o2_Mz 1`";
echo "t to 1^Mz:"
echo "3;28263384 = `tgmconv -k8 -it -o1^Mz 1`";
echo "oz to 3_Mz:"
echo "1;X8X7E668 = `tgmconv -k8 -ioz -o3_Mz 1`";
echo "g to 5_Mz:"
echo "9;7615XXEX = `tgmconv -k8 -ig -o5_Mz 1`";
echo "Dz to kg/m3:"
echo "999.9720008 = `tgmconv -k7 -iDz -okg/m3 1 | dec -k7`";
echo "kh/dm3 to Dz:"
echo "1;00006E73 = `tgmconv -k8 -ikg/dm3 -oDz 1`";
echo "Vv to m2/s2:"
echo "2.9006639794 = `tgmconv -k10 -iVv -om2/s2 1 | dec -k10`";
echo "Vl2 to m2/s2:"
echo "2.9006639794 = `tgmconv -k10 -iVl2 -om2/s2 1 | dec -k10`";
echo "m2/s2 to Vv:"
echo "0;417885E7 = `tgmconv -k8 -im2/s2 -oVv 1`";
echo "m2/s2 to Vl2:"
echo "0;417885E7 = `tgmconv -k8 -im2/s2 -oVl2 1`";
echo "Mv to kh*m/s:"
echo "44.0266086711 = `tgmconv -k10 -iMv -okg*m/s 1 | dec -k10`";
echo "Mz*Vl to kh*m/s:"
echo "44.0266086711 = `tgmconv -k10 -iMz*Vl -okg*m/s 1 | dec -k10`";
echo "Mv to lb*ft/s:"
echo "318.4450928058 = `tgmconv -k10 -iMv -olb*ft/s 1 | dec -k10`";
echo "Mz*Vl to lb*ft/s:"
echo "318.4450928058 = `tgmconv -k10 -iMz*Vl -olb*ft/s 1 | dec -k10`";
echo "kg*m/s to 2_Mv:"
echo "3;32EX3114 = `tgmconv -k8 -ikg*m/s -o2_Mv 1`";
echo "lb*ft/s to 3_Mv:"
echo "5;5149196E = `tgmconv -k8 -ilb*ft/s -o3_Mv 1`";
echo "Mg to N:"
echo "253.5932659458 = `tgmconv -k10 -iMg -oN 1 | dec -k10`";
echo "253.5932659458 = `tgmconv -k10 -iMz*G -oN 1 | dec -k10`";
echo "Mg to kgf:"
echo "25.8593164787 = `tgmconv -k10 -iMg -okgf 1 | dec -k10`";
echo "Mg to lbf:"
echo "57.0100381234 = `tgmconv -k10 -iMg -olbf 1 | dec -k10`";
echo "N to 3_Mg:"
echo "6;9928453X = `tgmconv -k8 -iN -o3_Mg 1`";
echo "kgf to 2_Mg:"
echo "5;69X64071 = `tgmconv -k8 -ikgf -o2_Mg 1`";
echo "lbf to 2_Mg:"
echo "2;63885635 = `tgmconv -k8 -ilbf -o2_Mg 1`";
echo "Tz to N/m:"
echo "857.652759595 = `tgmconv -k10 -iTz -oN/m 1 | dec -k10`";
echo "857.652759595 = `tgmconv -k10 -iMg/Gf -oN/m 1 | dec -k10`";
echo "4_Tz to dyn/cm:"
echo "41.360569039 = `tgmconv -k9 -i4_Tz -odyn/cm 1 | dec -k9`";
echo "41.360569039 = `tgmconv -k9 -i4_Mg/Gf -odyn/cm 1 | dec -k9`";
echo "N/m to 3_Tz:"
echo "2;0216E099 = `tgmconv -k8 -iN/m -o3_Tz 1`";
echo "2;0216E099 = `tgmconv -k8 -iN/m -o3_Mg/Gf 1`";
echo "dyn/cm to 6_Tz:"
echo "3;59411896 = `tgmconv -k8 -idyn/cm -o6_Tz 1`";
echo "3;59411896 = `tgmconv -k8 -idyn/cm -o6_Mg/Gf 1`";
echo "Pm to N/m2:"
echo "2900.582763 = `tgmconv -k6 -iPm -oN/m2 1 | dec -k6`";
echo "2900.582763 = `tgmconv -k6 -iMg/Sf -oN/m2 1 | dec -k6`";
echo "Pm to lbf/in2:"
echo "0.4206939918 = `tgmconv -k10 -iPm -olbf/in2 1 | dec -k10`";
echo "Pm to mmHg:"
echo "21.76 = `./tgmconv -k2 -iPm -ommHg 1 | dec -k2`";

exit;
