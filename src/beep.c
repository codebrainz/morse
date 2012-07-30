/* See COPYING file for copyright and license information. */
#include <stdlib.h>
#include <math.h>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "beep.h"
#include "beep-private.h"

void beep_buffer_generate_sine_data(BeepBuffer *buf, double freq, double duration)
{
  unsigned int i;

  if (buf == NULL) {
    return;
  }

  /* Don't re-create a buffer if it has the same freq and duration */
  if (buf->data != NULL && buf->freq == freq && buf->duration == duration) {
    return;
  }

  /* Free the old buffer */
  if (buf->data != NULL) {
    free(buf->data);
  }

  /* Setup the new buffer */
  buf->freq = freq;
  buf->duration = duration;
  buf->len = (unsigned int) (duration * SAMPLE_RATE);
  buf->data = calloc(buf->len, sizeof(char));

  /* Load sine wave data into buffer */
  for (i = 0; i < buf->len; i++) {
    buf->data[i] = (char) (AMPLITUDE * sin((2 * M_PI * i * freq) / SAMPLE_RATE));
  }
}
