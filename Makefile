bin/main: src/main.c src/info.c src/about.c src/loading.c
	mkdir -p bin/
	cc -o bin/main    \
		-Wall -Wextra \
		src/main.c src/info.c src/about.c src/loading.c \
	    -lncurses

clear:
	rm bin/main
