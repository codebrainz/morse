/* See COPYING file for copyright and license information. */
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef BEEP_BACKEND_PORTAUDIO

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <portaudio.h>

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
  PaStream *stream;
  PaStreamParameters params;
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
  PaError err;

  if (initialized)
    return;

  memset(&g_beep, 0, sizeof(g_beep));

  err = Pa_Initialize();
  if (err != paNoError) {
    fputs("error initializing the PortAudio backend\n", stderr);
    return;
  }

  g_beep.params.device = Pa_GetDefaultOutputDevice();
  g_beep.params.channelCount = 1;
  g_beep.params.sampleFormat = paUInt8;
  g_beep.params.suggestedLatency = Pa_GetDeviceInfo(g_beep.params.device)->defaultHighOutputLatency;
  g_beep.params.hostApiSpecificStreamInfo = NULL;

  err = Pa_OpenStream(&(g_beep.stream), NULL, &g_beep.params,
    8000, paFramesPerBufferUnspecified, 0, NULL, NULL);
  if (err != paNoError) {
    fputs("error opening the PortAudio output stream\n", stderr);
    return;
  }

  err = Pa_StartStream(g_beep.stream);
  if (err != paNoError) {
    fputs("error starting the PortAudio output stream\n", stderr);
    return;
  }

  initialized = 1;
}

void beep_shutdown(void)
{
  PaError err;

  if (!initialized)
    return;

  free(g_beep.buffer.data);

  if (g_beep.stream != NULL) {
    err = Pa_StopStream(g_beep.stream);
    if (err != paNoError) {
      fputs("error stopping the PortAudio output stream\n", stderr);
      return;
    }
    err = Pa_CloseStream(g_beep.stream);
    if (err != paNoError) {
      fputs("error closing the PortAudio output stream\n", stderr);
    }
  }

  Pa_Terminate();

  memset(&g_beep, 0, sizeof(g_beep));

  initialized = 0;
}

void beep(double freq, double duration)
{
  PaError err;

  beep_init();

  /* If different from last call, re-create the sine wave */
  if (freq != g_beep.buffer.freq || duration != g_beep.buffer.duration) {
    free(g_beep.buffer.data);
    g_beep.buffer = generate_beep_sine(freq, duration);
  }

  err = Pa_WriteStream(g_beep.stream, g_beep.buffer.data, g_beep.buffer.len);
  if (err != paNoError && err != paOutputUnderflowed) {
    fputs("error writing data to PortAudio output stream\n", stderr);
    return;
  }
}

#endif /* BEEP_BACKEND_PORTAUDIO */
