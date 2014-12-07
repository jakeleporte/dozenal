# +AMDG
#
# This document was begun on 13 January 2009, the
# commemoration of the Baptism of Our Lord, and it is humbly
# dedicated to the Immaculate Heart of Mary for her prayers,
# and to the Sacred Heart of Jesus for His mercy.
#
# Makefile for the decimal to dozenal converter.
#
# Changes 12/2014 by Nathan Fisher <nfisher.sr@gmx.com>

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR =../include
CC = gcc
binobjects = dec
objects = main.o dec.o

all: bin

dec: main.o ../conv/conv.o dec.o
	$(CC) -lm -o dec main.o ../conv/conv.o dec.o

main.o: main.c ../conv/conv.o dec.o
	$(CC) -I$(IDIR) -c main.c

../conv/conv.o:
	$(MAKE) -C ../conv

dec.o: ../conv/conv.o dec.c
	$(CC) -I$(IDIR) -c dec.c

bin: $(binobjects)

installdirs:
	install -d -m $(dirmode) $(bindir)

installbin: $(binobjects)
	for obj in $(binobjects) ; do \
		install -m $(binmode) $${obj} $(bindir) ; done

install: installdirs installbin

uninstall:
	for bin in $(binobjects) ; do \
		unlink $(bindir)/$${bin} ; done

clean:
	for obj in $(binobjects) $(objects) ; do \
		rm -f $${obj} ; done

.PHONY: bin clean install installbin uninstall
