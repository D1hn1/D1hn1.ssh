#include <string.h>
#include <ncurses.h>
#include "../include/loading.h"

int  LOADING_TIME = 150;
char LOADING_TEXT[] = "Hello, World!";

void load_anim(WINDOW *win) {
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	wclear(win);

	int y = LINES / 2;
	int text_size = strlen(LOADING_TEXT); // 13
	char subtext[text_size];

	for (int i = 0; i <= text_size; i++) {
		// Move to center
		wmove(win, y, (COLS / 2) - (text_size / 2));
		// Print text
		strncpy(subtext, LOADING_TEXT, i + 1);
		subtext[i + 1] = '\0';
		wprintw(win, "%s", subtext);
		// Cursor
		wmove(win, y, (COLS/2) - (text_size / 2) + i);
		addch(' ' | A_REVERSE);
		// Refresh window
		wrefresh(win);
		napms(LOADING_TIME);
	}

	napms(LOADING_TIME + 150);
	wclear(win);
}
