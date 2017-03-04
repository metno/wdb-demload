#-----------------------------------------------------------------------------
# Project Makefile for wdb's demLoad
#
# This file is processed by automake to generate the non-recursive
# project Makefile
#-----------------------------------------------------------------------------

# Scanned by Autoreconf; must be static (no expansion)
ACLOCAL_AMFLAGS = -I config/m4
				
# Share directory organization
wdblibdir =				$(libdir)/wdb

# Setting Targets
wdblib_PROGRAMS = demLoad

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(wdb_CFLAGS) $(BOOST_CPPFLAGS) $(AM_CPPFLAGS)
demLoad_LDADD=\
	$(wdb_LIBS) -llog4cpp -lboost_date_time -lboost_filesystem \
        -lboost_program_options -lboost_system -lwdbLoad \
        -lwdbConfig -lwdbProj -lwdbExcept -lwdbLog -lwdbMath -lproj

EXTRA_DIST =
CLEANFILES =

include src/demLoad.mk
include doc/demLoad.mk

# Debian
include config/mk/debian.mk

debian: common-debian
