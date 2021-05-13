# +AMDG
# This document was begun on 26 January 11E9, the feast of
# St. Martina, Virgin and Martyr; and it is humbly dedicated
# her and to the Immaculate Heart of Mary for their prayers,
# and to the Sacred Heart of Jesus for His mercy.
#
# Changes 12/2014 by Nathan Fisher <nfisher.sr@gmx.com>

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR = ../include
CC = tcc
objects = main.o
binobjects = dozstring

all: bin

dozstring : main.o ../doz/doz.o ../dec/dec.o
	$(CC) -I$(IDIR) -g main.o ../conv/conv.o ../doz/doz.o \
		../dec/dec.o -o dozstring -lm 

main.o : main.c ../conv/conv.o ../doz/doz.o ../dec/dec.o
	$(CC) -I$(IDIR) -g -c main.c

../doz/doz.o: ../conv/conv.o ../doz/doz.c
	$(MAKE) -C ../doz

../dec/dec.o: ../conv/conv.o ../dec/dec.c
	$(MAKE) -C ../dec

../conv/conv.o: ../conv/conv.c $(IDIR)/conv.h
	$(MAKE) -C ../conv

bin: $(binobjects)

installbin: $(binobjects)
	for obj in $(binobjects) ; do \
		install -m $(binmode) $${obj} $(bindir) ; done

install: installbin

uninstall:
	for bin in $(binobjects) ; do \
		unlink $(bindir)/$${bin} ; done

clean:
	for obj in $(binobjects) $(objects) ; do \
		rm -f $${obj} ; done

.PHONY: bin clean install installbin uninstall
