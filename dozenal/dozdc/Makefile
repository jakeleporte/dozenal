# +AMDG
# This document was begun on 15 January 2010, the feast of
# St. Paul the Hermit, and it is humbly dedicated to him and
# to the Immaculate Heart of Mary for their prayers, and to
# the Sacred Heart of Jesus for His mercy.
#
# Changes 12/2014 by Nathan Fisher <nfisher.sr@gmx.com>

prefix ?= /usr/local
bindir ?= $(prefix)/bin
binmode = 755
dirmode = 755
IDIR =../include
XFORMS_FLAGS =-DXFORMS
CC = gcc
GCCFLAGS = -Wall -std=c99 -pedantic
objects = dozdc.o getop.o vars.o stack.o shunt.o
other_objects = ../conv/conv.o ../doz/doz.o ../dec/dec.o
XFORM_OBJS = dozbc.o xdozbc.o
XFORM_LIBS = -lforms -L/usr/X11R6/lib -lX11
XFORM_INC = -I/usr/local/include -I/usr/X11R6/include
ifeq ($(XFORMS_FLAGS),-DXFORMS)
	binobjects = dozdc gdozdc xdozdc
else
	binobjects = dozdc gdozdc
endif

all: bin

dozdc : main.o $(objects) $(other_objects)
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -o dozdc main.o $(objects) \
		$(other_objects) -lm

xdozdc : $(XFORM_OBJS) $(objects) $(other_objects)
	$(CC) $(GCCFLAGS) -g -o xdozdc $(XFORM_OBJS) \
		$(objects) $(other_objects) \
		$(XFORM_LIBS) -lm

main.o : main.c $(IDIR)/conv.h $(IDIR)/doz.h $(IDIR)/dozdc.h stack.h getop.h
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c main.c

dozdc.o : dozdc.c $(IDIR)/dozdc.h stack.h getop.h $(IDIR)/conv.h
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c dozdc.c

xdozbc.o : xdozbc.c dozbc.h $(IDIR)/dozdc.h getop.h $(IDIR)/conv.h
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) $(XFORM_INC) -I$(IDIR) -g -c xdozbc.c

dozbc.o : dozbc.c dozbc.h
	$(CC) $(GCCFLAGS) $(XFORMS_FLAGS) $(XFORM_INC) -I$(DIR) -g -c dozbc.c

shunt.o : shunt.c
	$(CC) $(GCCFLAGS) -I$(DIR) -g -c shunt.c

getop.o : getop.c $(IDIR)/conv.h $(IDIR)/doz.h $(IDIR)/dozdc.h stack.h $(IDIR)/vars.h
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c getop.c

../doz/doz.o: ../conv/conv.o ../doz/doz.c
	$(MAKE) -C ../doz

../dec/dec.o: ../conv/conv.o ../dec/dec.c
	$(MAKE) -C ../dec

../conv/conv.o: ../conv/conv.c $(IDIR)/conv.h
	$(MAKE) -C ../conv

vars.o : vars.c $(IDIR)/vars.h stack.h
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c vars.c

stack.o : stack.c $(IDIR)/stack.h $(IDIR)/conv.h
	$(CC) $(GCCFLAGS) -I$(IDIR) -g -c stack.c

gdozdc : gdozdc.pl
	cp gdozdc.pl gdozdc

bin: $(binobjects)

installbin: $(binobjects)
	for obj in $(binobjects) ; do \
		install -m $(binmode) $${obj} $(bindir) ; done

install: installbin

uninstall:
	for bin in $(binobjects) ; do \
		unlink $(bindir)/$${bin} ; done

clean:
	for obj in $(binobjects) $(objects) $(XFORM_OBJS) main.o ; do \
		rm -f $${obj} ; done

.PHONY: bin clean install installbin uninstall
