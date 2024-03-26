CFLAGS=-Wall -g
programs=ex1 ex3 bitwise ex7 ex10 ex11

all: $(programs)

clean:
	rm -f $(programs)
