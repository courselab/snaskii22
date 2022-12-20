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


#include <string.h>
#include <sys/time.h>

#include "times.h"


#define MICRO_RATIO 1000000


static void subtract_time(struct timeval* minuend, struct timeval* subtrahend, struct timeval* result)
{
	// Perform the carry for the later subtraction by updating subtrahend
	if (minuend->tv_usec < subtrahend->tv_usec)
	{
		int seconds = (subtrahend->tv_usec - minuend->tv_usec) / MICRO_RATIO + 1;
		subtrahend->tv_usec -= MICRO_RATIO * seconds;
		subtrahend->tv_sec += seconds;
	}
	if (minuend->tv_usec - subtrahend->tv_usec > MICRO_RATIO)
	{
		int seconds = (minuend->tv_usec - subtrahend->tv_usec) / MICRO_RATIO;
		subtrahend->tv_usec += MICRO_RATIO * seconds;
		subtrahend->tv_sec -= seconds;
	}

	// Compute the time remaining to wait. tv_usec is certainly positive
	result->tv_sec = minuend->tv_sec - subtrahend->tv_sec;
	result->tv_usec = minuend->tv_usec - subtrahend->tv_usec;
}


void init_times(times_t* times)
{
	gettimeofday(&times->start, NULL);
	memcpy(&times->now, &times->start, sizeof(struct timeval));
}

void update_times(times_t* times)
{
	memcpy(&times->last_frame, &times->now, sizeof(struct timeval));
	gettimeofday(&times->now, NULL);

	subtract_time(&times->now, &times->start, &times->elapsed_start);
	subtract_time(&times->now, &times->last_frame, &times->elapsed_last_frame);
}


double get_fps(const times_t* times) {
    return 1.0 / (times->elapsed_last_frame.tv_sec + times->elapsed_last_frame.tv_usec * 1E-6);
}