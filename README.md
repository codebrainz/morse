Morse
=====

Morse is a very basic and probably inaccurate text to Morse code converter.
It takes ASCII text read from standard input and playes the Morse codes
audibly (as well as printing each character played as it's played).

### Disclaimer

I'm not a Morse code enthusiast or expert and this program just works
according to some information I read on Wikipedia. If you find a problem or
bug with the software let me know and I'll fix it.

Dependencies
------------

There's a choice of two audio backends and at least one is required:

* libao - http://xiph.org/ao (default)
* PortAudio - http://www.portaudio.com

Installation
------------

The usual:

    $ ./configure
    $ make
    $ make install

### Interesting Configuration Options

The `--with-portaudio` argument to `./configure` enables the PortAudio
backend and disables the libao backend. The default is to use libao.

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

Credits and License
-------------------

This program is written and maintained by:

    Matthew Brush <mbrush@codebrainz.ca>

It is license under the MIT license, see COPYING file for more information.
