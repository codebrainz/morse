/* See COPYING file for copyright and license information. */
#ifndef KEYER_H_
#define KEYER_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

#define KEYER_DEFAULT_FREQ 1000.0
#define KEYER_DEFAULT_UNIT_DURATION 0.1

typedef struct Keyer Keyer;

/*
 * Globally initialize the keyer's backend. This is called implicity by
 * the `keyer_new()` function so you generally don't need to call it.
 */
void keyer_init(void);

/*
 * Globally shutdown the keyer's backend. Call this to free global memory
 * rather than to let the operating system free it on exit. Useful for
 * memory leaks checkers and stuff. After calling this function,
 * `keyer_init()` must be called again to re-initialize the global data for
 * further use.
 */
void keyer_shutdown(void);

/*
 * Allocate a new keyer.
 */
Keyer *keyer_new(void);

/*
 * Free memory used by a keyer.
 */
void keyer_free(Keyer *keyer);

/*
 * Set and get the frequency of the tones/beeps used by the keyer. The
 * unit is Hertz.
 */
void keyer_set_freq(Keyer *keyer, double freq);
double keyer_get_freq(Keyer *keyer);

/*
 * Set and get the duration of a single unit (ex. a dot). This is used to
 * determine the duration of the other elements (ex. dash, gaps, etc.). The
 * unit is Seconds.
 */
void keyer_set_unit_duration(Keyer *keyer, double unit_duration);
double keyer_get_unit_duration(Keyer *keyer);

/*
 * Play a string as morse code. The string must be nul (0) terminated.
 * Non-morse characters are not keyed and are ignored. Multiple consecutive
 * whitespace characters are played as a sigle space.
 */
void keyer_key_string(Keyer *keyer, const char *s);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* KEYER_H_ */
