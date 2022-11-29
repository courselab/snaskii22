/*
	movie.h - Intro movie animation functions.
	Copyright (c) 2021 - Monaco F. J. <monaco@usp.br>

	This file is part of Snaskii

	Snaskii is free software: you can redistribute it and/or modify
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


#ifndef MOVIE_H
#define MOVIE_H


#include "scene.h"


#define MOVIE_SCENES_SIZE 485
#define MOVIE_DIRECTORY "intro"


// Play the intro movie animation
void play_movie(scene_t scenes[MOVIE_SCENES_SIZE]);

// Skip the intro movie animation
void skip_movie();


#endif // MOVIE_H
