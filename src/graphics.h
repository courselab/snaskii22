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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define SCREEN_ROWS    40
#define SCREEN_COLUMNS 90

#define BLANK ' '

struct sprite {
	int x_pos, y_pos;
	char value;
};

void screen_init();
void screen_clear();
void screen_show();
void screen_end();

void screen_print(char* format, ...);

void draw_death_scene(int score, int elapsed_time, char death_scene[SCREEN_ROWS][SCREEN_COLUMNS]);
void draw_background(char** background);
void draw_sprite(struct sprite* spr);
void put_energy_block(int x, int y);

#endif // GRAPHICS_H
