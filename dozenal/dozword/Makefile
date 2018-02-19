# +AMDG
# This document was remade on 16 August 1201, the feast of
# St. Agapitus, M, and it is humbly dedicated to him and to
# the Immaculate Heart of Mary for her prayers, and to the
# Sacred Heart of Jesus for His mercy.

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR =../include
CC = gcc
GCCFLAGS = -Wall -std=c99 -pedantic
binobjects = dozword

all: bin

dozword: dozword.c ../conv/conv.o ../doz/doz.o ../dec/dec.o
	$(CC) $(GCCFLAGS) -I$(IDIR) -o dozword dozword.c ../conv/conv.o ../dec/dec.o ../doz/doz.o -lm 

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
