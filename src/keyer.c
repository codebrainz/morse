/* See COPYING file for copyright and license information. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "beep.h"
#include "morse.h"
#include "keyer.h"

/* Frequency for silence (0) */
#define SILENCE 0.0

struct Keyer {
  double freq;          // in hertz
  double unit_duration; // in seconds
  char verbose; // whether to print each char played to standard streams
};

void keyer_init(void)
{
  beep_init();
}

void keyer_shutdown(void)
{
  beep_shutdown();
}

Keyer *keyer_new(void)
{
  Keyer *k = calloc(1, sizeof(Keyer));
  if (k) {
    k->freq = KEYER_DEFAULT_FREQ;
    k->unit_duration = KEYER_DEFAULT_UNIT_DURATION;
    k->verbose = 1;
    keyer_init();
  }
  return k;
}

void keyer_free(Keyer *keyer)
{
  if (keyer) {
    /* ... */
    free(keyer);
  }
}

void keyer_set_freq(Keyer *keyer, double freq)
{
  if (keyer) {
    keyer->freq = freq;
  }
}

double keyer_get_freq(Keyer *keyer)
{
  return keyer ? keyer->freq : 0.0;
}

void keyer_set_unit_duration(Keyer *keyer, double unit_duration)
{
  if (keyer) {
    keyer->unit_duration = unit_duration;
  }
}

double keyer_get_unit_duration(Keyer *keyer)
{
  return keyer ? keyer->unit_duration : 0.0;
}

void keyer_set_verbose(Keyer *keyer, char verbose)
{
  if (keyer) {
    keyer->verbose = verbose;
  }
}

char keyer_get_verbose(Keyer *keyer)
{
  return keyer ? keyer->verbose : 1;
}

static void keyer_putchar(Keyer *keyer, char c)
{
  if (keyer != NULL && keyer->verbose) {
    fputc(c, stdout);
    fflush(stdout);
  }
}

static char *keyer_cleanstring(const char *s)
{
  unsigned int i;
  unsigned int dlen = 0;
  unsigned int slen = strlen(s);
  char *ptr;
  char *dup = malloc(slen+1);

  for (i = 0; i < slen; i++) {
    /* handle a single space not preceeded by another space */
    if (isspace(s[i]) && (i == 0 || !isspace(s[i-1]))) {
      dup[dlen++] = ' ';
      continue;
    } else if (morse_code_is_char(s[i])) { /* other valid morse chars */
      dup[dlen++] = s[i];
    }
  }
  dup[dlen-1] = '\0';

  /* Strip off trailing space */
  for (i = dlen-1; i >= 0; i--) {
    if (isspace(dup[i])) {
      dup[i] = '\0';
    } else {
      break;
    }
  }

  /* Strip off leading whitespace */
  for (ptr = dup; *ptr && isspace(*ptr); ptr++) {
    ;
  }
  memmove(dup, ptr, dlen-(ptr-dup));

  return dup;
}

void keyer_key_string(Keyer *keyer, const char *s)
{
  char *dup;
  char *ptr;
  unsigned int len;

  if (keyer == NULL || s == NULL) {
    return;
  }

  dup = keyer_cleanstring(s);

  for (ptr = dup; *ptr != '\0'; ptr++) {
    unsigned int i;
    char *code;

    if (isspace(*ptr)) {
      keyer_putchar(keyer, ' ');
      beep(SILENCE, keyer->unit_duration * 7); /* Inter-word gap */
    }

    code = (char*) morse_code_from_asc(*ptr);
    if (!code || !code[0])
      continue;
    len = strlen(code);

    keyer_putchar(keyer, *ptr);
    for (i = 0; i < len; i++) {
      if (code[i] == '.') {
        beep(keyer->freq, keyer->unit_duration);
      } else if (code[i] == '-') {
        beep(keyer->freq, keyer->unit_duration * 3);
      }
      beep(SILENCE, keyer->unit_duration); /* Inter-element gap */
    }
    beep(SILENCE, keyer->unit_duration*3); /* Inter-letter gap */

  }
  keyer_putchar(keyer, '\n');

  free(dup);
}
