# +AMDG

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR = ../include
CC = tcc
GCCFLAGS = -Wall -std=c99 -pedantic
objects = main.o tgm.o
binobjects = tgmconv

all: bin

tgmconv: main.o ../doz/doz.o ../dec/dec.o tgm.o $(IDIR)/tgmconv.h \
		../conv/conv.o
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -o tgmconv main.o tgm.o ../doz/doz.o \
		../dec/dec.o ../conv/conv.o -lm

main.o: main.c $(IDIR)/tgmconv.h ../dec/dec.o ../doz/doz.o ../conv/conv.c
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c main.c

tgm.o: tgm.c $(IDIR)/tgmconv.h $(IDIR)/conv.h ../conv/conv.c
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c tgm.c

../doz/doz.o: ../doz/doz.c ../conv/conv.o
	$(MAKE) -C ../doz

../dec/dec.o: ../dec/dec.c ../conv/conv.o
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

.PHONY: bin clean install install_bin uninstall
