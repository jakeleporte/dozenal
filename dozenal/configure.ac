# Process this file with autoconf to produce a configure script.

AC_INIT([dozenal], [12010904-3])
AC_CONFIG_SRCDIR([src/doz.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([subdir-objects -Wall foreign])
AC_CONFIG_FILES([Makefile])

# Option to disable `xdoozdc'
AC_ARG_ENABLE([xforms],
[AS_HELP_STRING([--disable-xforms],
[Do not compile `xdozdc', which depends on the XForms Toolkit.])],
[XFORMS=$enableval],
[XFORMS=yes])

# Check for a C compiler
AC_PROG_CC

# Check for the math library
AC_CHECK_LIB([m], [fmod])

# Check for the ncurses library
AC_CHECK_LIB([ncurses], [initscr])

# If needed, check for the XForms library and X11
if test "$XFORMS" = "yes"; then
AC_CHECK_LIB([X11], [XCreateWindow])
AC_CHECK_LIB([forms], [fl_initialize])
AC_SUBST([XDOZDC], [xdozdc])
fi

AX_PROG_LUA([5.2])
AX_LUA_HEADERS
AX_LUA_LIBS
AC_OUTPUT
