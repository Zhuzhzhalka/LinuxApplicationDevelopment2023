COMMON_GENERATES = src/*.o src/num_guesser
AUTOTOOLS_GENERATES = configure configure~ Makefile autom4te.cache Makefile.in aclocal.m4 config.h* config.log config.status install-sh missing stamp-h1 .deps depcomp compile autoscan.log test config.guess config.rpath config.sub m4 po/en@* po/ru@* po/insert-header.sin po/Make* po/POTFILES po/quot.sed po/stamp-it po/ru.gmo po/Rules-quot src/Makefile src/Makefile.in po/remove-potcdate.sin po/boldquot.sed ABOUT-NLS src/.deps doxygen-doc Doxyfile

SUBDIRS = src po

# нещадно взято с https://git.sr.ht/~frbrgeorge/namegen/tree/master/item/Makefile.am
@DX_RULES@

doxygen-doc/man/man1/num_guesser.1: doxygen-doc

man1_MANS = doxygen-doc/man/man1/num_guesser.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http:	doxygen-doc
	python3 -m http.server --directory $</html

clean:
	rm -rf $(AUTOTOOLS_GENERATES) $(COMMON_GENERATES)
