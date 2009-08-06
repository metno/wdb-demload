bin_PROGRAMS = demLoad

include src/demLoad.mk

demLoad_CPPFLAGS = -I$(top_srcdir)/src $(libwdbLoad_CFLAGS)
demLoad_LDADD = $(libwdbLoad_LIBS) -lwdbLog
