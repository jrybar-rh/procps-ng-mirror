CYGWINFLAGS =
if CYGWIN
  CYGWINFLAGS += -lintl
endif

AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-I$(top_srcdir)/include \
	-DLOCALEDIR=\"$(localedir)\"

AM_LDFLAGS = ../proc/libprocps.la

LDADD = $(CYGWINFLAGS)

dist_man_MANS = ps.1

# Use `ginstall' in the definition of PROGRAMS and in dependencies to avoid
# confusion with the `install' target.  The install rule transforms `ginstall'
# to install before applying any user-specified name transformations.
if CYGWIN
transform = s/pscommand/procps/; $(program_transform_name)
usrbin_exec_PROGRAMS = pscommand
else
transform = s/pscommand/ps/; $(program_transform_name)
bin_PROGRAMS = pscommand
endif
pscommand_SOURCES =  \
	common.h \
	display.c \
	global.c \
	help.c \
	output.c \
	parser.c \
	select.c \
	sortformat.c \
	stacktrace.c \
	$(top_srcdir)/lib/fileutils.c

EXTRA_DIST = \
	HACKING \
	regression
