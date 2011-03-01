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
CLEANFILES =

include src/demLoad.mk
include doc/demLoad.mk

# Debian
include mk/debian.mk

debian: common-debian
