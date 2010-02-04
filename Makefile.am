ACLOCAL_AMFLAGS = -I m4

wdblibdir = $(libdir)/wdb

wdblib_PROGRAMS = demLoad

include src/demLoad.mk
include doc/demLoad.mk

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(AM_CPPFLAGS)

foo:
	 @echo DO_CREATE_USER = $(DO_CREATE_USER)

install-data-hook:
	if [ $(DO_CREATE_USER) = true ]; then \
		$(WDB_ADMINISTRATION) createuser demload write; \
	fi
	
uninstall-hook:
	if [ $(DO_CREATE_USER) = true ]; then \
		$(WDB_ADMINISTRATION) dropuser demload; \
	fi

admin:
	@echo WDB_ADMINISTRATION = $(WDB_ADMINISTRATION)
	@echo wdb_CONFIG = $(wdb_CONFIG)

include mk/debian.mk

