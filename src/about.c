#include <ncurses.h>
#include "../include/about.h"

#define ABOUT_HEIGHT 3

const char *ABOUT_TEXT[ABOUT_HEIGHT] = {
	"  Ncurses page made in C for ssh",
	"D1hn1 <tobedefinedlater@gmail.com>",
	"   2026(C). All rights reserved.",
};

void buffer_about(WINDOW *win) {
	int HEIGHT, WIDTH;
	getmaxyx(win, HEIGHT, WIDTH);
	for (size_t i = 0; i < ABOUT_HEIGHT; i++) {
		wmove(win, (HEIGHT / 2) - 1 + i, (WIDTH / 2) - 19);
		wprintw(win, "%s", ABOUT_TEXT[i]);
	}
}
