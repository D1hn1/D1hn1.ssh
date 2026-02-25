#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "../include/game.h"

#define DARRAY_IMPLEMENTATION
#include "../include/darray.h"

typedef struct {
	int x;
	int y;
	int xv;
	int yv;

	int prevx;
	int prevy;
} snake_part;

typedef struct {
	int x;
	int y;
} snake_food;

// Bools
bool SETUP = true;
bool RESUME = true;

// Controls
bool UP    = false;
bool DOWN  = false;
bool LEFT  = false;
bool RIGHT = false;

// Snake vars
char SNAKE_HEAD = '#';
char SNAKE_BODY = '%';
char SNAKE_FOOD = '$';

// Define array
darray array;
snake_food food;
const char *RESUME_TEXT = "Press B to begin";

void random_food(darray *array, snake_food *food, int WIDTH, int HEIGHT) {
	int x = rand() % (WIDTH);
	int y = rand() % (HEIGHT);
	for (size_t i = 0; i < array->length; i++) {
		snake_part *actual_sp = darray_at(array, i);
		bool collision = (actual_sp->x == x && actual_sp->y == y) ||
						 (x <= 0) || (x >= (WIDTH - 1))  ||
						 (y <= 0) || (y >= (HEIGHT - 1));
		if (collision) {
			random_food(array, food, WIDTH, HEIGHT);
			return;
		}
	}
	food->x = x;
	food->y = y;
}

void update_head(snake_part *actual_sp) {
	if (UP) { 
		UP = false;
		if (actual_sp->yv == 0) {
			actual_sp->yv = -1;
			actual_sp->xv = 0;
		}
	}
	if (DOWN) {
		DOWN = false;
		if (actual_sp->yv == 0) {
			actual_sp->yv = 1;
			actual_sp->xv = 0;
		}
	}
	if (LEFT) {
		LEFT = false;
		if (actual_sp->xv == 0) {
			actual_sp->xv = -1;
			actual_sp->yv = 0;
		}
	}
	if (RIGHT) {
		RIGHT = false;
		if (actual_sp->xv == 0) {
			actual_sp->xv = 1;
			actual_sp->yv = 0;
		}
	}
}

void update_body(darray *array, snake_part *actual, int i) {
	if (i > 0) {
		snake_part *prev = (snake_part *)darray_at(array, (i - 1));
		actual->x = prev->prevx;
		actual->y = prev->prevy;
	}
}

void draw_snake(WINDOW *win, snake_part *actual_sp, bool is_head) {
	wmove(win, actual_sp->y, actual_sp->x);
	if (is_head) {
		wprintw(win, "%c", SNAKE_HEAD);
		return;
	}
	wprintw(win, "%c", SNAKE_BODY);
}

void draw_food(WINDOW *win, snake_food food) {
	wmove(win, food.y, food.x);
	wprintw(win, "%c", SNAKE_FOOD);
}

void apply_direction(snake_part *actual_sp) {
	actual_sp->prevx = actual_sp->x;
	actual_sp->prevy = actual_sp->y;

	actual_sp->x += actual_sp->xv;
	actual_sp->y += actual_sp->yv;
}

void check_eaten(darray *array, snake_food *food, snake_part *head, int width, int height) {
	if ((food->x == head->x) && (food->y == head->y)) {

		snake_part *body = malloc(sizeof(snake_part));
		*body = (snake_part){
			.x = head->x,
			.y = head->y,
			.xv = head->xv,
			.yv = head->yv,
		};
		darray_push(array, body);

		random_food(array, food, width, height); // Create food after to not interfer with new body
	}
}

void check_collisions(darray *array, snake_part *head, int HEIGHT, int WIDTH) {
	// Check walls
	bool outside = (head->x >= (WIDTH - 1)) ||
				   (head->x <= 0)           ||
				   (head->y >= (HEIGHT - 1))||
				   (head->y <= 0);
	if (outside) {
		SETUP = true;
		RESUME = true;
		return;
	}
	// Check head in body
	if (array->length > 1) {
		for (size_t i = 1; i < array->length; i++) {
			snake_part *body = darray_at(array, i);
			bool collision = (head->x == body->prevx) &&
							 (head->y == body->prevy);
			if (collision) {
				SETUP = true;
				RESUME = true;
			}
		}
	}
}

void buffer_game(WINDOW *win) {
	
	int HEIGHT, WIDTH;
	getmaxyx(win, HEIGHT, WIDTH);
	
	// Single run code to setup things
	if (SETUP) {

		SETUP = false;
		// Random seed
		srand(time(NULL));
		// Destroy if reset
		darray_destroy(&array);
		array = darray_init();
		// Create snake head
		snake_part *head = malloc(sizeof(snake_part));
		*head = (snake_part){
			.x = WIDTH / 2,
			.y = HEIGHT / 2,
			.xv = 0,
			.yv = 0,
		};
		darray_push(&array, head);
		// Create snake food
		food = (snake_food){
			.x = 0,
			.y = 0,
		};
		random_food(&array, &food, WIDTH, HEIGHT);

	}

	// Resume - Running
	if (RESUME) {

		int rtlen = strlen(RESUME_TEXT);
		wmove(win, (HEIGHT / 2), (WIDTH / 2) - (rtlen / 2));
		wprintw(win, "%s", RESUME_TEXT);

	} else {

		werase(win);
		draw_food(win, food);
		for (size_t i = 0; i < array.length; i++) {

			snake_part *actual_sp = (snake_part *)darray_at(&array, i);

			if (i == 0) {
				// Update movement
				update_head(actual_sp);
				apply_direction(actual_sp);
				// Check for food
				check_eaten(&array, &food, actual_sp, WIDTH, HEIGHT);
				check_collisions(&array, actual_sp, HEIGHT, WIDTH);
				draw_snake(win, actual_sp, true);
			} else {
				apply_direction(actual_sp);
				update_body(&array, actual_sp, i);
				draw_snake(win, actual_sp, false);
			}

		}

	}

}
