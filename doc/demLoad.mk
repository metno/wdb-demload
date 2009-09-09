man_MANS = demLoad.1

demLoad.1:	doc/demLoad.man.xml doc/docbook/wdb_entities.ent
	$(DOCBOOK) man $<
	
EXTRA_DIST = doc/demLoad.man.xml
CLEANFILES = demLoad.1

