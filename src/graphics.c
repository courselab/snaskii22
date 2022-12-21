/*
	Copyright (c) 2022 - CCOS ICMC-USP

	This file is part of Snaskii22.
	Snaskii22 is based on Snaskii, available at
	https://github.com/courselab/snaskii.

	Snaskii22 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
	We use ncurses library, a CRT screen handling and optimization package.
	It implements wrapper over terminal capabilities and provides handy
	functions to draw characters at arbitrary positions on the screen,
	clear the terminal etc.

	See https://tldp.org/HOWTO/NCURSES-Programming-HOWTO.
*/
#include <ncurses.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "graphics.h"

// ! lines and columns need to reflect position of %d in sprites
#define DEATH_SCORE_LINE 12
#define DEATH_SCORE_COLUMN 60
#define DEATH_TIME_LINE 13
#define DEATH_TIME_COLUMN 70
#defube WIN_TIME_LINE 28
#define WIN_TIME_COLUMN 52
#define NUM_MAX_SIZE 5

static char screen_buffers[2][SCREEN_ROWS][SCREEN_COLUMNS];
static size_t curr_buffer_show = 0;

// Ncurses initialization.
void screen_init() {
	initscr();
	noecho();
	curs_set(FALSE);
	cbreak();

	memset(screen_buffers, ' ', sizeof(screen_buffers));
}

void screen_end() {
	endwin();
}

void draw_death_scene(int score, int elapsed_seconds, char death_scene[SCREEN_ROWS][SCREEN_COLUMNS]) {
	char original[2][SCREEN_COLUMNS];
	memcpy(original[0], death_scene[DEATH_SCORE_LINE], SCREEN_COLUMNS);
	memcpy(original[1], death_scene[DEATH_TIME_LINE], SCREEN_COLUMNS);

	int i, mod;
	int val = score;
	for (i = DEATH_SCORE_COLUMN; i < SCREEN_COLUMNS - 2 && val; i++) {
		mod = val % 10; val = val / 10;
		death_scene[DEATH_SCORE_LINE][i] = mod + '0';
	}

	val = elapsed_seconds;
	for (i = DEATH_TIME_COLUMN; i < SCREEN_COLUMNS - 3 && val; i++) {
		mod = val % 10; val = val / 10;
		death_scene[DEATH_TIME_LINE][i] = mod + '0';
	}
	death_scene[DEATH_TIME_LINE][i + (i == DEATH_TIME_COLUMN)] = 's';

	draw_background((char **)death_scene);

	memcpy(death_scene[DEATH_SCORE_LINE], original[0], SCREEN_COLUMNS);
	memcpy(death_scene[DEATH_TIME_LINE], original[1], SCREEN_COLUMNS);
}


void draw_win_scene(int elapsed_seconds, char scene[SCREEN_ROWS][SCREEN_COLUMNS]) {
    char original[SCREEN_COLUMNS];
    memcpy(original, scene[WIN_SCORE_LINE], SCREEN_COLUMNS);

    int i, mod;
    for (i = DEATH_TIME_COLUMN; i < SCREEN_COLUMNS - 3 && val; i++) {
        mod = val % 10; val = val / 10;
        scene[DEATH_TIME_LINE][i] = mod + '0';
    }
    scene[WIN_TIME_LINE][i + (i == WIN_TIME_COLUMN)] = 's';

    draw_background((char **)death_scene);
    memcpy(scene[WIN_TIME_LINE], original, SCREEN_COLUMNS);
}


void draw_sprite(struct sprite* spr) {
	screen_buffers[!curr_buffer_show][spr->y_pos][spr->x_pos] = spr->value;
}

void draw_background(char** background) {
	memcpy(screen_buffers[!curr_buffer_show], background, SCREEN_ROWS * SCREEN_COLUMNS);
}

void screen_show() {
	refresh();
	for (int y = 0; y < SCREEN_ROWS; y++) {
		for (int x = 0; x < SCREEN_COLUMNS; x++) {
			mvaddch(y, x, screen_buffers[curr_buffer_show][y][x]);
		}
	}
	addch('\n');

	curr_buffer_show = !curr_buffer_show;
}

// TODO: Make screen_print() just store in a local buffer and make screen_show() print this buffer.
// This would be cool to make screen_print() callable in any order and not after an scree_show().
void screen_print(char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vw_printw(stdscr, fmt, args);
	va_end(args);
}

void screen_clear() {
	memset(screen_buffers[!curr_buffer_show], BLANK, SCREEN_ROWS * SCREEN_COLUMNS);
}
