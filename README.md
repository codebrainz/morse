Morse
=====

Morse is a very basic and probably inaccurate text to Morse code converter.
It takes ASCII text read from standard input and plays the Morse codes
audibly (as well as printing each character as it's played).

### Disclaimer

I'm not a Morse code enthusiast or expert and this program just works
according to some information I read on Wikipedia. If you find a problem or
bug with the software let me know and I'll fix it.

Dependencies
------------

There's a choice of two audio backends and at least one is required:

* libao - http://xiph.org/ao (default)
* PortAudio - http://www.portaudio.com

Also, in order to generate the Morse code/character table in `morse.c`,
Python 2.6 or greater is required. Normally you will not need Python unless
you update the `morse.json` file and want to re-generate the `morse.c` file.

Installation
------------

The usual:

    $ ./configure
    $ make
    $ make install

### Interesting Configuration Options

The `--with-portaudio` argument to `./configure` enables the PortAudio
backend and disables the libao backend. The default is to use libao.

### Regenerating the morse.c file

The `morse.c` file is generated using the `gencodes.py` Python script in
the `src` directory. It reads the data in `morse.json` and generates some C
code which is put into the contents of `morse.c.in` by replacing a special
token and the replaced contents are written to `morse.c`.

If you want to regerenate `morse.c`, do the following:

    $ cd src
    $ python gencodes.py -t morse.c.in -j morse.json > morse.c

And then perform a rebuild/re-install according to the instructions above.

Usage
-----

The most basic usage is:

    $ echo "foo" | morse

Alternatively, you can run it in interactive mode:

    $ morse
    Whatever you type will get played as morse code when you hit enter.
    What
        ^ What's playing get's echoed back as it's playing

### Options

There are only two options. `-f` specifies the frequency of the tones in
Hertz (default is 1000). `-d` specifies the duration of one unit (ie. one
dot length) in seconds. The duration of all tones is based on this value
(default is 0.1 seconds).

There's also a not very helpful `-h` option that will just print a usage
message.

Using the Library
-----------------

The best example to see how to use the library is the `main.c` file. Here's
a little (untested) snippet that shows how to use some parts of the library:

```c
#include <morse/keyer.h>

int main(int argc, char *argv[])
{
  Keyer *k;
  const char *TEST_STRING = "Hello World";

  /* Allocates a new keyer and implicitely calls `keyer_init()` if
   * it hasn't been called yet. */
  k = keyer_new();

  if (k) {
    keyer_set_freq(k, 2000.0 /* Hz */);
    keyer_set_unit_duration(k, 0.08 /* Seconds */);
    keyer_key_string(k, TEST_STRING);
    keyer_free(k);
  }

  /* Optionally clean up some allocated resources, otherwise the OS
   * will clean it up when the program exits. */
  keyer_shutdown();

  return 0;
}
```

If you just want to use the "beep" code:

```c
#include <morse/beep.h>

int main(int argc, char *argv[])
{

  beep(440.0, 2.0); /* Play a 440 Hz sine wave for 2 seconds. */
  beep(1000.0, 0.5); /* Play a 1000 Hz sine wave for 0.5 seconds. */

  /* Optional, use to free resources instead of letting the OS clean
   * it up when the program exits */
  beep_shutdown();
}
```

To get the Morse code as a string of encoded `-` and `.` characters, use:

```c
#include <morse/morse.h>

int main(int argc, char *argv[])
{
  char test_char = 'a';
  const char *morse_code = morse_code_from_asc(test_char);

  printf("The character '%c' encoded into a Morse string is: %s\n",
    test_char, morse_code);

  /* To test to see if a char is a supported Morse character */
  if (morse_code_is_char('<')) {
    printf("The Morse code for '<' is: %s\n", morse_code_from_asc('<'));
  }
}
```

None of the functions in the library claim to be thread-safe.

Credits and License
-------------------

This program is written and maintained by:

    Matthew Brush <mbrush@codebrainz.ca>

It is license under the MIT license, see COPYING file for more information.
