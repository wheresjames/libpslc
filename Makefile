
OUT := ../bin

#-------------------------------------------------------------------
# Libs
#-------------------------------------------------------------------
BUILDDIRS := $(BUILDDIRS) \
			 src

#-------------------------------------------------------------------
# Apps
#-------------------------------------------------------------------
BUILDDIRS := $(BUILDDIRS) \
			 app/test

#-------------------------------------------------------------------
# doxygen
#-------------------------------------------------------------------
ifdef DOX
BUILDDIRS := $(BUILDDIRS) dox
endif

#-------------------------------------------------------------------
# multithreading
#-------------------------------------------------------------------
ifeq ($(NOMULTI),)
ifeq ($(NUMJOBS),)
ifdef NUMBER_OF_PROCESSORS
NUMJOBS := -j$(NUMBER_OF_PROCESSORS)
else
NUMJOBS := -j2
endif
endif
endif

ASPACE:=
ASPACE+=

.PHONY all: $(BUILDDIRS)

.PHONY rebuild: $(BUILDDIRS)

.PHONY $(BUILDDIRS) :
	$(MAKE) $(NUMJOBS) -C $@ $(BUILDTYPE) OUT=$(OUT) REL=$(subst $(ASPACE),/,$(foreach p,$(subst /, ,$@),..))
