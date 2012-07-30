lib_LTLIBRARIES = libmorse.la

libmorse_la_SOURCES = morse.c keyer.c beep-ao.c beep-pa.c
libmorse_la_CPPFLAGS = $(PA_CFLAGS) $(AO_CFLAGS)
libmorse_la_LIBADD = $(PA_LIBS) $(AO_LIBS) -lm

morseincludedir = $(includedir)/morse
morseinclude_HEADERS = morse.h keyer.h beep.h

bin_PROGRAMS = morse

morse_SOURCES = main.c
morse_LDADD = $(top_builddir)/src/libmorse.la

EXTRA_DIST = morse.c.in morse.json gencodes.py
