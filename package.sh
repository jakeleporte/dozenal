#!/bin/bash
# +AMDG
# This document was begun on 8 February 2010, the feast of
# St. John Matha, and it is humbly dedicated to him and to 
# the Immaculate Heart of Mary for her prayers, and to the
# Sacred Heart of Jesus for His mercy.

tar -cvvf dozenal_v1.0_src.tar ./dozenal/dec ./dozenal/doz \
./dozenal/dozdc ./dozenal/tgmconv ./dozenal/dozword \
./dozenal/install.sh ./dozenal/uninstall.sh;
tar -f dozenal_v1.0_src.tar --wildcards --verbose --delete *.o ./dozenal/dozdc/dozdc ./dozenal/doz/doz ./dozenal/dec/dec ./dozenal/tgmconv/tgmconv ./dozenal/dozword/dozword;
gzip dozenal_v1.0_src.tar;
