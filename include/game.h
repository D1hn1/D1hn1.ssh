#include <ncurses.h>

#ifndef WIN_GAME_H
#define WIN_GAME_H

extern bool SETUP;
extern bool RESUME;
extern bool UP, DOWN, LEFT, RIGHT;
void buffer_game(WINDOW *win);

#endif // WIN_GAME_H
