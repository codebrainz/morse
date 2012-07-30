/* See COPYING file for copyright and license information. */
#ifndef BEEP_PRIVATE_H_
#define BEEP_PRIVATE_H_ 1

#define AMPLITUDE 255
#define SAMPLE_RATE 8000

typedef struct BeepBuffer {
  char *data;
  unsigned int len;
  double freq;
  double duration;
} BeepBuffer;

void beep_buffer_generate_sine_data(BeepBuffer *buf, double freq, double duration);

#endif /* BEEP_PRIVATE_H_ */
