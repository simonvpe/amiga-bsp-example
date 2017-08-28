DOCKER   := docker run --user $(shell id -u) --rm -v $(CURDIR):/tmp -w /tmp brownout
CXX      := $(DOCKER) m68k-ataribrowner-elf-g++ -Ttext=0
LD       := $(DOCKER) m68k-ataribrowner-elf-ld
OBJDUMP  := $(DOCKER) m68k-ataribrowner-elf-objdump
AS       := $(DOCKER) vasmm68k_mot
HUNKTOOL := $(DOCKER) hunktool
CXXFLAGS := -std=c++1z -Os
LDLAGS   := --gc-sections --emit-relocs -e__start
CPU      := -m68000
LIBPATHS := -L/lib/gcc/m68k-ataribrown-elf/6.2.0/m68000 -L/usr/m68k-ataribrowner-elf/lib/m68000
INC      := -Iinclude


all: out/hunk

out:
	mkdir -p "$@"

out/%.s.o: src/%.s out
	$(AS) $(ASFLAGS) "$<" -o "$@"

out/%.o: src/%.cpp out
	$(CXX) $(CXXFLAGS) $(INC) $(CPU) -c "$<" -o "$@"

out/elf: $(patsubst src/%.cpp,out/%.o,$(wildcard src/*.cpp)) $(patsubst src/%.s,out/%.s.o,$(wildcard src/*.s))
	$(LD) $(LDFLAGS) $(LIBPATHS) -static -o "$@" -T memory.ld $^

out/hunk: out/elf
	scripts/ploink "$<" "$@"
	$(OBJDUMP) -D "$<"
	$(HUNKTOOL) info "$@" || true

.PHONY: all
