AC_PREREQ([2.61])
AC_INIT([morse], [0.01], [mbrush@codebrainz.ca])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([src/config.h])
AM_INIT_AUTOMAKE([1.11.1 -Wall -Werror foreign])
AM_SILENT_RULES([yes])
LT_INIT

AC_PROG_CC

AC_ARG_WITH([portaudio], AS_HELP_STRING([--with-portaudio], [Use the PortAudio backend]))

if test "$with_portaudio" = "yes"
then
  PKG_CHECK_MODULES([PA], [portaudio-2.0])
  AC_DEFINE(BEEP_BACKEND_PORTAUDIO, 1, [Use the PortAudio backend])
else
  PKG_CHECK_MODULES([AO], [ao])
  AC_DEFINE(BEEP_BACKEND_LIBAO, 1, [Use the LibAO backend])
fi

AM_CONDITIONAL(USE_PORTAUDIO, [test "x$with_portaudio" = "xyes"])

AC_PATH_PROG([PYTHON], [python], [no])
AC_SUBST([PYTHON])
if [[ x"$PYTHON" = "xno" ]]; then
  AC_MSG_ERROR([Python was not found, you need Python.])
fi

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT
