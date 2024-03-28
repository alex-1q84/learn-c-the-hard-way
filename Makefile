CFLAGS=-Wall -g
src=$(shell ls *.c)
programs=$(src:.c=)
debug_info := $(patsubst %,%.dSYM,$(programs))

all: $(programs)

clean:
	rm -f $(programs)
	rm -rf $(debug_info)
