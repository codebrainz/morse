/* See COPYING file for copyright and license information. */
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef BEEP_BACKEND_PORTAUDIO

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <portaudio.h>

#include "beep.h"
#include "beep-private.h"

static short initialized = 0;

static struct {
  PaStream *stream;
  PaStreamParameters params;
  BeepBuffer buffer;
} g_beep;

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
  beep_buffer_generate_sine_data(&(g_beep.buffer), freq, duration);

  err = Pa_WriteStream(g_beep.stream, g_beep.buffer.data, g_beep.buffer.len);
  if (err != paNoError && err != paOutputUnderflowed) {
    fputs("error writing data to PortAudio output stream\n", stderr);
    return;
  }
}

#endif /* BEEP_BACKEND_PORTAUDIO */
