SRCS := $(wildcard ./src/*.c)

bin/main: $(SRCS) 
	mkdir -p bin/
	cc -o bin/main    \
		-Wall -Wextra \
		$(SRCS) \
	    -lncurses

clear:
	rm bin/main
