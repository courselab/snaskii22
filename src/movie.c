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
#include <stdbool.h>

#include "movie.h"
#include "scene.h"
#include "graphics.h"


static bool playing_movie = true;


void play_movie(scene_t *scenes, int movie_scenes_size, int movie_delay, bool loop)
{
	playing_movie = true;
	int scene = 0;

	struct timespec request;
	request.tv_sec = 0;

	int i = 0;
	while(playing_movie)
	{
		if(!loop && i >= movie_scenes_size){
			break;
		}

		// Draw the current movie frame
		draw_background((char**)scenes[scene]);
		screen_show();

		scene = (scene + 1) % movie_scenes_size;

		// Wait until the next frame
		request.tv_nsec = movie_delay * 1e3;
		nanosleep(&request, NULL);
		
		i++;
	}
}

void skip_movie()
{
	playing_movie = false;
}
