/*
	times.h - Struct to group time information and functions to manipulate it.
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


#ifndef TIMES_H
#define TIMES_H


#include <sys/time.h>


typedef struct Times
{
	struct timeval now;
	struct timeval start;
	struct timeval last_frame;
	struct timeval elapsed_start;
	struct timeval elapsed_last_frame;
}
times_t;


// Init the time information with current time
void init_times(times_t* times);

// Update the time information stored
void update_times(times_t* times);


#endif // TIMES_H
