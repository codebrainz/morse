/* See COPYING file for copyright and license information. */
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef BEEP_BACKEND_LIBAO

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ao/ao.h>
#include "beep.h"

#define AMPLITUDE 255
#define SAMPLE_RATE 8000

static short initialized = 0;

typedef struct buffer_t {
  char *data;
  unsigned int len;
  double freq;
  double duration;
} buffer_t;

static struct {
  int driver;
  ao_sample_format fmt;
  ao_device *device;
  buffer_t buffer;
} g_beep;

static buffer_t
generate_beep_sine(double freq, double duration)
{
  unsigned int i;
  buffer_t buf = { NULL, 0 };

  buf.freq = freq;
  buf.duration = duration;
  buf.len = (unsigned int) (duration * SAMPLE_RATE);
  buf.data = calloc(buf.len, sizeof(char));

  for (i = 0; i < buf.len; i++) {
    buf.data[i] = (char) (AMPLITUDE * sin((2 * M_PI * i * freq) / SAMPLE_RATE));
  }

  return buf;
}

void beep_init(void)
{
  if (initialized)
    return;

  memset(&g_beep, 0, sizeof(g_beep));

  ao_initialize();

  //g_beep.driver = ao_default_driver_id();
  /* FIXME: on my system the default Alsa doesn't work, only pulse. */
  g_beep.driver = ao_driver_id("pulse");

  if (g_beep.driver < 0) {
    fputs("error getting default driver\n", stderr);
    return;
  }

  g_beep.fmt.bits = 8;
  g_beep.fmt.rate = 8000;
  g_beep.fmt.channels = 1;

  g_beep.device = ao_open_live(g_beep.driver, &(g_beep.fmt), NULL);
  if (g_beep.device == NULL) {
    fprintf(stderr, "error opening default device for live playback: %s\n",
      strerror(errno));
    return;
  }

  initialized = 1;
}

void beep_shutdown(void)
{
  if (!initialized)
    return;
  free(g_beep.buffer.data);
  if (g_beep.device != NULL)
    ao_close(g_beep.device);
  ao_shutdown();
  memset(&g_beep, 0, sizeof(g_beep));
  initialized = 0;
}

void beep(double freq, double duration)
{
  beep_init();

  /* If different from last call, re-create the sine wave */
  if (freq != g_beep.buffer.freq || duration != g_beep.buffer.duration) {
    free(g_beep.buffer.data);
    g_beep.buffer = generate_beep_sine(freq, duration);
  }

  if (!ao_play(g_beep.device, g_beep.buffer.data, g_beep.buffer.len)) {
    fputs("error rendering sound sample, restarting audio system\n", stderr);
    beep_shutdown();
    beep_init();
  }
}

#endif /* BEEP_BACKEND_LIBAO */
