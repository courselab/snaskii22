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

#ifndef UTILS_H
#define UTILS_H


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Report a system error and exit
#define sysfatal(expression)																\
	if ((expression))																		\
	{																						\
		fprintf(stderr, "%s: %d: %s: %s\n", __FILE__, __LINE__, __func__, strerror(errno));	\
		exit(EXIT_FAILURE);																	\
	}


#endif // UTILS_H
