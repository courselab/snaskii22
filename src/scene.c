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


#include <stdio.h>
#include <string.h>

#include "scene.h"
#include "times.h"
#include "utils.h"
#include "graphics.h"


#define FILE_NAME_SIZE 1024


void clear_scenes(scene_t scenes[], int size)
{
	memset(scenes, BLANK, size * SCREEN_ROWS * SCREEN_COLUMNS * sizeof(char));
}

void load_scenes(scene_t scenes[], int size, const char* path, const char* directory)
{
	for (int scene = 0; scene < size; scene++)
	{
		char file_name[FILE_NAME_SIZE];
		sprintf(file_name, "%s/%s/scene-%07d.txt", path, directory, scene + 1);

		FILE* file = fopen(file_name, "r");
		sysfatal(!file);

		for (int i = 0; i < SCREEN_ROWS; i++)
		{
			for (int j = 0; j < SCREEN_COLUMNS; j++)
			{
				/*
					Actual ascii text file may be smaller than SCENE_ROWS x SCENE_COLUMNS
					If we read something out of the 32-127 ascii range, consider a BLANK instead
				*/

				char sprite = fgetc(file);
				scenes[scene][i][j] = (sprite >= ' ' && sprite <= '~') ? sprite : BLANK;
			}


			// Discard the rest of the line if longer than SCENE_COLUMNS

			char ignore;
			while ((ignore = fgetc(file)) != '\n' && ignore != EOF);
		}

		fclose(file);
	}
}

void draw_menu(const times_t* times)
{
	double fps = 1.0 / (times->elapsed_last_frame.tv_sec + times->elapsed_last_frame.tv_usec * 1E-6);
	screen_print("Elapsed: %5ds, fps = %5.2f\n", (int)times->elapsed_start.tv_sec, fps);

	screen_print("Movement:             Commands:\n");
  screen_print("      W - Up                R - Restart\n");
  screen_print("      A - Left              Q - Quit\n");
  screen_print("      S - Down\n");
  screen_print("      D - Right\n");
	// TODO: Controls menu display
}
