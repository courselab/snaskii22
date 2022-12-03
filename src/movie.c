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


#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>

#include "movie.h"
#include "scene.h"


#define MOVIE_DELAY (1e5 / 4) // 40us per frame

static bool playing_movie = true;


void play_movie(scene_t scenes[MOVIE_SCENES_SIZE])
{
	int scene = 0;

	struct timespec request;
	request.tv_sec = 0;

	for (int i = 0; i < MOVIE_SCENES_SIZE && playing_movie; i++)
	{
		// Draw the current movie frame
		clear();
		draw_scene(scenes[scene]);
		refresh();

		scene = (scene + 1) % MOVIE_SCENES_SIZE;

		// Wait until the next frame
		request.tv_nsec = MOVIE_DELAY * 1e3;
		nanosleep(&request, NULL);
	}
}

void skip_movie()
{
	playing_movie = false;
}
