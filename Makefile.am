ACLOCAL_AMFLAGS = -I config

wdblibdir = $(libdir)/wdb

wdblib_PROGRAMS = demLoad

include src/demLoad.mk
include doc/demLoad.mk

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(wdb_CFLAGS)
demLoad_LDADD = $(wdb_LIBS) 

install-data-hook:
	$(WDB_ADMINISTRATION) createuser demload write
	
uninstall-hook:
	$(WDB_ADMINISTRATION) dropuser demload

admin:
	@echo WDB_ADMINISTRATION = $(WDB_ADMINISTRATION)
	@echo wdb_CONFIG = $(wdb_CONFIG)

include config/debian.mk

