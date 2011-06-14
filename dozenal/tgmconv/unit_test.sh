#!/bin/bash
# +AMDG

echo "TIMS TO SECONDS:"
tgmconv -k8 -os -iTm 1 | dec;
echo "SECONDS TO TIMS:"
tgmconv -k8 -oTm -is 1;
echo "5 MINUTES TO TRINATIMS:"
tgmconv -k8 -o3^Tm -imin 5;
echo "TRINITIMS TO MS:"
tgmconv -k8 -oms -i3_Tm 1 | dec;
echo "MS TO 3_TM:"
tgmconv -k8 -ims -o3_Tm 1;
echo "G TO M/S2:"
tgmconv -k8 -iG -o m/s2 1 | dec;
echo "G TO FT/S2:"
tgmconv -k8 -iG -oft/s2 1 | dec;
echo "M/S2 TO G:"
tgmconv -k8 -oG -im/s2 1;
echo "FT/S2 TO G:"
tgmconv -k8 -oG -ift/s2 1;
echo "Gf to m:"
tgmconv -k8 -iGf -om 1 | dec;
echo "Gf to ft:"
tgmconv -k8 -iGf -oft 1 | dec;
echo "Gf to in:"
tgmconv -k8 -iGf -oin 1 | dec;
echo "2_Gf to mm:"
tgmconv -k8 -i2_Gf -omm 1 | dec;
echo "6_Gf to m:"
tgmconv -k8 -i6_Gf -om -e 1 | dec -e;
echo "4^Gf to km:"
tgmconv -k8 -i4^Gf -okm 1 | dec;
echo "4^Gf to mi:"
tgmconv -k8 -i4^Gf -omi 1 | dec;
echo "m to Gf:"
tgmconv -k8 -im -oGf 1;
echo "ft to Gf:"
tgmconv -k8 -ift -oGf 1;
echo "in to Gf:"
tgmconv -k8 -iin -oGf 1;
echo "mm to 2_Gf:"
tgmconv -k8 -imm -o2_Gf 1;
echo "um to 6_Gf:"
tgmconv -k8 -ium -o6_Gf 1;
echo "km to Gf:"
tgmconv -k8 -ikm -oGf 1;
echo "mi to 3^Gf:"
tgmconv -k8 -imi -o3^Gf 1;
echo "Vl to m/s:"
tgmconv -k8 -iVl -om/s 1 | dec;
echo "Vl to ft/s:"
tgmconv -k8 -iVl -oft/s 1 | dec;
echo "m/s to Vl:"
tgmconv -k8 -im/s -oVl 1;
echo "ft/s to Vl:"
tgmconv -k8 -ift/s -oVl 1;
echo "km/hr to Vl:"
tgmconv -k8 -ikm/hr -oVl 1;
echo "Vl to km/hr:"
tgmconv -k8 -okm/hr -iVl 1 | dec;
echo "Sf to m2:"
tgmconv -k8 -iSf -om2 1 | dec;
echo "Sf to ft2:"
tgmconv -k8 -iSf -oft2 1 | dec;
echo "4^Sf to acre:"
tgmconv -k8 -i4^Sf -oacre 1 | dec;
echo "4^Sf to ha:"
tgmconv -k8 -i4^Sf -oha 1 | dec;
echo "6^Sf to km2:"
tgmconv -k8 -i6^Sf -okm2 1 | dec;
echo "6^Sf to mi2:"
tgmconv -k8 -i6^Sf -omi2 1 | dec;
echo "4_Sf to mm2:"
tgmconv -k8 -i4_Sf -omm2 1 | dec;
echo "m2 to Sf:"
tgmconv -k8 -oSf -im2 1;
echo "ft2 to Sf:"
tgmconv -k8 -oSf -ift2 1;
echo "acre to 4^Sf:"
tgmconv -k8 -o4^Sf -iacre 1;
echo "ha to 4^Sf:"
tgmconv -k8 -o4^Sf -iha 1;
echo "km2 to 6^Sf:"
tgmconv -k8 -o6^Sf -ikm2 1;
echo "mi2 to 6^Sf:"
tgmconv -k8 -o6^Sf -imi2 1;
echo "mm2 to 5^Sf:"
tgmconv -k8 -o5_Sf -imm2 1;
echo "Vm to m3:"
tgmconv -k8 -iVm -om3 1 | dec;
echo "Vm to L:"
tgmconv -k8 -iVm -oL 1 | dec;
echo "Vm to ft3:"
tgmconv -k8 -iVm -oft3 1 | dec;
echo "Vm to yd3:"
tgmconv -k8 -iVm -oyd3 1 | dec;
echo "Vm to gali:"
tgmconv -k8 -iVm -ogali 1 | dec;
echo "Vm to galc:"
tgmconv -k8 -iVm -ogalc 1 | dec;
echo "2_Vm to pti:"
tgmconv -k8 -i2_Vm -opti 1 | dec;
echo "2_Vm to ptc:"
tgmconv -k8 -i2_Vm -optc 1 | dec;
echo "4_Vm to mL:"
tgmconv -k8 -i4_Vm -omL 1 | dec;
echo "m3 to 1^Vm:"
tgmconv -k8 -im3 -o1^Vm 1;
echo "L to 2_Vm:"
tgmconv -k8 -iL -o2_Vm 1;
echo "ft3 to Vm:"
tgmconv -k8 -ift3 -oVm 1;
echo "yd3 to 1^Vm:"
tgmconv -k8 -iyd3 -o1^Vm 1;
echo "gali to 1_Vm:"
tgmconv -k8 -igali -o1_Vm 1;
echo "galc to 1_Vm:"
tgmconv -k8 -igalc -o1_Vm 1;
echo "pti to 2_Vm:"
tgmconv -k8 -ipti -o2_Vm 1;
echo "ptc to 2_Vm:"
tgmconv -k8 -iptc -o2_Vm 1;
echo "mL to 5_Vm:"
tgmconv -k8 -imL -o5_Vm 1;
echo "Mz to kg:"
tgmconv -k8 -iMz -okg 1 | dec;
echo "Mz to lb:"
tgmconv -k8 -iMz -olb 1 | dec;
echo "2^Mz to t:"
tgmconv -k8 -i2^Mz -ot 1 | dec;
echo "3_Mz to oz:"
tgmconv -k8 -i3_Mz -ooz 1 | dec;
echo "4_Mz to g:"
tgmconv -k8 -i4_Mz -og 1 | dec;
echo "kg to 2_Mz:"
tgmconv -k8 -ikg -o2_Mz 1;
echo "lb to 2_Mz:"
tgmconv -k8 -ilb -o2_Mz 1;
echo "t to 1^Mz:"
tgmconv -k8 -it -o1^Mz 1;
echo "oz to 3_Mz:"
tgmconv -k8 -ioz -o3_Mz 1;
echo "g to 5_Mz:"
tgmconv -k8 -ig -o5_Mz 1;

exit;
