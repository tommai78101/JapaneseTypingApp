#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITPRO)/libnx/switch_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
# EXEFS_SRC is the optional input directory containing data copied into exefs, if anything this normally should only contain "main.npdm".
#
# NO_ICON: if set to anything, do not use icon.
# NO_NACP: if set to anything, no .nacp file is generated.
# APP_TITLE is the name of the app stored in the .nacp file (Optional)
# APP_AUTHOR is the author of the app stored in the .nacp file (Optional)
# APP_VERSION is the version of the app stored in the .nacp file (Optional)
# APP_TITLEID is the titleID of the app stored in the .nacp file (Optional)
# ICON is the filename of the icon (.jpg), relative to the project folder.
#   If not set, it attempts to use one of the following (in this order):
#     - <Project name>.jpg
#     - icon.jpg
#     - <libnx folder>/default_icon.jpg
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	source  \
				source/game
DATA		:=	data/font \
				data/dict
INCLUDES	:=	include
EXEFS_SRC	:=	exefs_src

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	-march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIE

CFLAGS		:=	-g -Wall -O2 -ffunction-sections $(ARCH) `sdl2-config --cflags` `freetype-config --cflags` $(DEFINES)

CFLAGS		+=	$(INCLUDE) -D__SWITCH__

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++14

ASFLAGS		:=	-g $(ARCH)
LDFLAGS		=	-g $(ARCH) -Wl,-Map,$(notdir $*.map)

#---------------------------------------------------------------------------------
# Backticks are used to write a literal subshell command for execution.
# The subshell command to add additional libraries from dkp-pacman packages is to 
# add
#     `XXX-config --libs`
# where XXX refers to the library's name.
# 
# Do not include "-lnx" whenever you call on the dkp-pacman packages. There is no 
# need.
# 
# sdl-config	:= SDL 1.2.15
# sdl2-config	:= SDL 2.0.8
# 
# Some libraries must use the -L flag (lowercase L)
# While other libraries may require using `XXX-config --libs`.
# Check and see if this is the case or not.
#
# If you noticed make errors out with the message, "XXX-config: not found", update
# libnx, by:
#     1. git clone https://github.com/switchbrew/libnx
#     2. cd libnx
#     3. make && make install
#
# Whenever freetype is used, it must have the dependency libraries on the right,
# like so:
#     `freetype-config --libs` -lpng -lz -lbz2
# Or, install pkg-config:
#     sudo apt-get install pkg-config
# As freetype-config piggybacks on pkg-config.
#---------------------------------------------------------------------------------
LIBS		:= -lSDL2_ttf `sdl2-config --libs` -L/mnt/c/devkitPro/portlibs/switch/lib -L/mnt/c/devkitPro/libnx/lib -L/mnt/c/devkitPro/portlibs/switch/lib -lfreetype -lbz2 -lpng16 -lz -lm -lnx -lz

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS		:= $(PORTLIBS) $(LIBNX)


#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	\
	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
	$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
			$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

export BUILD_EXEFS_SRC := $(TOPDIR)/$(EXEFS_SRC)

ifeq ($(strip $(ICON)),)
	icons := $(wildcard *.jpg)
	ifneq (,$(findstring $(TARGET).jpg,$(icons)))
		export APP_ICON := $(TOPDIR)/$(TARGET).jpg
	else
		ifneq (,$(findstring icon.jpg,$(icons)))
			export APP_ICON := $(TOPDIR)/icon.jpg
		endif
	endif
else
	export APP_ICON := $(TOPDIR)/$(ICON)
endif

ifeq ($(strip $(NO_ICON)),)
	export NROFLAGS += --icon=$(APP_ICON)
endif

ifeq ($(strip $(NO_NACP)),)
	export NROFLAGS += --nacp=$(CURDIR)/$(TARGET).nacp
endif

ifneq ($(APP_TITLEID),)
	export NACPFLAGS += --titleid=$(APP_TITLEID)
endif

.PHONY: clean all $(BUILD) switch test

#---------------------------------------------------------------------------------
all: $(BUILD)

$(BUILD):
	@echo build ...
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).pfs0 $(TARGET).nso $(TARGET).nro $(TARGET).nacp $(TARGET).elf

switch:
	@echo build ...
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

test:
	@echo $(DEVKITPRO)
	@echo `freetype-config --libs`


#---------------------------------------------------------------------------------
else
.PHONY:	all

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
all	:	$(OUTPUT).pfs0 $(OUTPUT).nro

$(OUTPUT).pfs0	:	$(OUTPUT).nso

$(OUTPUT).nso	:	$(OUTPUT).elf

ifeq ($(strip $(NO_NACP)),)
$(OUTPUT).nro	:	$(OUTPUT).elf $(OUTPUT).nacp
else
$(OUTPUT).nro	:	$(OUTPUT).elf
endif

$(OUTPUT).elf	:	$(OFILES)

#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
	@echo $(notdir $<)
	@$(bin2o)

%.ttc.o :	%.ttc
	@echo $(notdir $<)
	@$(bin2o)

%.ttf.o :	%.ttf
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
