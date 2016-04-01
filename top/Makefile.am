CYGWINFLAGS =
if CYGWIN
  CYGWINFLAGS += -lintl
endif

AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-I$(top_srcdir)/include \
	-DLOCALEDIR=\"$(localedir)\"

AM_LDFLAGS = ../proc/libprocps.la
AM_LDFLAGS += $(DL_LIB)

if WITH_NCURSES
usrbin_exec_PROGRAMS = \
	top

top_SOURCES =  \
	top.h \
	top.c \
	top_nls.h \
	top_nls.c \
	$(top_srcdir)/lib/fileutils.c

if CYGWIN
  top_SOURCES += $(top_srcdir)/lib/strverscmp.c
endif

dist_man_MANS = \
	top.1

top_LDADD = @NCURSES_LIBS@ $(CYGWINFLAGS)
endif

EXTRA_DIST =

procpsngdir = $(docdir)
dist_procpsng_DATA = \
	README.top
