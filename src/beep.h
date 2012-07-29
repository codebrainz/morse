/* See COPYING file for copyright and license information. */
#ifndef BEEP_H_
#define BEEP_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

void beep_init(void);
void beep_shutdown(void);
void beep(double freq, double duration);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BEEP_H_ */
