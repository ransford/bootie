TARGET=bootloader

include Makefile.common

FWDIR ?= firmwares
FIRMWARES ?= $(wildcard $(FWDIR)/*.c)
FWNAMES=$(notdir $(basename $(FIRMWARES)))
FWRENAMED=$(FIRMWARES:.c=-main-renamed.o)

.DUMMY: all clean

all: $(TARGET)

$(TARGET).c: $(TARGET).c.tmpl scripts/genbootloader.pl
	< $< perl scripts/genbootloader.pl $(FWNAMES) > $@

$(TARGET).bc: $(FWRENAMED) $(TARGET).o
	llvm-link -o $@ $^

$(TARGET): $(TARGET).bc
	$(LLC) -o $@.s $<
	$(MCC) $(MCFLAGS) -o $@ $@.s $(MCLIBS)

clean:
	$(RM) $(FWDIR)/*.o \
		$(TARGET) $(TARGET).bc $(TARGET).s $(TARGET).o $(TARGET).c
