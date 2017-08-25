DOCKER := docker run --user $(shell id -u) --rm -v $(CURDIR):/tmp -w /tmp brownout
CXX=$(DOCKER) m68k-ataribrowner-elf-g++
OBJDUMP=$(DOCKER) m68k-ataribrowner-elf-objdump
INC=-Iinclude

all: build/main.o

build:
	mkdir -p "$@"

build/main.o: src/main.cpp build
	$(CXX) $(INC) -std=c++1z -O3 -c "$<" -o "$@"
	$(OBJDUMP) -d "$@"

.PHONY: all
