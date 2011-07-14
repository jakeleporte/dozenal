#!/bin/bash
# +AMDG

echo "Tm to s:"
echo "0.17361111 = `./tgmconv -k8 -os -iTm 1 | dec -k8`";
echo "s to Tm:"
echo "5;915343X1 = `./tgmconv -k8 -oTm -is 1`";
echo "5 min to 3^Tm:"
echo "1 = `./tgmconv -k8 -o3^Tm -imin 5`";
echo "3_Tm to ms:"
echo "0.1004693929 = `./tgmconv -kX -oms -i3_Tm 1 | dec -k10`";
echo "ms to 3_Tm:"
echo "9;E53326X4 = `./tgmconv -k8 -ims -o3_Tm 1`";
echo "G to m/s2:"
echo "9.8100494007 = `./tgmconv -kX -iG -o m/s2 1 | dec -k10`";
echo "G to ft/s2:"
echo "32.18520142 = `./tgmconv -k8 -iG -oft/s2 1 | dec -k8`";
echo "m/s2 TO G:"
echo "0;12819015 = `./tgmconv -k8 -oG -im/s2 1`";
echo "ft/s2 TO G:"
echo "0;04583309 = `./tgmconv -k8 -oG -ift/s2 1`";
echo "Gf to m:"
echo "0.2956829126 = `./tgmconv -kX -iGf -om 1 | dec -k10`";
echo "Gf to ft:"
echo "0.9700882959 = `./tgmconv -kX -iGf -oft 1 | dec -k10`";
echo "Gf to in:"
echo "11.6410595508 = `./tgmconv -kX -iGf -oin 1 | dec -k10`";
echo "2_Gf to mm:"
echo "2.0533535596 = `./tgmconv -kX -i2_Gf -omm 1 | dec -k10`";
echo "6_Gf to m:"
echo "0.9902360916e-7 = `./tgmconv -kX -i6_Gf -om -e 1 | dec -k10 -e`"
echo "4^Gf to km:"
echo "6.1312808754 = `./tgmconv -kX -i4^Gf -okm 1 | dec -k10`";
echo "4^Gf to mi:"
echo "3.8098013075 = `./tgmconv -kX -i4^Gf -omi 1 | dec -k10`";
echo "m to Gf:"
echo "3;4701219X = `./tgmconv -k8 -im -oGf 1`";
echo "ft to Gf:"
echo "1;045345X0 = `./tgmconv -k8 -ift -oGf 1`";
echo "in to Gf:"
echo "0;1045345X = `./tgmconv -k8 -iin -oGf 1`";
echo "mm to 2_Gf:"
echo "0;5X16727E = `./tgmconv -k8 -imm -o2_Gf 1`";
echo "um to 6_Gf:"
echo "X;12247357 = `./tgmconv -k8 -ium -o6_Gf 1`";
echo "km to Gf:"
echo "1E5X;00233X8 = `./tgmconv -k7 -ikm -oGf 1`";
echo "mi to 3^Gf:"
echo "3;1969786 = `./tgmconv -k7 -imi -o3^Gf 1`";
echo "Vl to m/s:"
echo "1.7031335765 = `./tgmconv -kX -iVl -om/s 1 | dec -k10`";
echo "Vl to ft/s:"
echo "5.5877085843 = `./tgmconv -kX -iVl -oft/s 1 | dec -k10`";
echo "m/s to Vl:"
echo "0;7067255X = `./tgmconv -k8 -im/s -oVl 1`";
echo "ft/s to Vl:"
echo "2;1930041E = `./tgmconv -k8 -ift/s -o1_Vl 1`";
echo "km/hr to Vl:"
echo "0;1E5X = `./tgmconv -k4 -ikm/hr -oVl 1`";
echo "Vl to km/hr:"
echo "6.131 = `./tgmconv -k3 -okm/hr -iVl 1 | dec -k3`";
echo "Sf to m2:"
echo "8.7428384796e-2 = `./tgmconv -kX -iSf -om2 1 | dec -ek10`";
echo "Sf to ft2:"
echo "0.9410713018 = `./tgmconv -kX -iSf -oft2 1 | dec -k10`";
echo "4^Sf to acre:"
echo "0.4479810495 = `./tgmconv -kX -i4^Sf -oacre 1 | dec -k10`";
echo "4^Sf to ha:"
echo "0.1812914987 = `./tgmconv -kX -i4^Sf -oha 1 | dec -k10`";
echo "6^Sf to km2:"
echo "0.2610597581 = `./tgmconv -kX -i6^Sf -okm2 1 | dec -k10`";
echo "6^Sf to mi2:"
echo "0.1007957361 = `./tgmconv -kX -i6^Sf -omi2 1 | dec -k10`";
echo "4_Sf to mm2:"
echo "4.2162608409 = `./tgmconv -kX -i4_Sf -omm2 1 | dec -k10`";
echo "m2 to Sf:"
echo "E;5308E881 = `./tgmconv -k8 -oSf -im2 1`";
echo "ft2 to Sf:"
echo "1;09025668 = `./tgmconv -k8 -oSf -ift2 1`";
echo "acre to 4^Sf:"
echo "2;29538098 = `./tgmconv -k8 -o4^Sf -iacre 1`";
echo "ha to 4^Sf:"
echo "5;62373E49 = `./tgmconv -k8 -o4^Sf -iha 1`";
echo "km2 to 6^Sf:"
echo "3;9E7210XE = `./tgmconv -k8 -o6^Sf -ikm2 1`";
echo "mi2 to 6^Sf:"
echo "9;E076EX30 = `./tgmconv -k8 -o6^Sf -imi2 1`";
echo "mm2 to 5^Sf:"
echo "2;X1X127X9 = `./tgmconv -k8 -o5_Sf -imm2 1`";
echo "Vm to m3:"
echo "2.5851079459e-2 = `./tgmconv -kX -iVm -om3 1 | dec -ek10`";
echo "Vm to L:"
echo "25.8503556494 = `./tgmconv -kX -iVm -oL 1 | dec -k10`";
echo "Vm to ft3:"
echo "0.9129222555 = `./tgmconv -kX -iVm -oft3 1 | dec -k10`";
echo "Vm to yd3:"
echo "0.033811935389 = `./tgmconv -k12 -iVm -oyd3 1 | dec -k12`";
echo "Vm to gali:"
echo "5.6864459111 = `./tgmconv -kX -iVm -ogali 1 | dec -k10`";
echo "Vm to galc:"
echo "6.8290818133 = `./tgmconv -kX -iVm -ogalc 1 | dec -k10`";
echo "2_Vm to pti:"
echo "0.3159136617 = `./tgmconv -kX -i2_Vm -opti 1 | dec -k10`";
echo "2_Vm to ptc:"
echo "0.3793934341 = `./tgmconv -kX -i2_Vm -optc 1 | dec -k10`";
echo "4_Vm to mL:"
echo "1.2466413797 = `./tgmconv -kX -i4_Vm -omL 1 | dec -k10`";
echo "m3 to 1^Vm:"
echo "3;28244X22 = `./tgmconv -k8 -im3 -o1^Vm 1`";
echo "L to 2_Vm:"
echo "5;6X1X4457 = `./tgmconv -k8 -iL -o2_Vm 1`";
echo "ft3 to Vm:"
echo "1;1189X583 = `./tgmconv -k8 -ift3 -oVm 1`";
echo "yd3 to 1^Vm:"
echo "2;56XX2696 = `./tgmconv -k8 -iyd3 -o1^Vm 1`";
echo "gali to 1_Vm:"
echo "2;13X69515 = `./tgmconv -k8 -igali -o1_Vm 1`";
echo "galc to 1_Vm:"
echo "1;91051389 = `./tgmconv -k8 -igalc -o1_Vm 1`";
echo "pti to 2_Vm:"
echo "3;1E9X22E1 = `./tgmconv -k8 -ipti -o2_Vm 1`";
echo "ptc to 2_Vm:"
echo "2;77677E72 = `./tgmconv -k8 -iptc -o2_Vm 1`";
echo "mL to 5_Vm:"
echo "9;7615XXEX = `./tgmconv -k8 -imL -o5_Vm 1`";
echo "Mz to kg:"
echo "25.8503556494 = `./tgmconv -kX -iMz -okg 1 | dec -k10`";
echo "Mz to lb:"
echo "56.9902828681 = `./tgmconv -kX -iMz -olb 1 | dec -k10`";
echo "2^Mz to t:"
echo "3.7224512135 = `./tgmconv -kX -i2^Mz -ot 1 | dec -k10`";
echo "3_Mz to oz:"
echo "0.5276878043 = `./tgmconv -kX -i3_Mz -ooz 1 | dec -k10`";
echo "4_Mz to g:"
echo "1.2466413797 = `./tgmconv -kX -i4_Mz -og 1 | dec -k10`";
echo "kg to 2_Mz:"
echo "5;6X1X4457 = `./tgmconv -k8 -ikg -o2_Mz 1`";
echo "lb to 2_Mz:"
echo "2;63X2748X = `./tgmconv -k8 -ilb -o2_Mz 1`";
echo "t to 1^Mz:"
echo "3;28263384 = `./tgmconv -k8 -it -o1^Mz 1`";
echo "oz to 3_Mz:"
echo "1;X8X7E668 = `./tgmconv -k8 -ioz -o3_Mz 1`";
echo "g to 5_Mz:"
echo "9;7615XXEX = `./tgmconv -k8 -ig -o5_Mz 1`";
echo "Dz to kg/m3:"
echo "999.9720008 = `./tgmconv -k7 -iDz -okg/m3 1 | dec -k7`";
echo "kh/dm3 to Dz:"
echo "1;00006E73 = `./tgmconv -k8 -ikg/dm3 -oDz 1`";
echo "Vv to m2/s2:"
echo "2.9006639794 = `./tgmconv -kX -iVv -om2/s2 1 | dec -k10`";
echo "Vl2 to m2/s2:"
echo "2.9006639794 = `./tgmconv -kX -iVl2 -om2/s2 1 | dec -k10`";
echo "m2/s2 to Vv:"
echo "0;417885E7 = `./tgmconv -k8 -im2/s2 -oVv 1`";
echo "m2/s2 to Vl2:"
echo "0;417885E7 = `./tgmconv -k8 -im2/s2 -oVl2 1`";
echo "Mv to kh*m/s:"
echo "44.0266086711 = `./tgmconv -kX -iMv -okg*m/s 1 | dec -k10`";
echo "Mz*Vl to kh*m/s:"
echo "44.0266086711 = `./tgmconv -kX -iMz*Vl -okg*m/s 1 | dec -k10`";
echo "Mv to lb*ft/s:"
echo "318.4450928058 = `./tgmconv -kX -iMv -olb*ft/s 1 | dec -k10`";
echo "Mz*Vl to lb*ft/s:"
echo "318.4450928058 = `./tgmconv -kX -iMz*Vl -olb*ft/s 1 | dec -k10`";
echo "kg*m/s to 2_Mv:"
echo "3;32EX3114 = `./tgmconv -k8 -ikg*m/s -o2_Mv 1`";
echo "lb*ft/s to 3_Mv:"
echo "5;5149196E = `./tgmconv -k8 -ilb*ft/s -o3_Mv 1`";
echo "Mg to N:"
echo "253.5932659458 = `./tgmconv -kX -iMg -oN 1 | dec -k10`";
echo "253.5932659458 = `./tgmconv -kX -iMz*G -oN 1 | dec -k10`";
echo "Mg to kgf:"
echo "25.8593164787 = `./tgmconv -kX -iMg -okgf 1 | dec -k10`";
echo "Mg to lbf:"
echo "57.0100381234 = `./tgmconv -kX -iMg -olbf 1 | dec -k10`";
echo "N to 3_Mg:"
echo "6;9928453X = `./tgmconv -k8 -iN -o3_Mg 1`";
echo "kgf to 2_Mg:"
echo "5;69X64071 = `./tgmconv -k8 -ikgf -o2_Mg 1`";
echo "lbf to 2_Mg:"
echo "2;63885635 = `./tgmconv -k8 -ilbf -o2_Mg 1`";
echo "Tz to N/m:"
echo "857.652759595 = `./tgmconv -kX -iTz -oN/m 1 | dec -k10`";
echo "857.652759595 = `./tgmconv -kX -iMg/Gf -oN/m 1 | dec -k10`";
echo "4_Tz to dyn/cm:"
echo "41.360569039 = `./tgmconv -k9 -i4_Tz -odyn/cm 1 | dec -k9`";
echo "41.360569039 = `./tgmconv -k9 -i4_Mg/Gf -odyn/cm 1 | dec -k9`";
echo "N/m to 3_Tz:"
echo "2;0216E099 = `./tgmconv -k8 -iN/m -o3_Tz 1`";
echo "2;0216E099 = `./tgmconv -k8 -iN/m -o3_Mg/Gf 1`";
echo "dyn/cm to 6_Tz:"
echo "3;59411896 = `./tgmconv -k8 -idyn/cm -o6_Tz 1`";
echo "3;59411896 = `./tgmconv -k8 -idyn/cm -o6_Mg/Gf 1`";
echo "Pm to N/m2:"
echo "2900.582763 = `./tgmconv -k6 -iPm -oN/m2 1 | dec -k6`";
echo "2900.582763 = `./tgmconv -k6 -iMg/Sf -oN/m2 1 | dec -k6`";
echo "Pm to lbf/in2:"
echo "0.4206939918 = `./tgmconv -kX -iPm -olbf/in2 1 | dec -k10`";
echo "Pm to mmHg:"
echo "21.76 = `./tgmconv -k2 -iPm -ommHg 1 | dec -k2`";
echo "Pm to inHg:"
echo "0.85669 = `./tgmconv -k5 -iPm -oinHg 1 | dec -k5`";
echo "4^Pm to N/m2:"
echo "60.1464841756e6 = `./tgmconv -kX -i4^Pm -oN/m2 1 | dec -ek10`";
echo "60.1464841756e6 = `./tgmconv -kX -i4^Mg/Sf -oN/m2 1 | dec -ek10`";
echo "4^Pm to ton/in2:"
echo "3.8944243812 = `./tgmconv -kX -i4^Pm -otoni/in2 1 | dec -k10`";
echo "Atz to N/m2:"
echo "1.015204e5 = `./tgmconv -k6 -iAtz -oN/m2 1 | dec -ek6`";
echo "N/m2 to 4_Pm:"
echo "7;19539173 = `./tgmconv -k8 -iN/m2 -o4_Pm 1`";
echo "7;19539173 = `./tgmconv -k8 -iN/m2 -o4_Mg/Sf 1`";
echo "lbf/in2 to Pm:"
echo "2;4635E97X = `./tgmconv -k8 -ilbf/in2 -oPm 1`";
echo "mmHg to 2_Pm:"
echo "6;75 = `./tgmconv -k4 -immHg -o2_Pm 1`";
echo "inHg to Pm:"
echo "1;2011 = `./tgmconv -k5 -iinHg -oPm 1`";
echo "MeN/m2 to 2^Pm:"
echo "2;4891242X = `./tgmconv -k8 -iMeN/m2 -o2^Pm 1`";
echo "toni/in2 to 3^Pm:"
echo "3;0E8650E6 = `./tgmconv -k8 -itoni/in2 -o3^Pm 1`";
echo "atm to Atz:"
echo "0;EE88 = `./tgmconv -k8 -iatm -oAtz 1`";
echo "Wg to J:"
echo "74.9831954874 = `./tgmconv -kX -iWg -oJ 1 | dec -k10`";
echo "74.9831954874 = `./tgmconv -kX -iMg/Gf -oJ 1 | dec -k10`";
echo "Wg to ft-lbf:"
echo "55.3047707318 = `./tgmconv -kX -iWg -oft*lbf 1 | dec -k10`";
echo "55.3047707318 = `./tgmconv -kX -iMg/Gf -oft*lbf 1 | dec -k10`";
echo "Wg to cal(15):"
echo "17.9149911570 = `./tgmconv -kX -iWg -ocal 1 | dec -k10`";
echo "Wg to btu:"
echo "0.0711051221 = `./tgmconv -kX -iWg -obtu 1 | dec -k10`";
echo "5^Wg to kW*hr:"
echo "5.1828384721 = `./tgmconv -kX -i5^Wg -okW*hr 1 | dec -k10`";
echo "ePl to J:"
echo "1.3959244694e-16 = `./tgmconv -ek10 -iePl -oJ 1 | dec -ek10`";
echo "J to 2_Wg:"
echo "1;E0660616 = `./tgmconv -k8 -iJ -o2_Wg 1`";
echo "ft*lbf to 2_Wg:"
echo "2;72E352X2 = `./tgmconv -k8 -ift*lbf -o2_Wg 1`";
echo "cal to 2_Wg:"
echo "8;05571XXX = `./tgmconv -k8 -ical -o2_Wg 1`";
echo "btu to Wg:"
echo "12;0920688X = `./tgmconv -k8 -ibtu -oWg 1`";
echo "kW*hr to 4^Wg:"
echo "2;394X9107 = `./tgmconv -k8 -ikW*hr -o4^Wg 1`";
echo "fJ to ePl:"
echo "7;1E6X8767 = `./tgmconv -k8 -ifJ -oePl 1`";
echo "Pv to J/s (W):"
echo "431.9032060077 = `./tgmconv -kX -oJ/s -iPv 1 | dec -k10`";
echo "431.9032060077 = `./tgmconv -kX -oJ/s -iWg/Tm 1 | dec -k10`";
echo "Pv to ft*lbf/s:"
echo "318.5554794154 = `./tgmconv -kX -oft*lbf/s -iPv 1 | dec -k10`";
echo "318.5554794154 = `./tgmconv -kX -oft*lbf/s -iWg/Tm 1 | dec -k10`";
echo "Pv to hp:"
echo "0.5789587212 = `./tgmconv -kX -ohp -iPv 1 | dec -k10`";
echo "0.5789587212 = `./tgmconv -kX -ohp -iWg/Tm 1 | dec -k10`";
echo "W to 3_Pv:"
echo "4;00167091 = `./tgmconv -k8 -o3_Pv -iW 1`";
echo "4;00167091 = `./tgmconv -k8 -o3_Wg/Tm -iW 1`";
echo "ft*lbf/s to 3_Pv:"
echo "5;51161XX3 = `./tgmconv -k8 -o3_Pv -ift*lbf/s 1`";
echo "5;51161XX3 = `./tgmconv -k8 -o3_Wg/Tm -ift*lbf/s 1`";
echo "hp to Pv:"
echo "1;88880371 = `./tgmconv -k8 -oPv -ihp 1`";
echo "Vsd to N*s/m2:"
echo "503.5733963715 = `./tgmconv -kX -oN*s/m2 -iVsd 1 | dec -k10`";
echo "503.5733963715 = `./tgmconv -kX -oN*s/m2 -iMg*Tm/Sf 1 | dec -k10`";
echo "Vsn to m2/s:"
echo "0.50358749643 = `./tgmconv -k11 -om2/s -iVsn 1 | dec -k11`";
echo "0.50358749643 = `./tgmconv -k11 -om2/s -iSf/Tm 1 | dec -k11`";
echo "N*s/m2 to 3_Vsd:"
echo "3;52171036 = `./tgmconv -k8 -o3_Vsd -iN*s/m2 1`";
echo "3;52171036 = `./tgmconv -k8 -o3_Mg*Tm/Sf -iN*s/m2 1`";
echo "m2/s to Vsn:"
echo "1;E9E46851 = `./tgmconv -k8 -oVsn -im2/s 1`";
echo "1;E9E46851 = `./tgmconv -k8 -oSf/Tm -im2/s 1`";
echo "rGf (rad) to deg:"
echo "57.2957795131 = `./tgmconv -kX -irGf -odeg 1 | dec -k10`";
echo "57.2957795131 = `./tgmconv -kX -irad -odeg 1 | dec -k10`";
echo "deg to 2_rGf (2_rad):"
echo "2;61XE303X = `./tgmconv -k8 -ideg -o2_rGf 1`";
echo "0;0261XE303X = `./tgmconv -kX -ideg -orad 1`";
echo "rVl to rad/s:"
echo "5.76 = `./tgmconv -irVl -orad/s 1 | dec`";
echo "5.76 = `./tgmconv -irGf/Tm -orad/s 1 | dec`";
echo "rad/s to 1_rVl:"
echo "2;1 = `./tgmconv -irad/s -o1_rVl 1`";
echo "2;1 = `./tgmconv -irad/s -o1_rGf/Tm 1`";
echo "rG to rad/s2:"
echo "33.1776 = `./tgmconv -irG -orad/s2 1 | dec`";
echo "33.1776 = `./tgmconv -irGf/Tm2 -orad/s2 1 | dec`";
echo "rad/s2 to 2_rG:"
echo "4;41 = `./tgmconv -irad/s2 -o2_rG 1`";
echo "4;41 = `./tgmconv -irad/s2 -o2_rGf/Tm2 1`";
echo "Fq to Hz:"
echo "5.76 = `./tgmconv -iFq -oHz 1 | dec`";
echo "Fq to RPM:"
echo "345.6 = `./tgmconv -iFq -oRPM 1 | dec`";
echo "3^Fq to kHz:"
echo "9.95328 = `./tgmconv -k5 -i3^Fq -okHz 1 | dec -k5`";
echo "Hz to 1_Fq:"
echo "2;1 = `./tgmconv -iHz -o1_Fq 1`";
echo "RPM to 3_Fq:"
echo "5 = `./tgmconv -iRPM -o3_Fq 1`";
echo "X kHz to 3^Fq:"
echo "1;00814 = `./tgmconv -k5 -ikHz -o3^Fq X`";
echo "RMv to kg*m2/s:"
echo "13.0179158832 = `./tgmconv -kX -iRMv -okg*m2/s 1 | dec -k10`";
echo "13.0179158832 = `./tgmconv -kX -iMv*rGf -okg*m2/s 1 | dec -k10`";
echo "kg*m2/s to 2_RMv:"
echo "E;08X6E6E6 = `./tgmconv -k8 -ikg*m2/s -o2_RMv 1`";
echo "RMg to N*m:"
echo "74.9831954874 = `./tgmconv -kX -iRMg -oN*m 1 | dec -k10`";
echo "74.9831954874 = `./tgmconv -kX -iMg*rGf -oN*m 1 | dec -k10`";
echo "N*m to 2_RMg:"
echo "1;E0660616 = `./tgmconv -k8 -iN*m -o2_RMg 1`";
echo "1;E0660616 = `./tgmconv -k8 -iN*m -o2_Mg*rGf 1`";
echo "QMz to kg*m2:"
echo "2.2600548408 = `./tgmconv -kX -iQMz -okg*m2 1 | dec -k10`";
echo "2.2600548408 = `./tgmconv -kX -iRMg/rG -okg*m2 1 | dec -k10`";
echo "kg*m2 to 1_QMz:"
echo "5;386EE970 = `./tgmconv -k8 -ikg*m2 -o1_QMz 1`";
echo "5;386EE970 = `./tgmconv -k8 -ikg*m2 -o1_RMg/rG 1`";
echo "Kr to amp:"
echo "0.4957220687 = `./tgmconv -kX -iKr -oA 1 | dec -k10`";
echo "5_Kr to uA:"
echo "1.9921958137 = `./tgmconv -kX -i5_Kr -ouA 1 | dec -k10`";
echo "4^Kr to kA:"
echo "10.2792928167 = `./tgmconv -kX -i4^Kr -okA 1 | dec -k10`";
echo "A to Kr:"
echo "2;0259X834 = `./tgmconv -k8 -iA -oKr 1`";
echo "uA to 6_Kr:"
echo "6;03474748 = `./tgmconv -k8 -iuA -o6_Kr 1`";
echo "kA to 3^Kr:"
echo "1;2013142X = `./tgmconv -k8 -ikA -o3^Kr 1`";
echo "Kn to At:"
echo "0.4957220687 = `./tgmconv -kX -oAt -iKn 1 | dec -k10`";
echo "At to Kn:"
echo "2;0259X834 = `./tgmconv -k8 -iAt -oKn 1`";
echo "Pl to V:"
echo "871.2607996978 = `./tgmconv -kX -iPl -oV 1 | dec -k10`";
echo "1^Pl to kV:"
echo "10.4551295964 = `./tgmconv -kX -i1^Pl -okV 1 | dec -k10`";
echo "2^Pl to kV:"
echo "125.4615551565 = `./tgmconv -kX -i2^Pl -okV 1 | dec -k10`";
echo "1_Pl to V:"
echo "72.6050666415 = `./tgmconv -kX -i1_Pl -oV 1 | dec -k10`";
echo "2_Pl to V:"
echo "6.0504222201 = `./tgmconv -kX -i2_Pl -oV 1 | dec -k10`";
echo "3_Pl to V:"
echo "0.5042018517 = `./tgmconv -kX -i3_Pl -oV 1 | dec -k10`";
echo "6_Pl to mV:"
echo "0.2917834790 = `./tgmconv -kX -i6_Pl -omV 1 | dec -k10`";
echo "8_Pl to uV:"
echo "2.0262741596 = `./tgmconv -kX -i8_Pl -ouV 1 | dec -k10`";
echo "Og to ohm:"
echo "1757.55903297 = `./tgmconv -k8 -iOg -oohm 1 | dec -k8`";
echo "1757.55903297 = `./tgmconv -k8 -iPl/Kr -oohm 1 | dec -k8`";
echo "3^Og to Meohm:"
echo "3.0370620090 = `./tgmconv -kX -i3^Og -oMeohm 1 | dec -k10`";
echo "3.0370620090 = `./tgmconv -kX -i3^Pl/Kr -oMeohm 1 | dec -k10`";
echo "3_Og to ohm:"
echo "1.0171059219 = `./tgmconv -kX -i3_Og -oohm 1 | dec -k10`";
echo "kohm to 1_Og:"
echo "6;9E222121 = `./tgmconv -k8 -ikohm -o1_Og 1`";
echo "6;9E222121 = `./tgmconv -k8 -ikohm -o1_Pl/Kr 1`";
echo "Meohm to 2^Og:"
echo "3;E4E7992X = `./tgmconv -k8 -iMeohm -o2^Og 1`";
echo "ohm to 3_Og:"
echo "0;E96E3105 = `./tgmconv -k8 -iohm -o3_Og 1`";
echo "Go to umho:"
echo "568.9709314098 = `./tgmconv -kX -iGo -oumho 1 | dec -k10`";
echo "568.9709314098 = `./tgmconv -kX -iKr/Pl -ouS 1 | dec -k10`";
echo "3^Go to mho:"
echo "0.9831817695 = `./tgmconv -kX -i3^Go -omho 1 | dec -k10`";
echo "0.9831817695 = `./tgmconv -kX -i3^Kr/Pl -oS 1 | dec -k10`";
echo "mmho to Go:"
echo "1;91108E1X = `./tgmconv -k8 -immho -oGo 1`";
echo "1;91108E1X = `./tgmconv -k8 -imS -oKr/Pl 1`";
echo "mho to 3^Go:"
echo "1;02568601 = `./tgmconv -k8 -imho -o3^Go 1`";
echo "1;02568601 = `./tgmconv -k8 -iS -o3^Kr/Pl 1`";
echo "Quel to mC:"
echo "86.0628591502 = `./tgmconv -kX -iQl -omC 1 | dec -k10`";
echo "86.0628591502 = `./tgmconv -kX -iKr*Tm -omC 1 | dec -k10`";
echo "1^Ql to C:"
echo "1.0327543098 = `./tgmconv -kX -i1^Ql -oC 1 | dec -k10`";
echo "1.0327543098 = `./tgmconv -kX -i1^Kr*Tm -oC 1 | dec -k10`";
echo "mC to 2_Ql:"
echo "1;80E34748 = `./tgmconv -k8 -imC -o2_Ql 1`";
echo "1;80E34748 = `./tgmconv -k8 -imC -o2_Kr*Tm 1`";
echo "C to 1^Ql:"
echo "0;E7524207 = `./tgmconv -k8 -iC -o1^Ql 1`";
echo "0;E7524207 = `./tgmconv -k8 -iC -o1^Kr*Tm 1`";
echo "Kp to uF:"
echo "98.7796755920 = `./tgmconv -kX -iKp -ouF 1 | dec -k10`";
echo "98.7796755920 = `./tgmconv -kX -iQl/Pl -ouF 1 | dec -k10`";
echo "1_Kp to uF:"
echo "8.2316396327 = `./tgmconv -kX -i1_Kp -ouF 1 | dec -k10`";
echo "8.2316396327 = `./tgmconv -kX -i1_Ql/Pl -ouF 1 | dec -k10`";
echo "5_Kp to nF:"
echo "0.3969733619 = `./tgmconv -kX -i5_Kp -onF 1 | dec -k10`";
echo "0.3969733619 = `./tgmconv -kX -i5_Ql/Pl -onF 1 | dec -k10`";
echo "8_Kp to pF:"
echo "0.2297299548 = `./tgmconv -kX -i8_Kp -opF 1 | dec -k10`";
echo "0.2297299548 = `./tgmconv -kX -i8_Ql/Pl -opF 1 | dec -k10`";
echo "F to 3^Kp:"
echo "5;X3765921 = `./tgmconv -k8 -iF -o3^Kp 1`";
echo "5;X3765921 = `./tgmconv -k8 -iF -o3^Ql/Pl 1`";
echo "uF to 2_Kp:"
echo "1;55E088XE = `./tgmconv -k8 -iuF -o2_Kp 1`";
echo "1;55E088XE = `./tgmconv -k8 -iuF -o2_Ql/Pl 1`";
echo "nF to 5_Kp:"
echo "2;628E2XEX = `./tgmconv -k8 -inF -o5_Kp 1`";
echo "2;628E2XEX = `./tgmconv -k8 -inF -o5_Ql/Pl 1`";
echo "pF to 8_Kp:"
echo "4;429X5EE8 = `./tgmconv -k8 -ipF -o8_Kp 1`";
echo "4;429X5EE8 = `./tgmconv -k8 -ipF -o8_Ql/Pl 1`";
echo "Mt to uF/m:"
echo "334.0729930165 = `./tgmconv -kX -iMt -ouF/m 1 | dec -k10`";
echo "334.0729930165 = `./tgmconv -kX -iMb*Vv-1 -ouF/m 1 | dec -k10`";
echo "uF/m to 3_Mt:"
echo "5;20X15093 = `./tgmconv -k8 -o3_Mt -iuF/m 1`";
echo "5;20X15093 = `./tgmconv -k8 -o3_Mb*Vv-1 -iuF/m 1`";
echo "Fm to Wb:"
echo "151.2605555031 = `./tgmconv -kX -iFm -oWb 1 | dec -k10`";
echo "151.2605555031 = `./tgmconv -kX -iMb*Kr*Gf -oWb 1 | dec -k10`";
echo "6_Fm to uWb:"
echo "50.6568539895 = `./tgmconv -kX -i6_Fm -ouWb 1 | dec -k10`";
echo "50.6568539895 = `./tgmconv -kX -i6_Mb*Kr*Gf -ouWb 1 | dec -k10`";
echo "Wb to 2_Fm:"
echo "0;E5107E98 = `./tgmconv -k8 -iWb -o2_Fm 1`";
echo "0;E5107E98 = `./tgmconv -k8 -iWb -o2_Mb*Kr*Gf 1`";
echo "100 uWb to 6_Fm:"
echo "1;E8322E0E = `./tgmconv -k8 -iuWb -o6_Fm 84`";
echo "1;E8322E0E = `./tgmconv -k8 -iuWb -o6_Mb*Kr*Gf 84`";
echo "Fz to T:"
echo "1730.1080862416 = `./tgmconv -kX -iFz -oT 1 | dec -k10`";
echo "1730.1080862416 = `./tgmconv -kX -iFm/Sf -oT 1 | dec -k10`";
echo "3_Fz to T:"
echo "1.0012199573 = `./tgmconv -kX -i3_Fz -oT 1 | dec -k10`";
echo "1.0012199573 = `./tgmconv -kX -i3_Fm/Sf -oT 1 | dec -k10`";
echo "8_Fz to uT:"
echo "4.0236784550 = `./tgmconv -kX -i8_Fz -ouT 1 | dec -k10`";
echo "4.0236784550 = `./tgmconv -kX -i8_Fm/Sf -ouT 1 | dec -k10`";
echo "T to 3_Fz:"
echo "0;EE9X8980 = `./tgmconv -k8 -iT -o3_Fz 1`";
echo "0;EE9X8980 = `./tgmconv -k8 -iWb/m2 -o3_Fm/Gf2 1`";
echo "mT to 6_Fz:"
echo "1;88641939 = `./tgmconv -k8 -imT -o6_Fz 1`";
echo "uT to 9_Fz:";
echo "2;E955E053 = `./tgmconv -k8 -iuT -o9_Fz 1`";
echo "2;E955E053 = `./tgmconv -k8 -iuT -o9_Fm/Sf 1`";
echo "Gn to H:"
echo "305.1317765583 = `./tgmconv -kX -iGn -oH 1 | dec -k10`";
echo "305.1317765583 = `./tgmconv -kX -iMb*Gf -oH 1 | dec -k10`";
echo "6_Gn to mH:"
echo "0.1021880146 = `./tgmconv -kX -i6_Gn -omH 1 | dec -k10`";
echo "0.1021880146 = `./tgmconv -kX -i6_Mb*Gf -omH 1 | dec -k10`";
echo "H to 3_Gn:"
echo "5;7E5X7271 = `./tgmconv -k8 -iH -o3_Gn 1`";
echo "5;7E5X7271 = `./tgmconv -k8 -iH -o3_Mb*Gf 1`";
echo "mH to 6_Gn:"
echo "9;95200E47 = `./tgmconv -k8 -imH -o6_Gn 1`";
echo "9;95200E47 = `./tgmconv -k8 -imH -o6_Mb*Gf 1`";
echo "Lk to At/Wb:"
echo "0.0032772725649 = `./tgmconv -k13 -iLk -oAt/Wb 1 | dec -k13`";
echo "0.0032772725649 = `./tgmconv -k13 -iKn/Fm -oAt/Wb 1 | dec -k13`";
echo "At/Wb to 2^Lk:"
echo "2;1516E863 = `./tgmconv -k8 -iAt/Wb -o2^Lk 1`";
echo "2;1516E863 = `./tgmconv -k8 -iAt/Wb -o2^Kn/Fm 1`";
echo "Mb to H/m:"
echo "1031.9560704 = `./tgmconv -k7 -iMb -oH/m 1 | dec -k7`";
echo "H/m to 3_Mb:"
echo "1;811628 = `./tgmconv -k8 -iH/m -o3_Mb 1`";
echo "Pz to kW/m2:"
echo "4.9400798953 = `./tgmconv -kX -iPz -okW/m2 1 | dec -k10`";
echo "4.9400798953 = `./tgmconv -kX -iPv/Sf -okW/m2 1 | dec -k10`";
echo "kW/m2 to 1_Pz:"
echo "2;51960515 = `./tgmconv -k8 -ikW/m2 -o1_Pz 1`";
echo "2;51960515 = `./tgmconv -k8 -ikW/m2 -o1_Pv/Sf 1`";
echo "Lp to lm:"
echo "1.1795967512 = `./tgmconv -kX -iLp -olm 1 | dec -k10`";
echo "lm to 1_Lp:"
echo "X;20XX7E81 = `./tgmconv -k8 -ilm -o 1_Lp 1`";
echo "Ld to lm/m2:"
echo "13.4921485051 = `./tgmconv -kX -iLd -olm/m2 1 | dec -k10`";
echo "13.4921485051 = `./tgmconv -kX -iLp/Sf -olm/m2 1 | dec -k10`";
echo "lm/m2 to 2_Ld:"
echo "X;80X88694 = `./tgmconv -k8 -ilm/m2 -o2_Ld 1`";
echo "X;80X88694 = `./tgmconv -k8 -ilm/m2 -o2_Lp/Sf 1`";
echo "Sz to m2/lm*s:"
echo "0.4269149571 = `./tgmconv -kX -om2/lm*s -iSz 1 | dec -k10`";
echo "0.4269149571 = `./tgmconv -kX -om2/lm*s -iLd*Tm-1 1 | dec -k10`";
echo "m2/lm*s to Sz:"
echo "2;41378995 = `./tgmconv -k8 -im2/lm*s -oSz 1`";
echo "2;41378995 = `./tgmconv -k8 -im2/lm*s -oLd*Tm-1 1`";
echo "QLd to cd:"
echo "1.1795967512 = `./tgmconv -iQLd -ocd -kX 1 | dec -k10`";
echo "cd to 1_QLd:"
echo "X;20XX7E81 = `./tgmconv -k8 -icd -o1_QLd 1`";
echo "2^Cg to K:"
echo "0.1 = `./tgmconv -i2^Cg -oK 1 | dec`";
echo "K to 2^Cg:"
echo "X = `./tgmconv -o2^Cg -iK 1`";
echo "Ck to kJ/K:"
echo "107.9758015019 = `./tgmconv -kX -iCk -okJ/K 1 | dec -k10`";
echo "107.9758015019 = `./tgmconv -kX -iWg/Cg -okJ/K 1 | dec -k10`";
echo "5_Ck to J/K:"
echo "0.4339305294 = `./tgmconv -kX -i5_Ck -oJ/K 1 | dec -k10`";
echo "0.4339305294 = `./tgmconv -kX -i5_Wg/Cg -oJ/K 1 | dec -k10`";
echo "kJ/K to 2_Ck:"
echo "1;40062430 = `./tgmconv -k8 -ikJ/K -o2_Ck 1`";
echo "1;40062430 = `./tgmconv -k8 -ikJ/K -o2_Wg/Cg 1`";
echo "J/K to 5_Ck:"
echo "2;37X254E5 = `./tgmconv -k8 -iJ/K -o5_Ck 1`";
echo "2;37X254E5 = `./tgmconv -k8 -iJ/K -o5_Wg/Cg 1`";
echo "Csp to kJ/K*kg:"
echo "4.1769561304 = `./tgmconv -kX -okJ/K*kg -iCsp 1 | dec -k10`";
echo "4.1769561304 = `./tgmconv -kX -okJ/K*kg -iWg/Cg*Mz 1 | dec -k10`";
echo "4_Csp to J/K*kg:"
echo "0.2014349986 = `./tgmconv -kX -oJ/K*kg -i4_Csp 1 | dec -k10`";
echo "0.2014349986 = `./tgmconv -kX -oJ/K*kg -i4_Wg/Cg*Mz 1 | dec -k10`";
echo "kJ/K*kg to 1_Csp:"
echo "2;X5846983 = `./tgmconv -k8 -ikJ/K*kg -o1_Csp 1`";
echo "2;X5846983 = `./tgmconv -k8 -ikJ/K*kg -o1_Wg/Cg*Mz 1`";
echo "J/K*kg to 4_Csp:"
echo "4;E6X54908 = `./tgmconv -k8 -iJ/K*kg -o4_Csp 1`";
echo "4;E6X54908 = `./tgmconv -k8 -iJ/K*kg -o4_Wg/Cg*Mz 1`";
echo "Cdu to MeW/m*K:"
echo "2.1034039851 = `./tgmconv -kX -oMeW/m*K -iCdu 1 | dec -k10`";
echo "2.1034039851 = `./tgmconv -kX -oMeW/m*K -iWg*Gf/Sf*Cg 1 | dec -k10`";
echo "4_Cdu to W/m*K:"
echo "101.4373063783 = `./tgmconv -kX -oW/m*K -i4_Cdu 1 | dec -k10`";
echo "101.4373063783 = `./tgmconv -kX -oW/m*K -i4_Wg*Gf/Sf*Cg 1 | dec -k10`";
echo "kW/m*K to 4_Cdu:"
echo "9;X3719E98 = `./tgmconv -k8 -ikW/m*K -o4_Cdu 1`";
echo "9;X3719E98 = `./tgmconv -k8 -ikW/m*K -o4_Wg*Gf/Sf*Cg 1`";
echo "W/m*K to 2_Cdu:"
echo "1;50508E14 = `./tgmconv -k8 -iW/m*K -o6_Cdu 1`";
echo "1;50508E14 = `./tgmconv -k8 -iW/m*K -o6_Wg*Gf/Sf*Cg 1`";
echo "Tgr to m*K/m:"
echo "2.3486120262 = `./tgmconv -kX -iTgr -omK/m 1 | dec -k10`";
echo "2.3486120262 = `./tgmconv -kX -iCg/Gf -omK/m 1 | dec -k10`";
echo "2^Tgr to K/m:"
echo "0.3382001318 = `./tgmconv -kX -i2^Tgr -oK/m 1 | dec -k10`";
echo "0.3382001318 = `./tgmconv -kX -i2^Cg/Gf -oK/m 1 | dec -k10`";
echo "4^Tgr to K/m:"
echo "48.7008189752 = `./tgmconv -kX -i4^Tgr -oK/m 1 | dec -k10`";
echo "48.7008189752 = `./tgmconv -kX -i4^Cg/Gf -oK/m 1 | dec -k10`";
echo "K/m to 2^Tgr:"
echo "2;E5949856 = `./tgmconv -k8 -iK/m -o2^Tgr 1`";
echo "2;E5949856 = `./tgmconv -k8 -iK/m -o2^Cg/Gf 1`";
echo "K/cm to 4^Tgr:"
echo "2;078240X6 = `./tgmconv -k8 -iK/cm -o4^Tgr 1`";
echo "2;078240X6 = `./tgmconv -k8 -iK/cm -o4^Cg/Gf 1`";
echo "K/mm to 5^Tgr:"
echo "1;8649E489 = `./tgmconv -k8 -iK/mm -o5^Tgr 1`";
echo "1;8649E489 = `./tgmconv -k8 -iK/mm -o5^Cg/Gf 1`";
echo "Wsp to J/kg:"
echo "2.9006639794 = `./tgmconv -kX -iWsp -o J/kg 1 | dec -k10`";
echo "2.9006639794 = `./tgmconv -kX -iWg/Mz -o J/kg 1 | dec -k10`";
echo "4^Wsp to kJ/kg:"
echo "60.1481682772 = `./tgmconv -kX -i4^Wsp -okJ/kg 1 | dec -k10`";
echo "60.1481682772 = `./tgmconv -kX -i4^Wg/Mz -okJ/kg 1 | dec -k10`";
echo "6^Wsp to kJ/g:"
echo "8.6613362319 = `./tgmconv -kX -i6^Wsp -okJ/g 1 | dec -k10`";
echo "8.6613362319 = `./tgmconv -kX -i6^Wg/Mz -okJ/g 1 | dec -k10`";
echo "J/kg to 1_Wsp:"
echo "4;17885166 = `./tgmconv -k8 -iJ/kg -o1_Wsp 1`";
echo "4;17885166 = `./tgmconv -k8 -iJ/kg -o1_Wg/Mz 1`";
echo "kJ/kg to 2^Wsp:"
echo "2;488E980X = `./tgmconv -k8 -ikJ/kg -o2^Wsp 1`";
echo "2;488E980X = `./tgmconv -k8 -ikJ/kg -o2^Wg/Mz 1`";
echo "kJ/g to 5^Wsp:"
echo "1;476107X1 = `./tgmconv -k8 -ikJ/g -o5^Wsp 1`";
echo "1;476107X1 = `./tgmconv -k8 -ikJ/g -o5^Wg/Mz 1`";
echo "Fl to m3/s:"
echo "0.1489022177 = `./tgmconv -kX -iFl -om3/s 1 | dec -k10`";
echo "0.1489022177 = `./tgmconv -kX -iVm/Tm -om3/s 1 | dec -k10`";
echo "Fl to L/s:"
echo "148.89804854 = `./tgmconv -k8 -iFl -oL/s 1 | dec -k8`";
echo "148.89804854 = `./tgmconv -k8 -iVm/Tm -oL/s 1 | dec -k8`";
echo "Fl to ft3/s:"
echo "5.2584321917 = `./tgmconv -kX -iFl -oft3/s 1 | dec -k10`";
echo "5.2584321917 = `./tgmconv -kX -iVm/Tm -oft3/s 1 | dec -k10`";
echo "Fl to m3/min:"
echo "8.9341330612 = `./tgmconv -kX -iFl -om3/min 1 | dec -k10`";
echo "8.9341330612 = `./tgmconv -kX -iVm/Tm -om3/min 1 | dec -k10`";
echo "2_Fl to ft3/min:"
echo "2.1910134132 = `./tgmconv -kX -i2_Fl -oft3/min 1 | dec -k10`";
echo "2.1910134132 = `./tgmconv -kX -i2_Vm/Tm -oft3/min 1 | dec -k10`";
echo "2_Fl to gali/min:"
echo "13.6474701869 = `./tgmconv -kX -i2_Fl -ogali/min 1 | dec -k10`"; 
echo "13.6474701869 = `./tgmconv -kX -i2_Vm/Tm -ogali/min 1 | dec -k10`"; 
echo "2_Fl to galc/min:"
echo "16.3897963520 = `./tgmconv -kX -i2_Fl -ogalc/min 1 | dec -k10`"; 
echo "16.3897963520 = `./tgmconv -kX -i2_Vm/Tm -ogalc/min 1 | dec -k10`"; 
echo "m3/s to Fl:"
echo "6.870E2126 = `./tgmconv -k8 -im3/s -oFl 1`";
echo "6.870E2126 = `./tgmconv -k8 -im3/s -oVm/Tm 1`";
echo "L/s to 3_Fl:"
echo "E;731X7139 = `./tgmconv -k8 -iL/s -o3_Fl 1`";
echo "E;731X7139 = `./tgmconv -k8 -iL/s -o3_Vm/Tm 1`";
echo "ft3/s to Fl:"
echo "0;2347469X = `./tgmconv -k8 -ift3/s -oFl 1`";
echo "0;2347469X = `./tgmconv -k8 -ift3/s -oVm/Tm 1`";
echo "m3/min to 1_Fl:"
echo "1;414EX02E = `./tgmconv -k8 -im3/min -o1_Fl 1`";
echo "1;414EX02E = `./tgmconv -k8 -im3/min -o1_Vm/Tm 1`";
echo "ft3/min to 3_Flo:"
echo "5;58814451 = `./tgmconv -k8 -ift3/min -o3_Fl 1`";
echo "5;58814451 = `./tgmconv -k8 -ift3/min -o3_Vm/Tm 1`";
echo "gali/min to 4_Flo:"
echo "X;6749E590 = `./tgmconv -k8 -igali/min -o4_Fl 1`";
echo "X;6749E590 = `./tgmconv -k8 -igali/min -o4_Vm/Tm 1`";
echo "galc/min to 4_Flo:"
echo "8;95216679 = `./tgmconv -k8 -igalc/min -o4_Fl 1`";
echo "8;95216679 = `./tgmconv -k8 -igalc/min -o4_Vm/Tm 1`";
echo "Vsp to m3/kg:"
echo "1.000028e-03 = `./tgmconv -ek6 -iVsp -om3/kg 1 | dec -ek6`";
echo "1.000028e-03 = `./tgmconv -ek6 -iVm/Mz -om3/kg 1 | dec -ek6`";
echo "m3/kg to 2^Vsp:"
echo "6;E3E7E74E = `./tgmconv -k8 -im3/kg -o2^Vsp 1`";
echo "6;E3E7E74E = `./tgmconv -k8 -im3/kg -o2^Vm/Mz 1`";
echo "Ag to kg*m2/s:"
echo "13.0179158832 = `./tgmconv -kX -iAg -okg*m2/s 1 | dec -k10`";
echo "13.0179158832 = `./tgmconv -kX -iMv*Gf -okg*m2/s 1 | dec -k10`";
echo "kg*m2/s to 2_Ag:"
echo "E;08X6E6E6 = `./tgmconv -k8 -ikg*m2/s -o2_Ag 1`";
echo "E;08X6E6E6 = `./tgmconv -k8 -ikg*m2/s -o2_Mv*Gf 1`";
echo "RQl to C*m:"
echo "2.5447316859e-02 = `./tgmconv -ek10 -iRQl -oC*m 1 | dec -ek10`";
echo "2.5447316859e-02 = `./tgmconv -ek10 -iQl*Gf -oC*m 1 | dec -ek10`";
echo "C*m to 1^RQl:"
echo "3;3368EE86 = `./tgmconv -k8 -iC*m -o1^RQl 1`";
echo "3;3368EE86 = `./tgmconv -k8 -iC*m -o1^Ql*Gf 1`";
echo "Ry to ohm*m2/m:"
echo "519.6801739150 = `./tgmconv -kX -iRy -oohm*m2/m 1 | dec -k10`";
echo "519.6801739150 = `./tgmconv -kX -iOg*Sf/Gf -oohm*m2/m 1 | dec -k10`";
echo "4_Ry to ohm*cm2/cm:"
echo "2.5061736782 = `./tgmconv -kX -i4_Ry -oohm*cm2/cm 1 | dec -k10`";
echo "2.5061736782 = `./tgmconv -kX -i4_Og*Sf/Gf -oohm*cm2/cm 1 | dec -k10`";
echo "ohm*m2/m to 3_Ry:"
echo "3;3X998926 = `./tgmconv -k8 -iohm*m2/m -o3_Ry 1`";
echo "3;3X998926 = `./tgmconv -k8 -iohm*m2/m -o3_Og*Sf/Gf 1`";
echo "ohm*cm2/cm to 5_Ry:"
echo "4;955E7418 = `./tgmconv -k8 -iohm*cm2/cm -o5_Ry 1`";
echo "4;955E7418 = `./tgmconv -k8 -iohm*cm2/cm -o5_Og*Sf/Gf 1`";
echo "Edu to mho*m/m2:"
echo "0.00192426044 = `./tgmconv -k11 -iEdu -omho*m/m2 1 | dec -k11`";
echo "0.00192426044 = `./tgmconv -k11 -iGo*Gf/Sf -oS*m/m2 1 | dec -k11`";
echo "0.00192426044 = `./tgmconv -k11 -iGo*Gf/Sf -oohm-1*m/m2 1 | dec -k11`";
echo "4^Edu to mho*cm/cm2:"
echo "0.3990146448 = `./tgmconv -kX -i4^Edu -omho*cm/cm2 1 | dec -k10`";
echo "0.3990146448 = `./tgmconv -kX -i4^Go*Gf/Sf -oS*cm/cm2 1 | dec -k10`";
echo "0.3990146448 = `./tgmconv -kX -i4^Go*Gf/Sf -oohm-1*cm/cm2 1 | dec -k10`";
echo "mho*m/m2 to 2^Edu:"
echo "3;7381E410 = `./tgmconv -k8 -imho*m/m2 -o2^Edu 1`";
echo "3;7381E410 = `./tgmconv -k8 -iS*m/m2 -o2^Edu 1`";
echo "3;7381E410 = `./tgmconv -k8 -iohm-1*m/m2 -o2^Go*Gf/Sf 1`";
echo "mho*cm/cm2 to 4^Edu:"
echo "2;60180261 = `./tgmconv -k8 -imho*cm/cm2 -o4^Edu 1`";
echo "2;60180261 = `./tgmconv -k8 -iS*cm/cm2 -o4^Go*Gf/Sf 1`";
echo "2;60180261 = `./tgmconv -k8 -iohm-1*cm/cm2 -o4^Go*Gf/Sf 1`";
echo "Im to m2/V*s:"
echo "0.000577998570 = `./tgmconv -k10 -iIm -om2/V*s 1 | dec -k12`";
echo "0.000577998570 = `./tgmconv -k10 -iVl/Egr -om2/V*s 1 | dec -k12`";
echo "Im to cm2/V*s:"
echo "5.7799857012 = `./tgmconv -kX -iIm -ocm2/V*s 1 | dec -k10`";
echo "5.7799857012 = `./tgmconv -kX -iVl/Egr -ocm2/V*s 1 | dec -k10`";
echo "m2/V*s to 3^Im:"
echo "1;00213693 = `./tgmconv -k8 -im2/V*s -o3^Im 1`";
echo "1;00213693 = `./tgmconv -k8 -im2/V*s -o3^Vl/Egr 1`";
echo "cm2/V*s to 1_Im:"
echo "2;0XE6760E = `./tgmconv -k8 -icm2/V*s -o1_Im 1`";
echo "2;0XE6760E = `./tgmconv -k8 -icm2/V*s -o1_Vl/Egr 1`";
echo "Qz to C/m2:"
echo "0.9843812093 = `./tgmconv -kX -iQz -oC/m2 1 | dec -k10`";
echo "0.9843812093 = `./tgmconv -kX -iQl/Sf -oC/m2 1 | dec -k10`";
echo "C/m2 to Qz:"
echo "1;02350153 = `./tgmconv -k8 -iC/m2 -oQz 1`";
echo "1;02350153 = `./tgmconv -k8 -iC/m2 -oQl/Sf 1`";
echo "Dp to kg/C:"
echo "300.365987195 = `./tgmconv -k9 -iDp -okg/C 1 | dec -k9`";
echo "300.365987195 = `./tgmconv -k9 -iMz/Ql -okg/C 1 | dec -k9`";
echo "6_Dp to g/C:"
echo "1.0059196138 = `./tgmconv -kX -i6_Dp -og/C 1 | dec -k10`";
echo "1.0059196138 = `./tgmconv -kX -i6_Mz/Ql -og/C 1 | dec -k10`";
echo "kg/C to 3_Dp:"
echo "5;90519E05 = `./tgmconv -k8 -ikg/C -o3_Dp 1`";
echo "5;90519E05 = `./tgmconv -k8 -ikg/C -o3_Mz/Ql 1`";
echo "g/C to 6_Dp:"
echo "0;EE19E819 = `./tgmconv -k8 -ig/C -o6_Dp 1`";
echo "0;EE19E819 = `./tgmconv -k8 -ig/C -o6_Mz/Ql 1`";
echo "Egr to kV/m:"
echo "2.9466051727 = `./tgmconv -kX -iEgr -okV/m 1 | dec -k10`";
echo "2.9466051727 = `./tgmconv -kX -iPl/Gf -okV/m 1 | dec -k10`";
echo "4_Egr to V/m:"
echo "0.1421009489 = `./tgmconv -kX -i4_Egr -oV/m 1 | dec -k10`";
echo "0.1421009489 = `./tgmconv -kX -i4_Pl/Gf -oV/m 1 | dec -k10`";
echo "kV/m to 1_Egr:"
echo "4;0X530174 = `./tgmconv -k8 -ikV/m -o1_Egr 1`";
echo "4;0X530174 = `./tgmconv -k8 -ikV/m -o1_Pl/Gf 1`";
echo "V/m to 4_Egr:"
echo "7;05445283 = `./tgmconv -k8 -iV/m -o4_Egr 1`";
echo "7;05445283 = `./tgmconv -k8 -iV/m -o4_Pl/Gf 1`";
echo "RFm to Wb*m:"
echo "44.7251616108 = `./tgmconv -kX -iRFm -oWb*m 1 | dec -k10`";
echo "44.7251616108 = `./tgmconv -kX -iFm*Gf -oWb*m 1 | dec -k10`";
echo "Wb*m to 2_RFm:"
echo "3;2776E581 = `./tgmconv -k8 -iWb*m -o2_RFm 1`";
echo "3;2776E581 = `./tgmconv -k8 -iWb*m -o2_Fm*Gf 1`";
echo "Mgr to At/m:"
echo "1.6765326896 = `./tgmconv -kX -iMgr -oAt/m 1 | dec -k10`";
echo "1.6765326896 = `./tgmconv -kX -iKn/Gf -oAt/m 1 | dec -k10`";
echo "At/m to 1_Mgr:"
echo "7;1X847356 = `./tgmconv -k8 -iAt/m -o1_Mgr 1`";
echo "7;1X847356 = `./tgmconv -k8 -iAt/m -o1_Kn/Gf 1`";
echo "Lq to lum*s:"
echo "0.2047911026 = `./tgmconv -kX -iLq -olm*s 1 | dec -k10`";
echo "0.2047911026 = `./tgmconv -kX -iLp*Tm -olm*s 1 | dec -k10`";
echo "lum*s to Lq:"
echo "4;X71X4954 = `./tgmconv -k8 -ilm*s -oLq 1`";
echo "4;X71X4954 = `./tgmconv -k8 -ilm*s -oLp*Tm 1`";
echo "PGf to diopt:"
echo "3.3820013177 = `./tgmconv -kX -iPGf -odiopt 1 | dec -k10`";
echo "3.3820013177 = `./tgmconv -kX -iGf-1 -om-1 1 | dec -k10`";
echo "diopt to 1_PGf:"
echo "3;66E34543 = `./tgmconv -k8 -idiopt -o1_PGf 1`";
echo "Lf to lm/W:"
echo "2.7311599794e-03 = `./tgmconv -ekX -iLf -olm/W 1 | dec -ek10`";
echo "2.7311599794e-03 = `./tgmconv -ekX -iLp/Pv -olm/W 1 | dec -ek10`";
echo "5^Lf to lm/W:"
echo "679.6 = `./tgmconv -kX -i5^Lf -olm/W 1 | dec -k10`";
echo "679.6 = `./tgmconv -kX -i5^Lp/Pv -olm/W 1 | dec -k10`";
echo "lm/W to 2^Lf:"
echo "2;6618X247 = `./tgmconv -k8 -ilm/W -o2^Lf 1`";
echo "2;6618X247 = `./tgmconv -k8 -ilm/W -o2^Lp/Pv 1`";
echo "Osp to rad*m2/kg:"
echo "0.0033820960138 = `./tgmconv -k11 -iOsp -orad*m2/kg 1 | dec -k13`";
echo "0.0033820960138 = `./tgmconv -k11 -irGf/Gf*Dz -orad*m2/kg 1 | dec -k13`";
echo "Osp to rad*dm2/kg:"
echo "0.33820960138 = `./tgmconv -kE -iOsp -orad*dm2/kg 1 | dec -k11`";
echo "0.33820960138 = `./tgmconv -kE -irGf/Gf*Dz -orad*dm2/kg 1 | dec -k11`";
echo "rad*m2/kg to 2^Osp:"
echo "2;07811925 = `./tgmconv -k8 -irad*m2/kg -o2^Osp 1`";
echo "2;07811925 = `./tgmconv -k8 -irad*m2/kg -o2^rGf/Gf*Dz 1`";
echo "rad*dm2/kg to Osp:"
echo "2;E5931131 = `./tgmconv -k8 -irad*dm2/kg -oOsp 1`";
echo "2;E5931131 = `./tgmconv -k8 -irad*dm2/kg -orGf/Gf*Dz 1`";
echo "Mlz to kmol:"
echo "25.8503556494 = `./tgmconv -kX -iMlz -okmol 1 | dec -k10`";
echo "4_Mlz to mol:"
echo "1.2466413797 = `./tgmconv -kX -i4_Mlz -omol 1 | dec -k10`";
echo "kmol to 2_Mlz:"
echo "5;6X1X4457 = `./tgmconv -k8 -ikmol -o2_Mlz 1`";
echo "mol to 5_Mlz:"
echo "9;7615XXEX = `./tgmconv -k8 -imol -o5_Mlz 1`";
echo "Slz to mm2/mol:"
echo "3.3820960138 = `./tgmconv -kX -iSlz -omm2/mol 1 | dec -k10`";
echo "3.3820960138 = `./tgmconv -kX -iVlz/Gf -omm2/mol 1 | dec -k10`";
echo "2^Slz to cm2/mol:"
echo "4.8702182598 = `./tgmconv -kX -i2^Slz -ocm2/mol 1 | dec -k10`";
echo "4.8702182598 = `./tgmconv -kX -i2^Vlz/Gf -ocm2/mol 1 | dec -k10`";
echo "4^Slz to dm3/mol*cm:"
echo "0.7013114294 = `./tgmconv -kX -i4^Slz -odm3/mol*cm 1 | dec -k10`";
echo "0.7013114294 = `./tgmconv -kX -i4^Vlz/Gf -odm3/mol*cm 1 | dec -k10`";
echo "6^Slz to m2/mol:"
echo "10.0988845836 = `./tgmconv -kX -i6^Slz -om2/mol 1 | dec -k10`";
echo "10.0988845836 = `./tgmconv -kX -i6^Vlz/Gf -om2/mol 1 | dec -k10`";
echo "mm2/mol to 1_Slz:"
echo "3;66E13886 = `./tgmconv -k8 -imm2/mol -o1_Slz 1`";
echo "cm2/mol to 1^Slz:"
echo "2;56986E07 = `./tgmconv -k8 -icm2/mol -o1^Slz 1`";
echo "dm3/mol*cm to 4^Slz:"
echo "1;513E5688 = `./tgmconv -k8 -idm3/mol*cm -o4^Slz 1`";
echo "1;513E5688 = `./tgmconv -k8 -idm3/mol*cm -o4^Vlz/Gf 1`";
echo "m2/mol to 5^Slz:"
echo "1;23136773 = `./tgmconv -k8 -im2/mol -o5^Slz 1`";
echo "1;23136773 = `./tgmconv -k8 -im2/mol -o5^Vlz/Gf 1`";
echo "Vlz to cm3/mol:"
echo "1.000028 = `./tgmconv -k6 -iVlz -ocm3/mol 1 | dec -k6`";
echo "1.000028 = `./tgmconv -k6 -iVm/Mlz -ocm3/mol 1 | dec -k6`";
echo "6^Vlz to m3/mol:"
echo "2.9860676076 = `./tgmconv -kX -i6^Vlz -om3/mol 1 | dec -k10`";
echo "2.9860676076 = `./tgmconv -kX -i6^Vm/Mlz -om3/mol 1 | dec -k10`";
echo "cm3/mol to Vlz:"
echo "0;EEEE5049 = `./tgmconv -k8 -icm3/mol -oVlz 1`";
echo "0;EEEE5049 = `./tgmconv -k8 -icm3/mol -oVm/Mlz 1`";
echo "m3/mol to 5^Vlz:"
echo "4;0283 = `./tgmconv -im3/mol -o5^Vlz 1`";
echo "4;0283 = `./tgmconv -im3/mol -o5^Vm/Mlz 1`";
echo "Mlv to mol/dm3:"
echo "999.9720007840 = `./tgmconv -kX -iMlv -omol/dm3 1 | dec -k10`";
echo "999.9720007840 = `./tgmconv -kX -iMlz/Vm -omol/dm3 1 | dec -k10`";
echo "mol/dm3 to 3_Mlv:"
echo "1;88X0989E = `./tgmconv -k8 -imol/dm3 -o3_Mlv 1`";
echo "1;88X0989E = `./tgmconv -k8 -imol/dm3 -o3_Mlz/Vm 1`";
echo "Mlm to mol/kg:"
echo "1000.0 = `./tgmconv -iMlm -omol/kg 1 | dec`";
echo "1000.0 = `./tgmconv -iMlz/Mz -omol/kg 1 | dec`";
echo "mol/kg to 3_Mlm:"
echo "1;889E9843 = `./tgmconv -imol/kg -o3_Mlm -k8 1`";
echo "1;889E9843 = `./tgmconv -imol/kg -o3_Mlz/Mz -k8 1`";
echo "Wlz to J/kmol:"
echo "2.9006639794 = `./tgmconv -kX -iWlz -o J/kmol 1 | dec -k10`";
echo "2.9006639794 = `./tgmconv -kX -iWg/Mlz -o J/kmol 1 | dec -k10`";
echo "4^Wlz to J/mol:"
echo "60.1481682772 = `./tgmconv -kX -i4^Wlz -oJ/mol 1 | dec -k10`";
echo "60.1481682772 = `./tgmconv -kX -i4^Wg/Mlz -oJ/mol 1 | dec -k10`";
echo "6^Wlz to kJ/mol:"
echo "8.6613362319 = `./tgmconv -kX -i6^Wlz -okJ/mol 1 | dec -k10`";
echo "8.6613362319 = `./tgmconv -kX -i6^Wg/Mlz -okJ/mol 1 | dec -k10`";
echo "J/kmol to 1_Wlz:"
echo "4.17885167 = `./tgmconv -k8 -iJ/kmol -o1_Wlz 1`";
echo "4.17885167 = `./tgmconv -k8 -iJ/kmol -o1_Wg/Mlz 1`";
echo "J/mol to 2^Wlz:"
echo "2;488E980X = `./tgmconv -k8 -iJ/mol -o2^Wlz 1`";
echo "2;488E980X = `./tgmconv -k8 -iJ/mol -o2^Wg/Mlz 1`";
echo "kJ/mol to 5^Wlz:"
echo "1;476107X1 = `./tgmconv -k8 -ikJ/mol -o5^Wlz 1`";
echo "1;476107X1 = `./tgmconv -k8 -ikJ/mol -o5^Wg/Mlz 1`";
echo "Eul to S*cm2/kmol:"
echo "0.01924314319 = `./tgmconv -kE -iEul -oS*cm2/kmol 1 | dec -k11`";
echo "0.01924314319 = `./tgmconv -kE -iGo*Sf/Mlz -oS*cm2/kmol 1 | dec -k11`";
echo "4^Eul to S*cm2/mol:"
echo "0.3990258172 = `./tgmconv -kX -i4^Eul -oS*cm2/mol 1 | dec -k10`";
echo "0.3990258172 = `./tgmconv -kX -i4^Go*Sf/Mlz -oS*cm2/mol 1 | dec -k10`";
echo "8^Eul to S*m2/mol:"
echo "0.8274199345 = `./tgmconv -kX -i8^Eul -oS*m2/mol 1 | dec -k10`";
echo "0.8274199345 = `./tgmconv -kX -i8^Go*Sf/Mlz -oS*m2/mol 1 | dec -k10`";
echo "S*cm2/kmol to 1^Eul:"
echo "4;3E722778 = `./tgmconv -k8 -iS*cm2/kmol -o1^Eul 1`";
echo "4;3E722778 = `./tgmconv -k8 -iS*cm2/kmol -o1^Go*Sf/Mlz 1`";
echo "S*cm2/mol to 4^Eul:"
echo "2;60X668E8 = `./tgmconv -k8 -iS*cm2/mol -o4^Eul 1`";
echo "2;60X668E8 = `./tgmconv -k8 -iS*cm2/mol -o4^Go*Sf/Mlz 1`";
echo "S*m2/mol to 8^Eul:"
echo "1;26050507 = `./tgmconv -k8 -iS*m2/mol -o8^Eul 1`";
echo "1;26050507 = `./tgmconv -k8 -iS*m2/mol -o8^Go*Sf/Mlz 1`";
echo "Clz to J/K*mol:"
echo "4.1769561304 = `./tgmconv -kX -iClz -oJ/K*mol 1 | dec -k10`";
echo "4.1769561304 = `./tgmconv -kX -iWg/Cg*Mlz -oJ/K*mol 1 | dec -k10`";
echo "J/K*mol to 1_Clz:"
echo "2;X5846983 = `./tgmconv -k8 -iJ/K*mol -o1_Clz 1`";
echo "2;X5846983 = `./tgmconv -k8 -iJ/K*mol -o1_Wg/Cg*Mlz 1`";
echo "Olz to rad*mm2/mol:"
echo "3.3820960138 = `./tgmconv -kX -iOlz -orad*mm2/mol 1 | dec -k10`";
echo "3.3820960138 = `./tgmconv -kX -irGf*Vlz/Gf -orad*mm2/mol 1 | dec -k10`";
echo "6^Olz to rad*m2/mol:"
echo "10.0988845836 = `./tgmconv -kX -i6^Olz -orad*m2/mol 1 | dec -k10`";
echo "10.0988845836 = `./tgmconv -kX -i6^rGf*Vlz/Gf -orad*m2/mol 1 | dec -k10`";
echo "rad*mm2/mol to 1_Olz:"
echo "3;66E13886 = `./tgmconv -k8 -irad*mm2/mol -o1_Olz 1`";
echo "3;66E13886 = `./tgmconv -k8 -irad*mm2/mol -o1_rGf*Vlz/Gf 1`";
echo "rad*m2/mol to 5^Olz:"
echo "1;23136773 = `./tgmconv -k8 -irad*m2/mol -o5^Olz 1`";
echo "1;23136773 = `./tgmconv -k8 -irad*m2/mol -o5^rGf*Vlz/Gf 1`";
echo "Bq and Ci:"
echo "3.7e10 = `./tgmconv -ek8 -iCi -os-1 1 | dec -ek8`";
echo "37 = `./tgmconv -iCi -oGBq 1 | dec`";
echo "3.7 = `./tgmconv -imCi -oGBq 84 | dec`";
echo "2.7e-11 = `./tgmconv -e -iBq -oCi 1 | dec -e`";
echo "1;2E330765e9 = `./tgmconv -ek8 -iCi -oTm-1 1`";
echo "1;2E330765e9 = `doz 3.7e10 | ./tgmconv -iBq -oTm-1 -ek8`";
echo "1 = `./tgmconv -iTm-1 -oCi \"1;2E330765e9\"`";
echo "3.7e10 = `./tgmconv -ek8 -iTm-1 -oBq \"1;2E330765e9\" | dec -ek8`";
echo "Tmb to 2_Vm:"
echo "3 = `./tgmconv -iTmb -o2_Vm 1`";
echo "Tmb to pti:"
echo "0.94774 = `./tgmconv -iTmb -opti -k5 1 | dec -k5`";
echo "Tmb to ptc:"
echo "1.13818 = `./tgmconv -iTmb -optc -k5 1 | dec -k5`";
echo "Tmb to L:"
echo "0.538549 = `./tgmconv -iTmb -oL -k6 1 | dec -k6`";
echo "Qrt to 2_Vm:"
echo "6 = `./tgmconv -iQrt -o2_Vm 1`";
echo "Qrt to pti:"
echo "1.89548 = `./tgmconv -iQrt -opti -k5 1 | dec -k5`";
echo "Qrt to ptc:"
echo "2.27636 = `./tgmconv -iQrt -optc -k5 1 | dec -k5`";
echo "Qrt to L:"
echo "1.077098 = `./tgmconv -iQrt -oL -k6 1 | dec -k6`";
echo "Glv to 1_Vm:"
echo "2 = `./tgmconv -iGlv -o1_Vm 1`";
echo "Glv to pti:"
echo "7.58192 = `./tgmconv -iGlv -opti -k5 1 | dec -k5`";
echo "Glv to ptc:"
echo "9.10544 = `./tgmconv -iGlv -optc -k5 1 | dec -k5`";
echo "Glv to L:"
echo "4.308392 = `./tgmconv -iGlv -oL -k6 1 | dec -k6`";
echo "Oum to 3_Mz:"
echo "2 = `./tgmconv -iOum  -o3_Mz 1`";
echo "28 = `./tgmconv -iOum -o3_Mz 14`";
echo "Oum to 2_Mz:"
echo "6 = `./tgmconv -iOum -o2_Mz 30`";
echo "Oum to 1_Mz:"
echo "3 = `./tgmconv -iOum -o1_Mz 160`";
echo "Oum to Mz:"
echo "2 = `./tgmconv -iOum -oMz 1000`";
echo "Oum to oz:"
echo "1.0553756 = `./tgmconv -iOum -ooz -k7 1 | dec -k7`";
echo "Oum to lb:"
echo "1.0553756 = `./tgmconv -iOum -olb -k7 14 | dec -k7`";
echo "Oum to kg:"
echo "1.077098 = `./tgmconv -iOum -okg -k6 30 | dec -k6`";
echo "Oum to st:"
echo "1.01768 = `./tgmconv -iOum -ost -k5 160 | dec -k5`";
echo "Oum to cwt:"
echo "1.01768 = `./tgmconv -iOum -ocw -k5 1000 | dec -k5`";
echo "ePl to 25_Wg:"
echo "4;169150 = `./tgmconv -iePl -o15_Wg -k6 1`";
echo "ePl to eV:"
echo "871.2608 = `./tgmconv -iePl -oeV 1 | dec`";
echo "ePl to J:"
echo "1.3959244694e-16 = `./tgmconv -iePl -oJ -ekX 1 | dec -ek10`";
echo "3^ePl to MeeV:"
echo "1.505538662 = `./tgmconv -i3^ePl -oMeeV -kX 1 | dec -k10`";
echo "3^ePl to J:"
echo "2.4121574831e-13 = `./tgmconv -i3^ePl -oJ -ekX 1 | dec -ek10`";
echo "MeeV to 2^ePl:"
echo "7;E79187E2 = `./tgmconv -iMeeV -o2^ePl -k8 1`";
echo "Me to faraday:"
echo "25850.36 = `./tgmconv -iMe -ofaraday -k8 1 | dec -k8`";
echo "Me to 9^Ql:"
echo "5;749690 = `./tgmconv -iMe -o9^Ql -k8 1`";
echo "Me to C:"
echo "2.493358e09 = `./tgmconv -iMe -oC -ek8 1 | dec -ek8`";

exit;
