CFLAGS=-Wall -g
src=$(shell ls *.c)
programs=$(src:.c=)
debug_info := $(patsubst %,%.dSYM,$(programs))

all: $(programs)

checkpoint:
	git add *.c
	git add .gitignore Makefile
	git commit -m "$(shell date +%Y%m%d%H%M%S)"

clean:
	rm -f $(programs)
	rm -rf $(debug_info)
