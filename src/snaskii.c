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

// Autoconf tests
#include <config.h>

#include <time.h>
#include <stdio.h>
#include <getopt.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

#include "movie.h"
#include "scene.h"
#include "times.h"
#include "utils.h"
#include "graphics.h"
#include "snake.h"

#define MAX_DELAY 999999

#define GAME_SCENES_SIZE 1
#define GAME_DIRECTORY "game"
#define GAME_DELAY (1e5 / 3) // 30us per frame

#define ENERGY_BLOCK '+'
#define INACTIVE_BLOCK -1
#define ENERGY_BLOCKS_SIZE 5

#define USAGE                                \
	"snaskii [options]                 \n\n" \
	"    options:                      \n\n" \
	"    -h         this help message    \n" \
	"    -d <path>  path to data files   \n" \
	"    -s         skip intro scene     \n"

#ifndef DATADIR
	// Remove the undefined DATADIR error, but this should be set with the -D compilation flag
	#define DATADIR "."
#endif

typedef struct Coord
{
	int x;
	int y;
}
coord_t;

// Global variables

bool playing_game = true;
int game_delay = GAME_DELAY;
snake_t snake;


void quit()
{
	skip_movie();
	playing_game = false;
}


void init_game(snake_t* snake, coord_t energy_blocks[ENERGY_BLOCKS_SIZE])
{
	init_snake(snake, SCREEN_COLUMNS/2, SCREEN_ROWS/2);
	memset(energy_blocks, INACTIVE_BLOCK, ENERGY_BLOCKS_SIZE * sizeof(coord_t));
}

void play_game(scene_t scenes[GAME_SCENES_SIZE], times_t* times)
{
	int scene = 0;

	struct timespec request;
	request.tv_sec = 0;

	while (playing_game)
	{
		update_times(times);

		// TODO: Advance game
		move_snake(&snake);

		// Draw the current scene frame
		draw_background((char**)scenes[scene]);
		draw_snake(&snake);
		screen_show();

		draw_menu(times);

		scene = (scene + 1) % GAME_SCENES_SIZE;

		// Wait until the next frame
		request.tv_nsec = game_delay * 1e3;
		nanosleep(&request, NULL);
	}
}


void* get_inputs()
{
	// TODO: Discuss the possibility of a independent event system

	while (playing_game)
	{
		int input = getch();

		switch (input)
		{
			case '+': // Increase FPS
				game_delay = game_delay * (0.9);
				break;

			case '-': // Decrease FPS
				game_delay = game_delay * (1.1);
				if(game_delay > MAX_DELAY) game_delay = MAX_DELAY;
				break;

			case 'q':
				quit();
				break;

			case ' ':
				skip_movie();
				break;

			case 'w':
				if(snake.direction != DOWN) snake.direction = UP;
				break;

			case 's':
				if(snake.direction != UP) snake.direction = DOWN;
				break;

			case 'a':
				if(snake.direction != RIGHT) snake.direction = LEFT;
				break;

			case 'd':
				if(snake.direction != LEFT) snake.direction = RIGHT;
				break;
		}
	}

	return NULL;
}


int main(int argc, char** argv)
{
	char* data_path = malloc((strlen(DATADIR) + strlen(PACKAGE_TARNAME) + 2) * sizeof(char));
	sprintf(data_path, "%s/%s", DATADIR, PACKAGE_TARNAME);


	// Process command-line options

	int option;

	while ((option = getopt(argc, argv, "hsd:")) != -1)
	{
		switch (option)
		{
			case 'h':
				puts(USAGE);
				exit(EXIT_SUCCESS);

			case 's':
				skip_movie();
				break;

			case 'd':
				data_path = strdup(optarg);
				break;

			default:
				fputs(USAGE, stderr);
				exit(EXIT_FAILURE);
		}
	}


	// Handle SIGINT (Ctrl + C) to quit

	struct sigaction action;
	sigaction(SIGINT, NULL, &action);

	action.sa_handler = quit;
	sigaction(SIGINT, &action, NULL);


	screen_init();

	// Handle game controls in a different thread

	pthread_t pthread;

	int error = pthread_create(&pthread, NULL, get_inputs, NULL);
	sysfatal(error);


	// Play movie

	scene_t movie_scenes[MOVIE_SCENES_SIZE];
	clear_scenes(movie_scenes, MOVIE_SCENES_SIZE);
	load_scenes(movie_scenes, MOVIE_SCENES_SIZE, data_path, MOVIE_DIRECTORY);

	play_movie(movie_scenes);


	// Play game

	times_t times;
	coord_t energy_blocks[ENERGY_BLOCKS_SIZE];

	scene_t game_scenes[GAME_SCENES_SIZE];
	clear_scenes(game_scenes, GAME_SCENES_SIZE);
	load_scenes(game_scenes, GAME_SCENES_SIZE, data_path, GAME_DIRECTORY);

	init_times(&times);
	init_game(&snake, energy_blocks);

	play_game(game_scenes, &times);


	// Cleanup and exit

	screen_end();
	free(data_path);

	pthread_cancel(pthread);
	pthread_join(pthread, NULL);

	return EXIT_SUCCESS;
}
