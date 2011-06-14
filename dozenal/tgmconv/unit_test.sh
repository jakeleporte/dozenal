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
echo "Pm to inHg:"
echo "0.85669 = `./tgmconv -k5 -iPm -oinHg 1 | dec -k5`";
echo "4^Pm to N/m2:"
echo "60.1464841756e6 = `./tgmconv -k10 -i4^Pm -oN/m2 1 | dec -ek10`";
echo "60.1464841756e6 = `./tgmconv -k10 -i4^Mg/Sf -oN/m2 1 | dec -ek10`";
echo "4^Pm to ton/in2:"
echo "3.8944243812 = `./tgmconv -k10 -i4^Pm -otoni/in2 1 | dec -k10`";
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
echo "74.9831954874 = `./tgmconv -k10 -iWg -oJ 1 | dec -k10`";
echo "74.9831954874 = `./tgmconv -k10 -iMg/Gf -oJ 1 | dec -k10`";
echo "Wg to ft-lbf:"
echo "55.3047707318 = `./tgmconv -k10 -iWg -oft*lbf 1 | dec -k10`";
echo "55.3047707318 = `./tgmconv -k10 -iMg/Gf -oft*lbf 1 | dec -k10`";
echo "Wg to cal(15):"
echo "17.9149911570 = `./tgmconv -k10 -iWg -ocal 1 | dec -k10`";
echo "Wg to btu:"
echo "0.0711051221 = `./tgmconv -k10 -iWg -obtu 1 | dec -k10`";
echo "5^Wg to kW*hr:"
echo "5.1828384721 = `./tgmconv -k10 -i5^Wg -okW*hr 1 | dec -k10`";
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
echo "431.9032060077 = `./tgmconv -k10 -oJ/s -iPv 1 | dec -k10`";
echo "431.9032060077 = `./tgmconv -k10 -oJ/s -iWg/Tm 1 | dec -k10`";
echo "Pv to ft*lbf/s:"
echo "318.5554794154 = `./tgmconv -k10 -oft*lbf/s -iPv 1 | dec -k10`";
echo "318.5554794154 = `./tgmconv -k10 -oft*lbf/s -iWg/Tm 1 | dec -k10`";
echo "Pv to hp:"
echo "0.5789587212 = `./tgmconv -k10 -ohp -iPv 1 | dec -k10`";
echo "0.5789587212 = `./tgmconv -k10 -ohp -iWg/Tm 1 | dec -k10`";
echo "W to 3_Pv:"
echo "4;00167091 = `./tgmconv -k8 -o3_Pv -iW 1`";
echo "4;00167091 = `./tgmconv -k8 -o3_Wg/Tm -iW 1`";
echo "ft*lbf/s to 3_Pv:"
echo "5;51161XX3 = `./tgmconv -k8 -o3_Pv -ift*lbf/s 1`";
echo "5;51161XX3 = `./tgmconv -k8 -o3_Wg/Tm -ift*lbf/s 1`";
echo "hp to Pv:"
echo "1;88880371 = `./tgmconv -k8 -oPv -ihp 1`";
echo "Vsd to N*s/m2:"
echo "503.5733963715 = `./tgmconv -k10 -oN*s/m2 -iVsd 1 | dec -k10`";
echo "503.5733963715 = `./tgmconv -k10 -oN*s/m2 -iMg*Tm/Sf 1 | dec -k10`";
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
echo "57.2957795131 = `./tgmconv -k10 -irGf -odeg 1 | dec -k10`";
echo "57.2957795131 = `./tgmconv -k10 -irad -odeg 1 | dec -k10`";
echo "deg to 2_rGf (2_rad):"
echo "2;61XE303X = `./tgmconv -k8 -ideg -o2_rGf 1`";
echo "0;0261XE303X = `./tgmconv -k10 -ideg -orad 1`";
echo "rVl to rad/s:"
echo "5.76 = `./tgmconv -irVl -orad/s 1 | dec`";
echo "5.76 = `./tgmconv -irGf/Tm -orad/s 1 | dec`";
echo "rad/s to 1_rVl:"
echo "2;1 = `./tgmconv -irad/s -orVl 1`";
echo "2;1 = `./tgmconv -irad/s -orGf/Tm 1`";
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
echo "13.0179158832 = `./tgmconv -k10 -iRMv -okg*m2/s 1 | dec -k10`";
echo "13.0179158832 = `./tgmconv -k10 -iMv*rGf -okg*m2/s 1 | dec -k10`";
echo "kg*m2/s to 2_RMv:"
echo "E;08X6E6E6 = `./tgmconv -k8 -ikg*m2/s -o2_RMv 1`";
echo "RMg to N*m:"
echo "74.9831954874 = `./tgmconv -k10 -iRMg -oN*m 1 | dec -k10`";
echo "74.9831954874 = `./tgmconv -k10 -iMg*rGf -oN*m 1 | dec -k10`";
echo "N*m to 2_RMg:"
echo "1;E0660616 = `./tgmconv -k8 -iN*m -o2_RMg 1`";
echo "1;E0660616 = `./tgmconv -k8 -iN*m -o2_Mg*rGf 1`";
echo "QMz to kg*m2:"
echo "2.2600548408 = `./tgmconv -k10 -iQMz -okg*m2 1 | dec -k10`";
echo "2.2600548408 = `./tgmconv -k10 -iRMg/rG -okg*m2 1 | dec -k10`";
echo "kg*m2 to 1_QMz:"
echo "5;386EE970 = `./tgmconv -k8 -ikg*m2 -o1_QMz 1`";
echo "5;386EE970 = `./tgmconv -k8 -ikg*m2 -o1_RMg/rG 1`";
echo "Kr to amp:"
echo "0.4957220687 = `./tgmconv -k10 -iKr -oA 1 | dec -k10`";
echo "5_Kr to uA:"
echo "1.9921958137 = `./tgmconv -k10 -i5_Kr -ouA 1 | dec -k10`";
echo "4^Kr to kA:"
echo "10.2792928167 = `./tgmconv -k10 -i4^Kr -okA 1 | dec -k10`";
echo "A to Kr:"
echo "2;0259X834 = `./tgmconv -k8 -iA -oKr 1`";
echo "uA to 6_Kr:"
echo "6;03474748 = `./tgmconv -k8 -iuA -o6_Kr 1`";
echo "kA to 3^Kr:"
echo "1;2013142X = `./tgmconv -k8 -ikA -o3^Kr 1`";
echo "Kn to At:"
echo "0.4957220687 = `./tgmconv -k10 -oAt -iKn 1 | dec -k10`";
echo "At to Kn:"
echo "2;0259X834 = `./tgmconv -k8 -iAt -oKn 1`";
echo "Pl to V:"
echo "871.2607996978 = `./tgmconv -k10 -iPl -oV 1 | dec -k10`";
echo "1^Pl to kV:"
echo "10.4551295964 = `./tgmconv -k10 -i1^Pl -okV 1 | dec -k10`";
echo "2^Pl to kV:"
echo "125.4615551565 = `./tgmconv -k10 -i2^Pl -okV 1 | dec -k10`";
echo "1_Pl to V:"
echo "72.6050666415 = `./tgmconv -k10 -i1_Pl -oV 1 | dec -k10`";
echo "2_Pl to V:"
echo "6.0504222201 = `./tgmconv -k10 -i2_Pl -oV 1 | dec -k10`";
echo "3_Pl to V:"
echo "0.5042018517 = `./tgmconv -k10 -i3_Pl -oV 1 | dec -k10`";
echo "6_Pl to mV:"
echo "0.2917834790 = `./tgmconv -k10 -i6_Pl -omV 1 | dec -k10`";
echo "8_Pl to uV:"
echo "2.0262741596 = `./tgmconv -k10 -i8_Pl -ouV 1 | dec -k10`";
echo "Og to Ohm:"
echo "1757.55903297 = `./tgmconv -k8 -iOg -oOhm 1 | dec -k8`";
echo "1757.55903297 = `./tgmconv -k8 -iPl/Kr -oOhm 1 | dec -k8`";
echo "3^Og to MeOhm:"
echo "3.0370620090 = `./tgmconv -k10 -i3^Og -oMeOhm 1 | dec -k10`";
echo "3.0370620090 = `./tgmconv -k10 -i3^Pl/Kr -oMeOhm 1 | dec -k10`";
echo "3_Og to Ohm:"
echo "1.0171059219 = `./tgmconv -k10 -i3_Og -oOhm 1 | dec -k10`";
echo "kOhm to 1_Og:"
echo "6;9E222121 = `./tgmconv -k8 -ikOhm -o1_Og 1`";
echo "6;9E222121 = `./tgmconv -k8 -ikOhm -o1_Pl/Kr 1`";
echo "MeOhm to 2^Og:"
echo "3;E4E7992X = `./tgmconv -k8 -iMeOhm -o2^Og 1`";
echo "Ohm to 3_Og:"
echo "0;E96E3105 = `./tgmconv -k8 -iOhm -o3_Og 1`";
echo "Go to uMho:"
echo "568.9709314098 = `./tgmconv -k10 -iGo -ouMho 1 | dec -k10`";
echo "568.9709314098 = `./tgmconv -k10 -iKr/Pl -ouS 1 | dec -k10`";
echo "3^Go to Mho:"
echo "0.9831817695 = `./tgmconv -k10 -i3^Go -oMho 1 | dec -k10`";
echo "0.9831817695 = `./tgmconv -k10 -i3^Kr/Pl -oS 1 | dec -k10`";
echo "mMho to Go:"
echo "1;91108E1X = `./tgmconv -k8 -imMho -oGo 1`";
echo "1;91108E1X = `./tgmconv -k8 -imS -oKr/Pl 1`";
echo "Mho to 3^Go:"
echo "1;02568601 = `./tgmconv -k8 -iMho -o3^Go 1`";
echo "1;02568601 = `./tgmconv -k8 -iS -o3^Kr/Pl 1`";
echo "Quel to mC:"
echo "86.0628591502 = `./tgmconv -k10 -iQl -omC 1 | dec -k10`";
echo "86.0628591502 = `./tgmconv -k10 -iKr*Tm -omC 1 | dec -k10`";
echo "1^Ql to C:"
echo "1.0327543098 = `./tgmconv -k10 -i1^Ql -oC 1 | dec -k10`";
echo "1.0327543098 = `./tgmconv -k10 -i1^Kr*Tm -oC 1 | dec -k10`";
echo "mC to 2_Ql:"
echo "1;80E34748 = `./tgmconv -k8 -imC -o2_Ql 1`";
echo "1;80E34748 = `./tgmconv -k8 -imC -o2_Kr*Tm 1`";
echo "C to 1^Ql:"
echo "0;E7524207 = `./tgmconv -k8 -iC -o1^Ql 1`";
echo "0;E7524207 = `./tgmconv -k8 -iC -o1^Kr*Tm 1`";
echo "Kp to uF:"
echo "98.7796755920 = `./tgmconv -k10 -iKp -ouF 1 | dec -k10`";
echo "98.7796755920 = `./tgmconv -k10 -iQl/Pl -ouF 1 | dec -k10`";
echo "1_Kp to uF:"
echo "8.2316396327 = `./tgmconv -k10 -i1_Kp -ouF 1 | dec -k10`";
echo "8.2316396327 = `./tgmconv -k10 -i1_Ql/Pl -ouF 1 | dec -k10`";
echo "5_Kp to nF:"
echo "0.3969733619 = `./tgmconv -k10 -i5_Kp -onF 1 | dec -k10`";
echo "0.3969733619 = `./tgmconv -k10 -i5_Ql/Pl -onF 1 | dec -k10`";
echo "8_Kp to pF:"
echo "0.2297299548 = `./tgmconv -k10 -i8_Kp -opF 1 | dec -k10`";
echo "0.2297299548 = `./tgmconv -k10 -i8_Ql/Pl -opF 1 | dec -k10`";
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
echo "334.0729930165 = `./tgmconv -k10 -iMt -ouF/m 1 | dec -k10`";
echo "334.0729930165 = `./tgmconv -k10 -iMb*Vv-1 -ouF/m 1 | dec -k10`";
echo "uF/m to 3_Mt:"
echo "5;20X15093 = `./tgmconv -k8 -o3_Mt -iuF/m 1`";
echo "5;20X15093 = `./tgmconv -k8 -o3_Mb*Vv-1 -iuF/m 1`";
echo "Fm to Wb:"
echo "151.2605555031 = `./tgmconv -k10 -iFm -oWb 1 | dec -k10`";
echo "151.2605555031 = `./tgmconv -k10 -iMb*Kr*Gf -oWb 1 | dec -k10`";
echo "6_Fm to uWb:"
echo "50.6568539895 = `./tgmconv -k10 -i6_Fm -ouWb 1 | dec -k10`";
echo "50.6568539895 = `./tgmconv -k10 -i6_Mb*Kr*Gf -ouWb 1 | dec -k10`";
echo "Wb to 2_Fm:"
echo "0;E5107E98 = `./tgmconv -k8 -iWb -o2_Fm 1`";
echo "0;E5107E98 = `./tgmconv -k8 -iWb -o2_Mb*Kr*Gf 1`";
echo "100 uWb to 6_Fm:"
echo "1;E8322E0E = `./tgmconv -k8 -iuWb -o6_Fm 84`";
echo "1;E8322E0E = `./tgmconv -k8 -iuWb -o6_Mb*Kr*Gf 84`";
echo "Fz to T:"
echo "1730.1080862416 = `./tgmconv -k10 -iFz -oT 1 | dec -k10`";
echo "1730.1080862416 = `./tgmconv -k10 -iFm/Sf -oT 1 | dec -k10`";
echo "3_Fz to T:"
echo "1.0012199573 = `./tgmconv -k10 -i3_Fz -oT 1 | dec -k10`";
echo "1.0012199573 = `./tgmconv -k10 -i3_Fm/Sf -oT 1 | dec -k10`";
echo "8_Fz to uT:"
echo "4.0236784550 = `./tgmconv -k10 -i8_Fz -ouT 1 | dec -k10`";
echo "4.0236784550 = `./tgmconv -k10 -i8_Fm/Sf -ouT 1 | dec -k10`";
echo "T to 3_Fz:"
echo "0;EE9X8980 = `./tgmconv -k8 -iT -o3_Fz 1`";
echo "0;EE9X8980 = `./tgmconv -k8 -iWb/m2 -o3_Fm/Gf2 1`";
echo "mT to 6_Fz:"
echo "1;88641939 = `./tgmconv -k8 -imT -o6_Fz 1`";
echo "uT to 9_Fz:";
echo "2;E955E053 = `./tgmconv -k8 -iuT -o9_Fz 1`";
echo "2;E955E053 = `./tgmconv -k8 -iuT -o9_Fm/Sf 1`";
echo "Gn to H:"
echo "305.1317765583 = `./tgmconv -k10 -iGn -oH 1 | dec -k10`";
echo "305.1317765583 = `./tgmconv -k10 -iMb*Gf -oH 1 | dec -k10`";
echo "6_Gn to mH:"
echo "0.1021880146 = `./tgmconv -k10 -i6_Gn -omH 1 | dec -k10`";
echo "0.1021880146 = `./tgmconv -k10 -i6_Mb*Gf -omH 1 | dec -k10`";
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
exit;
