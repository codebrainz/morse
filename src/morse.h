/* See COPYING file for copyright and license information. */
#ifndef MORSE_H_
#define MORSE_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

char morse_code_is_char(char asc_char);
const char *morse_code_from_asc(char asc_char);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MORSE_H_ */

