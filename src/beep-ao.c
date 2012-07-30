/* See COPYING file for copyright and license information. */
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef BEEP_BACKEND_LIBAO

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ao/ao.h>
#include "beep.h"
#include "beep-private.h"

static short initialized = 0;

static struct {
  int driver;
  ao_sample_format fmt;
  ao_device *device;
  BeepBuffer buffer;
} g_beep;

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
  beep_buffer_generate_sine_data(&(g_beep.buffer), freq, duration);

  if (!ao_play(g_beep.device, g_beep.buffer.data, g_beep.buffer.len)) {
    fputs("error rendering sound sample, restarting audio system\n", stderr);
    beep_shutdown();
    beep_init();
  }
}

#endif /* BEEP_BACKEND_LIBAO */
