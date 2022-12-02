// SPDX-License-Identifier: GPL-3.0-only
/**
 * Copyright (c) 2022 - CCOS ICMC-USP
 */

/* POSIX C libraries. */

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/* Autoconf tests. */

#include <config.h>

/* We use ncurses library, a CRT screen handling and optimization package.
   It implements wrapper over terminal capabilities and provides handy
   functions to draw characters at arbitrary positions on the screen,
   clear the terminal etc.

   See https://tldp.org/HOWTO/NCURSES-Programming-HOWTO.

*/

#include <ncurses.h>

/* This header contains some handy functions. */

#include "utils.h"

/* Game defaults */

#define N_INTRO_SCENES 485 /* Number of frames of the intro animation.*/
#define N_GAME_SCENES 1    /* Number of frames of the gamepay scnene. */

#define MAX_DELAY 999999 /* Maximum possible delay. */

#define NCOLS 90 /* Number of columns of the scene. */
#define NROWS 40 /* Number of rows of the scene. */

#define BLANK ' ' /* Blank-screen character. */

#define BUFFSIZE 1024 /* Generic, auxilary buffer size. */
#define SCENE_DIR_INTRO                                                     \
    "intro"                   /* Directory with the intro animation scenes. \
                               */
#define SCENE_DIR_GAME "game" /* Directory with the game animation scene. */

#define SNAKE_BODY "O"   /* Character to draw the snake. */
#define ENERGY_BLOCK "+" /* Character to draw the energy block. */

#define MAX_ENERGY_BLOCKS 5 /* Maximum number of energy blocks. */

/* Global variables.*/

struct timeval beginning, /* Time when game started. */
    now,                  /* Time now. */
    before,               /* Time in the last frame. */
    elapsed_last,         /* Elapsed time since last frame. */
    elapsed_total;        /* Elapsed time since game baginning. */

int movie_delay; /* How long between move scenes scenes. */
int game_delay;  /* How long between game scenes. */
int go_on;       /* Whether to continue or to exit main loop.*/

/* SIGINT handler.

   This function is called asynchronously when the user press Ctr-C.  */

void quit() { go_on = 0; /* Sentinel controlling the main loop.*/ }

/* The snake data structrue. */

typedef enum { up, right, left, down } direction_t;

typedef struct snake_st snake_t;

struct snake_st {
    struct {
        int x;             /* Coordinate x of the snake's head. */
        int y;             /* Coordinate y of the snake's head. */
    } head;                /* The snake's head. */
    int length;            /* The snake length (including head). */
    direction_t direction; /* Moviment direction. */
};

snake_t snake; /* The snake instance. */

/* Energy blocks. */

struct {
    int x;                         /* Coordinate x of the energy block. */
    int y;                         /* Coordinate y of the energy block. */
} energy_block[MAX_ENERGY_BLOCKS]; /* Array of energy blocks. */

/* Clear the scene vector.

   The scene vector is an array of nscenes scenes. Each scene is a matrix of
   (NROWS x NCOLS) chars, representing and image in ASCII.
*/

void clearscene(char scene[][NROWS][NCOLS], int nscenes) {
    int i, j, k;

    /* Fill the ncenes matrixes with blanks. */

    for (k = 0; k < nscenes; k++)
        for (i = 0; i < NROWS; i++)
            for (j = 0; j < NCOLS; j++) scene[k][i][j] = BLANK;
}

/* Load nscenes scenes from path/dir into the scene vector. */

void readscenes(char *path, char *dir, char scene[][NROWS][NCOLS],
                int nscenes) {
    int i, j, k;
    FILE *file;
    char scenefile[1024], c;

    /* Read nscenes. */

    i = 0;
    for (k = 0; k < nscenes; k++) {
        sprintf(scenefile, "%s/%s/scene-%07d.txt", path, dir, k + 1);

        file = fopen(scenefile, "r");
        sysfatal(!file);

        /* Iterate through NROWS. */

        for (i = 0; i < NROWS; i++) {
            /* For each row read NCOLS columns.*/

            for (j = 0; j < NCOLS; j++) {
                /* Actual ascii text file may be smaller than NROWS x NCOLS.
                   If we read something out of the 32-127 ascii range,
                   consider a blank instead (e.g. get rid of trailing \n)*/

                c = (char)fgetc(file);
                scene[k][i][j] = ((c >= ' ') && (c <= '~')) ? c : BLANK;
            }

            /* Discard the rest of the line (if longer than NCOLS). */

            while (((c = fgetc(file)) != '\n') && (c != EOF))
                ;
        }

        fclose(file);
    }
}

/* Draw the given scene on the screen. The function iterates through the
   scene matrix outputting character by character.

   Note: the implementation make repeated calls to putchar(). Are there
   more efficient alternatives ? */

void draw(char scene[][NROWS][NCOLS], int number) {
    int i, j;
    for (i = 0; i < NROWS; i++) {
        for (j = 0; j < NCOLS; j++) {
            putchar(scene[number][i][j]);
        }
        putchar('\n');
        putchar('\r');
    }
}

/* Draw scene indexed by number, get some statics and repeat.
   If menu is true, draw the game controls.*/

void showscene(char scene[][NROWS][NCOLS], int number, int menu) {
    double fps;

    /* Draw the scene. */

    draw(scene, number);

    memcpy(&before, &now, sizeof(struct timeval));
    gettimeofday(&now, NULL);

    timeval_subtract(&elapsed_last, &now, &before);

    timeval_subtract(&elapsed_total, &now, &beginning);

    fps = 1 / (elapsed_last.tv_sec + (elapsed_last.tv_usec * 1E-6));

    if (menu) {
        printf("Elapsed: %5ds, fps=%5.2f\r\n", /* CR-LF because of ncurses. */
               (int)elapsed_total.tv_sec, fps);
        printf("Controls: \r\n");
    }
}

/* Instantiate the snake and a set of energy blocks. */

#define BLOCK_INACTIVE -1;

void init_game() {
    int i;

    snake.head.x = 0;
    snake.head.y = 0;
    snake.direction = right;
    snake.length = 1;

    for (i = 0; i < MAX_ENERGY_BLOCKS; i++) {
        energy_block[i].x = BLOCK_INACTIVE;
        energy_block[i].y = BLOCK_INACTIVE;
    }
}

/* This functions advances the game: it computes the next state
   and updates the scene vector. This is the game logic. */

void advance(char scene[][NROWS][NCOLS]) {
    scene[0][0][0] += 0; /* Does nothing, for now. */
}

/* This function plays the game introduction animation. */

void playmovie(char scene[N_INTRO_SCENES][NROWS][NCOLS]) {
    int k = 0, i;
    struct timespec how_long;
    how_long.tv_sec = 0;

    for (i = 0; (i < N_INTRO_SCENES) && (go_on); i++) {
        clear();                              /* Clear screen.    */
        refresh();                            /* Refresh screen.  */
        showscene(scene, k, 0);               /* Show k-th scene .*/
        k = (k + 1) % N_INTRO_SCENES;         /* Circular buffer. */
        how_long.tv_nsec = (movie_delay)*1e3; /* Compute delay. */
        nanosleep(&how_long, NULL);           /* Apply delay. */
    }
}

/* This function implements the gameplay loop. */

void playgame(char scene[N_GAME_SCENES][NROWS][NCOLS]) {
    int k = 0;
    struct timespec how_long;
    how_long.tv_sec = 0;

    /* User may change delay (game speedy) asynchronously. */

    while (go_on) {
        clear();   /* Clear screen. */
        refresh(); /* Refresh screen. */

        advance(scene); /* Advance game.*/

        showscene(scene, k, 1);              /* Show k-th scene. */
        k = (k + 1) % N_GAME_SCENES;         /* Circular buffer. */
        how_long.tv_nsec = (game_delay)*1e3; /* Compute delay. */
        nanosleep(&how_long, NULL);          /* Apply delay. */
    }
}

/* Process user input.
   This function runs in a separate thread. */

void *userinput() {
    int c;
    while (1) {
        c = getchar();
        switch (c) {
            case '+': /* Increase FPS. */
                game_delay = game_delay * (0.9);
                break;
            case '-': /* Decrease FPS. */
                game_delay = game_delay * (1.1);
                if(game_delay > MAX_DELAY) game_delay = MAX_DELAY;
                break;
            case 'q':
                kill(0, SIGINT); /* Quit. */
                break;
            default:
                break;
        }
    }
}

#define USAGE                           \
    "snaskii [options]\n\n"             \
    "   options\n\n"                    \
    "   -h         this help message\n" \
    "   -d <path>  path to data files\n"\
    "   -s         skip intro scene\n"

/* The main function. */

int main(int argc, char **argv) {
    int rs, opt;
    struct sigaction act;
    pthread_t pthread;
    bool skip_intro_scene = false;
    char intro_scene[N_INTRO_SCENES][NROWS][NCOLS];
    char game_scene[N_GAME_SCENES][NROWS][NCOLS];
    char *custom_data_path = DATADIR "/" PACKAGE_TARNAME;

    /* Process command-line options. */

    while ((opt = getopt(argc, argv, "hsd:")) != -1) {
        switch (opt) {
            case 'h':
                printf(USAGE);
                exit(0);
            case 'd':
                custom_data_path = strdup(optarg);
                break;
            case 's':
                skip_intro_scene = true;
                break;
            default:
                fprintf(stderr, USAGE);
                exit(1);
        }
    }

    /* Handle SIGNINT (loop control flag). */

    sigaction(SIGINT, NULL, &act);
    act.sa_handler = quit;
    sigaction(SIGINT, &act, NULL);

    /* Ncurses initialization. */

    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();

    /* Default values. */

    movie_delay = 1E5 / 4; /* Movie frame duration in usec (40usec) */
    game_delay = 1E5 / 3;  /* Game frame duration in usec (30usec) */

    /* Handle game controls in a different thread. */

    rs = pthread_create(&pthread, NULL, userinput, NULL);
    sysfatal(rs);

    /* Play intro. */    
    clearscene(intro_scene, N_INTRO_SCENES);

#define scene_path_intro DATADIR "/" PACKAGE_TARNAME

    readscenes(custom_data_path, "intro", intro_scene, N_INTRO_SCENES);

    go_on = 1; /* User may skip intro (q). */
    if (skip_intro_scene) go_on = 0;

    playmovie(intro_scene);

    /* Play game. */

    clearscene(intro_scene, N_GAME_SCENES);

    readscenes(custom_data_path, "game", game_scene, N_GAME_SCENES);

    go_on = 1;
    gettimeofday(&beginning, NULL);

    init_game();

    playgame(game_scene);

    endwin();

    return EXIT_SUCCESS;
}
