#include <stdio.h>
#include <ncurses.h>
#include "../include/info.h"
#include "../include/game.h"
#include "../include/about.h"
#include "../include/loading.h"

enum {
	WIN_INFO,
	WIN_SNAKE,
	WIN_ABOUT,
} WIN_TYPE; 

int WINDOW_NUM = 0;
int WINDOW_MAX = 2;
bool RUNNING   = true;

#define PAGER "<- %d/%d ->"
#define DOMAIN "dahni.local"
#define CONTROLS "^c (exit) h (left) l (right) b (begin) wasd (snake controls) r (reset)"

void window_switcher(WINDOW *win) {
	switch (WINDOW_NUM) {

		case WIN_INFO:
			wclear(win);
			buffer_info(win);
			break;

		case WIN_SNAKE:
			werase(win);
			buffer_game(win);
			break;

		case WIN_ABOUT:
			wclear(win);
			buffer_about(win);
			break;
		
		default:
			break;
	}
}

void handle_input(int input) {
	switch (input) {

		case 'h':
			if (WINDOW_NUM != 0) {
				WINDOW_NUM--;
			}
			RESUME = true;
			break;

		case 'l':
			if (WINDOW_NUM != WINDOW_MAX) {
				WINDOW_NUM++;
			}
			RESUME = true;
			break;

		// Game inputs
		case 'b':
			RESUME = false;
			break;
		case 'w':
			UP = true;
			break;
		case 'a':
			LEFT = true;
			break;
		case 's':
			DOWN = true;
			break;
		case 'd':
			RIGHT = true;
			break;
		case 'r':
			SETUP = true;
			break;
		// Game inputs

		case KEY_EXIT:
			RUNNING = false;
			break;

		default:
			break;
	}
} 

int main(void) {
	// Init main window 
	WINDOW *root = initscr();
	curs_set(0);
	noecho();
	cbreak();
	
	// Init variables
	int WIN_WIDTH  = 104;
	int WIN_HEIGHT = 26;
	int WIN_X 	   = (COLS / 2)  - (WIN_WIDTH / 2);
	int WIN_Y	   = (LINES / 2) - (WIN_HEIGHT / 2);

	// Loading screen
	load_anim(root);

	// Draw decorations
	wmove(root, LINES - 1, 0);
	wprintw(root, CONTROLS);
	wmove(root, WIN_Y - 1, WIN_X + 1);
	wprintw(root, DOMAIN);

	// Init second window
	WINDOW *win = newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);
	
	while (RUNNING) {
		// Window switcher
		window_switcher(win);

		// Draw borders
		wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);

		// Update pager
		wmove(root, (LINES / 2) + (WIN_HEIGHT / 2), (COLS / 2) - 6);
		wprintw(root, PAGER, WINDOW_NUM + 1, WINDOW_MAX + 1);	

		// Refresh windows
		refresh();
		wrefresh(win);
		
		// Handle input
		timeout(-1);
		if (WINDOW_NUM == WIN_SNAKE)
			timeout(150);
		int input = getch();
		handle_input(input);
	}

	// End windows
	endwin();
	return 0;

}
