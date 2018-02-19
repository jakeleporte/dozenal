# +AMDG
# This document was begun on 7 February 2010, Sexagesima
# Sunday, and it is humbly dedicated to the Immaculate Heart
# of Mary for her prayers, and to the Sacred Heart of Jesus
# for His mercy.
#
# Changes 12/2014 by Nathan Fisher <nfisher.sr@gmx.com>

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR = ../include
CC = gcc
GCCFLAGS = -Wall -std=c99 -pedantic
objects = dozpret.o conv.h.gch
binobjects = dozpret

all: bin

dozpret: dozpret.o ../conv/conv.o
	$(CC) $(GCCFLAGS) -I$(IDIR) -o dozpret dozpret.o conv.o

dozpret.o: dozpret.c ../conv/conv.o
	$(CC) $(GCCFLAGS) -I$(IDIR) -c dozpret.c $(IDIR)/conv.h ../conv/conv.c

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
