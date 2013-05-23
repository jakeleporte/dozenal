#!/bin/bash
# +AMDG
# This document was begun on 8 February 2010, the feast of
# St. John Matha, and it is humbly dedicated to him and to 
# the Immaculate Heart of Mary for her prayers, and to the
# Sacred Heart of Jesus for His mercy.

tar -cvvf dozenal_v11E90216_src.tar ./dozenal/dec ./dozenal/doz \
./dozenal/dozdc ./dozenal/tgmconv ./dozenal/dozword \
./dozenal/dozpret ./dozenal/dozdate ./dozenal/dozstring \
./dozenal/install.sh ./dozenal/uninstall.sh;
tar -f dozenal_v11E90216_src.tar --wildcards --verbose --delete *.o ./dozenal/dozdc/dozdc ./dozenal/doz/doz ./dozenal/dec/dec ./dozenal/tgmconv/tgmconv ./dozenal/dozword/dozword ./dozenal/dozpret/dozpret ./dozenal/dozdate/dozdate ./dozenal/dozstring/dozstring;
gzip dozenal_v11E90216_src.tar;
tar -cvvf dozenal_v11E90216_bin_x86.tar ./dozenal/dozstring/dozstring ./dozenal/doz/doz ./dozenal/dec/dec ./dozenal/dozdc/dozdc ./dozenal/dozword/dozword ./dozenal/tgmconv/tgmconv ./dozenal/dozpret/dozpret ./dozenal/dozdate/dozdate ./dozenal/dozdate/gpl-3.0.txt;
gzip dozenal_v11E90216_bin_x86.tar;
