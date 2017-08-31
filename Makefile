DOCKER   := docker run --user $(shell id -u) --rm -v $(CURDIR):/tmp -w /tmp brownout
CXX      := $(DOCKER) m68k-ataribrowner-elf-g++ -Ttext=0
CC       := $(DOCKER) m68k-ataribrowner-elf-gcc -Ttext=0
LD       := $(DOCKER) m68k-ataribrowner-elf-ld
OBJDUMP  := $(DOCKER) m68k-ataribrowner-elf-objdump
VAS      := $(DOCKER) vasmm68k_mot
AS       := $(DOCKER) m68k-ataribrowner-elf-as
HUNKTOOL := $(DOCKER) hunktool
CXXFLAGS := -std=c++1z -Os -mpcrel
CFLAGS   := -Os -mpcrel
VASFLAGS := -Felf -pic
ASFLAGS  :=
LDFLAGS  := --gc-sections -static -T memory.ld -eentry
CPU      := -m68000
LIBPATHS := -L/usr/lib/gcc/m68k-ataribrowner-elf/7.1.0/m68000 -L/usr/m68k-ataribrowner-elf/lib/m68000
INC      := -Iinclude -Icmap/include

OBJECTS := \
	$(patsubst src/%.cpp,out/%.o,$(wildcard src/*.cpp)) \
	$(patsubst src/%.s,out/%.s.o,$(wildcard src/*.s))   \
	$(patsubst src/%.S,out/%.S.o,$(wildcard src/*.S))   \
	$(patsubst src/%.c,out/%.c.o,$(wildcard src/*.c))

all: out/hunk

out:
	mkdir -p "$@"

out/%.s.o: src/%.s out
	$(AS) $(ASFLAGS) $(CPU) "$<" -o "$@"

out/%.S.o: src/%.S out
	$(VAS) $(VASFLAGS) $(CPU) "$<" -o "$@"

out/%.c.o: src/%.c out
	$(CC) $(CFLAGS) $(INC) $(CPU) -c "$<" -o "$@"

out/%.o: src/%.cpp out
	$(CXX) $(CXXFLAGS) $(INC) $(CPU) -c "$<" -o "$@"

out/elf: $(OBJECTS)
	$(LD) $(LIBPATHS) $(LDFLAGS) -o "$@" $^


out/hunk: out/elf
	$(OBJDUMP) -D "$<"
	scripts/ploink "$<" "$@"
	$(HUNKTOOL) info "$@" || true

.PHONY: all
