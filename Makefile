bin/main: src/main.c src/info.c src/about.c
	mkdir -p bin/
	cc -o bin/main    \
		-Wall -Wextra \
		src/main.c src/info.c src/about.c \
	    -lncurses

clear:
	rm bin/main
