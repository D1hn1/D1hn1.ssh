#include <ncurses.h>
#include "../include/info.h"

// Info buffer vars
#define TITLE_HEIGHT 8
#define CONTACT_HEIGHT 5
#define PROJECTS_HEIGHT 13
#define PRO_PROFILE_HEIGHT 7
#define TECHNOLOGIES_HEIGHT 6

const char *TITLE[TITLE_HEIGHT] = {
	"mmmmm        mm     mm    mm  mmm   mm  mmmmmm",
	"##   ##     ####    ##    ##  ###   ##    ##  ",
	"##    ##    ####    ##    ##  ## #  ##    ##  ",
	"##    ##   ##  ##   ########  ## ## ##    ##  ",
	"##    ##   ######   ##    ##  ##  #m##    ##  ",
	"##mmm##   m##  ##m  ##    ##  ##   ###  mm##mm",
	"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*",
	"==============================================",
};

const char *PRO_PROFILE[PRO_PROFILE_HEIGHT] = {
	"PROFESIONAL PROFILE",
	"",
	"Software developer with experience, good",
	"capabilities to resolve problems as well as to learn",
	"new things. Proactive, with adaptability for team work",
	"and open to learn new things about other fields",
	"about computer science.",
};

const char *TECHNOLOGIES[TECHNOLOGIES_HEIGHT] = {
	"TECHNOLOGIES",
	"",
	"Python  MySQL       Docker      MongoDB",
	"C       PostgreSQL  Java        HTML",
	"C++     Windows     SpringBoot  CSS",
	"Bash    Git         NodeJS      JavaScript",
};

const char *CONTACT[CONTACT_HEIGHT] = {
	"LINKS",
	"",
	"https://github.com/d1hn1",
	"https://www.linkedin.com/in/dahnils",
	"https://www.credly.com/users/dahnils",
};

const char *PROJECTS[PROJECTS_HEIGHT] = {
	"PROJECTS",
	"",
	"FEB 26 - * This same 'page' made",
	"XXX 26   | in C with ncurses.",
	"         |",
	"         |",
	"JAN 26 - * Tiny gravity simulation",
	"FEB 26   | in C with Raylib.",
	"         |",
	"         |",
	"JAN 25 - * Proxy made in Java which",
	"APR 25   | handles HTTP & HTTPS traffic.",
	"         +",
};

void draw_bold(WINDOW *win, const char *text) {
	wattron(win, A_BOLD);
	wprintw(win, "%s", text);
	wattroff(win, A_BOLD);
}

void draw_text(WINDOW *win, size_t height, int y, int x, const char *text[], bool bold) {
	for (size_t i = 0; i < height; i++) {
		wmove(win, y + i, x);
		if (bold && i == 0) {
			draw_bold(win, text[i]);
			continue;
		}
		wprintw(win, "%s", text[i]);
	}
}

void buffer_info(WINDOW *win) {
	draw_text(win, TITLE_HEIGHT, 1, 2, TITLE, false);
	draw_text(win, PRO_PROFILE_HEIGHT, TITLE_HEIGHT + 2, 2, PRO_PROFILE, true);
	draw_text(win, TECHNOLOGIES_HEIGHT, TITLE_HEIGHT + PRO_PROFILE_HEIGHT + 3, 2, TECHNOLOGIES, true);
	draw_text(win, CONTACT_HEIGHT, 2, 60, CONTACT, true);
	draw_text(win, PROJECTS_HEIGHT, TITLE_HEIGHT + 2, 60, PROJECTS, true);
}
