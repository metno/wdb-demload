ACLOCAL_AMFLAGS = -I config

wdblibdir = $(libdir)/wdb

wdblib_PROGRAMS = demLoad

include src/demLoad.mk
include doc/demLoad.mk

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(wdb_CFLAGS)
demLoad_LDADD = $(wdb_LIBS) 

include config/debian.mk

