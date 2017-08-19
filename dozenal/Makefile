#  Makefile
#
#  Copyright 2014 Nathan Fisher <nfisher.sr@gmx.com>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#
#

prefix ?= /usr/local
bindir ?= $(prefix)/bin
mandir ?= $(prefix)/share/man
htmldir ?= $(prefix)/share/doc/dozenal
binmode = 755
dirmode = 755
manmode = 644
subdirs = \
doz \
dec \
dozdc \
tgmconv \
dozword \
dozpret \
dozdate \
dozstring \
dozcal \
doman

all: $(subdirs)

$(subdirs):
	$(MAKE) -C $@

htmldoc:
	$(MAKE) -C doc htmldoc

installhtml:
	$(MAKE) -C doc installhtml

installdirs:
	install -d -m $(dirmode) $(bindir)
	install -d -m $(dirmode) $(mandir)/man1

installbin:
	for dir in $(subdirs) ; do \
		$(MAKE) -C $${dir} install ; done

installdoc:
	$(MAKE) -C doc install

install: installbin installdoc

clean:
	for dir in $(subdirs) conv doc ; do \
		$(MAKE) -C $${dir} clean ; done
	rm -f ./include/conv.h.gch

uninstall:
	for dir in $(subdirs) doc ; do \
		$(MAKE) -C $$(dir) uninstall ; done

.PHONY: \
all \
$(subdirs) \
installbin \
installman \
installhtml \
install \
clean \
uninstall \
htmldoc \
installhtml
