# +AMDG
# This document was begun on 7 February 2010, Sexagesima
# Sunday, and it is humbly dedicated to the Immaculate Heart
# of Mary for her prayers, and to the Sacred Heart of Jesus
# for His mercy.

dozpret : dozpret.c
	gcc -o dozpret dozpret.c

doc : dozpret.1
	rman -fHTML dozpret.1 > dozpret_man.html

prefix = /usr/local
bindir = /usr/local/bin
mandir = /usr/local/share/man/man1

install : dozpret dozpret.1
	cp ./dozpret $(bindir)
	cp ./dozpret.1 $(mandir)

uninstall :
	rm $(bindir)/dozpret
	rm $(mandir)/dozpret.1
