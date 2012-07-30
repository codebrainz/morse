#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <morse/beep.h>

#define DEFAULT_FREQ 440.0 /* in hertz */
#define DEFAULT_DUR 250.0  /* in milliseconds */

static void
parse_args(int argc, char *argv[], double *freq, double *dur);

int main(int argc, char *argv[])
{
  double freq, dur;

  parse_args(argc, argv, &freq, &dur);
  beep(freq, dur / 1000.0);
  beep_shutdown();

  return 0;
}

static void
print_help(void)
{
  static const char *help_text = "Usage: beep [-f VAL] [-d VAL]\n"
    "\nOptions:\n"
    "  -f VAL  Beep's sine wave frequency in Hertz.\n"
    "  -d VAL  Duration of the beep in milliseconds.\n"
    "\n"
    "Written by Matthew Brush <mbrush@codebrainz.ca>\n";
  fputs(help_text, stdout);
}

static void
parse_args(int argc, char *argv[], double *freq, double *dur)
{
  int i;
  double f = DEFAULT_FREQ;
  double d = DEFAULT_DUR;

  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      print_help();
      exit(EXIT_SUCCESS);
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

  if (freq)
    *freq = f;

  if (dur)
    *dur = d;
}
