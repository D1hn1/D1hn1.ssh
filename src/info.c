#include <ncurses.h>
#include "../include/info.h"

// Info buffer vars
#define TITLE_HEIGHT 8
#define CONTACT_HEIGHT 4
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
	"CONTACT",
	"",
	"https://www.linkedin.com/in/dahnils",
	"https://github.com/d1hn1",
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

void buffer_info(WINDOW *win) {
	// Draw title
	for (size_t i = 0; i < TITLE_HEIGHT; i++) {
		wmove(win, i + 1, 2);
		wprintw(win, "%s", TITLE[i]);
	}
	// Draw profesional profile
	for (size_t i = 0; i < PRO_PROFILE_HEIGHT; i++) {
		wmove(win, TITLE_HEIGHT + i + 2, 2);
		if (i == 0) {
			draw_bold(win, PRO_PROFILE[i]);
			continue;
		}
		wprintw(win, "%s", PRO_PROFILE[i]);
	}
	// Draw technologies
	for (size_t i = 0; i < TECHNOLOGIES_HEIGHT; i++) {
		wmove(win, TITLE_HEIGHT + PRO_PROFILE_HEIGHT + 3 + i, 2);
		if (i == 0) {
			draw_bold(win, TECHNOLOGIES[i]);
			continue;
		}
		wprintw(win, "%s", TECHNOLOGIES[i]);
	}
	// Draw contact
	for (size_t i = 0; i < CONTACT_HEIGHT; i++) {
		wmove(win, 2 + i, 60);
		if (i == 0) {
			draw_bold(win, CONTACT[i]);
			continue;
		}
		wprintw(win, "%s", CONTACT[i]);
	}
	// Draw projects
	for (size_t i = 0; i < PROJECTS_HEIGHT; i++) {
		wmove(win, TITLE_HEIGHT + i + 2, 60);
		if (i == 0) {
			draw_bold(win, PROJECTS[i]);
			continue;
		}
		wprintw(win, "%s", PROJECTS[i]);
	}
}
