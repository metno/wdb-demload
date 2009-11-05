ACLOCAL_AMFLAGS = -I m4

wdblibdir = $(libdir)/wdb

wdblib_PROGRAMS = demLoad

include src/demLoad.mk
include doc/demLoad.mk

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(AM_CPPFLAGS)

install-data-hook:
	$(WDB_ADMINISTRATION) createuser demload write
	
uninstall-hook:
	$(WDB_ADMINISTRATION) dropuser demload

admin:
	@echo WDB_ADMINISTRATION = $(WDB_ADMINISTRATION)
	@echo wdb_CONFIG = $(wdb_CONFIG)

include mk/debian.mk

