/* See COPYING file for copyright and license information. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "keyer.h"

#ifdef HAVE_TERMIOS_H
#  include <termios.h>
#endif

#define INPUT_LINE_MAX 4096

static void parse_args(int argc, char *argv[], double *freq, double *dur,
  char *quiet, char *chr_mode);

int main(int argc, char *argv[])
{
  char line[INPUT_LINE_MAX] = { 0 };
  double freq = -1.0;
  double unit_dur = -1.0;
  char quiet = 0;
  char chr_mode = 0;
  int tty_fd = 0;
  Keyer *keyer;

  parse_args(argc, argv, &freq, &unit_dur, &quiet, &chr_mode);

  keyer = keyer_new();

  if (freq > 0.0) {
    keyer_set_freq(keyer, freq);
  }

  if (unit_dur > 0.0) {
    keyer_set_unit_duration(keyer, unit_dur);
  }

  keyer_set_verbose(keyer, !quiet);

#ifdef HAVE_TERMIOS_H
  if (chr_mode) {
    int c;
    struct termios tty_attr;

    keyer_set_verbose(keyer, 0);

    tcgetattr(tty_fd, &tty_attr);
    tty_attr.c_lflag &= ~ICANON;
    if (quiet)
      tty_attr.c_lflag &= ~ECHO;
    tcsetattr(tty_fd, 0, &tty_attr);

    while ((c = fgetc(stdin)) != EOF) {
      line[0] = (char) c;
      line[1] = '\0';
      keyer_key_string(keyer, line);
      memset(line, 0, INPUT_LINE_MAX);
    }

    tty_attr.c_lflag |= ICANON;
    if (quiet)
      tty_attr.c_lflag |= ECHO;
    tcsetattr(tty_fd, 0, &tty_attr);

  } else {
#else
  {
#endif
    while (fgets(line, INPUT_LINE_MAX, stdin) != NULL) {
      keyer_key_string(keyer, line);
      memset(line, 0, INPUT_LINE_MAX);
    }
  }

  keyer_free(keyer);
  keyer_shutdown();

  return 0;
}

static void print_help(void)
{
  static const char *help_text = "Usage: " PACKAGE " [-d VAL] [-f VAL] [-q]"
#ifdef HAVE_TERMIOS_H
    " [-c]"
#endif
    "\n\n"
    "Options:\n"
    "  -h      Show this message and exit.\n"
    "  -v      Show a version message and exit.\n"
    "  -d VAL  The duration of one unit (ex. dot).\n"
    "  -f VAL  The frequency of the beep's sine wave.\n"
    "  -q      Don't echo input to standard output.\n"
#ifdef HAVE_TERMIOS_H
    "  -c      Enable \"continuous\" or \"character\" mode.\n"
#endif
    "\nBackend in use: "
#if defined(BEEP_BACKEND_LIBAO)
    "libao\n"
#elif defined(BEEP_BACKEND_PORTAUDIO)
    "PortAudio\n"
#else
    "unknown\n"
#endif
    "\nWritten by Matthew Brush <mbrush@codebrainz.ca>\n";

  fputs(help_text, stdout);
}

static void parse_args(int argc, char *argv[], double *freq, double *dur,
  char *quiet, char *chr_mode)
{
  int i;
  double f = -1.0;
  double d = -1.0;
  char q = 0;
#ifdef HAVE_TERMIOS_H
  char c = 0;
#endif

  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      print_help();
      exit(EXIT_SUCCESS);
    } else if (strcmp(argv[i], "-v") == 0) {
      fputs(PACKAGE " v" PACKAGE_VERSION "\n", stdout);
      exit(EXIT_SUCCESS);
    } else if (strcmp(argv[i], "-q") == 0) {
      q = 1;
      continue;
#ifdef HAVE_TERMIOS_H
    } else if (strcmp(argv[i], "-c") == 0) {
      c = 1;
      continue;
#endif
    } else if (strcmp(argv[i], "-f") == 0) {
      if (i == argc-1) { /* last opt missing */
        fputs("error: missing value for frequency (-f) option\n", stderr);
        exit(EXIT_FAILURE);
      } else {
        char *endptr = NULL;
        errno = 0;
        f = strtod(argv[i+1], &endptr);
        if (endptr == argv[i+1] || errno != 0) {
          fprintf(stderr, "error: unable to convert '%s' to double\n", argv[i+1]);
          exit(EXIT_FAILURE);
        }
        i++;
        continue;
      }
    } else if (strcmp(argv[i], "-d") == 0) {
      if (i == argc-1) { /* last opt missing */
        fputs("error: missing value for unit duration (-d) option\n", stderr);
        exit(EXIT_FAILURE);
      } else {
        char *endptr = NULL;
        errno = 0;
        d = strtod(argv[i+1],  &endptr);
        if (endptr == argv[i+1] || errno != 0) {
          fprintf(stderr, "error: unable to convert '%s' to double\n", argv[i+1]);
          exit(EXIT_FAILURE);
        }
        i++;
        continue;
      }
    }
  }

  if (freq) { *freq = f; }
  if (dur) { *dur = d; }
  if (quiet) { *quiet = q; }
#ifdef HAVE_TERMIOS_H
  if (chr_mode) { *chr_mode = c; }
#endif
}
