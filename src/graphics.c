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
