
ifeq (${PROJECTROOT},)
    export PROJECTROOT := $(shell /bin/pwd)
endif

ifeq (${GLOBAL_BUILDROOT},)
    export GLOBAL_BUILDROOT=$(shell /bin/pwd)/build
endif

ifeq ($(TARGET),)
    $(error "TARGET not set!")
endif

export GLOBAL_TARGET_BUILDROOT=$(GLOBAL_BUILDROOT)/$(TARGET)

all: makedirs $(GLOBAL_TARGET_BUILDROOT)/$(TARGET).bin

TARGETROOT=$(PROJECTROOT)/targets/$(TARGET)
BUILDROOT=$(GLOBAL_TARGET_BUILDROOT)

export BUILDRULES=$(PROJECTROOT)/platform/$(PLATFORM)/Makefile.build

include $(TARGETROOT)/Makefile

#release flag overwrites debug flag
ifeq (${RELEASE},)
	export RELEASE=0
	export DEBUG=1
	CFLAGS+=-DDEBUG
else
	export DEBUG=0
	CFLAGS+=-DRELEASE
endif
# CFLAGS+=-DMOS_VERSION_COMMIT_COUNT=\""$(shell git rev-list --count HEAD | tr -d '\n')\""
# CFLAGS+=-DMOS_VERSION_COMMIT_SHA=\""$(shell git rev-parse HEAD | tr -d '\n')\""
# CFLAGS+=-DMOS_VERSION_BRANCH=\""$(shell git branch | grep "*" | tr -s ' ' | cut -d ' ' -f2 | tr -d '\n')\""


LINKER_SCRIPT ?= $(PROJECTROOT)/core/linkerScript.ld

ifeq ($(PLATFORM),)
    $(error "TARGET does not specify a PLATFORM!")
endif

MODULE_LIBS=$(foreach m,$(MODULES),$(GLOBAL_TARGET_BUILDROOT)/modules/$(m)/$(m).a)
CFLAGS+=-I$(PROJECTROOT)/targets/$(TARGET)/include -I$(PROJECTROOT)/platform/$(PLATFORM)/include $(foreach m,$(MODULES),-I$(PROJECTROOT)/modules/$(m)/include)

$(GLOBAL_TARGET_BUILDROOT)/$(TARGET).bin: $(GLOBAL_TARGET_BUILDROOT)/$(TARGET).elf
	$(OBJCOPY) -Obinary $< $@

$(GLOBAL_TARGET_BUILDROOT)/$(TARGET).elf: $(GLOBAL_TARGET_BUILDROOT)/$(TARGET).a $(GLOBAL_TARGET_BUILDROOT)/platform/$(PLATFORM)/$(PLATFORM).a $(MODULE_LIBS)
	$(CC) $(LDFLAGS) $^ $(LINKER_SCRIPT) -o $@

$(GLOBAL_TARGET_BUILDROOT)/modules/%.a: FORCE
	mkdir -p $(GLOBAL_TARGET_BUILDROOT)/modules/$(notdir $*)
	make -C $(PROJECTROOT)/modules/$(notdir $*) MODULEROOT=$(PROJECTROOT)/modules/$(notdir $*) BUILDROOT=$(GLOBAL_TARGET_BUILDROOT)/modules/$(notdir $*) MODULE=$(notdir $*) PLATFORM=$(PLATFORM)

$(GLOBAL_TARGET_BUILDROOT)/platform/$(PLATFORM)/$(PLATFORM).a: FORCE
	mkdir -p $(GLOBAL_TARGET_BUILDROOT)/platform/$(PLATFORM)
	make -C $(PROJECTROOT)/platform/$(PLATFORM) PLATFORMROOT=$(PROJECTROOT)/platform/$(PLATFORM) BUILDROOT=$(GLOBAL_TARGET_BUILDROOT)/platform/$(PLATFORM) PLATFORM=$(PLATFORM)

FORCE: ;

makedirs:
	mkdir -p $(GLOBAL_TARGET_BUILDROOT)

clean:
	rm -rf $(GLOBAL_TARGET_BUILDROOT)
