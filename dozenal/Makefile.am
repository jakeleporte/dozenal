bin_PROGRAMS = doz dec dozword dozpret dozstring \
		doman tgmconv dozlua dozdate dozdc \
		dozcal ical $(XDOZDC)

bin_SCRIPTS = gdozdc
CLEANFILES = $(bin_SCRIPTS)
EXTRA_PROGRAMS = xdozdc

# doz
doz_SOURCES = src/doz.c src/conv.c

# dec
dec_SOURCES = src/dec.c src/conv.c

# dozword
dozword_SOURCES = src/dozword.c src/conv.c

# dozpret
dozpret_SOURCES = src/dozpret.c src/conv.c

# dozstring
dozstring_SOURCES = src/dozstring.c src/conv.c

# doman
doman_SOURCES = src/doman.c src/conv.c

# tgmconv
tgmconv_SOURCES = src/tgmconv.c src/tgm.c src/conv.c

# dozdate
dozdate_SOURCES = src/dozdate.c src/process_date.c \
			src/get_symmdate.c src/conv.c

# dozlua
dozlua_SOURCES = src/dozlua.c src/conv.c
dozlua_LDADD = $(LUA_LIB)
dozlua_CPPFLAGS = $(LUA_INCLUDE)

# dozdc
dozdc_SOURCES = src/dozdc_cli.c src/conv.c src/dozdc.c \
		src/getop.c src/vars.c src/stack.c src/shunt.c

# dozcal
dozcal_SOURCES = src/dozcal.c src/utility.c src/proc_date.c \
		src/process_file.c src/moon.c src/opt_file.c \
		src/easter.c src/nat_holidays.c src/jewish_date.c \
		src/islamic.c src/call_lua.c src/julday.c \
		src/astron.c src/geog.c src/sunriset.c src/tui.c \
		src/conv.c
dozcal_LDADD = $(LUA_LIB)
dozcal_CPPFLAGS = $(LUA_INCLUDE)

# ical
ical_SOURCES = src/icaltodcal.c

# xdozdc
xdozdc_SOURCES = src/xdozbc.c src/dozbc.c src/conv.c src/dozdc.c \
		src/getop.c src/vars.c src/stack.c src/shunt.c

# gdozdc
gdozdc: src/gdozdc.pl
	cp $< gdozdc
	chmod +x gdozdc
