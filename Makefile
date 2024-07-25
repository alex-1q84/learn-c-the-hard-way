CFLAGS=-Wall -g
src=$(shell ls *.c)
programs=$(src:.c=)
debug_info := $(patsubst %,%.dSYM,$(programs))

.PHONY: all update_gitignore checkpoint clean

all: $(programs)

update_gitignore:
	racket update-gitignore.rkt

checkpoint: update_gitignore
	git add *.rkt
	git add *.c *.h
	git add .gitignore Makefile
	git commit -m "$(shell date +%Y%m%d%H%M%S)"

clean:
	rm -f $(programs)
	rm -rf $(debug_info)
