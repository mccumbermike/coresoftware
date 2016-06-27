AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = \
  libPHGenEvent.la 

INCLUDES = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include \
  -I`root-config --incdir` 

AM_CXXFLAGS = -Wall -Werror

libPHGenEvent_la_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib \
  `root-config --libs`

libPHGenEvent_la_LIBADD = \
  -lgsl \
  -lgslcblas \
  -lHepMC \
  -lphool \
  -lfun4all

pkginclude_HEADERS = \
  PHEventGenMethod.h \
  PHEventGenTrigger.h \
  PHEventGenBase.h \
  PHGenEvent.h \
  PHGenEvent_v1.h \
  PHGenParticle.h \
  PHGenVertex.h \
  PHGenEventMap.h \
  PHGenEventMap_v1.h

libPHGenEvent_la_SOURCES = \
  PHEventGenMethod.C \
  PHEventGenMethod_Dict.C \
  PHEventGenTrigger.C \
  PHEventGenTrigger_Dict.C \
  PHEventGenBase.C \
  PHEventGenBase_Dict.C \
  PHGenEvent.C \
  PHGenEvent_Dict.C \
  PHGenEvent_v1.C \
  PHGenEvent_v1_Dict.C \
  PHGenParticle.C \
  PHGenParticle_Dict.C \
  PHGenVertex.C \
  PHGenVertex_Dict.C \
  PHGenEventMap.C \
  PHGenEventMap_Dict.C \
  PHGenEventMap_v1.C \
  PHGenEventMap_v1_Dict.C

PHGenEvent_Dict.C: $(OFFLINE_MAIN)/include/HepMC/*.h \
  PHGenEvent.h PHGenEventLinkDef.h
	rootcint -f $@ -c $(DEFAULT_INCLUDES) $(INCLUDES) $^

%_Dict.C: %.h %LinkDef.h
	rootcint -f $@ -c $(DEFAULT_INCLUDES) $(INCLUDES) $^

%_Dict.cpp: %.h %LinkDef.h
	rootcint -f $@ -c $(DEFAULT_INCLUDES) $(INCLUDES) $^

################################################
# linking tests

noinst_PROGRAMS = testexternals

BUILT_SOURCES = \
  testexternals.C

testexternals_LDADD = \
  libPHGenEvent.la

testexternals.C:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

clean-local:
	rm -f *Dict*
