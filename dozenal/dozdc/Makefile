# +AMDG
# This document was begun on 15 January 2010, the feast of
# St. Paul the Hermit, and it is humbly dedicated to him and
# to the Immaculate Heart of Mary for their prayers, and to
# the Sacred Heart of Jesus for His mercy.

logo_shapes_mask.xbm : logo_shapes_dozenal.xbm
	convert logo_shapes_dozenal.png -alpha copy \
	logo_shapes_mask.xbm

dozdc : main.o conv.h conv.o doz.o dec.o dozdc.h \
			getop.o stack.o stack.h vars.o vars.h
	gcc -g -lm -o dozdc main.o conv.o doz.o dec.o \
	getop.o stack.o stack.h vars.o vars.h

main.o : main.c conv.h conv.o doz.o dec.o dozdc.h \
			conv.h stack.o stack.h vars.o vars.h
	gcc -g -c main.c

getop.o : getop.c conv.h conv.o doz.o dec.o dozdc.h \
			stack.o stack.h vars.o vars.h
	gcc -g -lm -c getop.c

doz.o : conv.c conv.h doz.c
	gcc -lm -std=c99 -g -c doz.c

dec.o : conv.o conv.h dec.c
	gcc -g -c dec.c

conv.o : conv.c conv.h
	gcc -g -c conv.c

vars.o : vars.c vars.h stack.o
	gcc -g -c vars.c

stack.o : stack.c stack.h
	gcc -g -c stack.c

doc : dozdc.1
	rman -fHTML dozdc.1 > dozdc_man.html

prefix = /usr/local
bindir = /usr/local/bin
mandir = /usr/local/share/man/man1

install : dozdc dozdc.1
	cp ./dozdc $(bindir)
	cp ./dozdc.1 $(mandir)

uninstall :
	rm $(bindir)/dozdc
	rm $(mandir)/dozdc.1
