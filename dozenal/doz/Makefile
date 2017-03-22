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
objects = main.o doz.o
binobjects = doz

all: bin

doz : $(objects) ../conv/conv.o ../dec/dec.o
	$(CC) -g -o doz  main.o ../conv/conv.o doz.o ../dec/dec.o -lm 

main.o : main.c ../conv/conv.o doz.o ../dec/dec.o
	$(CC) -I$(IDIR) -g -lm -c main.c

../dec/dec.o:
	$(MAKE) -C ../dec

../conv/conv.o:
	$(MAKE) -C ../conv

doz.o : ../conv/conv.o doz.c
	$(CC) -I$(IDIR) -g -std=c99 -lm -c doz.c

bin: $(binobjects)

installbin: $(binobjects)
	for obj in $(binobjects)  ; do \
		install -m $(binmode) $${obj} $(bindir) ; done

install: installbin

uninstall:
	for bin in $(binobjects) ; do \
		unlink $(bindir)/$${bin} ; done

clean:
	for obj in $(binobjects) $(objects) ; do \
		rm -f $${obj} ; done

.PHONY: bin clean install installbin uninstall
