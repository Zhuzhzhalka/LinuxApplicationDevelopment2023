AM_CFLAGS = -std=c99 -Wall -Wextra
COMMON_GENERATES = *.o rhasher
AUTOTOOLS_GENERATES = configure configure~ Makefile autom4te.cache Makefile.in aclocal.m4 config.h* config.log config.status install-sh missing stamp-h1 .deps depcomp compile autoscan.log test

bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c

test:
	chmod +x test.sh
	bash test.sh

clean:
	rm -rf $(AUTOTOOLS_GENERATES) $(COMMON_GENERATES)

