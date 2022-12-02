/* snaskii.c - A very simple ASCII snake game.

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

#ifndef DEFINES_H
#define DEFINES_H
/* Game defaults */

#define N_INTRO_SCENES 485 /* Number of frames of the intro animation.*/
#define N_GAME_SCENES 1    /* Number of frames of the gamepay scnene. */

#define MAX_DELAY 999999 /* Maximum possible delay. */

#define NCOLS 90 /* Number of columns of the scene. */
#define NROWS 40 /* Number of rows of the scene. */

#define BLANK ' ' /* Blank-screen character. */

#define BUFFSIZE 1024           /* Generic, auxilary buffer size. */
#define SCENE_DIR_INTRO "intro" /* Path to the intro animation scenes. */
#define SCENE_DIR_GAME "game"   /* Path to the game animation scene. */

#define SNAKE_BODY "O"   /* Character to draw the snake. */
#define ENERGY_BLOCK "+" /* Character to draw the energy block. */

#define MAX_ENERGY_BLOCKS 5 /* Maximum number of energy blocks. */

#endif
