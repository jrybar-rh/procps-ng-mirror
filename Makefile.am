#AUTOMAKE_OPTIONS = subdir-objects

CYGWINFLAGS =
if CYGWIN
  CYGWINFLAGS += -lintl
endif

AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-I$(top_srcdir)/include \
	-DLOCALEDIR=\"$(localedir)\"

ACLOCAL_AMFLAGS = -I m4
SUBDIRS = \
	include \
	lib \
	man-po \
	po \
	proc \
	ps \
	testsuite \
	top

AM_CFLAGS = -Iproc
AM_LDFLAGS = ./proc/libprocps.la

if !CYGWIN
sbin_PROGRAMS = \
	sysctl
endif

usrbin_exec_PROGRAMS = \
	free \
	pgrep \
	pkill \
	pmap \
	pwdx \
	tload \
	uptime \
	vmstat \
	w

dist_man_MANS = \
	free.1 \
	pgrep.1 \
	pkill.1 \
	tload.1 \
	pmap.1 \
	pwdx.1 \
	uptime.1 \
	vmstat.8 \
	w.1

if !CYGWIN
dist_man_MANS += \
	sysctl.8 \
	sysctl.conf.5
endif

EXTRA_DIST = \
	autogen.sh \
	contrib \
	COPYING.LIB \
	misc/git-version-gen \
	Documentation/CodingStyle \
	Documentation/TODO \
	$(DIST_MAN_POTS)

if !CYGWIN
EXTRA_DIST += \
	sysctl.conf
endif

if BUILD_PIDOF
usrbin_exec_PROGRAMS += pidof
dist_man_MANS += pidof.1
pidof_SOURCES = pidof.c $(top_srcdir)/lib/fileutils.c
else
  EXTRA_DIST += pidof.1
endif

if BUILD_KILL
if CYGWIN
transform = s/^kill/prockill/; $(program_transform_name)
usrbin_exec_PROGRAMS += kill
else
bin_PROGRAMS = kill
endif
dist_man_MANS += kill.1
kill_SOURCES = skill.c $(top_srcdir)/lib/strutils.c $(top_srcdir)/lib/fileutils.c $(top_srcdir)/lib/nsutils.c
else
  EXTRA_DIST += kill.1
endif

if WITH_NCURSES
usrbin_exec_PROGRAMS += \
	watch
dist_man_MANS += \
	watch.1
if !CYGWIN
usrbin_exec_PROGRAMS += \
	slabtop
dist_man_MANS += \
	slabtop.1
slabtop_SOURCES = slabtop.c $(top_srcdir)/lib/strutils.c $(top_srcdir)/lib/fileutils.c
slabtop_LDADD = @NCURSES_LIBS@
endif
watch_SOURCES = watch.c $(top_srcdir)/lib/strutils.c $(top_srcdir)/lib/fileutils.c
watch_LDADD = @WATCH_NCURSES_LIBS@ $(CYGWINFLAGS)
endif

if BUILD_SKILL
usrbin_exec_PROGRAMS += \
	skill \
	snice
skill_SOURCES = skill.c $(top_srcdir)/lib/strutils.c $(top_srcdir)/lib/fileutils.c $(top_srcdir)/lib/nsutils.c
snice_SOURCES = skill.c $(top_srcdir)/lib/strutils.c $(top_srcdir)/lib/fileutils.c $(top_srcdir)/lib/nsutils.c
dist_man_MANS += \
	skill.1 \
	snice.1
else
  EXTRA_DIST += \
	skill.1 \
	snice.1
endif

free_SOURCES = free.c $(top_srcdir)/lib/strutils.c $(top_srcdir)/lib/fileutils.c
pgrep_SOURCES = pgrep.c $(top_srcdir)/lib/fileutils.c $(top_srcdir)/lib/nsutils.c
pkill_SOURCES = pgrep.c $(top_srcdir)/lib/fileutils.c $(top_srcdir)/lib/nsutils.c
pmap_SOURCES = pmap.c $(top_srcdir)/lib/fileutils.c
pwdx_SOURCES = pwdx.c $(top_srcdir)/lib/fileutils.c
if !CYGWIN
sysctl_SOURCES = sysctl.c $(top_srcdir)/lib/fileutils.c
endif
tload_SOURCES = tload.c $(top_srcdir)/lib/strutils.c $(top_srcdir)/lib/fileutils.c
uptime_SOURCES = uptime.c $(top_srcdir)/lib/fileutils.c
vmstat_SOURCES = vmstat.c $(top_srcdir)/lib/strutils.c $(top_srcdir)/lib/fileutils.c
w_SOURCES = w.c $(top_srcdir)/lib/fileutils.c

skill_LDADD = $(CYGWINFLAGS)
kill_LDADD = $(CYGWINFLAGS)
free_LDADD = $(CYGWINFLAGS)
pgrep_LDADD = $(CYGWINFLAGS)
pkill_LDADD = $(CYGWINFLAGS)
pidof_LDADD = $(CYGWINFLAGS)
pmap_LDADD = $(CYGWINFLAGS)
pwdx_LDADD = $(CYGWINFLAGS)
snice_LDADD = $(CYGWINFLAGS)
tload_LDADD = $(CYGWINFLAGS)
uptime_LDADD = $(CYGWINFLAGS)
w_LDADD = $(CYGWINFLAGS)
vmstat_LDADD = $(CYGWINFLAGS)

if EXAMPLE_FILES
if !CYGWIN
sysconf_DATA = sysctl.conf
endif
endif

procpsngdir = $(docdir)
dist_procpsng_DATA = \
	Documentation/BUGS \
	Documentation/FAQ

BUILT_SOURCES = $(top_srcdir)/.version

$(top_srcdir)/.version:
	touch $(top_srcdir)/.version
	echo $(VERSION) > $@-t && mv $@-t $@
dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version

get-trans:
	echo "Getting the latest translations from translationproject.org..."
	rsync -Lrtvz  translationproject.org::tp/latest/procps-ng/  po
	rsync -Lrtvz  translationproject.org::tp/latest/procps-ng-man/  man-po
	rsync -Lrtvz  translationproject.org::tp/latest/procps-ng-man-ps/  man-po/ps
	rsync -Lrtvz  translationproject.org::tp/latest/procps-ng-man-top/  man-po/top
