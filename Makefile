DOCKER   := docker run --user $(shell id -u) --rm -v $(CURDIR):/tmp -w /tmp brownout
CXX      := $(DOCKER) m68k-ataribrowner-elf-g++ -Ttext=0
CC       := $(DOCKER) m68k-ataribrowner-elf-gcc -Ttext=0
LD       := $(DOCKER) m68k-ataribrowner-elf-ld
OBJDUMP  := $(DOCKER) m68k-ataribrowner-elf-objdump
AS       := $(DOCKER) vasmm68k_mot
HUNKTOOL := $(DOCKER) hunktool
CXXFLAGS := -std=c++1z -Os -mpcrel
CFLAGS   := -Os -mpcrel
LDFLAGS  := --gc-sections -static -T memory.ld -emain
CPU      := -m68000
LIBPATHS := -L/lib/gcc/m68k-ataribrown-elf/6.2.0/m68000 -L/usr/m68k-ataribrowner-elf/lib/m68000
INC      := -Iinclude -Icmap/include

OBJECTS := $(patsubst src/%.cpp,out/%.o,$(wildcard src/*.cpp))

#$(patsubst src/%.s,out/%.s.o,$(wildcard src/*.s))
#$(patsubst src/%.c,out/%.c.o,$(wildcard src/*.c))

all: out/hunk

out:
	mkdir -p "$@"

out/%.s.o: src/%.s out
	$(AS) $(ASFLAGS) $(CPU) "$<" -o "$@"

out/%.c.o: src/%.c out
	$(CC) $(CFLAGS) $(INC) $(CPU) -c "$<" -o "$@"

out/%.o: src/%.cpp out
	$(CXX) $(CXXFLAGS) $(INC) $(CPU) -c "$<" -o "$@"

out/elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(LIBPATHS) -o "$@" $^


out/hunk: out/elf
	$(OBJDUMP) -D "$<"
	scripts/ploink "$<" "$@"
	$(HUNKTOOL) info "$@" || true

.PHONY: all
