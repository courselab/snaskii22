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
#include <ncurses.h>

#include "movie.h"
#include "scene.h"
#include "times.h"
#include "utils.h"
#include "graphics.h"
#include "snake.h"

#define MAX_DELAY 999999
#define MIN_DELAY 10
#define CHANGE_DELAY 2

#define GAME_SCENES_SIZE 1
#define DEATH_SCENE_SIZE 1
#define MENU_SCENES_SIZE 2
#define GAME_DIRECTORY "game"
#define DEATH_DIRECTORY "death"
#define MENU_DIRECTORY "menu"
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

#define KEYS "wsda"

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
bool requested_restart = false;
int game_delay = GAME_DELAY;
snake_t snake;
times_t times;
coord_t energy_blocks[ENERGY_BLOCKS_SIZE];
int game_score;


void quit()
{
	skip_movie();
	playing_game = false;
}


void init_game()
{
	init_times(&times);
  
	init_snake(&snake, SCREEN_COLUMNS/2, SCREEN_ROWS/2);
  
	memset(energy_blocks, INACTIVE_BLOCK, ENERGY_BLOCKS_SIZE * sizeof(coord_t));
}


int detect_collision(coord_t target[], int max_targets) {

    for (int i = 0; i < max_targets; i++) {

        if (target[i].x == snake.head->sp.x_pos && target[i].y == snake.head->sp.y_pos) {
            // Return the index of the collided target
            return i;
        }
    }

    return -1;
}


void tick_step()
{
    /*
     * Contains all methods to perform physics, movement and calculations to be executed before
     * rendering the screen.
     * For example: updating the screen time, as well as calculating the snakes position
     */
    update_times(&times);

    // Sync variable calculation, for normalizing the snake's speed to the current FPS.
    double sync = (double) MIN_DELAY / get_fps(&times);

    move_snake(&snake, sync);

    int energy_target = detect_collision(energy_blocks, ENERGY_BLOCKS_SIZE);

    // TODO: When merging with PR #47, deallocate or remove energy block from game context
    if (energy_target != -1) {
        game_score++;
        // delete_energy(energy_target);
    }
}


void render(scene_t scene)
{
    /*
     * Renders a specific screen scene, as well as the menu and the current moving snake.
     * Can be used within any game loop, and with any dynamic scene.
     * Does not update any values, and should be only be run if both the snake and the scene
     * have been initialized previously.
     */
    draw_background((char**) scene);
    draw_snake(&snake);
    screen_show();
    draw_menu(&times);
}


void play_game(scene_t scenes[GAME_SCENES_SIZE], scene_t death_scene)
{
	int scene = 0;

	struct timespec request;
	request.tv_sec = 0;

	while (playing_game)
	{
		if (!snake.alive) 
		{
			draw_death_scene(game_score, (int)times.elapsed_start.tv_sec, death_scene);
			screen_show();


		} else {
            // If snake is alive, execute main game loop body
            // Contains code for calling the physics calculations, as well as
            // rendering gameplay elements (scene, snake and menu)
			tick_step();
            render(scenes[scene]);

			scene = (scene + 1) % GAME_SCENES_SIZE;
		}

        if (requested_restart) {
            init_game();
            requested_restart = false;
            game_score = 0;

        }

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

		if(input == '\033'){
			getch();
			input = KEYS[getch() - 65];
		}

		switch (input)
		{
			case '+': // Increase FPS
				game_delay = game_delay * (0.9);
				break;

			case '-': // Decrease FPS
                game_delay = game_delay * (1.1);
				if (game_delay > MAX_DELAY) game_delay = MAX_DELAY;
				break;

			case 'q':
				quit();
				break;

			case ' ':
				skip_movie();
				break;

			case 'r':
				requested_restart = true;
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

	play_movie((scene_t *)movie_scenes, MOVIE_SCENES_SIZE, MOVIE_DELAY, false);


	// Main Menu Wait 

	scene_t menu_scene[MENU_SCENES_SIZE];
	clear_scenes(menu_scene, MENU_SCENES_SIZE);
	load_scenes(menu_scene, MENU_SCENES_SIZE, data_path, MENU_DIRECTORY);

	play_movie((scene_t *)menu_scene, MENU_SCENES_SIZE, MENU_DELAY, true);


	// Play game
  
	scene_t game_scenes[GAME_SCENES_SIZE];

	clear_scenes(game_scenes, GAME_SCENES_SIZE);
	load_scenes(game_scenes, GAME_SCENES_SIZE, data_path, GAME_DIRECTORY);

	scene_t death_scene;
	clear_scenes(&death_scene, DEATH_SCENE_SIZE);
	load_scenes(&death_scene, DEATH_SCENE_SIZE, data_path, DEATH_DIRECTORY);


	init_game();
	play_game(game_scenes, death_scene);


	// Cleanup and exit
	screen_end();
	free(data_path);

	pthread_cancel(pthread);
	pthread_join(pthread, NULL);

	return EXIT_SUCCESS;
}
