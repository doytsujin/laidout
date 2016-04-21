###############################################
##############                  ###############
#############  Laidout Makefile  ##############
##############                  ###############
###############################################

 # Makefile-toinclude, generated by configure, 
 # defines LAXDIR, PREFIX, and LAIDOUTVERSION
include Makefile-toinclude


 # where the main executable goes
BINDIR=$(PREFIX)/bin
 # like /usr/local/share/, examples go here: $SHAREDIR/laidout
SHAREDIR=$(PREFIX)/share


 ### If you want to be sure that an install does not clobber anything that exists
 ### already, then uncomment the line with the '--backup=t' and comment out the other.
#INSTALL=install -D --backup=t 
INSTALL=install -D

INSTALLDIR=install -d


LAIDOUTNAME=laidout-$(LAIDOUTVERSION)

laidout: 
	cd src && $(MAKE)
	cd src/po && $(MAKE)

all: laidout docs

icons:
	cd src/icons && make

docs:
	cd docs && doxygen
	
alldocs:
	cd docs && doxygen Doxyfile-with-laxkit

quickref:
	src/laidout -H > QUICKREF.html

install: 
	echo 'Installing to $(BINDIR)/laidout which points to $(BINDIR)/$(LAIDOUTNAME)'
	$(INSTALL) -m755 src/laidout $(BINDIR)/$(LAIDOUTNAME)
	$(INSTALLDIR) $(SHAREDIR)/laidout/$(LAIDOUTVERSION)/examples
	$(INSTALL) -m644 -t $(SHAREDIR)/laidout/$(LAIDOUTVERSION)/examples examples/*
	$(INSTALLDIR) $(SHAREDIR)/laidout/$(LAIDOUTVERSION)/icons
	$(INSTALL) -m644 -t $(SHAREDIR)/laidout/$(LAIDOUTVERSION)/icons src/icons/*.png
	$(INSTALLDIR) $(SHAREDIR)/applications
	$(INSTALL) -m644 debian/laidout.desktop $(SHAREDIR)/applications
	$(INSTALLDIR) $(SHAREDIR)/icons/hicolor/48x48/apps
	$(INSTALL) -m644 src/icons/laidout-48x48.png $(SHAREDIR)/icons/hicolor/48x48/apps/laidout.png
	$(INSTALLDIR) $(SHAREDIR)/icons/hicolor/scalable/apps
	$(INSTALL) -m644 src/icons/laidout.svg $(SHAREDIR)/icons/hicolor/scalable/apps/laidout.svg
	$(INSTALLDIR)       $(SHAREDIR)/laidout/$(LAIDOUTVERSION)/coop/processing
	$(INSTALL) -m644 -t $(SHAREDIR)/laidout/$(LAIDOUTVERSION)/coop/processing coop/processing/*
	$(INSTALLDIR)       $(SHAREDIR)/laidout/$(LAIDOUTVERSION)/coop/scribus
	$(INSTALL) -m644 -t $(SHAREDIR)/laidout/$(LAIDOUTVERSION)/coop/scribus coop/scribus/*

	rm -f $(BINDIR)/laidout
	ln -s $(LAIDOUTNAME) $(BINDIR)/laidout
	cd src/po && $(MAKE) install

# ****** TODO!!! this is very primitive make uninstall!!
# should only uninstall things that were actually installed. Any resource added by
# the user to the system wide directories should not be uninstalled. Should use
# config log perhaps. The $(BINDIR)/laidout should be removed only if it points to
# $(BINDIR)/$(LAIDOUTNAME)
uninstall: 
	echo 'Uninstalling laidout.'
	echo '  Removing $(BINDIR)/laidout'
	rm -f  $(BINDIR)/laidout
	echo '  Removing $(SHAREDIR)/laidout/$(LAIDOUTVERSION)'
	rm -fr $(SHAREDIR)/laidout/$(LAIDOUTVERSION)
	echo '  Removing $(BINDIR)/$(LAIDOUTNAME)'
	rm -f  $(BINDIR)/$(LAIDOUTNAME)
	cd src/po && $(MAKE) uninstall

#link debian to debian-lo if not there.. Debian guidelines say don't put 
#a "debian" directory in upstream sources by default.
deb:
	if [ ! -e debian ] ; then ln -s debian-lo debian; fi
	dpkg-buildpackage -rfakeroot

hidegarbage: touchdepends
	cd src && $(MAKE) hidegarbage

unhidegarbage: touchdepends
	cd src && $(MAKE) unhidegarbage

depends: touchdepends
	cd src && $(MAKE) depends

touchdepends:
	touch src/makedepend
	touch src/calculator/makedepend
	touch src/dataobjects/makedepend
	touch src/filetypes/makedepend
	touch src/impositions/makedepend
	touch src/interfaces/makedepend
	touch src/printing/makedepend
	touch src/api/makedepend
	touch src/polyptych/src/makedepend

.PHONY: all icons laidout clean docs install uninstall hidegarbage unhidegarbage depends touchdepends
clean:
	cd src && $(MAKE) clean
	
