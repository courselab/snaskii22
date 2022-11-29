/*
	snaskii.c - A very simple ASCII snake game.
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


/*
	We use ncurses library, a CRT screen handling and optimization package.
	It implements wrapper over terminal capabilities and provides handy
	functions to draw characters at arbitrary positions on the screen,
	clear the terminal etc.

	See https://tldp.org/HOWTO/NCURSES-Programming-HOWTO.
*/
#include <ncurses.h>

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


#define GAME_SCENES_SIZE 1
#define GAME_DIRECTORY "game"
#define GAME_DELAY (1e6 / 4) // 4us per frame

#define SNAKE_BODY 'O'
#define SNAKE_BODY_SIZE ROWS * COLUMNS

#define ENERGY_BLOCK '+'
#define INACTIVE_BLOCK -1
#define ENERGY_BLOCKS_SIZE 5

#define USAGE                                \
	"snaskii [options]                 \n\n" \
	"    options:                      \n\n" \
	"    -h         this help message    \n" \
	"    -d <path>  path to data files   \n"

#ifndef DATADIR
	// Remove the undefined DATADIR error, but this should be set with the -D compilation flag
	#define DATADIR "."
#endif


typedef enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}
direction_t;

typedef struct Coord
{
	int x;
	int y;
}
coord_t;

typedef struct Snake
{
	int length;
	coord_t head;
	direction_t direction;
}
snake_t;


// Global variables

bool playing_game = true;
int game_delay = GAME_DELAY;


void quit()
{
	skip_movie();
	playing_game = false;
}


void init_game(snake_t* snake, coord_t energy_blocks[ENERGY_BLOCKS_SIZE])
{
	snake->length = 1;
	snake->direction = RIGHT;

	snake->head.x = 0;
	snake->head.y = 0;

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

		// Draw the current scene frame
		clear();
		draw_scene(scenes[scene]);
		draw_menu(times);
		refresh();

		scene = (scene + 1) % GAME_SCENES_SIZE;

		// Wait until the next frame
		request.tv_nsec = game_delay * 1e3;
		nanosleep(&request, NULL);
	}
}


void* get_inputs()
{
	// TODO: Discuss the possibility of a independent event system
	// TODO: Add snake controls

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
				break;

			case 'q':
				quit();
				break;

			case ' ':
				skip_movie();
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

	while ((option = getopt(argc, argv, "hd:")) != -1)
	{
		switch (option)
		{
			case 'h':
				puts(USAGE);
				exit(EXIT_SUCCESS);

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


	// Ncurses initialization

	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);


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

	snake_t snake;
	times_t times;
	coord_t energy_blocks[ENERGY_BLOCKS_SIZE];

	scene_t game_scenes[GAME_SCENES_SIZE];
	clear_scenes(game_scenes, GAME_SCENES_SIZE);
	load_scenes(game_scenes, GAME_SCENES_SIZE, data_path, GAME_DIRECTORY);

	init_times(&times);
	init_game(&snake, energy_blocks);

	play_game(game_scenes, &times);


	// Cleanup and exit

	endwin();
	free(data_path);

	pthread_cancel(pthread);
	pthread_join(pthread, NULL);

	return EXIT_SUCCESS;
}
