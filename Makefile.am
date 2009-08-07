bin_PROGRAMS = demLoad

include src/demLoad.mk

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(libwdbLoad_CFLAGS)
demLoad_LDADD = $(libwdbLoad_LIBS) -lwdbLog

###
# Debian package related stuff
###

PKG_DIR = $(PACKAGE)-$(VERSION)
DEBIAN_DIR = $(PKG_DIR)/debian
DEBIAN_PACKAGE = $(PACKAGE)_$(VERSION)
ARCH = `dpkg-architecture -qDEB_HOST_ARCH_CPU`
DEBIAN_PACKAGE_NAME= `head -n1 $(top_srcdir)/debian_files/changelog | sed "s/ (/_/" | sed "s/).*//"`_$(ARCH).deb

debian:	dist clean-debian 
	tar xvzf $(PKG_DIR).tar.gz
	mkdir -p $(DEBIAN_DIR)
	rm -rf $(DEBIAN_DIR)/*
	cp -r $(top_srcdir)/debian_files/* $(DEBIAN_DIR)
	chmod 744 $(DEBIAN_DIR)/rules
	cp $(PKG_DIR).tar.gz $(DEBIAN_PACKAGE).orig.tar.gz
	cd $(PKG_DIR) && dpkg-buildpackage -rfakeroot -us -uc
	lintian $(DEBIAN_PACKAGE_NAME)

update-debian:
	rm -rf $(DEBIAN_DIR)/*
	cp -r $(top_srcdir)/debian_files/* $(DEBIAN_DIR)
	chmod 744 $(DEBIAN_DIR)/rules
	cd $(PKG_DIR) && dpkg-buildpackage -rfakeroot -us -uc -nc
	lintian $(DEBIAN_PACKAGE_NAME)


clean-debian:
	debclean
	rm -rf $(PKG_DIR) $(DEBIAN_PACKAGE)*

