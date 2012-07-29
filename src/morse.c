/* See COPYING file for copyright and license information. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "morse.h"

#define MORSE_CHAR_MAX 255

const char *MORSE_CODES[MORSE_CHAR_MAX+1] = {
  "",       /* 0: NOT USED */
  "",       /* 1: NOT USED */
  "",       /* 2: NOT USED */
  "",       /* 3: NOT USED */
  "",       /* 4: NOT USED */
  "",       /* 5: NOT USED */
  "",       /* 6: NOT USED */
  "",       /* 7: NOT USED */
  "",       /* 8: NOT USED */
  "",       /* 9: NOT USED */
  "",       /* 10: NOT USED */
  "",       /* 11: NOT USED */
  "",       /* 12: NOT USED */
  "",       /* 13: NOT USED */
  "",       /* 14: NOT USED */
  "",       /* 15: NOT USED */
  "",       /* 16: NOT USED */
  "",       /* 17: NOT USED */
  "",       /* 18: NOT USED */
  "",       /* 19: NOT USED */
  "",       /* 20: NOT USED */
  "",       /* 21: NOT USED */
  "",       /* 22: NOT USED */
  "",       /* 23: NOT USED */
  "",       /* 24: NOT USED */
  "",       /* 25: NOT USED */
  "",       /* 26: NOT USED */
  "",       /* 27: NOT USED */
  "",       /* 28: NOT USED */
  "",       /* 29: NOT USED */
  "",       /* 30: NOT USED */
  "",       /* 31: NOT USED */
  "",       /* 32: NOT USED */
  "-.-.--", /* 33: EXCLAMATION_MARK */
  ".-..-.", /* 34: DOUBLE_QUOTE */
  "",       /* 35: NOT USED */
  "...-..-",/* 36: DOLLAR_SIGN */
  "",       /* 37: NOT USED */
  ".-...",  /* 38: AMPERSAND */
  ".----.", /* 39: APOSTROPHE */
  "-.--.-", /* 40: OPEN_PAREN */
  "-.--.-", /* 41: CLOSE_PAREN */
  "",       /* 42: NOT USED */
  ".-.-.",  /* 43: PLUS */
  "--..--", /* 44: COMMA */
  "-....-", /* 45: MINUS */
  ".-.-.-", /* 46: PERIOD */
  "-..-.",  /* 47: SLASH */
  "-----",  /* 48: 0 */
  ".----",  /* 49: 1 */
  "..---",  /* 50: 2 */
  "...--",  /* 51: 3 */
  "....-",  /* 52: 4 */
  ".....",  /* 53: 5 */
  "-....",  /* 54: 6 */
  "--...",  /* 55: 7 */
  "---..",  /* 56: 8 */
  "----.",  /* 57: 9 */
  "---...", /* 58: COLON */
  "-.-.-.", /* 59: SEMI_COLON */
  "",       /* 60: NOT USED */
  "-...-",  /* 61: EQUALS */
  "",       /* 62: NOT USED */
  "..--..", /* 63: QUESTION_MARK */
  ".--.-.", /* 64: AT_SIGN */
  ".-",     /* 65: A */
  "-...",   /* 66: B */
  "-.-.",   /* 67: C */
  "-..",    /* 68: D */
  ".",      /* 69: E */
  "..-.",   /* 70: F */
  "--.",    /* 71: G */
  "....",   /* 72: H */
  "..",     /* 73: I */
  ".---",   /* 74: J */
  "-.-",    /* 75: K */
  ".-..",   /* 76: L */
  "--",     /* 77: M */
  "-.",     /* 78: N */
  "---",    /* 79: O */
  ".--.",   /* 80: P */
  "--.-",   /* 81: Q */
  ".-.",    /* 82: R */
  "...",    /* 83: S */
  "-",      /* 84: T */
  "..-",    /* 85: U */
  "...-",   /* 86: V */
  ".--",    /* 87: W */
  "-..-",   /* 88: X */
  "-.--",   /* 89: Y */
  "--..",   /* 90: Z */
  "",       /* 91: NOT USED */
  "",       /* 92: NOT USED */
  "",       /* 93: NOT USED */
  "",       /* 94: NOT USED */
  "..--.-", /* 95: UNDERSCORE */
  "",       /* 96: NOT USED */
  ".-",     /* 97: A */
  "-...",   /* 98: B */
  "-.-.",   /* 99: C */
  "-..",    /* 100: D */
  ".",      /* 101: E */
  "..-.",   /* 102: F */
  "--.",    /* 103: G */
  "....",   /* 104: H */
  "..",     /* 105: I */
  ".---",   /* 106: J */
  "-.-",    /* 107: K */
  ".-..",   /* 108: L */
  "--",     /* 109: M */
  "-.",     /* 110: N */
  "---",    /* 111: O */
  ".--.",   /* 112: P */
  "--.-",   /* 113: Q */
  ".-.",    /* 114: R */
  "...",    /* 115: S */
  "-",      /* 116: T */
  "..-",    /* 117: U */
  "...-",   /* 118: V */
  ".--",    /* 119: W */
  "-..-",   /* 120: X */
  "-.--",   /* 121: Y */
  "--..",   /* 122: Z */
  "",       /* 123: NOT USED */
  "",       /* 124: NOT USED */
  "",       /* 125: NOT USED */
  "",       /* 126: NOT USED */
  "",       /* 127: NOT USED */
  "",       /* 128: NOT USED */
  "",       /* 129: NOT USED */
  "",       /* 130: NOT USED */
  "",       /* 131: NOT USED */
  "",       /* 132: NOT USED */
  "",       /* 133: NOT USED */
  "",       /* 134: NOT USED */
  "",       /* 135: NOT USED */
  "",       /* 136: NOT USED */
  "",       /* 137: NOT USED */
  "",       /* 138: NOT USED */
  "",       /* 139: NOT USED */
  "",       /* 140: NOT USED */
  "",       /* 141: NOT USED */
  "",       /* 142: NOT USED */
  "",       /* 143: NOT USED */
  "",       /* 144: NOT USED */
  "",       /* 145: NOT USED */
  "",       /* 146: NOT USED */
  "",       /* 147: NOT USED */
  "",       /* 148: NOT USED */
  "",       /* 149: NOT USED */
  "",       /* 150: NOT USED */
  "",       /* 151: NOT USED */
  "",       /* 152: NOT USED */
  "",       /* 153: NOT USED */
  "",       /* 154: NOT USED */
  "",       /* 155: NOT USED */
  "",       /* 156: NOT USED */
  "",       /* 157: NOT USED */
  "",       /* 158: NOT USED */
  "",       /* 159: NOT USED */
  "",       /* 160: NOT USED */
  "",       /* 161: NOT USED */
  "",       /* 162: NOT USED */
  "",       /* 163: NOT USED */
  "",       /* 164: NOT USED */
  "",       /* 165: NOT USED */
  "",       /* 166: NOT USED */
  "",       /* 167: NOT USED */
  "",       /* 168: NOT USED */
  "",       /* 169: NOT USED */
  "",       /* 170: NOT USED */
  "",       /* 171: NOT USED */
  "",       /* 172: NOT USED */
  "",       /* 173: NOT USED */
  "",       /* 174: NOT USED */
  "",       /* 175: NOT USED */
  "",       /* 176: NOT USED */
  "",       /* 177: NOT USED */
  "",       /* 178: NOT USED */
  "",       /* 179: NOT USED */
  "",       /* 180: NOT USED */
  "",       /* 181: NOT USED */
  "",       /* 182: NOT USED */
  "",       /* 183: NOT USED */
  "",       /* 184: NOT USED */
  "",       /* 185: NOT USED */
  "",       /* 186: NOT USED */
  "",       /* 187: NOT USED */
  "",       /* 188: NOT USED */
  "",       /* 189: NOT USED */
  "",       /* 190: NOT USED */
  "",       /* 191: NOT USED */
  "",       /* 192: NOT USED */
  "",       /* 193: NOT USED */
  "",       /* 194: NOT USED */
  "",       /* 195: NOT USED */
  "",       /* 196: NOT USED */
  "",       /* 197: NOT USED */
  "",       /* 198: NOT USED */
  "",       /* 199: NOT USED */
  "",       /* 200: NOT USED */
  "",       /* 201: NOT USED */
  "",       /* 202: NOT USED */
  "",       /* 203: NOT USED */
  "",       /* 204: NOT USED */
  "",       /* 205: NOT USED */
  "",       /* 206: NOT USED */
  "",       /* 207: NOT USED */
  "",       /* 208: NOT USED */
  "",       /* 209: NOT USED */
  "",       /* 210: NOT USED */
  "",       /* 211: NOT USED */
  "",       /* 212: NOT USED */
  "",       /* 213: NOT USED */
  "",       /* 214: NOT USED */
  "",       /* 215: NOT USED */
  "",       /* 216: NOT USED */
  "",       /* 217: NOT USED */
  "",       /* 218: NOT USED */
  "",       /* 219: NOT USED */
  "",       /* 220: NOT USED */
  "",       /* 221: NOT USED */
  "",       /* 222: NOT USED */
  "",       /* 223: NOT USED */
  "",       /* 224: NOT USED */
  "",       /* 225: NOT USED */
  "",       /* 226: NOT USED */
  "",       /* 227: NOT USED */
  "",       /* 228: NOT USED */
  "",       /* 229: NOT USED */
  "",       /* 230: NOT USED */
  "",       /* 231: NOT USED */
  "",       /* 232: NOT USED */
  "",       /* 233: NOT USED */
  "",       /* 234: NOT USED */
  "",       /* 235: NOT USED */
  "",       /* 236: NOT USED */
  "",       /* 237: NOT USED */
  "",       /* 238: NOT USED */
  "",       /* 239: NOT USED */
  "",       /* 240: NOT USED */
  "",       /* 241: NOT USED */
  "",       /* 242: NOT USED */
  "",       /* 243: NOT USED */
  "",       /* 244: NOT USED */
  "",       /* 245: NOT USED */
  "",       /* 246: NOT USED */
  "",       /* 247: NOT USED */
  "",       /* 248: NOT USED */
  "",       /* 249: NOT USED */
  "",       /* 250: NOT USED */
  "",       /* 251: NOT USED */
  "",       /* 252: NOT USED */
  "",       /* 253: NOT USED */
  "",       /* 254: NOT USED */
  "",       /* 255: NOT USED */
};

char morse_code_is_char(char asc_char)
{
  return (asc_char >= 0 && asc_char <= MORSE_CHAR_MAX &&
      MORSE_CODES[(unsigned int) asc_char][0] != '\0');
}

const char *morse_code_from_asc(char asc_char)
{
  if (!morse_code_is_char(asc_char))
    return NULL;
  else
    return (const char *) MORSE_CODES[(unsigned int) asc_char];
}

