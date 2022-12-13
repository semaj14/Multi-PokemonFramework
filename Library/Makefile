.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
    $(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/3ds_rules

TARGET      :=  ctrpf
SOURCES     :=  Sources \
                Sources/Framework \
                Sources/CTRPluginFramework \
                Sources/CTRPluginFramework/Graphics \
                Sources/CTRPluginFramework/Menu \
                Sources/CTRPluginFramework/System \
                Sources/CTRPluginFramework/Utils \
                Sources/CTRPluginFrameworkImpl \
                Sources/CTRPluginFrameworkImpl/ActionReplay \
                Sources/CTRPluginFrameworkImpl/Disassembler \
                Sources/CTRPluginFrameworkImpl/Graphics \
                Sources/CTRPluginFrameworkImpl/Graphics/Icons \
                Sources/CTRPluginFrameworkImpl/Menu \
                Sources/CTRPluginFrameworkImpl/Search \
                Sources/CTRPluginFrameworkImpl/System \
                Sources/CTRPluginFrameworkImpl/System/Services \
                Sources/ctrulibExtension \
                Sources/ctrulibExtension/allocator \
                Sources/ctrulibExtension/gpu \
                Sources/ctrulibExtension/services \
                Sources/ctrulibExtension/system \
                Sources/ctrulibExtension/util/utf \
                Sources/ctrulibExtension/util/rbtree \
                Sources/lodepng

INCLUDES    :=  Includes \
                ../Includes

#---------------------------------------------------------------------------------
# Options for code generation
#---------------------------------------------------------------------------------

ARCH    := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft
DEFINES := -DCTRPF_VERSION_MAJOR="\"$(CTRPF_VERSION_MAJOR)\"" -DCTRPF_VERSION_MINOR="\"$(CTRPF_VERSION_MINOR)\"" \
           -DCTRPF_VERSION_BUILD="\"$(CTRPF_VERSION_BUILD)\"" -DCOMMIT_HASH="\"$(COMMIT)\"" -DCOMPILE_DATE="\"$(COMPILE_DATE)\""

GCC11_FALSEPOSITIVES := -Wno-array-bounds -Wno-stringop-overflow -Wno-stringop-overread

CFLAGS   := -Wall -Werror -Wno-psabi -mword-relocations \
            -ffunction-sections \
            -fdata-sections \
            $(GCC11_FALSEPOSITIVES) \
            $(ARCH) \
            $(BUILD_CFLAGS) $(G)

CFLAGS   += $(INCLUDE) -D__3DS__ $(DEFINES)
CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
ASFLAGS  := $(G) $(ARCH) $(INCLUDE) -Os -Wl,$(WL)--gc-sections

#---------------------------------------------------------------------------------
# List of directories containing libraries, this must be the top level containing include and lib
#---------------------------------------------------------------------------------

LIBS    := -lctru -lm -lcwav -lncsnd
LIBDIRS := $(CTRULIB) $(CURDIR)/libcwav $(CURDIR)/libcwav/libncsnd

#---------------------------------------------------------------------------------
# No real need to edit anything past this point unless you need to add additional rules for different file extensions
#---------------------------------------------------------------------------------

ifneq ($(BUILD), $(notdir $(CURDIR)))

#---------------------------------------------------------------------------------

export VPATH := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
                $(foreach dir,$(DATA),$(CURDIR)/$(dir))

CFILES       := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES     := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES       := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------

ifeq ($(strip $(CPPFILES)),)
    export LD := $(CC)

else
    export LD := $(CXX)

endif

#---------------------------------------------------------------------------------

export OFILES_BIN := #$(addsuffix .o,$(BINFILES))
export OFILES_SRC := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export HFILES_BIN := $(addsuffix .h,$(subst .,_,$(BINFILES)))

export OFILES     := $(OFILES_BIN) $(OFILES_SRC)

export INCLUDE    := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
                     $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                     -I.

.PHONY: clean all

#---------------------------------------------------------------------------------

all: lib/libctrpf.a

lib:
	@[ -d $@ ] || mkdir -p $@

Release:
	@[ -d $@ ] || mkdir -p $@

lib/libctrpf.a : SHELL := /bin/bash
lib/libctrpf.a : lib Release
	@$(MAKE) BUILD=Release OUTPUT=$(CURDIR)/$@ WL=--strip-discarded,--strip-debug, \
	BUILD_CFLAGS="-DNDEBUG=1 -Os -fomit-frame-pointer" DEPSDIR=$(CURDIR)/Release \
	--no-print-directory -C Release	-f $(CURDIR)/Makefile
	@rm Release/PluginMenuTools.o

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr release debug lib docs

#---------------------------------------------------------------------------------
else

DEPENDS := $(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# Main targets
#---------------------------------------------------------------------------------

$(OUTPUT)     : $(OFILES)
$(OFILES_SRC) : $(HFILES_BIN)

#---------------------------------------------------------------------------------
%.bin.o    %_bin.h :    %.bin
#---------------------------------------------------------------------------------

	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif