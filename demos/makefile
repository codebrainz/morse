#
# Run this after installing, good for testing installation.
#
# Don't forget to set the variables LD_LIBRARY_PATH, CFLAGS and LDFLAGS
# as needed. For example if the Morse library is installed into `/opt/morse`,
# the run make like this:
#  $ CFLAGS="-I/opt/morse/include" \
#      LDFLAGS="-L/opt/morse/lib" \
#      LD_LIBRARY_PATH="/opt/morse/lib" make
#

beep: beep.c
	cc $(CFLAGS) -Wall -Werror -o $@ $^ $(LDFLAGS) -lmorse

clean:
	rm -f beep
