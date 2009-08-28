ACLOCAL_AMFLAGS = -I config

bin_PROGRAMS = demLoad

include src/demLoad.mk
include doc/demLoad.mk

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(libwdbLoad_CFLAGS)
demLoad_LDADD = $(libwdbLoad_LIBS) -lwdbLog

include config/debian.mk

