#-----------------------------------------------------------------------------
# Project Makefile for wdb's demLoad
#
# This file is processed by automake to generate the non-recursive
# project Makefile
#-----------------------------------------------------------------------------

# Scanned by Autoreconf; must be static (no expansion)
ACLOCAL_AMFLAGS = -I m4
				
# Share directory organization
wdblibdir =				$(libdir)/wdb

# Setting Targets
wdblib_PROGRAMS = demLoad

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(AM_CPPFLAGS)
	
EXTRA_DIST =

include src/demLoad.mk
include doc/demLoad.mk

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

# Debian

include mk/debian.mk

debian: common-debian
