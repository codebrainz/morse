/* See COPYING file for copyright and license information. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "keyer.h"

#define INPUT_LINE_MAX 4096

static void parse_args(int argc, char *argv[], double *freq, double *dur, char *quiet);

int main(int argc, char *argv[])
{
  char line[INPUT_LINE_MAX] = { 0 };
  double freq = -1.0;
  double unit_dur = -1.0;
  char quiet = 0;
  Keyer *keyer = keyer_new();

  parse_args(argc, argv, &freq, &unit_dur, &quiet);

  if (freq > 0.0) {
    keyer_set_freq(keyer, freq);
  }

  if (unit_dur > 0.0) {
    keyer_set_unit_duration(keyer, unit_dur);
  }

  keyer_set_verbose(keyer, !quiet);

  while (fgets(line, INPUT_LINE_MAX, stdin) != NULL) {
    keyer_key_string(keyer, line);
    memset(line, 0, INPUT_LINE_MAX);
  }

  keyer_free(keyer);
  keyer_shutdown();

  return 0;
}

static void parse_args(int argc, char *argv[], double *freq, double *dur, char *quiet)
{
  int i;
  double f = -1.0;
  double d = -1.0;
  char q = 0;

  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      fputs("Usage: morse [-d VAL] [-f VAL] [-q]\n", stdout);
      exit(EXIT_SUCCESS);
    }
    if (strcmp(argv[i], "-q") == 0) {
      q = 1;
    }
    if (strcmp(argv[i], "-f") == 0) {
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
    }
    if (strcmp(argv[i], "-d") == 0) {
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

  if (freq) {
    *freq = f;
  }

  if (dur) {
    *dur = d;
  }

  if (quiet) {
    *quiet = q;
  }
}
