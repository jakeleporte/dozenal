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
GCCFLAGS = -Wall -std=c99 -pedantic
objects = main.o get_symmdate.o process_date.o
binobjects = dozdate

all: bin

dozdate: $(objects) ../doz/doz.o ../dec/dec.o ../conv/conv.o
	$(CC) $(GCCFLAGS) -I$(IDIR) -std=c99 -g -o dozdate main.o ../conv/conv.o \
		../doz/doz.o ../dec/dec.o process_date.o get_symmdate.o -lm 

main.o: main.c ../conv/conv.o ../doz/doz.o process_date.o \
		$(IDIR)/process_date.h $(IDIR)/get_symmdate.h get_symmdate.o
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c main.c

get_symmdate.o: get_symmdate.c ../conv/conv.o $(IDIR)/get_symmdate.h
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c get_symmdate.c

process_date.o: process_date.c ../conv/conv.c $(IDIR)/process_date.h
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c process_date.c ../conv/conv.c

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
	for obj in $(binobjects) $(objects) conv.o ; do \
		rm -f $${obj} ; done

.PHONY: bin clean installbin install uninstall
