
default_target: all
_END_ := 1

#-------------------------------------------------------------------
# Configure
#-------------------------------------------------------------------

OUTNAME := pslc
OUTTYPE := lib

PRJ_INC := inc
PRJ_LIB := pslc

#-------------------------------------------------------------------
# System
#-------------------------------------------------------------------

ifneq ($(findstring debug,$(TGT)),)
	CFG_DBG := 1
endif
		   
ifneq ($(findstring windows,$(TGT)),)
	CFG_WIN := 1
	CFG_SYSTEM := windows
else
	CFG_SYSTEM := posix
endif

ifneq ($(findstring static,$(TGT)),)
	CFG_STATIC := 1
endif

ifdef CFG_WIN
	PR := i586-mingw32msvc-
endif

#-------------------------------------------------------------------
# Input / Output
#-------------------------------------------------------------------

# Create bin output path
ifneq ($(OUT),)
	ifneq ($(REL),)
		BINPATH := $(REL)/$(OUT)/$(CFG_SYSTEM)
		LIBPATH := $(REL)/
	else
		BINPATH := $(OUT)/$(CFG_SYSTEM)
	endif
else
	BINPATH := ../bin/$(CFG_SYSTEM)
endif

ifdef CFG_STATIC
	BINPATH := $(BINPATH)-static
else
	BINPATH := $(BINPATH)-shared
endif

ifdef CFG_DBG
	BINPATH := $(BINPATH)-debug
endif

# Create intermediate file output path
OBJPATH := $(BINPATH)/_obj/$(OUTNAME)

# Output file
ifdef CFG_WIN
	CFG_OBJ_POST := .obj
	ifeq ($(OUTTYPE),lib)
		OUTFILE := $(BINPATH)/$(OUTNAME).lib
	else
		ifeq ($(OUTTYPE),dll)
			OUTFILE := $(BINPATH)/$(OUTNAME).dll
		else
			OUTFILE := $(BINPATH)/$(OUTNAME).exe
		endif
	endif
else
	CFG_OBJ_POST := .o
	ifeq ($(OUTTYPE),lib)
		OUTFILE := $(BINPATH)/lib$(OUTNAME).a
	else
		ifeq ($(OUTTYPE),dll)
			OUTFILE := $(BINPATH)/$(OUTNAME).so
		else
			OUTFILE := $(BINPATH)/$(OUTNAME)
		endif
	endif
endif

# Input files
CCFILES := $(wildcard *.c)
PPFILES := $(wildcard *.cpp)

# Object files
DEPENDS := $(foreach f,$(CCFILES),$(OBJPATH)/c/$(f:.c=$(CFG_OBJ_POST))) \
		   $(foreach f,$(PPFILES),$(OBJPATH)/cpp/$(f:.cpp=$(CFG_OBJ_POST)))

#-------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------

# Paths tools
RM := rm -f
MD := mkdir -p

# GCC
PP := $(PR)g++ -c
CC := $(PR)gcc -c
LD := $(PR)g++
AR := $(PR)ar -cq
RC := $(PR)windres

PP_FLAGS :=
CC_FLAGS :=
LD_FLAGS :=

ifdef CFG_STATIC
	PP_FLAGS := $(PP_FLAGS) -static
	CC_FLAGS := $(CC_FLAGS) -static
else
	PP_FLAGS := $(PP_FLAGS) -shared
	CC_FLAGS := $(CC_FLAGS) -shared
endif

ifeq ($(OUTTYPE),dll)
	LD_FLAGS := $(LD_FLAGS) -shared -module
else
	ifdef CFG_STATIC
	LD_FLAGS := $(LD_FLAGS) -static
	endif
endif

ifndef CFG_WIN
	PP_FLAGS := $(PP_FLAGS) -fPIC
	CC_FLAGS := $(CC_FLAGS) -fPIC
	LD_FLAGS := $(LD_FLAGS) -fPIC
endif

ifdef CFG_DBG
	PP_FLAGS := $(PP_FLAGS) -g -DDEBUG -D_DEBUG
	CC_FLAGS := $(CC_FLAGS) -g -DDEBUG -D_DEBUG
	LD_FLAGS := $(LD_FLAGS) -g
else
	PP_FLAGS := $(PP_FLAGS) -O2
	CC_FLAGS := $(CC_FLAGS) -O2
endif

#-------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------

DEFS := $(foreach p,$(PRJ_DEF),-D$(p))
INCS := $(foreach p,$(PRJ_INC),-I$(LIBPATH)$(p))
LIBS := -L$(BINPATH) $(foreach p,$(PRJ_LIB),-l$(p))

#-------------------------------------------------------------------
# Build
#-------------------------------------------------------------------

# Create 'c++' object file path
$(OBJPATH)/cpp :
	- $(MD) $@

# Create 'c' object file path
$(OBJPATH)/c :
	- $(MD) $@

# How to build a 'c++' file
$(OBJPATH)/cpp/%$(CFG_OBJ_POST) : %.cpp $(OBJPATH)/cpp
	$(PP) $< $(PP_FLAGS) $(DEFS) $(INCS) -o $@

# How to build a 'c' file
$(OBJPATH)/c/%$(CFG_OBJ_POST) : %.c $(OBJPATH)/c
	$(CC) $< $(CC_FLAGS) $(DEFS) $(INCS) -o $@

ifeq ($(OUTTYPE),lib)

# Build the output
$(OUTFILE) : $(DEPENDS)
	- $(RM) $@
	$(AR) "$@" $(AR_FLAGS) $(DEPENDS) 

else

# Build the output
$(OUTFILE) : $(DEPENDS)
	- $(RM) $@
	$(LD) $(LD_FLAGS) $(LIBS) $(DEPENDS) -o "$@"

endif

# Default target
all : $(OUTFILE)

clean :
	- $(RM) -R $(OBJPATH)

rebuild : clean all
