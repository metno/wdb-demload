ACLOCAL_AMFLAGS = -I config

bin_PROGRAMS = demLoad

include src/demLoad.mk
include doc/demLoad.mk

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(wdb_CFLAGS)
demLoad_LDADD = $(wdb_LIBS) 

include config/debian.mk

