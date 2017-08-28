PROGRAM=out/makeadf
OBJS=out/makeadf.o

all: $(PROGRAM)

dirs:
	mkdir -p $(CURDIR)/out

./out/%.o: %.c dirs
	$(CC) -c "$<" -o "$@"

$(PROGRAM): $(OBJS)
	$(CC) -lc "$^" -o "$@"

.PHONY: all
