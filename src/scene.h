/**
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
**/


#ifndef SCENE_H
#define SCENE_H


#include "times.h"


#define SCENE_ROWS    40
#define SCENE_COLUMNS 90

#define BLANK ' '


typedef char scene_t[SCENE_ROWS][SCENE_COLUMNS];


// Set every character in every scene to BLANK
void clear_scenes(scene_t scenes[], int size);

// Load the scenes from path/directory to the array
void load_scenes(scene_t scenes[], int size, const char* path, const char* directory);

// Draw the scene matrix in the console
void draw_scene(const scene_t scene);

// Draw the menu with fps and controls information
void draw_menu(const times_t* times);


#endif // SCENE_H
