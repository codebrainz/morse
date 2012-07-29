bin_PROGRAMS = morse

morse_SOURCES = main.c morse.c morse.h keyer.c keyer.h beep-ao.c beep-pa.c beep.h
morse_CPPFLAGS = $(PA_CFLAGS) $(AO_CFLAGS)
morse_LDADD = $(PA_LIBS) $(AO_LIBS) -lm

morse.c: $(top_srcdir)/src/morse.c.in $(top_srcdir)/src/morse.json
	$(AM_V_GEN)$(PYTHON) gencodes.py -t $< \
		-j $(top_srcdir)/src/morse.json > $@

CLEANFILES = morse.c
EXTRA_DIST = morse.c.in morse.json gencodes.py
