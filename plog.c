/*
 * plog.c - print process log paths.
 * Copyright 2015 Vito Mule'
 * This file may be used subject to the terms and conditions of the
 * GNU Library General Public License Version 2 as published by the
 * Free Software Foundation.This program is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Library General Public License for more
 * details.
 */

#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "c.h"
#include "nls.h"
#include "fileutils.h"

static void __attribute__ ((__noreturn__)) usage(FILE * out) {
  fputs(USAGE_HEADER, out);
  fprintf(out, _(" %s [options] pid...\n"), program_invocation_short_name);
  fputs(USAGE_OPTIONS, out);
  fputs(USAGE_HELP, out);
  fputs(USAGE_VERSION, out);
  fprintf(out, USAGE_MAN_TAIL("plog(1)"));

  exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

int check_pid_argument(char *input) {
  int skip = 0;
  long pid;
  char *end = NULL;

  if (!strncmp("/proc/", input, 6)) {
    skip = 6;
  }
  errno = 0;
  pid = strtol(input + skip, &end, 10);

  if (errno || input + skip == end || (end && *end)) {
    return 1;
  }
  if (pid < 1) {
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int ch;

  static const struct option longopts[] = {
    {"version", no_argument, 0, 'V'},
    {"help", no_argument, 0, 'h'},
    {NULL, 0, 0, 0}
  };

  while ((ch = getopt_long(argc, argv, "Vh", longopts, NULL)) != -1)
    switch (ch) {
    case 'V':
      printf(PROCPS_NG_VERSION);
      return EXIT_SUCCESS;
    case 'h':
      usage(stdout);
    default:
      usage(stderr);
    }

  if (argc == 1) {
    usage(stderr);
  }

  /*
   * Allowed on the command line:
   *  -V
   *  /proc/nnnn
   *  nnnn
   *  where nnnn is any number that doesn't begin with 0.
   *  If --version or -V are present, further arguments are ignored
   *  completely.
   */

   if (check_pid_argument(argv[1])) {
     xerrx(EXIT_FAILURE, _("invalid process id: %s"),
           argv[1]);
   }

  /*
   * At this point, all arguments are in the form /proc/nnnn
   * or nnnn, so a simple check based on the first char is
   * possible.
   */

  struct dirent *namelist;
  char* fullpath = (char*) malloc(PATH_MAX+1);
  char* linkpath = (char*) malloc(PATH_MAX+1);
  char buf[PATH_MAX+1];
  DIR *proc_dir;

  if (argv[1][0] != '/') {
    strncpy(fullpath, "/proc/", PATH_MAX);
    strncat(fullpath, argv[1], PATH_MAX - strlen(fullpath));
    strncat(fullpath, "/fd/", PATH_MAX - strlen(fullpath));
  } else {
      strncpy(fullpath, argv[1], PATH_MAX);
      strncat(fullpath, "/fd/", PATH_MAX - strlen(fullpath));
    }

  proc_dir = opendir(fullpath);
  if (!proc_dir) {
    perror("opendir PID dir: ");
    return EXIT_FAILURE;
  }

  printf("Pid no %s:\n", argv[1]);

  regex_t re_log;
  regcomp(&re_log, "^(.*log)$",REG_EXTENDED|REG_NOSUB);

  while((namelist = readdir(proc_dir))) {
    strncpy(linkpath, fullpath, PATH_MAX);
    strncat(linkpath, namelist->d_name, PATH_MAX - strlen(linkpath));
    readlink(linkpath, buf, PATH_MAX -1);

    if (regexec(&re_log, buf, 0, NULL, 0) == 0) {
      printf("Log path: %s\n", buf);
    }
    memset(&linkpath[0], 0, sizeof(linkpath));
    memset(&buf[0], 0, sizeof(buf));
  }
  memset(&fullpath[0], 0, sizeof(fullpath));
  regfree(&re_log);
  return EXIT_SUCCESS;
}
