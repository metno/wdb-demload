man_MANS = demLoad.1

demLoad.1:	doc/demLoad.man.xml
	$(DOCBOOK) man $<
	
EXTRA_DIST = doc/demLoad.man.xml
CLEANFILES = demLoad.1

