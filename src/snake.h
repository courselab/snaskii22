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

#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "graphics.h"

#define SNAKE_HEAD_UP '^'
#define SNAKE_HEAD_DOWN 'v'
#define SNAKE_HEAD_RIGHT '>'
#define SNAKE_HEAD_LEFT '<'
#define SNAKE_BODY 'O'
#define DEFAULT_SPEED 3

typedef enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}
direction_t;

typedef struct Body {
	struct sprite sp;
	struct Body* next;
	struct Body* prev;
}
body_t;

typedef struct Snake {
	body_t* head;
	body_t* tail;
	int prev_tail_x;
	int prev_tail_y;
	int length;
	bool alive;
	direction_t direction;
    double x_pos, y_pos;
    double speed;
}
snake_t;

void init_snake(snake_t* snake, int head_x, int head_y);
void grow_snake(snake_t* snake);
void move_snake(snake_t* snake, double sync, bool boundless);
void draw_snake(snake_t* snake);

#endif // SNAKE_H
